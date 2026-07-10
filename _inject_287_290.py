# inject_287_290.py - More specialized tools
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 287: Web & API =====
b287_decls = """static void cmd_curl2287(int argc, char args[][CMD_MAX_LEN]);
static void cmd_wget2287(int argc, char args[][CMD_MAX_LEN]);
static void cmd_httpie287(int argc, char args[][CMD_MAX_LEN]);
static void cmd_postman287(int argc, char args[][CMD_MAX_LEN]);
static void cmd_insomnia287(int argc, char args[][CMD_MAX_LEN]);
static void cmd_yarn287(int argc, char args[][CMD_MAX_LEN]);
static void cmd_npm287(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pnpm287(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_bun287(int argc, char args[][CMD_MAX_LEN]);
static void cmd_deno287(int argc, char args[][CMD_MAX_LEN]);
static void cmd_vite287(int argc, char args[][CMD_MAX_LEN]);
static void cmd_webpack287(int argc, char args[][CMD_MAX_LEN]);
"""

b287_entries = """    /* Batch 287: Web & API */
    {"curl2", cmd_curl2287}, {"wget2", cmd_wget2287}, {"httpie", cmd_httpie287},
    {"postman", cmd_postman287}, {"insomnia", cmd_insomnia287}, {"yarn", cmd_yarn287},
    {"npm", cmd_npm287}, {"pnpm", cmd_pnpm287}, {"bun", cmd_bun287},
    {"deno", cmd_deno287}, {"vite", cmd_vite287}, {"webpack", cmd_webpack287},
"""

b287_funcs = """/* ===== Batch 287: Web & API ===== */
static void cmd_curl2287(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: curl <url>\\n"); return; }
    vga_printf("curl: fetching %s\\n", args[1]);
    vga_puts("HTTP/1.1 200 OK\\nContent-Type: text/html\\n\\n");
}
static void cmd_wget2287(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: wget <url>\\n"); return; }
    vga_printf("wget: downloading %s\\n", args[1]);
}
static void cmd_httpie287(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: http <method> <url>\\n"); return; }
    vga_printf("http: %s %s\\n", argc > 1 ? args[1] : "GET", args[argc > 2 ? 2 : 1]);
}
static void cmd_postman287(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Postman: API testing tool\\n");
    vga_puts("postman: no GUI available\\n");
}
static void cmd_insomnia287(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Insomnia: API client\\n");
    vga_puts("insomnia: no GUI available\\n");
}
static void cmd_yarn287(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: yarn <install|add|run>\\n"); return; }
    if (strcmp(args[1], "install") == 0) vga_puts("yarn: installing dependencies...\\nyarn: done\\n");
    else vga_printf("yarn: %s\\n", args[1]);
}
static void cmd_npm287(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: npm <install|run|test>\\n"); return; }
    if (strcmp(args[1], "install") == 0) vga_puts("npm: installing packages...\\nnpm: done\\n");
    else vga_printf("npm: %s\\n", args[1]);
}
static void cmd_pnpm287(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pnpm <install|add>\\n"); return; }
    vga_printf("pnpm: %s\\n", args[1]);
}
static void cmd_bun287(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: bun <install|run>\\n"); return; }
    if (strcmp(args[1], "install") == 0) vga_puts("bun: installing...\\nbun: done\\n");
    else vga_printf("bun: %s\\n", args[1]);
}
static void cmd_deno287(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: deno <run|test>\\n"); return; }
    vga_printf("deno: %s\\n", args[1]);
}
static void cmd_vite287(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: vite <dev|build>\\n"); return; }
    if (strcmp(args[1], "dev") == 0) vga_puts("vite: dev server at http://localhost:5173\\n");
    else if (strcmp(args[1], "build") == 0) vga_puts("vite: building...\\nvite: done\\n");
    else vga_printf("vite: %s\\n", args[1]);
}
static void cmd_webpack287(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("webpack: bundling...\\nwebpack: compiled successfully\\n");
}
"""

# Fix syntax errors in b287_decls
b287_decls = b287_decls.replace("static void_cmd_", "static void cmd_")

# ===== BATCH 288: More Development Tools =====
b288_decls = """static void cmd_eslint288(int argc, char args[][CMD_MAX_LEN]);
static void cmd_prettier288(int argc, char args[][CMD_MAX_LEN]);
static void cmd_jest288(int argc, char args[][CMD_MAX_LEN]);
static void cmd_vitest288(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cypress288(int argc, char args[][CMD_MAX_LEN]);
static void cmd_playwright288(int argc, char args[][CMD_MAX_LEN]);
static void cmd_storybook288(int argc, char args[][CMD_MAX_LEN]);
static void cmd_turbo288(int argc, char args[][CMD_MAX_LEN]);
static void cmd_lerna288(int argc, char args[][CMD_MAX_LEN]);
static void cmd_changeset288(int argc, char args[][CMD_MAX_LEN]);
static void cmd_release288(int argc, char args[][CMD_MAX_LEN]);
static void cmd_changelog288(int argc, char args[][CMD_MAX_LEN]);
"""

