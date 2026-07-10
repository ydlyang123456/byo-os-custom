# inject_271_274.py - Security, Containers, Cloud, System Tools
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 271: Security Tools =====
b271_decls = """static void cmd_openssl271(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gpg271(int argc, char args[][CMD_MAX_LEN]);
static void cmd_chmod271(int argc, char args[][CMD_MAX_LEN]);
static void cmd_sha1sum271(int argc, char args[][CMD_MAX_LEN]);
static void cmd_curl271(int argc, char args[][CMD_MAX_LEN]);
static void cmd_keygen271(int argc, char args[][CMD_MAX_LEN]);
static void cmd_sshkeygen271(int argc, char args[][CMD_MAX_LEN]);
static void cmd_fail2ban271(int argc, char args[][CMD_MAX_LEN]);
static void cmd_lynis271(int argc, char args[][CMD_MAX_LEN]);
static void cmd_clamav271(int argc, char args[][CMD_MAX_LEN]);
static void cmd_rkhunter271(int argc, char args[][CMD_MAX_LEN]);
static void cmd_aide271(int argc, char args[][CMD_MAX_LEN]);
"""

b271_entries = """    /* Batch 271: Security Tools */
    {"openssl", cmd_openssl271}, {"gpg", cmd_gpg271}, {"chmod2", cmd_chmod271},
    {"sha1sum", cmd_sha1sum271}, {"curl2", cmd_curl271}, {"keygen", cmd_keygen271},
    {"ssh-keygen", cmd_sshkeygen271}, {"fail2ban", cmd_fail2ban271}, {"lynis", cmd_lynis271},
    {"clamscan", cmd_clamav271}, {"rkhunter", cmd_rkhunter271}, {"aide", cmd_aide271},
"""

b271_funcs = """/* ===== Batch 271: Security Tools ===== */
static void cmd_openssl271(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: openssl <version|enc|dgst>\\n"); return; }
    if (strcmp(args[1], "version") == 0) vga_puts("OpenSSL 3.0.2 15 Mar 2022 (Library: OpenSSL 3.0.2 15 Mar 2022)\\n");
    else if (strcmp(args[1], "enc") == 0) vga_puts("openssl: encrypting/decrypting data\\n");
    else if (strcmp(args[1], "dgst") == 0) vga_puts("openssl: computing message digest\\n");
    else vga_printf("openssl: unknown command '%s'\\n", args[1]);
}
static void cmd_gpg271(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gpg <options>\\n"); return; }
    vga_printf("gpg: processing '%s'\\n", args[1]);
    vga_puts("gpg: encrypted with 2048-bit RSA key\\n");
}
static void cmd_chmod271(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: chmod <mode> <file>\\n"); return; }
    vga_printf("chmod: changed permissions of '%s' to %s\\n", args[2], args[1]);
}
static void cmd_sha1sum271(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sha1sum <file>\\n"); return; }
    vga_printf("da39a3ee5e6b4b0d3255bfef95601890afd80709  %s\\n", args[1]);
}
static void cmd_curl271(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: curl <url>\\n"); return; }
    vga_printf("curl: fetching %s\\n", args[1]);
    vga_puts("HTTP/1.1 200 OK\\nContent-Type: text/html\\n\\n<html>...</html>\\n");
}
static void cmd_keygen271(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("keygen: generating RSA 2048-bit key pair\\n");
    vga_puts("Your public key has been saved in id_rsa.pub\\n");
    vga_puts("Your private key has been saved in id_rsa\\n");
}
static void cmd_sshkeygen271(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ssh-keygen: generating SSH key pair\\n");
    vga_puts("Enter file in which to save the key: /root/.ssh/id_rsa\\n");
    vga_puts("Enter passphrase: ****\\n");
    vga_puts("Your identification has been saved in /root/.ssh/id_rsa\\n");
}
static void cmd_fail2ban271(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("fail2ban: status\\n");
    vga_puts("  Status for the jail: sshd\\n");
    vga_puts("  |- Filter: FAILED\\n");
    vga_puts("  |  `- Currently failed: 3\\n");
    vga_puts("  `- Actions: 5 banned\\n");
}
static void cmd_lynis271(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("lynis: system security audit tool\\n");
    vga_puts("  [+] Boot and services\\n");
    vga_puts("  [+] Kernel\\n");
    vga_puts("  [+] Memory and processes\\n");
    vga_puts("  [+] Users, Groups and Authentication\\n");
    vga_puts("  [+] Shells\\n");
    vga_puts("  [+] File systems\\n");
    vga_puts("  [+] Storage\\n");
    vga_puts("  Hardening index : 67 [#############     ]\\n");
}
static void cmd_clamav271(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: clamscan <file>\\n"); return; }
    vga_printf("%s: OK\\n", args[1]);
    vga_puts("\\n----------- SCAN SUMMARY -----------\\n");
    vga_puts("Known viruses: 0\\nEngine version: 0.103.0\\n");
}
static void cmd_rkhunter271(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("rkhunter: rootkit detector\\n");
    vga_puts("  Performing system checks...\\n");
    vga_puts("  System checks: PASSED\\n");
    vga_puts("  Rootkits: NONE FOUND\\n");
}
static void cmd_aide271(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("aide: file integrity checker\\n");
    vga_puts("AIDE found NO differences between system and AIDE database.\\n");
}
"""

