# inject_307_310.py
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 307: DNS & DHCP =====
b307_decls = """static void cmd_dig307(int argc, char args[][CMD_MAX_LEN]);
static void cmd_host307(int argc, char args[][CMD_MAX_LEN]);
static void cmd_whois307(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dhcpclient307(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dhclient307(int argc, char args[][CMD_MAX_LEN]);
static void cmd_wpa_supplicant307(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nmcli307(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nmtui307(int argc, char args[][CMD_MAX_LEN]);
static void cmd_networkmanager307(int argc, char args[][CMD_MAX_LEN]);
static void cmd_connman307(int argc, char args[][CMD_MAX_LEN]);
static void cmd_netplan307(int argc, char args[][CMD_MAX_LEN]);
static void cmd_resolvconf307(int argc, char args[][CMD_MAX_LEN]);
"""

b307_entries = """    /* Batch 307: DNS & DHCP */
    {"dig", cmd_dig307}, {"host", cmd_host307}, {"whois", cmd_whois307},
    {"dhclient", cmd_dhclient307}, {"wpa_supplicant", cmd_wpa_supplicant307}, {"nmcli", cmd_nmcli307},
    {"nmtui", cmd_nmtui307}, {"NetworkManager", cmd_networkmanager307}, {"connman", cmd_connman307},
    {"netplan", cmd_netplan307}, {"resolvconf", cmd_resolvconf307}, {"dhcp", cmd_dhcpclient307},
"""

b307_funcs = """/* ===== Batch 307: DNS & DHCP ===== */
static void cmd_dig307(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dig <domain>\\n"); return; }
    vga_printf("dig: querying %s\\n", args[1]);
    vga_puts(";; ANSWER SECTION:\\n;; A 192.168.1.1\\n");
}
static void cmd_host307(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: host <domain>\\n"); return; }
    vga_printf("host: %s has address 192.168.1.1\\n", args[1]);
}
static void cmd_whois307(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: whois <domain>\\n"); return; }
    vga_printf("whois: querying %s\\n", args[1]);
    vga_puts("Registrar: Example Inc.\\n");
}
static void cmd_dhclient307(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("dhclient: requesting IP...\\ndhclient: bound to 192.168.1.100\\n");
}
static void cmd_wpa_supplicant307(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("wpa_supplicant: wireless authentication\\n");
}
static void cmd_nmcli307(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nmcli <device|connection>\\n"); return; }
    if (strcmp(args[1], "device") == 0) vga_puts("DEVICE  TYPE  STATE\\neth0    wifi  connected\\n");
    else vga_printf("nmcli: %s\\n", args[1]);
}
static void cmd_nmtui307(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("nmtui: NetworkManager TUI\\n");
}
static void cmd_networkmanager307(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("NetworkManager: running\\n");
}
static void cmd_connman307(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ConnMan: network manager\\n");
}
static void cmd_netplan307(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Netplan: network configuration\\n");
}
static void cmd_resolvconf307(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("resolvconf: DNS resolver configuration\\n");
}
static void cmd_dhcpclient307(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("dhcp: requesting IP...\\ndhcp: bound\\n");
}
"""

# ===== BATCH 308: More AI/ML =====
b308_decls = """static void cmd_torch308(int argc, char args[][CMD_MAX_LEN]);
static void cmd_theano308(int argc, char args[][CMD_MAX_LEN]);
static void cmd_caffe308(int argc, char args[][CMD_MAX_LEN]);
static void cmd_mxnet308(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cntk308(int argc, char args[][CMD_MAX_LEN]);
static void cmd_deeplearning4j308(int argc, char args[][CMD_MAX_LEN]);
static void cmd_paddlepaddle308(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_mindspore308(int argc, char args[][CMD_MAX_LEN]);
static void cmd_onnxruntime308(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tflite308(int argc, char args[][CMD_MAX_LEN]);
static void cmd_coreml2308(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tensorrt2308(int argc, char args[][CMD_MAX_LEN]);
"""

