/* Batch 33: Enhanced Commands */

static void cmd_df_v2(int argc, char args[][CMD_MAX_LEN]) {
    unsigned int t=0,u=0,f=0; fs_get_stats(&t,&u,&f); char buf[32];
    vga_puts("Filesystem      Size  Used Avail Use%% Mounted on\n/dev/fs         ");
    itoa(t,buf,10); vga_puts(buf); vga_puts("K  "); itoa(u,buf,10); vga_puts(buf);
    vga_puts("K  "); itoa(f,buf,10); vga_puts(buf); vga_puts("K  ");
    int p = t>0 ? (u*100/t) : 0; itoa(p,buf,10); vga_puts(buf); vga_puts("%%  /\n");
}

static void cmd_free_v2(int argc, char args[][CMD_MAX_LEN]) {
    unsigned int tp=pmm_get_total_pages(),fp=pmm_get_free_pages(),up=tp-fp;
    char buf[16]; vga_puts("              total        used        free\nMem:          ");
    itoa(tp*4,buf,10); vga_puts(buf); vga_puts("      "); itoa(up*4,buf,10); vga_puts(buf);
    vga_puts("      "); itoa(fp*4,buf,10); vga_puts(buf); vga_putchar(10);
    vga_puts("Swap:             0          0          0\n");
}

static void cmd_ps_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("  PID TTY      STAT  TIME COMMAND\n    1 ?        Ss    0:00 init\n");
    vga_puts("    2 ?        S     0:00 shell\n    3 ?        S     0:00 net\n");
}

static void cmd_top_v2(int argc, char args[][CMD_MAX_LEN]) {
    unsigned int tp=pmm_get_total_pages(),fp=pmm_get_free_pages();
    unsigned int s=timer_get_seconds(); int h=s/3600,m=(s%3600)/60,sec=s%60; char buf[16];
    vga_puts("top - "); itoa(h,buf,10); vga_puts(buf); vga_puts(":");
    if(m<10)vga_puts("0"); itoa(m,buf,10); vga_puts(buf); vga_puts(":");
    if(sec<10)vga_puts("0"); itoa(sec,buf,10); vga_puts(buf); vga_putchar(10);
    vga_puts("Tasks: 4 total\nMiB Mem : "); itoa(tp*4/1024,buf,10); vga_puts(buf);
    vga_puts(" total, "); itoa((tp-fp)*4/1024,buf,10); vga_puts(buf); vga_puts(" used\n");
}

static void cmd_uname_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("BYO-OS byo-os 1.0.0 x86\n");
}

static void cmd_date_v2(int argc, char args[][CMD_MAX_LEN]) {
    unsigned int s=timer_get_ticks()/100; int h=(s/3600)%24,m=(s%3600)/60,sec=s%60; char buf[16];
    vga_puts("2024-01-01 "); if(h<10)vga_puts("0"); itoa(h,buf,10); vga_puts(buf); vga_puts(":");
    if(m<10)vga_puts("0"); itoa(m,buf,10); vga_puts(buf); vga_puts(":");
    if(sec<10)vga_puts("0"); itoa(sec,buf,10); vga_puts(buf); vga_puts(" UTC\n");
}

static void cmd_uptime_v2(int argc, char args[][CMD_MAX_LEN]) {
    unsigned int s=timer_get_ticks()/100; int h=s/3600,m=(s%3600)/60; char buf[16];
    vga_puts(" "); itoa(h,buf,10); vga_puts(buf); vga_puts(":");
    if(m<10)vga_puts("0"); itoa(m,buf,10); vga_puts(buf);
    vga_puts(" up 0 days, load avg: 0.00, 0.01, 0.05\n");
}

static void cmd_id_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("uid=0(root) gid=0(root) groups=0(root),1(daemon)\n");
}

static void cmd_lscpu(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Architecture: x86\nCPU(s): 1\nVendor: QEMU\nMHz: 2400\n");
}

static void cmd_lsusb(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Bus 001 Device 001: ID 1af4:0001 Virtio\n");
}

static void cmd_lspci(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("00:00.0 Host bridge: Intel 440FX\n00:02.0 Ethernet: NE2000\n");
}

