#!/usr/bin/env python3
"""Inject Batch 60-62 function bodies into shell.c"""
import re

with open("kernel/shell.c", "r", encoding="utf-8", errors="ignore") as f:
    shell = f.read()

with open("batch60_funcs.c", "r", encoding="utf-8", errors="ignore") as f:
    code = f.read()

# Extract function bodies using brace counting
funcs = []
lines = code.split("\n")
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

print(f"Found {len(funcs)} function bodies")
if funcs:
    print("First:", funcs[0][:80])
    print("Last:", funcs[-1][:80])

# Inject before shell_run
marker = "void shell_run(void) {"
idx = shell.rfind(marker)
if idx == -1:
    print("ERROR: Cannot find shell_run")
    exit(1)

body_code = "\n\n".join(funcs) + "\n\n\n"
shell = shell[:idx] + body_code + shell[idx:]

with open("kernel/shell.c", "w", encoding="utf-8") as f:
    f.write(shell)

print(f"Injected {len(funcs)} function bodies into shell.c")