b308_entries = """    /* Batch 308: AI Frameworks */
    {"torch", cmd_torch308}, {"theano", cmd_theano308}, {"caffe", cmd_caffe308},
    {"mxnet", cmd_mxnet308}, {"cntk", cmd_cntk308}, {"deeplearning4j", cmd_deeplearning4j308},
    {"paddlepaddle", cmd_paddlepaddle308}, {"mindspore", cmd_mindspore308}, {"onnxruntime2", cmd_onnxruntime308},
    {"tflite", cmd_tflite308}, {"coreml2", cmd_coreml2308}, {"tensorrt2", cmd_tensorrt2308},
"""

b308_funcs = """/* ===== Batch 308: AI Frameworks ===== */
static void cmd_torch308(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Torch: scientific computing\\n");
}
static void cmd_theano308(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Theano: deep learning\\n");
}
static void cmd_caffe308(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Caffe: deep learning framework\\n");
}
static void cmd_mxnet308(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("MXNet: deep learning\\n");
}
static void cmd_cntk308(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("CNTK: Cognitive Toolkit\\n");
}
static void cmd_deeplearning4j308(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Deeplearning4j: Java deep learning\\n");
}
static void cmd_paddlepaddle308(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("PaddlePaddle: Baidu deep learning\\n");
}
static void cmd_mindspore308(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("MindSpore: Huawei deep learning\\n");
}
static void cmd_onnxruntime308(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ONNX Runtime: ML inference\\n");
}
static void cmd_tflite308(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("TFLite: mobile ML\\n");
}
static void cmd_coreml2308(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Core ML: Apple ML\\n");
}
static void cmd_tensorrt2308(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("TensorRT: GPU inference\\n");
}
"""

# ===== BATCH 309: More Monitoring =====
b309_decls = """static void cmd_prometheus2309(int argc, char args[][CMD_MAX_LEN]);
static void cmd_grafana2309(int argc, char args[][CMD_MAX_LEN]);
static void cmd_elasticsearch2309(int argc, char args[][CMD_MAX_LEN]);
static void cmd_kibana2309(int argc, char args[][CMD_MAX_LEN]);
static void cmd_logstash2309(int argc, char args[][CMD_MAX_LEN]);
static void cmd_filebeat2309(int argc, char args[][CMD_MAX_LEN]);
static void cmd_metricbeat2309(int argc, char args[][CMD_MAX_LEN]);
static void cmd_apm2309(int argc, char args[][CMD_MAX_LEN]);
static void cmd_jaeger2309(int argc, char args[][CMD_MAX_LEN]);
static void cmd_zipkin2309(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_opentelemetry2309(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tempo2309(int argc, char args[][CMD_MAX_LEN]);
"""

b309_entries = """    /* Batch 309: Monitoring Stack */
    {"prometheus2", cmd_prometheus2309}, {"grafana2", cmd_grafana2309}, {"elasticsearch2", cmd_elasticsearch2309},
    {"kibana2", cmd_kibana2309}, {"logstash", cmd_logstash2309}, {"filebeat", cmd_filebeat2309},
    {"metricbeat", cmd_metricbeat2309}, {"apm", cmd_apm2309}, {"jaeger2", cmd_jaeger2309},
    {"zipkin2", cmd_zipkin2309}, {"opentelemetry", cmd_opentelemetry2309}, {"tempo", cmd_tempo2309},
"""

b309_funcs = """/* ===== Batch 309: Monitoring Stack ===== */
static void cmd_prometheus2309(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Prometheus: metrics collection\\n");
    vga_puts("prometheus: listening on :9090\\n");
}
static void cmd_grafana2309(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Grafana: visualization\\n");
    vga_puts("grafana: listening on :3000\\n");
}
static void cmd_elasticsearch2309(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Elasticsearch: search engine\\n");
}
static void cmd_kibana2309(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Kibana: dashboard\\n");
}
static void cmd_logstash2309(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Logstash: log pipeline\\n");
}
static void cmd_filebeat2309(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Filebeat: log shipper\\n");
}
static void cmd_metricbeat2309(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Metricbeat: metrics shipper\\n");
}
static void cmd_apm2309(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("APM: application performance monitoring\\n");
}
static void cmd_jaeger2309(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Jaeger: distributed tracing\\n");
}
static void cmd_zipkin2309(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Zipkin: distributed tracing\\n");
}
static void cmd_opentelemetry2309(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("OpenTelemetry: observability framework\\n");
}
static void cmd_tempo2309(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Tempo: trace storage\\n");
}
"""