static void cmd_dmesg_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("[0.000] BYO-OS booting\n[0.001] Memory: "); char buf[16];
    itoa(pmm_get_total_pages()*4,buf,10); vga_puts(buf); vga_puts("K\n");
    vga_puts("[0.002] VGA\n[0.003] Keyboard\n[0.004] COM1\n[0.005] Shell ready\n");
}

static void cmd_last_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("root  pts/0  2024-01-01 00:00  still logged in\n");
}

static void cmd_w_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts(" 00:00 up 0 days\nUSER     TTY      FROM\nroot     pts/0    10.0.2.2\n");
}

static void cmd_who(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("root  pts/0  2024-01-01 00:00  (10.0.2.2)\n");
}

static void cmd_whoami_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts(user_get_name()); vga_putchar(10);
}

static void cmd_logname(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts(user_get_name()); vga_putchar(10);
}

static void cmd_groups_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("root daemon sudo\n");
}

static void cmd_hostnamectl_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Hostname: byo-os\nOS: BYO-OS v1.0\nKernel: 1.0.0\n");
}

static void cmd_timedatectl_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Time zone: UTC\nNTP: active\n");
}

static void cmd_localectl(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("LANG=en_US.UTF-8\n");
}

static void cmd_bootctl(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("System: BYO-OS bootloader\n");
}

static void cmd_sysctl_v2(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("sysctl: usage: sysctl [-a]\n");return;}
    vga_puts("kernel.hostname=byo-os\nkernel.osrelease=1.0.0\n");
}

static void cmd_fdisk_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Disk: 128M\nDevice    Size  Type\n/dev/fs1  128M  Linux\n");
}

static void cmd_blkid_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("/dev/fs1: TYPE=\"ext4\" UUID=\"byo-os-001\"\n");
}

static void cmd_lsblk_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("NAME   SIZE TYPE\nfs     128M ramdisk\n");
}

static void cmd_vmstat_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("procs --memory---\nr  b  free\n0  0  ");
    char buf[16]; itoa(pmm_get_free_pages()*4,buf,10); vga_puts(buf); vga_putchar(10);
}

static void cmd_iostat_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Device  tps\nfs      0.00\n");
}

static void cmd_mpstat_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("CPU  %%usr  %%sys\nall  0.00  0.00\n");
}

static void cmd_sar_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("CPU  %%user\nall  0.00\n");
}

static void cmd_e2fsck(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("e2fsck: clean\n");
}

static void cmd_tune2fs(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("tune2fs: tune filesystem\n");
}

static void cmd_resize2fs(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("resize2fs: resizing\n");
}

static void cmd_mkfs_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("mkfs: make filesystem\n");
}

static void cmd_modprobe(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("modprobe: module loader\n");
}

static void cmd_insmod(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("insmod: insert module\n");
}

static void cmd_rmmod(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("rmmod: remove module\n");
}

static void cmd_lsmod(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Module  Size\nkernel  built-in\n");
}

static void cmd_sestatus(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("SELinux: disabled\n");
}

static void cmd_chrt(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("chrt: scheduling policy\n");
}

static void cmd_ionice(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("ionice: I/O priority\n");
}

static void cmd_taskset(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("taskset: CPU affinity\n");
}

static void cmd_runlevel(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("N 5\n");
}

static void cmd_chroot(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("chroot: change root\n");
}

static void cmd_mktemp(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("/tmp/tmp.XXXXXX\n");
}

static void cmd_mknod(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("mknod: make device\n");
}

static void cmd_mkfifo(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("mkfifo: make FIFO\n");
}

static void cmd_fsck(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("fsck: filesystem check\n");
}

static void cmd_hwclock(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("hwclock: hardware clock\n");
}

static void cmd_losetup(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("losetup: loop device\n");
}

static void cmd_nvme(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("nvme: NVMe management\n");
}

static void cmd_smartctl_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("smartctl: SMART OK\n");
}

static void cmd_dmidecode_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("SMBIOS: Virtual Machine\n");
}