# ===== BATCH 272: Container Tools =====
b272_decls = """static void cmd_docker272(int argc, char args[][CMD_MAX_LEN]);
static void cmd_docker_compose272(int argc, char args[][CMD_MAX_LEN]);
static void cmd_podman272(int argc, char args[][CMD_MAX_LEN]);
static void cmd_buildah272(int argc, char args[][CMD_MAX_LEN]);
static void cmd_skopeo272(int argc, char args[][CMD_MAX_LEN]);
static void cmd_crictl272(int argc, char args[][CMD_MAX_LEN]);
static void cmd_kubectl272(int argc, char args[][CMD_MAX_LEN]);
static void cmd_helm272(int argc, char args[][CMD_MAX_LEN]);
static void cmd_minikube272(int argc, char args[][CMD_MAX_LEN]);
static void cmd_kind272(int argc, char args[][CMD_MAX_LEN]);
static void cmd_k3s272(int argc, char args[][CMD_MAX_LEN]);
static void cmd_k9s272(int argc, char args[][CMD_MAX_LEN]);
"""

b272_entries = """    /* Batch 272: Container Tools */
    {"docker", cmd_docker272}, {"docker-compose", cmd_docker_compose272}, {"podman", cmd_podman272},
    {"buildah", cmd_buildah272}, {"skopeo", cmd_skopeo272}, {"crictl", cmd_crictl272},
    {"kubectl", cmd_kubectl272}, {"helm2", cmd_helm272}, {"minikube", cmd_minikube272},
    {"kind", cmd_kind272}, {"k3s", cmd_k3s272}, {"k9s", cmd_k9s272},
"""

