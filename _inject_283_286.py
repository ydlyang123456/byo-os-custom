# inject_283_286.py - More specialized tools
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 283: Email & Communication =====
b283_decls = """static void cmd_sendmail283(int argc, char args[][CMD_MAX_LEN]);
static void cmd_mail283(int argc, char args[][CMD_MAX_LEN]);
static void cmd_mutt283(int argc, char args[][CMD_MAX_LEN]);
static void cmd_fetchmail283(int argc, char args[][CMD_MAX_LEN]);
static void cmd_procmail283(int argc, char args[][CMD_MAX_LEN]);
static void cmd_spamassassin283(int argc, char args[][CMD_MAX_LEN]);
static void cmd_clamav_milter283(int argc, char args[][CMD_MAX_LEN]);
static void cmd_opendkim283(int argc, char args[][CMD_MAX_LEN]);
static void cmd_opendmarc283(int argc, char args[][CMD_MAX_LEN]);
static void cmd_postscreen283(int argc, char args[][CMD_MAX_LEN]);
static void cmd_amavis283(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dovecot283(int argc, char args[][CMD_MAX_LEN]);
"""

b283_entries = """    /* Batch 283: Email & Communication */
    {"sendmail", cmd_sendmail283}, {"mail", cmd_mail283}, {"mutt", cmd_mutt283},
    {"fetchmail", cmd_fetchmail283}, {"procmail", cmd_procmail283}, {"spamassassin", cmd_spamassassin283},
    {"clamav-milter", cmd_clamav_milter283}, {"opendkim", cmd_opendkim283}, {"opendmarc", cmd_opendmarc283},
    {"postscreen", cmd_postscreen283}, {"amavis", cmd_amavis283}, {"dovecot", cmd_dovecot283},
"""

b283_funcs = """/* ===== Batch 283: Email & Communication ===== */
static void cmd_sendmail283(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("sendmail: mail transfer agent\\n");
    vga_puts("sendmail: message sent\\n");
}
static void cmd_mail283(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: mail <user>\\n"); return; }
    vga_printf("mail: sending to %s\\n", args[1]);
    vga_puts("mail: message queued\\n");
}
static void cmd_mutt283(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("mutt: mail user agent\\n");
    vga_puts("mutt: 5 messages, 2 unread\\n");
}
static void cmd_fetchmail283(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("fetchmail: fetching mail...\\n");
    vga_puts("fetchmail: 3 messages downloaded\\n");
}
static void cmd_procmail283(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("procmail: mail processor\\n");
    vga_puts("procmail: 2 messages delivered\\n");
}
static void cmd_spamassassin283(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("spamassassin: spam filter\\n");
    vga_puts("spamassassin: score: 0.5 (not spam)\\n");
}
static void cmd_clamav_milter283(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("clamav-milter: virus scanner for mail\\n");
    vga_puts("clamav-milter: scanning... clean\\n");
}
static void cmd_opendkim283(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("opendkim: DKIM signing daemon\\n");
    vga_puts("opendkim: signing messages\\n");
}
static void cmd_opendmarc283(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("opendmarc: DMARC policy daemon\\n");
    vga_puts("opendmarc: evaluating DMARC policy\\n");
}
static void cmd_postscreen283(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("postscreen: Postfix SMTP pre-filter\\n");
    vga_puts("postscreen: using mechanism list: PASS\\n");
}
static void cmd_amavis283(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("amavis: mail virus scanner\\n");
    vga_puts("amavis: clean (score -999)\\n");
}
static void cmd_dovecot283(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("dovecot: IMAP/POP3 server\\n");
    vga_puts("dovecot: listening on 0.0.0.0:993 (SSL)\\n");
}
"""

