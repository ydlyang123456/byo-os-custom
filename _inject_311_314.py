# inject_311_314.py
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 311: More Web =====
b311_decls = """static void cmd_apache2311(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nginx2311(int argc, char args[][CMD_MAX_LEN]);
static void cmd_caddy2311(int argc, char args[][CMD_MAX_LEN]);
static void cmd_haproxy2311(int argc, char args[][CMD_MAX_LEN]);
static void cmd_traefik2311(int argc, char args[][CMD_MAX_LEN]);
static void cmd_envoy2311(int argc, char args[][CMD_MAX_LEN]);
static void cmd_varnish2311(int argc, char args[][CMD_MAX_LEN]);
static void cmd_squid2311(int argc, char args[][CMD_MAX_LEN]);
static void cmd_stunnel2311(int argc, char args[][CMD_MAX_LEN]);
static void cmd_haproxy2311(int argc, char args[][CMD_MAX_LEN]);
static void cmd_keepalived2311(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ucsncgi2311(int argc, char args[][CMD_MAX_LEN]);
"""

b311_entries = """    /* Batch 311: Web Infrastructure */
    {"apache3", cmd_apache2311}, {"nginx4", cmd_nginx2311}, {"caddy2", cmd_caddy2311},
    {"haproxy2", cmd_haproxy2311}, {"traefik2", cmd_traefik2311}, {"envoy2", cmd_envoy2311},
    {"varnish", cmd_varnish2311}, {"squid2", cmd_squid2311}, {"stunnel2", cmd_stunnel2311},
    {"keepalived", cmd_keepalived2311}, {"ucsnmp", cmd_ucsncgi2311}, {"haproxy3", cmd_haproxy2311},
"""

b311_funcs = """/* ===== Batch 311: Web Infrastructure ===== */
static void cmd_apache2311(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: apache2 <start|stop>\\n"); return; }
    vga_printf("apache2: %s\\n", args[1]);
}
static void cmd_nginx2311(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nginx <start|stop>\\n"); return; }
    vga_printf("nginx: %s\\n", args[1]);
}
static void cmd_caddy2311(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Caddy: automatic HTTPS\\n");
}
static void cmd_haproxy2311(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("HAProxy: load balancer\\n");
}
static void cmd_traefik2311(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Traefik: cloud-native proxy\\n");
}
static void cmd_envoy2311(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Envoy: service proxy\\n");
}
static void cmd_varnish2311(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Varnish: HTTP cache\\n");
}
static void cmd_squid2311(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Squid: proxy server\\n");
}
static void cmd_stunnel2311(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Stunnel: TLS tunnel\\n");
}
static void cmd_keepalived2311(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Keepalived: VRRP\\n");
}
static void cmd_ucsncgi2311(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ucsnmp: SNMP monitoring\\n");
}
"""

# ===== BATCH 312: More Storage =====
b312_decls = """static void cmd_zfs2312(int argc, char args[][CMD_MAX_LEN]);
static void cmd_btrfs2312(int argc, char args[][CMD_MAX_LEN]);
static void cmd_lvm2312(int argc, char args[][CMD_MAX_LEN]);
static void cmd_raid2312(int argc, char args[][CMD_MAX_LEN]);
static void cmd_mdadm2312(int argc, char args[][CMD_MAX_LEN]);
static void cmd_multipath2312(int argc, char args[][CMD_MAX_LEN]);
static void cmd_iscsi2312(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nfs2312(int argc, char args[][CMD_MAX_LEN]);
static void cmd_samba2312(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_cifs2312(int argc, char args[][CMD_MAX_LEN]);
static void cmd_glusterfs2312(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ceph2312(int argc, char args[][CMD_MAX_LEN]);
"""

