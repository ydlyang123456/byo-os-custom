#!/usr/bin/env python3
"""Fix all corrupted entries using byte-level detection"""
import re

with open("kernel/shell.c", "rb") as f:
    content = f.read()

text = content.decode("utf-8", errors="replace")
lines = text.split("\n")
print(f"Total lines: {len(lines)}")

# Find lines with non-ASCII bytes that look like corrupted code
bad_indices = set()
for i, line in enumerate(lines):
    # Check for non-ASCII characters
    has_bad = False
    for ch in line:
        if ord(ch) > 127:
            has_bad = True
            break
    if has_bad:
        # Check if it's a code line (not a comment)
        stripped = line.strip()
        if stripped.startswith("static void") or stripped.startswith('{"') or "cmd_" in stripped or "vga_puts" in stripped:
            bad_indices.add(i)

print(f"Found {len(bad_indices)} corrupted code lines")
for idx in sorted(bad_indices):
    preview = lines[idx][:80].encode("ascii", errors="replace").decode()
    print(f"  Line {idx+1}: {preview}...")

# Remove all corrupted lines
cleaned = [line for i, line in enumerate(lines) if i not in bad_indices]
print(f"Removed {len(bad_indices)} lines, remaining: {len(cleaned)}")

# Also fix the broken command table entry on line 19204 (0-indexed)
# It has {", which is invalid
fixed = []
for i, line in enumerate(cleaned):
    stripped = line.strip()
    # Remove entries that are just {", or similar broken fragments
    if stripped in ['{",', '{"",', '{",']: 
        continue
    # Remove lines that are just a comma
    if stripped == ',':
        continue
    fixed.append(line)

print(f"After fixing fragments: {len(fixed)} lines")

with open("kernel/shell.c", "w", encoding="utf-8", newline="\n") as f:
    f.write("\n".join(fixed))

print("shell.c cleaned!")