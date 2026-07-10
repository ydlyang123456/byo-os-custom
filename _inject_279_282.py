# inject_279_282.py - Hardware, Virtualization, Backup, Misc
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 279: Hardware Tools =====
b279_decls = """static void cmd_lspci279(int argc, char args[][CMD_MAX_LEN]);
static void cmd_lsusb279(int argc, char args[][CMD_MAX_LEN]);
static void cmd_lsblk279(int argc, char args[][CMD_MAX_LEN]);
static void cmd_fdisk279(int argc, char args[][CMD_MAX_LEN]);
static void cmd_mkfs279(int argc, char args[][CMD_MAX_LEN]);
static void cmd_fsck279(int argc, char args[][CMD_MAX_LEN]);
static void cmd_e2fsck279(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tune2fs279(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dumpe2fs279(int argc, char args[][CMD_MAX_LEN]);
static void cmd_hdparm279(int argc, char args[][CMD_MAX_LEN]);
static void cmd_smartctl279(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dmidecode279(int argc, char args[][CMD_MAX_LEN]);
"""

b279_entries = """    /* Batch 279: Hardware Tools */
    {"lspci", cmd_lspci279}, {"lsusb", cmd_lsusb279}, {"lsblk", cmd_lsblk279},
    {"fdisk", cmd_fdisk279}, {"mkfs", cmd_mkfs279}, {"fsck", cmd_fsck279},
    {"e2fsck", cmd_e2fsck279}, {"tune2fs", cmd_tune2fs279}, {"dumpe2fs", cmd_dumpe2fs279},
    {"hdparm", cmd_hdparm279}, {"smartctl", cmd_smartctl279}, {"dmidecode", cmd_dmidecode279},
"""

b279_funcs = """/* ===== Batch 279: Hardware Tools ===== */
static void cmd_lspci279(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("00:00.0 Host bridge: Intel Corporation 440FX\\n");
    vga_puts("00:01.0 ISA bridge: Intel Corporation PIIX3\\n");
    vga_puts("00:02.0 SCSI storage controller: LSI Logic / Symbios Logic 53c810\\n");
    vga_puts("00:03.0 Ethernet controller: Intel Corporation 82540EM\\n");
    vga_puts("00:05.0 VGA: VMware SVGA II\\n");
}
static void cmd_lsusb279(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub\\n");
    vga_puts("Bus 002 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub\\n");
}
static void cmd_lsblk279(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("NAME   MAJ:MIN RM  SIZE TYPE MOUNTPOINT\\n");
    vga_puts("sda      8:0    0   20G disk\\n");
    vga_puts("sda1     8:1    0   18G part /\\n");
    vga_puts("sda2     8:2    0    2G part [SWAP]\\n");
}
static void cmd_fdisk279(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: fdisk <device>\\n"); return; }
    vga_printf("fdisk: listing partitions of %s\\n", args[1]);
    vga_puts("Device     Boot   Start  End  Sectors  Size  Type\\n");
    vga_puts("/dev/sda1  *      2048   37748735  37746688 18G  Linux\\n");
    vga_puts("/dev/sda2         37748736  41943039  4194304  2G  Linux swap\\n");
}
static void cmd_mkfs279(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: mkfs.<type> <device>\\n"); return; }
    vga_printf("mkfs: creating filesystem on %s\\n", args[1]);
    vga_puts("mkfs: done\\n");
}
static void cmd_fsck279(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: fsck <device>\\n"); return; }
    vga_printf("fsck: checking %s\\n", args[1]);
    vga_puts("fsck: clean, 0 errors\\n");
}
static void cmd_e2fsck279(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: e2fsck <device>\\n"); return; }
    vga_printf("e2fsck 1.46.5: checking %s\\n", args[1]);
    vga_puts("e2fsck: clean\\n");
}
static void cmd_tune2fs279(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: tune2fs <device>\\n"); return; }
    vga_printf("tune2fs: tuning %s\\n", args[1]);
}
static void cmd_dumpe2fs279(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dumpe2fs <device>\\n"); return; }
    vga_printf("dumpe2fs: %s\\n", args[1]);
    vga_puts("Filesystem features: has_journal extents huge_file\\n");
}
static void cmd_hdparm279(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: hdparm <device>\\n"); return; }
    vga_printf("hdparm: %s\\n", args[1]);
    vga_puts(" Model=VBOX HARDDISK, FwRev=1.0, SerialNo=VB12345678\\n");
    vga_puts(" 20.0 GB\\n");
}
static void cmd_smartctl279(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: smartctl <device>\\n"); return; }
    vga_printf("smartctl: %s\\n", args[1]);
    vga_puts("SMART overall-health: PASSED\\n");
    vga_puts("  5 Reallocated_Sector_Ct: 000\\n");
}
static void cmd_dmidecode279(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("# dmidecode 3.3\\n");
    vga_puts("System Information:\\n");
    vga_puts("  Manufacturer: BYO-OS\\n  Product: Virtual Machine\\n");
    vga_puts("  Version: 1.0\\n  Serial: VM-SERIAL-123\\n");
}
"""