b312_entries = """    /* Batch 312: Storage */
    {"zfs", cmd_zfs2312}, {"btrfs", cmd_btrfs2312}, {"lvm", cmd_lvm2312},
    {"raid", cmd_raid2312}, {"mdadm", cmd_mdadm2312}, {"multipath", cmd_multipath2312},
    {"iscsi", cmd_iscsi2312}, {"nfs", cmd_nfs2312}, {"samba", cmd_samba2312},
    {"cifs", cmd_cifs2312}, {"glusterfs", cmd_glusterfs2312}, {"ceph", cmd_ceph2312},
"""

b312_funcs = """/* ===== Batch 312: Storage ===== */
static void cmd_zfs2312(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: zfs <command>\\n"); return; }
    vga_printf("zfs: %s\\n", args[1]);
}
static void cmd_btrfs2312(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: btrfs <command>\\n"); return; }
    vga_printf("btrfs: %s\\n", args[1]);
}
static void cmd_lvm2312(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: lvm <command>\\n"); return; }
    vga_printf("lvm: %s\\n", args[1]);
}
static void cmd_raid2312(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("RAID: redundant array\\n");
}
static void cmd_mdadm2312(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: mdadm <command>\\n"); return; }
    vga_printf("mdadm: %s\\n", args[1]);
}
static void cmd_multipath2312(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("multipath: device mapper\\n");
}
static void cmd_iscsi2312(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("iSCSI: block storage\\n");
}
static void cmd_nfs2312(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nfs <mount|umount>\\n"); return; }
    vga_printf("nfs: %s\\n", args[1]);
}
static void cmd_samba2312(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: samba <start|stop>\\n"); return; }
    vga_printf("samba: %s\\n", args[1]);
}
static void cmd_cifs2312(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cifs <mount>\\n"); return; }
    vga_printf("cifs: %s\\n", args[1]);
}
static void cmd_glusterfs2312(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("GlusterFS: distributed storage\\n");
}
static void cmd_ceph2312(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Ceph: unified storage\\n");
}
"""

# ===== BATCH 313: More DevOps =====
b313_decls = """static void cmd_ansible2313(int argc, char args[][CMD_MAX_LEN]);
static void cmd_salt2313(int argc, char args[][CMD_MAX_LEN]);
static void cmd_puppet2313(int argc, char args[][CMD_MAX_LEN]);
static void cmd_chef2313(int argc, char args[][CMD_MAX_LEN]);
static void cmd_terraform2313(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pulumi2313(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cdk2313(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cfn2313(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bicep2313(int argc, char args[][CMD_MAX_LEN]);
static void cmd_arm2313(int argc, char args[][CMD_MAX_LEN]);
static void cmd_crossplane2313(int argc, char args[][CMD_MAX_LEN]);
static void cmd_karpenter2313(int argc, char args[][CMD_MAX_LEN]);
"""

b313_entries = """    /* Batch 313: DevOps IaC */
    {"ansible2", cmd_ansible2313}, {"salt2", cmd_salt2313}, {"puppet2", cmd_puppet2313},
    {"chef2", cmd_chef2313}, {"terraform2", cmd_terraform2313}, {"pulumi2", cmd_pulumi2313},
    {"cdk3", cmd_cdk2313}, {"cfn", cmd_cfn2313}, {"bicep", cmd_bicep2313},
    {"arm", cmd_arm2313}, {"crossplane2", cmd_crossplane2313}, {"karpenter", cmd_karpenter2313},
"""

