SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# Find the problematic line and fix it
old = 'Type \\"help for help.\\n'
new = 'Type backslash-help for help.\\n'
count = content.count(old)
if count > 0:
    content = content.replace(old, new)
    print(f"Fixed {count} occurrences")
else:
    print("Pattern not found, trying alternative...")
    # Try the raw bytes approach
    old2 = b'Type \\\\"help for help'
    content_bytes = content.encode('utf-8', errors='replace')
    count2 = content_bytes.count(old2)
    if count2 > 0:
        content_bytes = content_bytes.replace(old2, b'Type backslash-help for help')
        content = content_bytes.decode('utf-8', errors='replace')
        print(f"Fixed {count2} occurrences (bytes)")
    else:
        print("Pattern not found at all")

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)