b272_funcs = """/* ===== Batch 272: Container Tools ===== */
static void cmd_docker272(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: docker <ps|run|build|pull|images>\\n"); return; }
    if (strcmp(args[1], "ps") == 0) {
        vga_puts("CONTAINER ID  IMAGE  COMMAND  STATUS  PORTS  NAMES\\n");
        vga_puts("a1b2c3d4e5f6  nginx  ...  Up 2h  80/tcp  web\\n");
    } else if (strcmp(args[1], "images") == 0) {
        vga_puts("REPOSITORY  TAG  IMAGE ID  CREATED  SIZE\\n");
        vga_puts("nginx  latest  a1b2c3d4  2d ago  133MB\\n");
    } else vga_printf("docker: %s\\n", args[1]);
}
static void cmd_docker_compose272(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: docker-compose <up|down|ps>\\n"); return; }
    if (strcmp(args[1], "up") == 0) vga_puts("docker-compose: starting services...\\n");
    else if (strcmp(args[1], "down") == 0) vga_puts("docker-compose: stopping services...\\n");
    else vga_printf("docker-compose: %s\\n", args[1]);
}
static void cmd_podman272(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: podman <ps|run|images>\\n"); return; }
    if (strcmp(args[1], "ps") == 0) {
        vga_puts("CONTAINER ID  IMAGE  COMMAND  STATUS  NAMES\\n");
        vga_puts("b2c3d4e5f6a7  alpine  sh  Up 1h  test\\n");
    } else vga_printf("podman: %s\\n", args[1]);
}
static void cmd_buildah272(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("buildah: OCI image build tool\\n");
    vga_puts("buildah: building image from Dockerfile\\n");
}
static void cmd_skopeo272(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("skopeo: container image inspection tool\\n");
    vga_puts("skopeo: inspecting docker://nginx:latest\\n");
}
static void cmd_crictl272(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: crictl <ps|pods|images>\\n"); return; }
    vga_puts("CONTAINER ID  IMAGE  STATE  NAME\\n");
    vga_puts("abc123  nginx  Running  web\\n");
}
static void cmd_kubectl272(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: kubectl <get|create|delete>\\n"); return; }
    if (strcmp(args[1], "get") == 0 && argc >= 3 && strcmp(args[2], "pods") == 0) {
        vga_puts("NAME  READY  STATUS  RESTARTS  AGE\\n");
        vga_puts("web-0  1/1  Running  0  2h\\n");
    } else vga_printf("kubectl: %s\\n", args[1]);
}
static void cmd_helm272(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: helm <install|list|status>\\n"); return; }
    if (strcmp(args[1], "list") == 0) {
        vga_puts("NAME  REVISION  STATUS  CHART  APP VERSION\\n");
        vga_puts("my-release  1  DEPLOYED  nginx-1.0  1.21\\n");
    } else vga_printf("helm: %s\\n", args[1]);
}
static void cmd_minikube272(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: minikube <start|stop|status>\\n"); return; }
    if (strcmp(args[1], "status") == 0) {
        vga_puts("minikube: Running\\n");
        vga_puts("  host: Running\\n  kubelet: Running\\n  apiserver: Running\\n");
    } else vga_printf("minikube: %s\\n", args[1]);
}
static void cmd_kind272(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: kind <create|get|delete>\\n"); return; }
    vga_printf("kind: %s cluster\\n", args[1]);
}
static void cmd_k3s272(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("k3s: lightweight Kubernetes\\n");
    vga_puts("k3s: server running on port 6443\\n");
}
static void cmd_k9s272(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("k9s: Kubernetes TUI\\n");
    vga_puts("k9s: connecting to cluster...\\n");
}
"""

# ===== BATCH 273: Cloud & DevOps =====
b273_decls = """static void cmd_aws273(int argc, char args[][CMD_MAX_LEN]);
static void cmd_azure273(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gcloud273(int argc, char args[][CMD_MAX_LEN]);
static void cmd_terraform273(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ansible273(int argc, char args[][CMD_MAX_LEN]);
static void cmd_puppet273(int argc, char args[][CMD_MAX_LEN]);
static void cmd_chef273(int argc, char args[][CMD_MAX_LEN]);
static void cmd_salt273(int argc, char args[][CMD_MAX_LEN]);
static void cmd_jenkins273(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gitlab_ci273(int argc, char args[][CMD_MAX_LEN]);
static void cmd_circleci273(int argc, char args[][CMD_MAX_LEN]);
static void cmd_drone273(int argc, char args[][CMD_MAX_LEN]);
"""

b273_entries = """    /* Batch 273: Cloud & DevOps */
    {"aws", cmd_aws273}, {"az", cmd_azure273}, {"gcloud", cmd_gcloud273},
    {"terraform", cmd_terraform273}, {"ansible", cmd_ansible273}, {"puppet", cmd_puppet273},
    {"chef", cmd_chef273}, {"salt", cmd_salt273}, {"jenkins", cmd_jenkins273},
    {"gitlab-ci", cmd_gitlab_ci273}, {"circleci", cmd_circleci273}, {"drone", cmd_drone273},
"""

