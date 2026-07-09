#!/usr/bin/env python3
"""Inject Batch 84-86 into shell.c"""
import re

with open("kernel/shell.c", "r", encoding="utf-8", errors="ignore") as f:
    shell = f.read()

with open("batch84_funcs.c", "r", encoding="utf-8", errors="ignore") as f:
    all_code = f.read()

fwd_lines = []
for line in all_code.split("\n"):
    if line.strip().startswith("static void cmd_"):
        m = re.match(r'(static void cmd_\w+)', line)
        if m:
            fwd_lines.append(f"{m.group(1)}(int argc, char args[][CMD_MAX_LEN]);")
fwd_decl = "\n".join(fwd_lines)

table_entries = []
for line in all_code.split("\n"):
    m = re.match(r'static void (cmd_\w+)\(', line)
    if m:
        cmd_name = m.group(1)
        short = re.sub(r'\d+$', '', cmd_name).replace('cmd_', '')
        table_entries.append(f'    {{"{short}", {cmd_name}}},')
table_code = "\n".join(table_entries)

funcs = []
lines = all_code.split("\n")
i = 0
while i < len(lines):
    line = lines[i]
    if re.match(r'\s*static void cmd_\w+\(int argc', line):
        func_lines = [line]
        depth = line.count('{') - line.count('}')
        i += 1
        while i < len(lines) and depth > 0:
            func_lines.append(lines[i])
            depth += lines[i].count('{') - lines[i].count('}')
            i += 1
        funcs.append("\n".join(func_lines))
    else:
        i += 1

body_code = "\n\n".join(funcs) + "\n\n\n"

all_fwd = [m.start() for m in re.finditer(r'static void cmd_\w+\(int argc, char args\[\]\[CMD_MAX_LEN\]\);', shell)]
if all_fwd:
    last_fwd_pos = all_fwd[-1]
    last_fwd_end = shell.index('\n', last_fwd_pos) + 1
    shell = shell[:last_fwd_end] + fwd_decl + "\n" + shell[last_fwd_end:]
    print(f"Injected {len(fwd_lines)} forward declarations")

all_entries = [m.start() for m in re.finditer(r'\{"[^"]+", cmd_\w+\}', shell)]
if all_entries:
    last_entry_pos = all_entries[-1]
    last_entry_end = shell.index('\n', last_entry_pos) + 1
    shell = shell[:last_entry_end] + table_code + "\n" + shell[last_entry_end:]
    print(f"Injected {len(table_entries)} command table entries")

marker = "void shell_run(void) {"
idx = shell.rfind(marker)
if idx == -1:
    print("ERROR: Cannot find shell_run")
    exit(1)
shell = shell[:idx] + body_code + shell[idx:]
print(f"Injected {len(funcs)} function bodies")

with open("kernel/shell.c", "w", encoding="utf-8") as f:
    f.write(shell)

print("Done!")