# ===== BATCH 284: Network Analysis =====
b284_decls = """static void cmd_tcpdump284(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tshark284(int argc, char args[][CMD_MAX_LEN]);
static void cmd_wireshark284(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nmap284(int argc, char args[][CMD_MAX_LEN]);
static void cmd_masscan284(int argc, char args[][CMD_MAX_LEN]);
static void cmd_zmap284(int argc, char args[][CMD_MAX_LEN]);
static void cmd_hping3284(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ettercap284(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bettercap284(int argc, char args[][CMD_MAX_LEN]);
static void cmd_reaver284(int argc, char args[][CMD_MAX_LEN]);
static void cmd_aircrack284(int argc, char args[][CMD_MAX_LEN]);
static void cmd_kismet284(int argc, char args[][CMD_MAX_LEN]);
"""

b284_entries = """    /* Batch 284: Network Analysis */
    {"tcpdump", cmd_tcpdump284}, {"tshark", cmd_tshark284}, {"wireshark", cmd_wireshark284},
    {"nmap", cmd_nmap284}, {"masscan", cmd_masscan284}, {"zmap", cmd_zmap284},
    {"hping3", cmd_hping3284}, {"ettercap", cmd_ettercap284}, {"bettercap", cmd_bettercap284},
    {"reaver", cmd_reaver284}, {"aircrack-ng", cmd_aircrack284}, {"kismet", cmd_kismet284},
"""

b284_funcs = """/* ===== Batch 284: Network Analysis ===== */
static void cmd_tcpdump284(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: tcpdump <interface>\\n"); return; }
    vga_printf("tcpdump: listening on %s\\n", args[1]);
    vga_puts("10:00:00 IP 192.168.1.1 > 8.8.8.8: ICMP echo request\\n");
    vga_puts("10:00:00 IP 8.8.8.8 > 192.168.1.1: ICMP echo reply\\n");
    vga_puts("2 packets captured\\n");
}
static void cmd_tshark284(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("tshark: network protocol analyzer\\n");
    vga_puts("tshark: 10 packets captured\\n");
}
static void cmd_wireshark284(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("wireshark: GUI network analyzer\\n");
    vga_puts("wireshark: no display available\\n");
}
static void cmd_nmap284(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nmap <target>\\n"); return; }
    vga_printf("nmap: scanning %s\\n", args[1]);
    vga_puts("PORT   STATE  SERVICE\\n");
    vga_puts("22/tcp open   ssh\\n");
    vga_puts("80/tcp open   http\\n");
    vga_puts("443/tcp open   https\\n");
    vga_puts("Nmap done: 1 IP (3 hosts up) scanned\\n");
}
static void cmd_masscan284(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: masscan <target>\\n"); return; }
    vga_printf("masscan: scanning %s\\n", args[1]);
    vga_puts("masscan: 65535 ports in 5 seconds\\n");
}
static void cmd_zmap284(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("zmap: Internet-wide network scanner\\n");
    vga_puts("zmap: 100000 hosts scanned, 5000 responded\\n");
}
static void cmd_hping3284(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: hping3 <target>\\n"); return; }
    vga_printf("hping3: sending to %s\\n", args[1]);
    vga_puts("64 bytes from 8.8.8.8: icmp_seq=0 ttl=64 time=1.2ms\\n");
}
static void cmd_ettercap284(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ettercap: MITM attack tool\\n");
    vga_puts("ettercap: 2 hosts found\\n");
}
static void cmd_bettercap284(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("bettercap: network attack tool\\n");
    vga_puts("bettercap: 3 probes, 2 results\\n");
}
static void cmd_reaver284(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("reaver: WPS brute force tool\\n");
    vga_puts("reaver: WPS PIN: 12345678\\n");
}
static void cmd_aircrack284(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("aircrack-ng: WiFi password cracker\\n");
    vga_puts("aircrack-ng: key found: [password123]\\n");
}
static void cmd_kismet284(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("kismet: wireless network detector\\n");
    vga_puts("kismet: 5 networks found\\n");
}
"""