# ===== BATCH 280: Virtualization =====
b280_decls = """static void cmd_virsh280(int argc, char args[][CMD_MAX_LEN]);
static void cmd_virt_280(int argc, char args[][CMD_MAX_LEN]);
static void cmd_qemu_280(int argc, char args[][CMD_MAX_LEN]);
static void cmd_vboxmanage280(int argc, char args[][CMD_MAX_LEN]);
static void cmd_vmrun280(int argc, char args[][CMD_MAX_LEN]);
static void cmd_xen280(int argc, char args[][CMD_MAX_LEN]);
static void cmd_lxc280(int argc, char args[][CMD_MAX_LEN]);
static void cmd_systemd_nspawn280(int argc, char args[][CMD_MAX_LEN]);
static void cmd_firejail280(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bubblewrap280(int argc, char args[][CMD_MAX_LEN]);
static void cmd_proot280(int argc, char args[][CMD_MAX_LEN]);
static void cmd_chroot280(int argc, char args[][CMD_MAX_LEN]);
"""

b280_entries = """    /* Batch 280: Virtualization */
    {"virsh", cmd_virsh280}, {"virt-manager", cmd_virt_280}, {"qemu-img", cmd_qemu_280},
    {"VBoxManage", cmd_vboxmanage280}, {"vmrun", cmd_vmrun280}, {"xl", cmd_xen280},
    {"lxc", cmd_lxc280}, {"systemd-nspawn", cmd_systemd_nspawn280}, {"firejail", cmd_firejail280},
    {"bwrap", cmd_bubblewrap280}, {"proot", cmd_proot280}, {"chroot", cmd_chroot280},
"""

b280_funcs = """/* ===== Batch 280: Virtualization ===== */
static void cmd_virsh280(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: virsh <list|start|stop>\\n"); return; }
    if (strcmp(args[1], "list") == 0) {
        vga_puts(" Id   Name   State\\n");
        vga_puts(" 1    vm1    running\\n 2    vm2    shut off\\n");
    } else vga_printf("virsh: %s\\n", args[1]);
}
static void cmd_virt_280(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("virt-manager: virtual machine manager\\n");
    vga_puts("virt-manager: connecting to QEMU/KVM\\n");
}
static void cmd_qemu_280(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: qemu-img <info|create|convert>\\n"); return; }
    if (strcmp(args[1], "info") == 0 && argc >= 3) {
        vga_printf("image: %s\\nfile format: qcow2\\nvirtual size: 20G\\n", args[2]);
    } else vga_printf("qemu-img: %s\\n", args[1]);
}
static void cmd_vboxmanage280(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: VBoxManage <list|startvm>\\n"); return; }
    if (strcmp(args[1], "list") == 0) {
        vga_puts("Virtual machines:\\n  vm1 [running]\\n  vm2 [poweroff]\\n");
    } else vga_printf("VBoxManage: %s\\n", args[1]);
}
static void cmd_vmrun280(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: vmrun <start|stop|list>\\n"); return; }
    vga_printf("vmrun: %s\\n", args[1]);
}
static void cmd_xen280(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: xl <list|create|destroy>\\n"); return; }
    if (strcmp(args[1], "list") == 0) {
        vga_puts("Name     ID  Mem    VCPUs  State\\nvm1      1   1024   2      r-----\\n");
    } else vga_printf("xl: %s\\n", args[1]);
}
static void cmd_lxc280(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: lxc <list|start|stop>\\n"); return; }
    if (strcmp(args[1], "list") == 0) {
        vga_puts("NAME   STATE   AUTOSTART\\nweb    RUNNING yes\\n");
    } else vga_printf("lxc: %s\\n", args[1]);
}
static void cmd_systemd_nspawn280(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("systemd-nspawn: container runtime\\n");
    vga_puts("systemd-nspawn: booting container...\\n");
}
static void cmd_firejail280(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: firejail <command>\\n"); return; }
    vga_printf("firejail: sandboxing '%s'\\n", args[1]);
}
static void cmd_bubblewrap280(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("bwrap: bubblewrap sandbox\\n");
}
static void cmd_proot280(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: proot <command>\\n"); return; }
    vga_printf("proot: running '%s' in chroot\\n", args[1]);
}
static void cmd_chroot280(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: chroot <dir> <command>\\n"); return; }
    vga_printf("chroot: executing '%s' in %s\\n", args[2], args[1]);
}
"""