# ===== BATCH 310: More Misc =====
b310_decls = """static void cmd_docker2310(int argc, char args[][CMD_MAX_LEN]);
static void cmd_podman2310(int argc, char args[][CMD_MAX_LEN]);
static void cmd_containerd2310(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cri2310(int argc, char args[][CMD_MAX_LEN]);
static void cmd_buildkit2310(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pacman2310(int argc, char args[][CMD_MAX_LEN]);
static void cmd_rpm2310(int argc, char args[][CMD_MAX_LEN]);
static void cmd_deb2310(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pkg2310(int argc, char args[][CMD_MAX_LEN]);
static void cmd_arch2310(int argc, char args[][CMD_MAX_LEN]);
static void cmd_suse2310(int argc, char args[][CMD_MAX_LEN]);
static void cmd_redhat2310(int argc, char args[][CMD_MAX_LEN]);
"""

b310_entries = """    /* Batch 310: Container & Package */
    {"docker2", cmd_docker2310}, {"podman2", cmd_podman2310}, {"containerd", cmd_containerd2310},
    {"cri-o", cmd_cri2310}, {"buildkit", cmd_buildkit2310}, {"pacman2", cmd_pacman2310},
    {"rpm", cmd_rpm2310}, {"dpkg", cmd_deb2310}, {"pkg", cmd_pkg2310},
    {"arch", cmd_arch2310}, {"zypper2", cmd_suse2310}, {"yum2", cmd_redhat2310},
"""

b310_funcs = """/* ===== Batch 310: Container & Package ===== */
static void cmd_docker2310(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: docker <command>\\n"); return; }
    vga_printf("docker: %s\\n", args[1]);
}
static void cmd_podman2310(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: podman <command>\\n"); return; }
    vga_printf("podman: %s\\n", args[1]);
}
static void cmd_containerd2310(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("containerd: container runtime\\n");
}
static void cmd_cri2310(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("CRI-O: Kubernetes container runtime\\n");
}
static void cmd_buildkit2310(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("BuildKit: container image builder\\n");
}
static void cmd_pacman2310(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pacman <command>\\n"); return; }
    vga_printf("pacman: %s\\n", args[1]);
}
static void cmd_rpm2310(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: rpm <command>\\n"); return; }
    vga_printf("rpm: %s\\n", args[1]);
}
static void cmd_deb2310(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dpkg <command>\\n"); return; }
    vga_printf("dpkg: %s\\n", args[1]);
}
static void cmd_pkg2310(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pkg <command>\\n"); return; }
    vga_printf("pkg: %s\\n", args[1]);
}
static void cmd_arch2310(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Arch Linux package manager\\n");
}
static void cmd_suse2310(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("SUSE package manager\\n");
}
static void cmd_redhat2310(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Red Hat package manager\\n");
}
"""

# Fix syntax
b308_decls = b308_decls.replace("static void_cmd_", "static void cmd_")
b309_decls = b309_decls.replace("static void_cmd_", "static void cmd_")

# Inject
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b307_decls + b308_decls + b309_decls + b310_decls + decl_marker)

old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + \
    '    /* Batch 263: Network Utilities */'
new_entries = b307_entries + b308_entries + b309_entries + b310_entries
content = content.replace(old_entry, old_entry + new_entries, 1)

func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b307_funcs + b308_funcs + b309_funcs + b310_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)
print("Injected Batches 307-310 (48 new commands)")