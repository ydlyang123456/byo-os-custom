#!/usr/bin/env python3
"""Inject Batch 60-62 into shell.c"""
import re

# Read files
with open("kernel/shell.c", "r", encoding="utf-8", errors="ignore") as f:
    shell = f.read()
with open("batch60_funcs.c", "r", encoding="utf-8", errors="ignore") as f:
    batch_code = f.read()

# Extract forward declarations
fwd_lines = []
for line in batch_code.split("\n"):
    if line.strip().startswith("static void cmd_"):
        m = re.match(r'(static void cmd_\w+)', line)
        if m:
            fwd_lines.append(f"{m.group(1)}(int argc, char args[][CMD_MAX_LEN]);")
fwd_decl = "\n".join(fwd_lines)

# Extract command table entries
table_entries = []
for line in batch_code.split("\n"):
    m = re.match(r'static void (cmd_\w+)\(', line)
    if m:
        cmd_name = m.group(1)
        # Extract command name from function name (remove batch suffix)
        short = re.sub(r'\d+$', '', cmd_name).replace('cmd_', '')
        table_entries.append(f'    {{"{short}", {cmd_name}}},')
table_code = "\n".join(table_entries)

# Extract function bodies
body_lines = []
in_func = False
brace_depth = 0
current_func = []
for line in batch_code.split("\n"):
    if line.strip().startswith("/* BATCH"):
        continue
    if re.match(r'static void cmd_\w+\(', line):
        in_func = True
        current_func = [line]
        brace_depth = line.count('{') - line.count('}')
        continue
    if in_func:
        current_func.append(line)
        brace_depth += line.count('{') - line.count('}')
        if brace_depth <= 0 and '}' in line:
            body_lines.append("\n".join(current_func))
            in_func = False
            current_func = []

body_code = "\n".join(body_lines)

# 1. Inject forward declarations after last batch's declarations
last_fwd = "static void cmd_gretl59(int argc, char args[][CMD_MAX_LEN]);"
idx1 = shell.rfind(last_fwd)
if idx1 == -1:
    print("ERROR: Cannot find last forward declaration")
    exit(1)
end1 = idx1 + len(last_fwd)
shell = shell[:end1] + "\n" + fwd_decl + "\n" + shell[end1:]
print(f"Injected {len(fwd_lines)} forward declarations")

# 2. Inject command table entries after last entry
last_entry = '    {"gretl", cmd_gretl59},'
idx2 = shell.rfind(last_entry)
if idx2 == -1:
    print("ERROR: Cannot find last command table entry")
    exit(1)
end2 = idx2 + len(last_entry)
shell = shell[:end2] + "\n" + table_code + "\n" + shell[end2:]
print(f"Injected {len(table_entries)} command table entries")

# 3. Inject function bodies before shell_run
shell_run_marker = "void shell_run(void) {"
idx3 = shell.rfind(shell_run_marker)
if idx3 == -1:
    print("ERROR: Cannot find shell_run")
    exit(1)
shell = shell[:idx3] + body_code + "\n\n\n" + shell[idx3:]
print(f"Injected {len(body_lines)} function bodies")

# Write back
with open("kernel/shell.c", "w", encoding="utf-8") as f:
    f.write(shell)

print("Done! shell.c updated.")