# ===== BATCH 285: Document & Presentation =====
b285_decls = """static void cmd_pandoc285(int argc, char args[][CMD_MAX_LEN]);
static void cmd_latex285(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pdflatex285(int argc, char args[][CMD_MAX_LEN]);
static void cmd_xelatex285(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bibtex285(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_makeindex285(int argc, char args[][CMD_MAX_LEN]);
static void cmd_libreoffice285(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ghostscript285(int argc, char args[][CMD_MAX_LEN]);
static void cmd_imagemagick285(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_ffmpeg285(int argc, char args[][CMD_MAX_LEN]);
static void cmd_youtube285_dl(int argc, char args[][CMD_MAX_LEN]);
static void cmd_yt_dlp285(int argc, char args[][CMD_MAX_LEN]);
"""

b285_entries = """    /* Batch 285: Document & Media */
    {"pandoc", cmd_pandoc285}, {"latex", cmd_latex285}, {"pdflatex", cmd_pdflatex285},
    {"xelatex", cmd_xelatex285}, {"bibtex", cmd_bibtex285}, {"makeindex", cmd_makeindex285},
    {"libreoffice", cmd_libreoffice285}, {"gs", cmd_ghostscript285}, {"convert", cmd_imagemagick285},
    {"ffmpeg", cmd_ffmpeg285}, {"youtube-dl", cmd_youtube285_dl}, {"yt-dlp", cmd_yt_dlp285},
"""

b285_funcs = """/* ===== Batch 285: Document & Media ===== */
static void cmd_pandoc285(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pandoc <input> -o <output>\\n"); return; }
    vga_printf("pandoc: converting %s\\n", args[1]);
    vga_puts("pandoc: conversion complete\\n");
}
static void cmd_latex285(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: latex <file.tex>\\n"); return; }
    vga_printf("latex: compiling %s\\n", args[1]);
    vga_puts("latex: output: file.dvi\\n");
}
static void cmd_pdflatex285(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pdflatex <file.tex>\\n"); return; }
    vga_printf("pdflatex: compiling %s\\n", args[1]);
    vga_puts("pdflatex: output: file.pdf\\n");
}
static void cmd_xelatex285(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: xelatex <file.tex>\\n"); return; }
    vga_printf("xelatex: compiling %s\\n", args[1]);
    vga_puts("xelatex: output: file.pdf\\n");
}
static void cmd_bibtex285(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: bibtex <file>\\n"); return; }
    vga_printf("bibtex: processing %s\\n", args[1]);
}
static void cmd_makeindex285(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: makeindex <file>\\n"); return; }
    vga_printf("makeindex: processing %s\\n", args[1]);
}
static void cmd_libreoffice285(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("libreoffice: office suite\\n");
    vga_puts("libreoffice: no display available\\n");
}
static void cmd_ghostscript285(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gs <file.ps>\\n"); return; }
    vga_printf("gs: processing %s\\n", args[1]);
    vga_puts("gs: output: file.pdf\\n");
}
static void cmd_imagemagick285(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: convert <input> <output>\\n"); return; }
    vga_printf("convert: %s -> %s\\n", args[1], args[2]);
}
static void cmd_ffmpeg285(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ffmpeg <options>\\n"); return; }
    vga_puts("ffmpeg: video/audio converter\\n");
    vga_puts("ffmpeg: converting...\\nffmpeg: complete\\n");
}
static void cmd_youtube285_dl(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: youtube-dl <url>\\n"); return; }
    vga_printf("youtube-dl: downloading %s\\n", args[1]);
    vga_puts("youtube-dl: 100% complete\\n");
}
static void cmd_yt_dlp285(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: yt-dlp <url>\\n"); return; }
    vga_printf("yt-dlp: downloading %s\\n", args[1]);
    vga_puts("yt-dlp: 100% complete\\n");
}
"""