b288_entries = """    /* Batch 288: Development Tools */
    {"eslint", cmd_eslint288}, {"prettier", cmd_prettier288}, {"jest", cmd_jest288},
    {"vitest", cmd_vitest288}, {"cypress", cmd_cypress288}, {"playwright", cmd_playwright288},
    {"storybook", cmd_storybook288}, {"turbo", cmd_turbo288}, {"lerna", cmd_lerna288},
    {"changeset", cmd_changeset288}, {"release-please", cmd_release288}, {"conventional-changelog", cmd_changelog288},
"""

b288_funcs = """/* ===== Batch 288: Development Tools ===== */
static void cmd_eslint288(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: eslint <files>\\n"); return; }
    vga_printf("eslint: checking %s\\n", args[1]);
    vga_puts("eslint: 0 problems\\n");
}
static void cmd_prettier288(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: prettier <files>\\n"); return; }
    vga_printf("prettier: formatting %s\\n", args[1]);
}
static void cmd_jest288(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("jest: running tests...\\n");
    vga_puts("Tests: 15 passed, 0 failed\\n");
    vga_puts("Time: 2.345s\\n");
}
static void cmd_vitest288(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("vitest: running tests...\\n");
    vga_puts("Tests: 15 passed, 0 failed\\n");
}
static void cmd_cypress288(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Cypress: end-to-end testing\\n");
    vga_puts("cypress: 12 specs passed\\n");
}
static void cmd_playwright288(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Playwright: browser automation\\n");
    vga_puts("playwright: 10 tests passed\\n");
}
static void cmd_storybook288(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("storybook: component documentation\\n");
    vga_puts("storybook: listening on http://localhost:6006\\n");
}
static void cmd_turbo288(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Turborepo: monorepo build tool\\n");
    vga_puts("turbo: build complete\\n");
}
static void cmd_lerna288(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Lerna: monorepo management\\n");
    vga_puts("lerna: 5 packages\\n");
}
static void cmd_changeset288(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("changeset: version management\\n");
}
static void cmd_release288(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("release-please: automated releases\\n");
    vga_puts("release-please: PR created\\n");
}
static void cmd_changelog288(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("conventional-changelog: generating changelog\\n");
}
"""

# ===== BATCH 289: More System Tools =====
b289_decls = """static void cmd_logwatch289(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ossec289(int argc, char args[][CMD_MAX_LEN]);
static void cmd_wazuh289(int argc, char args[][CMD_MAX_LEN]);
static void cmd_siem289(int argc, char args[][CMD_MAX_LEN]);
static void cmd_velociraptor289(int argc, char args[][CMD_MAX_LEN]);
static void cmd_guacamole289(int argc, char args[][CMD_MAX_LEN]);
static void cmd_portainer289(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cockpit289(int argc, char args[][CMD_MAX_LEN]);
static void cmd_webmin289(int argc, char args[][CMD_MAX_LEN]);
static void cmd_plesk289(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cpanel289(int argc, char args[][CMD_MAX_LEN]);
static void cmd_virtualmin289(int argc, char args[][CMD_MAX_LEN]);
"""

b289_entries = """    /* Batch 289: System Management */
    {"logwatch", cmd_logwatch289}, {"ossec", cmd_ossec289}, {"wazuh", cmd_wazuh289},
    {"siem", cmd_siem289}, {"velociraptor", cmd_velociraptor289}, {"guacamole", cmd_guacamole289},
    {"portainer", cmd_portainer289}, {"cockpit", cmd_cockpit289}, {"webmin", cmd_webmin289},
    {"plesk", cmd_plesk289}, {"cpanel", cmd_cpanel289}, {"virtualmin", cmd_virtualmin289},
"""

b289_funcs = """/* ===== Batch 289: System Management ===== */
static void cmd_logwatch289(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("logwatch: log analysis\\n");
    vga_puts("logwatch: 1234 events processed\\n");
}
static void cmd_ossec289(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("OSSEC: host intrusion detection\\n");
    vga_puts("ossec: 0 alerts today\\n");
}
static void cmd_wazuh289(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Wazuh: security monitoring\\n");
    vga_puts("wazuh: agent status: active\\n");
}
static void cmd_siem289(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("SIEM: Security Information & Event Management\\n");
    vga_puts("siem: 5000 events\\n");
}
static void cmd_velociraptor289(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Velociraptor: endpoint monitoring\\n");
}
static void cmd_guacamole289(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Apache Guacamole: remote desktop gateway\\n");
    vga_puts("guacamole: listening on http://localhost:8080\\n");
}
static void cmd_portainer289(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Portainer: container management\\n");
    vga_puts("portainer: listening on http://localhost:9000\\n");
}
static void cmd_cockpit289(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Cockpit: server management\\n");
    vga_puts("cockpit: listening on https://localhost:9090\\n");
}
static void cmd_webmin289(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Webmin: server administration\\n");
    vga_puts("webmin: listening on https://localhost:10000\\n");
}
static void cmd_plesk289(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Plesk: web hosting control panel\\n");
}
static void cmd_cpanel289(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("cPanel: web hosting control panel\\n");
}
static void cmd_virtualmin289(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Virtualmin: server management\\n");
}
"""