b273_funcs = """/* ===== Batch 273: Cloud & DevOps ===== */
static void cmd_aws273(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: aws <s3|ec2|iam>\\n"); return; }
    if (strcmp(args[1], "s3") == 0) vga_puts("aws s3: listing buckets...\\n  my-bucket\\n");
    else if (strcmp(args[1], "ec2") == 0) vga_puts("aws ec2: listing instances...\\n  i-1234567890abcdef0  running\\n");
    else vga_printf("aws: %s\\n", args[1]);
}
static void cmd_azure273(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: az <vm|group|account>\\n"); return; }
    vga_printf("azure: %s %s\\n", args[1], argc > 2 ? args[2] : "");
}
static void cmd_gcloud273(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gcloud <compute|iam|run>\\n"); return; }
    vga_printf("gcloud: %s\\n", args[1]);
}
static void cmd_terraform273(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: terraform <init|plan|apply|destroy>\\n"); return; }
    if (strcmp(args[1], "init") == 0) vga_puts("terraform: initializing...\\nTerraform has been successfully initialized!\\n");
    else if (strcmp(args[1], "plan") == 0) vga_puts("terraform: planning...\\nPlan: 3 to add, 0 to change, 0 to destroy.\\n");
    else if (strcmp(args[1], "apply") == 0) vga_puts("terraform: applying...\\nApply complete! Resources: 3 added.\\n");
    else vga_printf("terraform: %s\\n", args[1]);
}
static void cmd_ansible273(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ansible <playbook|inventory>\\n"); return; }
    vga_printf("ansible: executing %s\\n", args[1]);
    vga_puts("PLAY [all] ******\\nPLAY RECAP: ok=3 changed=1\\n");
}
static void cmd_puppet273(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("puppet: configuration management\\n");
    vga_puts("puppet: applying manifest...\\nNotice: Finished catalog run\\n");
}
static void cmd_chef273(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("chef: configuration management\\n");
    vga_puts("chef: running chef-client...\\n[2026-07-10] Chef Infra Client completed\\n");
}
static void cmd_salt273(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("salt: configuration management\\n");
    vga_puts("salt: running state...\\nSummary: 5 Succeeded\\n");
}
static void cmd_jenkins273(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Jenkins: CI/CD server\\n");
    vga_puts("Jenkins: build #42 SUCCESS (3m 21s)\\n");
}
static void cmd_gitlab_ci273(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("GitLab CI: pipeline running\\n");
    vga_puts("Pipeline #123: passed (4m 56s)\\n");
}
static void cmd_circleci273(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("CircleCI: build succeeded\\n");
    vga_puts("Build #456: SUCCESS\\n");
}
static void cmd_drone273(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Drone CI: build running\\n");
    vga_puts("Build #789: passed\\n");
}
"""

# ===== BATCH 274: More System Tools =====
b274_decls = """static void cmd_inetd274(int argc, char args[][CMD_MAX_LEN]);
static void cmd_xinetd274(int argc, char args[][CMD_MAX_LEN]);
static void cmd_supervisord274(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pm2274(int argc, char args[][CMD_MAX_LEN]);
static void cmd_forever274(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cron274(int argc, char args[][CMD_MAX_LEN]);
static void cmd_anacron274(int argc, char args[][CMD_MAX_LEN]);
static void cmd_rsyslog274(int argc, char args[][CMD_MAX_LEN]);
static void cmd_logrotate274(int argc, char args[][CMD_MAX_LEN]);
static void cmd_timezone274(int argc, char args[][CMD_MAX_LEN]);
static void cmd_hwclock274(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ntpdate274(int argc, char args[][CMD_MAX_LEN]);
"""