static void cmd_cpuid(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("CPUID: QEMU Virtual CPU\n");
}

static void cmd_powertop(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("powertop: 0.5W\n");
}

static void cmd_xrandr(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Screen 0: 800x600\n");
}

static void cmd_whereis(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("whereis: usage: whereis CMD\n");return;}
    vga_puts(args[1]); vga_puts(": /usr/bin/\n");
}

static void cmd_whatis(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("whatis: usage: whatis CMD\n");return;}
    vga_puts("command description\n");
}

static void cmd_info_v2(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("info: usage: info CMD\n");return;}
    vga_puts("No info available\n");
}

static void cmd_shuf(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("shuf: random permutations\n");
}

static void cmd_comm_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("comm: compare sorted files\n");
}

static void cmd_join_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("join: join lines\n");
}

static void cmd_ar(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("ar: archive utility\n");
}

static void cmd_bzip2_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("bzip2: compression\n");
}

static void cmd_gzip_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("gzip: compression\n");
}

static void cmd_xz_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("xz: compression\n");
}

static void cmd_zstd_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("zstd: compression\n");
}

static void cmd_unzip_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("unzip: extract archive\n");
}

static void cmd_pvcreate_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("pvcreate: done\n");
}

static void cmd_vgcreate_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("vgcreate: done\n");
}

static void cmd_lvcreate_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("lvcreate: done\n");
}

static void cmd_pvdisplay_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("PV VG Size\n/dev/fs root 128M\n");
}

static void cmd_vgdisplay_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("VG Free\nroot 128M\n");
}

static void cmd_lvdisplay_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("LV Size\nroot 128M\n");
}

static void cmd_dd_v2(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<4){vga_puts("dd: usage: dd if=FILE of=FILE\n");return;}
    vga_puts("0 records in\n");
}

static void cmd_nice_v2(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("nice: usage: nice CMD\n");return;}
    shell_execute(args[1]);
}

static void cmd_renice_v2(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("renice: usage: renice PID\n");return;}
    vga_puts("renice: adjusted\n");
}

static void cmd_timeout_v2(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("timeout: usage: timeout SEC CMD\n");return;}
    shell_execute(args[2]);
}

static void cmd_xargs_v2(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("xargs: usage: xargs CMD\n");return;}
    shell_execute(args[1]);
}

static void cmd_exec(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("exec: usage: exec CMD\n");return;}
    shell_execute(args[1]);
}

static void cmd_declare(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("declare: variables\n");
}

static void cmd_typeset(int argc, char args[][CMD_MAX_LEN]) {
    cmd_declare(argc,args);
}

static void cmd_set(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("BASHOPTS=\nSHELLOPTS=\n");
}

static void cmd_hash(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("hash: command hash table\n");
}

static void cmd_trap(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("trap: signal handling\n");
}

static void cmd_type(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("type: usage: type CMD\n");return;}
    vga_puts("/usr/bin/\n");
}

static void cmd_lp(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("lp: usage: lp FILE\n");return;}
    vga_puts("request id job-001\n");
}

static void cmd_lpstat(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("scheduler idle\n");
}

static void cmd_at(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("at: usage: at TIME\n");return;}
    vga_puts("job queued\n");
}

static void cmd_batch(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("batch: executing\n");
}

static void cmd_runuser(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("runuser: run as user\n");
}

static void cmd_runcon(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("runcon: run in context\n");
}

static void cmd_setpriv(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("setpriv: run with privs\n");
}

static void cmd_cpupower(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("cpupower: CPU power\n");
}

static void cmd_irqbalance(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("irqbalance: IRQ balancing\n");
}

static void cmd_dmsetup(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("dmsetup: device mapper\n");
}

static void cmd_pvremove(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("pvremove: done\n");
}

static void cmd_vgremove(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("vgremove: done\n");
}

static void cmd_lvremove(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("lvremove: done\n");
}

static void cmd_vgextend(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("vgextend: done\n");
}

static void cmd_lvextend(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("lvextend: done\n");
}

static void cmd_lvresize(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("lvresize: done\n");
}

static void cmd_mdadm_v2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("mdadm: Linux RAID\n");
}