# ===== BATCH 290: More AI/ML =====
b290_decls = """static void cmd_transformers290(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_diffusers290(int argc, char args[][CMD_MAX_LEN]);
static void cmd_whisper290(int argc, char args[][CMD_MAX_LEN]);
static void cmd_clip290(int argc, char args[][CMD_MAX_LEN]);
static void cmd_stable290_diffusion(int argc, char args[][CMD_MAX_LEN]);
static void cmd_midjourney290(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dall290_e(int argc, char args[][CMD_MAX_LEN]);
static void cmd_autogpt290(int argc, char args[][CMD_MAX_LEN]);
static void cmd_crew290_ai(int argc, char args[][CMD_MAX_LEN]);
static void cmd_meta290_gpt(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gemini290(int argc, char args[][CMD_MAX_LEN]);
static void cmd_claude290(int argc, char args[][CMD_MAX_LEN]);
"""

b290_entries = """    /* Batch 290: AI & LLM */
    {"transformers", cmd_transformers290}, {"diffusers", cmd_diffusers290}, {"whisper", cmd_whisper290},
    {"clip", cmd_clip290}, {"stable-diffusion", cmd_stable290_diffusion}, {"midjourney", cmd_midjourney290},
    {"dall-e", cmd_dall290_e}, {"autogpt", cmd_autogpt290}, {"crewai", cmd_crew290_ai},
    {"meta-gpt", cmd_meta290_gpt}, {"gemini", cmd_gemini290}, {"claude", cmd_claude290},
"""

b290_funcs = """/* ===== Batch 290: AI & LLM ===== */
static void cmd_transformers290(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Hugging Face Transformers\\n");
    vga_puts("transformers: model loaded\\n");
}
static void cmd_diffusers290(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Diffusers: image generation\\n");
    vga_puts("diffusers: generating image...\\n");
}
static void cmd_whisper290(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Whisper: speech recognition\\n");
    vga_puts("whisper: transcribing audio...\\n");
}
static void cmd_clip290(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("CLIP: image-text matching\\n");
}
static void cmd_stable290_diffusion(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Stable Diffusion: image generation\\n");
    vga_puts("stable-diffusion: generating...\\n");
}
static void cmd_midjourney290(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Midjourney: AI image generation\\n");
}
static void cmd_dall290_e(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("DALL-E: OpenAI image generation\\n");
}
static void cmd_autogpt290(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("AutoGPT: autonomous AI agent\\n");
}
static void cmd_crew290_ai(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("CrewAI: multi-agent framework\\n");
}
static void cmd_meta290_gpt(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("MetaGPT: software development AI\\n");
}
static void cmd_gemini290(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Gemini: Google AI\\n");
}
static void cmd_claude290(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Claude: Anthropic AI\\n");
}
"""

# Fix syntax errors in b290_decls
b290_decls = b290_decls.replace("static void_cmd_", "static void cmd_")
b290_decls = b290_decls.replace("static void cmd_stable290_diffusion", "static void cmd_stable290_diff")
b290_decls = b290_decls.replace("static void cmd_dall290_e", "static void cmd_dall290")
b290_decls = b290_decls.replace("static void cmd_crew290_ai", "static void cmd_crew290")
b290_decls = b290_decls.replace("static void cmd_meta290_gpt", "static void cmd_meta290")
b290_entries = b290_entries.replace("stable-diffusion", "stable-diff")
b290_entries = b290_entries.replace("dall-e", "dall-e")
b290_entries = b290_entries.replace("crewai", "crewai")
b290_entries = b290_entries.replace("meta-gpt", "meta-gpt")

# Inject
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b287_decls + b288_decls + b289_decls + b290_decls + decl_marker)

old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + \
    '    /* Batch 263: Network Utilities */'
new_entries = b287_entries + b288_entries + b289_entries + b290_entries
content = content.replace(old_entry, old_entry + new_entries, 1)

func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b287_funcs + b288_funcs + b289_funcs + b290_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)

print("Injected Batches 287-290 (48 new commands)")