b313_funcs = """/* ===== Batch 313: DevOps IaC ===== */
static void cmd_ansible2313(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ansible <playbook>\\n"); return; }
    vga_printf("ansible: %s\\n", args[1]);
}
static void cmd_salt2313(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: salt <command>\\n"); return; }
    vga_printf("salt: %s\\n", args[1]);
}
static void cmd_puppet2313(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Puppet: configuration management\\n");
}
static void cmd_chef2313(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Chef: configuration management\\n");
}
static void cmd_terraform2313(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: terraform <command>\\n"); return; }
    vga_printf("terraform: %s\\n", args[1]);
}
static void cmd_pulumi2313(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pulumi <command>\\n"); return; }
    vga_printf("pulumi: %s\\n", args[1]);
}
static void cmd_cdk2313(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cdk <command>\\n"); return; }
    vga_printf("cdk: %s\\n", args[1]);
}
static void cmd_cfn2313(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("CloudFormation: AWS IaC\\n");
}
static void cmd_bicep2313(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Bicep: Azure IaC\\n");
}
static void cmd_arm2313(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ARM: Azure Resource Manager\\n");
}
static void cmd_crossplane2313(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Crossplane: cloud infrastructure\\n");
}
static void cmd_karpenter2313(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Karpenter: Kubernetes autoscaler\\n");
}
"""

# ===== BATCH 314: More System =====
b314_decls = """static void cmd_cgroup2314(int argc, char args[][CMD_MAX_LEN]);
static void cmd_namespace2314(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_seccomp2314(int argc, char args[][CMD_MAX_LEN]);
static void cmd_apparmor2314(int argc, char args[][CMD_MAX_LEN]);
static void cmd_selinux2314(int argc, char args[][CMD_MAX_LEN]);
static void cmd_grsecurity2314(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_paX2314(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_RSBAC2314(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tomoyo2314(int argc, char args[][CMD_MAX_LEN]);
static void cmd_smack2314(int argc, char args[][CMD_MAX_LEN]);
static void cmd_yama2314(int argc, char args[][CMD_MAX_LEN]);
static void cmd_landlock2314(int argc, char args[][CMD_MAX_LEN]);
"""

b314_entries = """    /* Batch 314: Security & Isolation */
    {"cgroup", cmd_cgroup2314}, {"namespace", cmd_namespace2314}, {"seccomp", cmd_seccomp2314},
    {"apparmor", cmd_apparmor2314}, {"selinux", cmd_selinux2314}, {"grsecurity", cmd_grsecurity2314},
    {"pax", cmd_paX2314}, {"rsbac", cmd_RSBAC2314}, {"tomoyo", cmd_tomoyo2314},
    {"smack", cmd_smack2314}, {"yama", cmd_yama2314}, {"landlock", cmd_landlock2314},
"""

b314_funcs = """/* ===== Batch 314: Security & Isolation ===== */
static void cmd_cgroup2314(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("cgroups: process resource control\\n");
}
static void cmd_namespace2314(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("namespaces: process isolation\\n");
}
static void cmd_seccomp2314(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("seccomp: secure computing\\n");
}
static void cmd_apparmor2314(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("AppArmor: mandatory access control\\n");
}
static void cmd_selinux2314(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("SELinux: security enhanced Linux\\n");
}
static void cmd_grsecurity2314(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("grsecurity: kernel security\\n");
}
static void cmd_paX2314(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("PaX: memory protection\\n");
}
static void cmd_RSBAC2314(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("RSBAC: role-based access control\\n");
}
static void cmd_tomoyo2314(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("TOMOYO: path-based MAC\\n");
}
static void cmd_smack2314(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("SMACK: simplified MAC\\n");
}
static void cmd_yama2314(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Yama: ptrace restrictions\\n");
}
static void cmd_landlock2314(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Landlock: unprivileged sandboxing\\n");
}
"""

# Fix syntax
b311_decls = b311_decls.replace("static void_cmd_", "static void cmd_")
b312_decls = b312_decls.replace("static void_cmd_", "static void cmd_")
b314_decls = b314_decls.replace("static void_cmd_", "static void cmd_")

# Inject
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b311_decls + b312_decls + b313_decls + b314_decls + decl_marker)

old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + \
    '    /* Batch 263: Network Utilities */'
new_entries = b311_entries + b312_entries + b313_entries + b314_entries
content = content.replace(old_entry, old_entry + new_entries, 1)

func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b311_funcs + b312_funcs + b313_funcs + b314_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)
print("Injected Batches 311-314 (48 new commands)")