# ===== BATCH 281: Backup Tools =====
b281_decls = """static void cmd_rsync281(int argc, char args[][CMD_MAX_LEN]);
static void cmd_borg281(int argc, char args[][CMD_MAX_LEN]);
static void cmd_restic281(int argc, char args[][CMD_MAX_LEN]);
static void cmd_duplicity281(int argc, char args[][CMD_MAX_LEN]);
static void cmd_rclone281(int argc, char args[][CMD_MAX_LEN]);
static void cmd_mysqldump281(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pg_dumpall281(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dump281(int argc, char args[][CMD_MAX_LEN]);
static void cmd_restore281(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cpio281(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dd281(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pv281(int argc, char args[][CMD_MAX_LEN]);
"""

b281_entries = """    /* Batch 281: Backup Tools */
    {"rsync", cmd_rsync281}, {"borg", cmd_borg281}, {"restic", cmd_restic281},
    {"duplicity", cmd_duplicity281}, {"rclone", cmd_rclone281}, {"mysqldump2", cmd_mysqldump281},
    {"pg_dumpall", cmd_pg_dumpall281}, {"dump", cmd_dump281}, {"restore2", cmd_restore281},
    {"cpio", cmd_cpio281}, {"dd", cmd_dd281}, {"pv", cmd_pv281},
"""

b281_funcs = """/* ===== Batch 281: Backup Tools ===== */
static void cmd_rsync281(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: rsync <src> <dst>\\n"); return; }
    vga_printf("rsync: syncing %s -> %s\\n", args[1], args[2]);
    vga_puts("rsync: transferred 12.3MB, 156 files\\n");
}
static void cmd_borg281(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: borg <create|list|extract>\\n"); return; }
    if (strcmp(args[1], "create") == 0) vga_puts("borg: creating archive... done\\n");
    else if (strcmp(args[1], "list") == 0) vga_puts("borg: archive-2026-07-10  1.2GB\\n");
    else vga_printf("borg: %s\\n", args[1]);
}
static void cmd_restic281(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: restic <backup|list|restore>\\n"); return; }
    if (strcmp(args[1], "backup") == 0) vga_puts("restic: backup complete, 500MB written\\n");
    else vga_printf("restic: %s\\n", args[1]);
}
static void cmd_duplicity281(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: duplicity <backup|restore>\\n"); return; }
    vga_printf("duplicity: %s\\n", args[1]);
}
static void cmd_rclone281(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: rclone <copy|sync|ls>\\n"); return; }
    if (strcmp(args[1], "copy") == 0) vga_puts("rclone: copying files... done\\n");
    else vga_printf("rclone: %s\\n", args[1]);
}
static void cmd_mysqldump281(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: mysqldump <database>\\n"); return; }
    vga_printf("mysqldump: dumping %s\\n", args[1]);
    vga_puts("mysqldump: complete\\n");
}
static void cmd_pg_dumpall281(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("pg_dumpall: dumping all databases\\n");
    vga_puts("pg_dumpall: complete\\n");
}
static void cmd_dump281(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dump <device>\\n"); return; }
    vga_printf("dump: backing up %s\\n", args[1]);
    vga_puts("dump: 123456 blocks written\\n");
}
static void cmd_restore281(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: restore <backup>\\n"); return; }
    vga_printf("restore: restoring from %s\\n", args[1]);
}
static void cmd_cpio281(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("cpio: archive tool\\n");
    vga_puts("cpio: 1234 blocks\\n");
}
static void cmd_dd281(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: dd if=<src> of=<dst>\\n"); return; }
    vga_printf("dd: copying %s -> %s\\n", args[1], args[2]);
    vga_puts("dd: 1234567+0 records in\\ndd: 1234567+0 records out\\n");
}
static void cmd_pv281(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pv <file>\\n"); return; }
    vga_printf("pv: %s  [==>       ]  45%% 12.3MB/s\\n", args[1]);
}
"""