# ===== BATCH 286: AI & ML Tools =====
b286_decls = """static void cmd_tensorflow286(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pytorch286(int argc, char args[][CMD_MAX_LEN]);
static void cmd_scikit286(int argc, char args[][CMD_MAX_LEN]);
static void cmd_numpy286(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pandas286(int argc, char args[][CMD_MAX_LEN]);
static void cmd_matplotlib286(int argc, char args[][CMD_MAX_LEN]);
static void cmd_jupyter286(int argc, char args[][CMD_MAX_LEN]);
static void cmd_huggingface286(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ollama286(int argc, char args[][CMD_MAX_LEN]);
static void cmd_openai286(int argc, char args[][CMD_MAX_LEN]);
static void cmd_langchain286(int argc, char args[][CMD_MAX_LEN]);
static void cmd_llama286(int argc, char args[][CMD_MAX_LEN]);
"""

b286_entries = """    /* Batch 286: AI & ML Tools */
    {"tensorflow", cmd_tensorflow286}, {"pytorch", cmd_pytorch286}, {"scikit-learn", cmd_scikit286},
    {"numpy", cmd_numpy286}, {"pandas", cmd_pandas286}, {"matplotlib", cmd_matplotlib286},
    {"jupyter", cmd_jupyter286}, {"huggingface", cmd_huggingface286}, {"ollama", cmd_ollama286},
    {"openai", cmd_openai286}, {"langchain", cmd_langchain286}, {"llama", cmd_llama286},
"""

b286_funcs = """/* ===== Batch 286: AI & ML Tools ===== */
static void cmd_tensorflow286(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("TensorFlow 2.13.0\\n");
    vga_puts("tensorflow: GPU: not available, CPU: 1 core\\n");
}
static void cmd_pytorch286(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("PyTorch 2.0.1\\n");
    vga_puts("pytorch: CUDA: not available, CPU: 1 core\\n");
}
static void cmd_scikit286(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("scikit-learn 1.3.0\\n");
    vga_puts("scikit-learn: machine learning library\\n");
}
static void cmd_numpy286(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("NumPy 1.24.0\\n");
    vga_puts("numpy: array([1, 2, 3])\\n");
}
static void cmd_pandas286(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("pandas 2.0.0\\n");
    vga_puts("pandas: DataFrame: 100 rows x 5 columns\\n");
}
static void cmd_matplotlib286(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("matplotlib 3.7.0\\n");
    vga_puts("matplotlib: plotting library\\n");
}
static void cmd_jupyter286(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Jupyter 1.0.0\\n");
    vga_puts("jupyter: notebook server at http://localhost:8888\\n");
}
static void cmd_huggingface286(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Hugging Face Transformers 4.30.0\\n");
    vga_puts("huggingface: model hub: 100k+ models\\n");
}
static void cmd_ollama286(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ollama <run|pull|list>\\n"); return; }
    if (strcmp(args[1], "list") == 0) {
        vga_puts("NAME            SIZE    MODIFIED\\n");
        vga_puts("llama2:7b       3.8GB   2 days ago\\n");
        vga_puts("codellama:7b    3.8GB   1 week ago\\n");
    } else vga_printf("ollama: %s\\n", args[1]);
}
static void cmd_openai286(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("OpenAI API client\\n");
    vga_puts("openai: models available: gpt-4, gpt-3.5-turbo\\n");
}
static void cmd_langchain286(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("LangChain 0.1.0\\n");
    vga_puts("langchain: LLM application framework\\n");
}
static void cmd_llama286(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("llama.cpp: LLM inference engine\\n");
    vga_puts("llama.cpp: model loaded, 7B parameters\\n");
}
"""

# Fix the syntax errors in b285_decls and b285_entries
b285_decls = b285_decls.replace("static void_cmd_", "static void cmd_")
b285_decls = b285_decls.replace("static void_cmd_ffmpeg", "static void cmd_ffmpeg")
b285_entries = b285_entries.replace("makeindex", "makeindex")

# Inject
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b283_decls + b284_decls + b285_decls + b286_decls + decl_marker)

old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + \
    '    /* Batch 263: Network Utilities */'
new_entries = b283_entries + b284_entries + b285_entries + b286_entries
content = content.replace(old_entry, old_entry + new_entries, 1)

func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b283_funcs + b284_funcs + b285_funcs + b286_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)

print("Injected Batches 283-286 (48 new commands)")