#!/usr/bin/env python3
"""Comprehensive cleanup of shell.c - remove ALL corrupted entries"""
import re, sys, io

# Fix encoding for Windows
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')

with open("kernel/shell.c", "rb") as f:
    raw = f.read()

text = raw.decode("utf-8", errors="replace")
lines = text.split("\n")
print(f"Total lines: {len(lines)}")

# Find ALL lines with non-ASCII characters in code
bad_lines = set()
for i, line in enumerate(lines):
    has_non_ascii = any(ord(c) > 127 for c in line)
    if not has_non_ascii:
        continue
    stripped = line.strip()
    if stripped.startswith("//") or stripped.startswith("/*") or stripped.startswith("*"):
        continue
    bad_lines.add(i)

print(f"Found {len(bad_lines)} corrupted code lines")

# Remove corrupted lines
cleaned = []
for i, line in enumerate(lines):
    if i not in bad_lines:
        cleaned.append(line)

print(f"Removed {len(bad_lines)} lines, remaining: {len(cleaned)}")

# Fix broken table entries (entries with empty command names like {",")
fixed = []
for line in cleaned:
    stripped = line.strip()
    if stripped.startswith('{",') or stripped.startswith('{"",'):
        continue
    fixed.append(line)

print(f"After table fix: {len(fixed)} lines")

with open("kernel/shell.c", "w", encoding="utf-8", newline="\n") as f:
    f.write("\n".join(fixed))

print("Done!")