# ===== BATCH 282: More System Utilities =====
b282_decls = """static void cmd_irqbalance282(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tuned282(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cpupower282(int argc, char args[][CMD_MAX_LEN]);
static void cmd_powertop282(int argc, char args[][CMD_MAX_LEN]);
static void cmd_thermald282(int argc, char args[][CMD_MAX_LEN]);
static void cmd_lm_sensors282(int argc, char args[][CMD_MAX_LEN]);
static void cmd_numactl282(int argc, char args[][CMD_MAX_LEN]);
static void cmd_taskset282(int argc, char args[][CMD_MAX_LEN]);
static void cmd_chrt282(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ulimit282(int argc, char args[][CMD_MAX_LEN]);
static void cmd_limits282(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ionice282(int argc, char args[][CMD_MAX_LEN]);
"""

b282_entries = """    /* Batch 282: System Utilities */
    {"irqbalance", cmd_irqbalance282}, {"tuned", cmd_tuned282}, {"cpupower", cmd_cpupower282},
    {"powertop", cmd_powertop282}, {"thermald", cmd_thermald282}, {"sensors", cmd_lm_sensors282},
    {"numactl", cmd_numactl282}, {"taskset", cmd_taskset282}, {"chrt", cmd_chrt282},
    {"ulimit", cmd_ulimit282}, {"limits", cmd_limits282}, {"ionice", cmd_ionice282},
"""

b282_funcs = """/* ===== Batch 282: System Utilities ===== */
static void cmd_irqbalance282(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("irqbalance: balancing IRQs across CPUs\\n");
    vga_puts("irqbalance: balanced 12 IRQs\\n");
}
static void cmd_tuned282(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: tuned <profile>\\n"); return; }
    vga_printf("tuned: active profile: %s\\n", args[1]);
}
static void cmd_cpupower282(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cpupower <frequency-info|idle-info>\\n"); return; }
    vga_puts("cpupower: CPU frequency: 2400 MHz\\n");
    vga_puts("cpupower: governor: ondemand\\n");
}
static void cmd_powertop282(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("PowerTOP: power management\\n");
    vga_puts("  Package   |   C0     |   C1     |   C6\\n");
    vga_puts("  Avg residency: 15.2%  |  23.4%  |  61.4%\\n");
}
static void cmd_thermald282(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("thermald: thermal management daemon\\n");
    vga_puts("thermald: temperature: 45C (normal)\\n");
}
static void cmd_lm_sensors282(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("coretemp-isa-0000\\n");
    vga_puts("  Core 0: +45.0C\\n  Core 1: +43.0C\\n");
    vga_puts("acpitz-virtual-0\\n");
    vga_puts("  temp1: +42.0C\\n");
}
static void cmd_numactl282(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: numactl <command>\\n"); return; }
    vga_printf("numactl: binding to NUMA node 0\\n");
}
static void cmd_taskset282(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: taskset <mask> <command>\\n"); return; }
    vga_printf("taskset: binding to CPU mask %s\\n", args[1]);
}
static void cmd_chrt282(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: chrt <priority> <command>\\n"); return; }
    vga_printf("chrt: running with priority %s\\n", args[1]);
}
static void cmd_ulimit282(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ulimit: resource limits\\n");
    vga_puts("  core file size: unlimited\\n");
    vga_puts("  data seg size: unlimited\\n");
    vga_puts("  open files: 1024\\n");
    vga_puts("  max processes: 4096\\n");
}
static void cmd_limits282(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("limits: system resource limits\\n");
    vga_puts("  Max open files: 1024\\n  Max processes: 4096\\n");
}
static void cmd_ionice282(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ionice <command>\\n"); return; }
    vga_printf("ionice: scheduling class: best-effort, level 4\\n");
}
"""

# Inject
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b279_decls + b280_decls + b281_decls + b282_decls + decl_marker)

old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + \
    '    /* Batch 263: Network Utilities */'
new_entries = b279_entries + b280_entries + b281_entries + b282_entries
content = content.replace(old_entry, old_entry + new_entries, 1)

func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b279_funcs + b280_funcs + b281_funcs + b282_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)

print("Injected Batches 279-282 (48 new commands)")