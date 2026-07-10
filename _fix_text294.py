# fix_text294.py
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# Fix the entry to match the declaration
content = content.replace(
    '{"text-generation-inference", cmd_text294_generation_inference}',
    '{"text-generation-inference", cmd_text294_gen}'
)

# Also fix the function definition to match
content = content.replace(
    'static void cmd_text294_generation_inference(',
    'static void cmd_text294_gen('
)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)
print("Fixed text294 names")