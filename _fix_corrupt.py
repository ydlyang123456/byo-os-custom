#!/usr/bin/env python3
"""Clean up corrupted entries in shell.c"""
import re

with open("kernel/shell.c", "r", encoding="utf-8", errors="replace") as f:
    lines = f.readlines()

print(f"Original lines: {len(lines)}")

# Find all lines with non-ASCII characters
bad_lines = []
for i, line in enumerate(lines):
    # Check for non-ASCII in command name strings or function names
    if re.search(r'\{".*[\x80-\xff].*"', line) or re.search(r'void\s+\w*[\x80-\xff]\w*\(', line):
        bad_lines.append(i)

print(f"Found {len(bad_lines)} corrupted lines")

# Show them
for idx in bad_lines[:10]:
    print(f"  Line {idx+1}: {lines[idx][:100]}...")

# Also find forward declarations with non-ASCII
fwd_bad = []
for i, line in enumerate(lines):
    if re.search(r'static void \w*[\x80-\xff]\w*\(', line):
        fwd_bad.append(i)

print(f"\nFound {len(fwd_bad)} corrupted forward declarations")
for idx in fwd_bad[:10]:
    print(f"  Line {idx+1}: {lines[idx][:100]}...")

# Now remove corrupted entries
# Strategy: remove lines that contain non-ASCII in command table entries
# and their corresponding forward declarations and function implementations

# Collect all bad command names to remove
bad_names = set()
for idx in bad_lines + fwd_bad:
    # Extract the corrupted name
    m = re.search(r'"([^"]*[\x80-\xff][^"]*)"', lines[idx])
    if m:
        bad_names.add(m.group(1))
    m = re.search(r'void\s+(\w*[\x80-\xff]\w*)\(', lines[idx])
    if m:
        bad_names.add(m.group(1))

print(f"\nBad names to remove: {len(bad_names)}")
for n in list(bad_names)[:10]:
    print(f"  {n}")

# Remove lines containing any bad name
cleaned = []
removed = 0
for i, line in enumerate(lines):
    should_remove = False
    for name in bad_names:
        if name in line:
            should_remove = True
            break
    # Also check for lines that are just corrupted
    if re.search(r'[\x80-\xff]{3,}', line) and ('{' in line or 'void' in line):
        should_remove = True
    
    if should_remove:
        removed += 1
    else:
        cleaned.append(line)

print(f"Removed {removed} corrupted lines")
print(f"Remaining lines: {len(cleaned)}")

# Write back
with open("kernel/shell.c", "w", encoding="utf-8", newline="\n") as f:
    f.writelines(cleaned)

print("Done!")