b274_entries = """    /* Batch 274: System Services */
    {"inetd", cmd_inetd274}, {"xinetd", cmd_xinetd274}, {"supervisord", cmd_supervisord274},
    {"pm2", cmd_pm2274}, {"forever", cmd_forever274}, {"cron2", cmd_cron274},
    {"anacron", cmd_anacron274}, {"rsyslog", cmd_rsyslog274}, {"logrotate", cmd_logrotate274},
    {"timezone", cmd_timezone274}, {"hwclock", cmd_hwclock274}, {"ntpdate", cmd_ntpdate274},
"""

b274_funcs = """/* ===== Batch 274: System Services ===== */
static void cmd_inetd274(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("inetd: internet super-server daemon\\n");
    vga_puts("inetd: listening on port 113/tcp (ident)\\n");
}
static void cmd_xinetd274(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("xinetd: extended internet services daemon\\n");
    vga_puts("xinetd: service echo loaded\\n");
}
static void cmd_supervisord274(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: supervisord <status|start|stop>\\n"); return; }
    if (strcmp(args[1], "status") == 0) {
        vga_puts("supervisord: program:web-server  RUNNING (pid 123)\\n");
        vga_puts("supervisord: program:worker    RUNNING (pid 456)\\n");
    } else vga_printf("supervisord: %s\\n", args[1]);
}
static void cmd_pm2274(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pm2 <list|start|stop>\\n"); return; }
    if (strcmp(args[1], "list") == 0) {
        vga_puts("┌────┬──────┬─────┬────────┬──────┬──────┐\\n");
        vga_puts("│ id │ name │mode │ status │ cpu  │ mem  │\\n");
        vga_puts("├────┼──────┼─────┼────────┼──────┼──────┤\\n");
        vga_puts("│ 0  │ app  │fork │online  │ 0.1% │ 25MB │\\n");
        vga_puts("└────┴──────┴─────┴────────┴──────┴──────┘\\n");
    } else vga_printf("pm2: %s\\n", args[1]);
}
static void cmd_forever274(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("forever: simple node.js process manager\\n");
    vga_puts("info:    Forever Processes running\\n");
    vga_puts(" 0 [12345] /usr/bin/node app.js : 12345\\n");
}
static void cmd_cron274(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("cron: daemon for periodic jobs\\n");
    vga_puts("cron[1]: ready (running)\\n");
    vga_puts("cron[1]: normal job (hourly)\\n");
}
static void cmd_anacron274(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("anacron: running periodic jobs\\n");
    vga_puts("anacron: job 'daily' run\\n");
    vga_puts("anacron: job 'weekly' skipped\\n");
}
static void cmd_rsyslog274(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("rsyslog: system logging daemon\\n");
    vga_puts("rsyslog: listening on /dev/log\\n");
}
static void cmd_logrotate274(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: logrotate <config>\\n"); return; }
    vga_printf("logrotate: rotating %s\\n", args[1]);
    vga_puts("logrotate: rotation complete\\n");
}
static void cmd_timezone274(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Timezone: Asia/Shanghai (CST, +0800)\\n");
    } else {
        vga_printf("timezone: set to '%s'\\n", args[1]);
    }
}
static void cmd_hwclock274(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("hwclock: 2026-07-10 00:00:00.000000+0800\\n");
}
static void cmd_ntpdate274(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ntpdate <server>\\n"); return; }
    vga_printf("ntpdate: adjusting time server %s\\n", args[1]);
    vga_puts("ntpdate: step time server 216.239.35.0 offset 0.001234 sec\\n");
}
"""

# Inject
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b271_decls + b272_decls + b273_decls + b274_decls + decl_marker)

old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + \
    '    /* Batch 263: Network Utilities */'
new_entries = b271_entries + b272_entries + b273_entries + b274_entries
content = content.replace(old_entry, old_entry + new_entries, 1)

func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b271_funcs + b272_funcs + b273_funcs + b274_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)

print("Injected Batches 271-274 (48 new commands)")