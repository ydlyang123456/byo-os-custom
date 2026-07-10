SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()
# Add bombardier declaration and function
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, 
    "static void cmd_bombardier306(int argc, char args[][CMD_MAX_LEN]);\n" + decl_marker)
# Add bombardier function before shell_run
func_marker = "void shell_run(void) {"
bombardier_func = """static void cmd_bombardier306(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Bombardier: HTTP benchmarking\\n");
}
"""
content = content.replace(func_marker, bombardier_func + func_marker, 1)
with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)
print("Fixed bombardier")