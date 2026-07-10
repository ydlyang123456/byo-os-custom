/* BYO-OS - ProcFS: Virtual /proc filesystem (x86_64)
 * 
 * Dynamically generates /proc/cpuinfo, /proc/meminfo, /proc/uptime,
 * /proc/version, /proc/stat, /proc/self/status, etc.
 * Allows shell "cat /proc/meminfo" style access.
 */
#include <kernel.h>
#include <stdint.h>

/* Maximum size of a dynamically generated /proc file */
#define PROCFS_MAX 4096

/* Buffer used to generate /proc content */
static char proc_buf[PROCFS_MAX];

/* Forward declarations from kernel modules */
extern uint64_t pmm_get_total_pages_64(void);
extern uint64_t pmm_get_free_pages_64(void);
extern uint64_t pmm_get_used_pages_64(void);
extern uint64_t pmm_get_memory_size(void);
extern uint64_t heap_get_used_64(void);

extern uint32_t timer_get_ticks(void);
extern uint32_t timer_get_seconds(void);

/* Generate /proc/cpuinfo - emulate Debian 12 output */
static const char* proc_generate_cpuinfo(void) {
    int pos = 0;
    pos += sprintf(proc_buf + pos,
        "processor\t: 0\n"
        "vendor_id\t: GenuineIntel\n"
        "cpu family\t: 6\n"
        "model\t\t: 158\n"
        "model name\t: BYO-OS Virtual CPU (x86_64)\n"
        "stepping\t: 10\n"
        "microcode\t: 0x1\n"
        "cpu MHz\t\t: 2400.000\n"
        "cache size\t: 4096 KB\n"
        "physical id\t: 0\n"
        "siblings\t: %d\n"
        "core id\t\t: 0\n"
        "cpu cores\t: %d\n"
        "apicid\t\t: 0\n"
        "initial apicid\t: 0\n"
        "fpu\t\t: yes\n"
        "fpu_exception\t: yes\n"
        "cpuid level\t: 13\n"
        "wp\t\t: yes\n"
        "flags\t\t: fpu vme de pse tsc msr pae mce cx8 apic sep "
        "mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ss "
        "ht syscall nx rdtscp lm constant_tsc rep_good nopl xtopology "
        "cpuid tsc_known_freq pni pclmulqdq ssse3 fma cx16 pcid "
        "sse4_1 sse4_2 x2apic movbe popcnt aes xsave avx f16c "
        "rdrand hypervisor lahf_lm abm 3dnowprefetch cpuid_fault "
        "invpcid_single pti ssbd ibrs ibpb stibp fsgsbase bmi1 "
        "avx2 smep bmi2 erms invpcid avx512f avx512dq rdseed adx "
        "smap avx512ifma clflushopt clwb avx512cd sha_ni avx512bw "
        "avx512vl xsaveopt xsavec xgetbv1 xsaves arat umip pku "
        "ospke avx512_vnni md_clear arch_capabilities\n"
        "bugs\t\t: spectre_v1 spectre_v2 spec_store_bypass mds swapgs\n"
        "bogomips\t: 4800.00\n"
        "TLB size\t: 3072 4K pages\n"
        "clflush size\t: 64\n"
        "cache_alignment\t: 64\n"
        "address sizes\t: 46 bits physical, 48 bits virtual\n"
        "power management\t:\n",
        1, 1);
    proc_buf[pos] = 0;
    return proc_buf;
}

/* Generate /proc/meminfo */
static const char* proc_generate_meminfo(void) {
    uint64_t total_bytes = pmm_get_memory_size();
    uint64_t free_bytes = pmm_get_free_pages_64() * 4096;
    uint64_t used_bytes = pmm_get_used_pages_64() * 4096;
    uint64_t heap_used = heap_get_used_64();
    uint64_t heap_total = heap_get_used_64() + 4096;
    
    int pos = 0;
    pos += sprintf(proc_buf + pos,
        "MemTotal:        %lu kB\n"
        "MemFree:         %lu kB\n"
        "MemAvailable:    %lu kB\n"
        "Buffers:         %llu kB\n"
        "Cached:          %llu kB\n"
        "SwapCached:      0 kB\n"
        "Active:          %lu kB\n"
        "Inactive:        %lu kB\n"
        "Active(anon):    %lu kB\n"
        "Inactive(anon):  0 kB\n"
        "Active(file):    0 kB\n"
        "Inactive(file):  0 kB\n"
        "Unevictable:     0 kB\n"
        "Mlocked:         0 kB\n"
        "SwapTotal:       0 kB\n"
        "SwapFree:        0 kB\n"
        "Dirty:           0 kB\n"
        "Writeback:       0 kB\n"
        "AnonPages:       0 kB\n"
        "Mapped:          0 kB\n"
        "Shmem:           0 kB\n"
        "Slab:            %lu kB\n"
        "SReclaimable:    %lu kB\n"
        "SUnreclaim:      %lu kB\n"
        "KernelStack:     0 kB\n"
        "PageTables:      0 kB\n"
        "NFS_Unstable:    0 kB\n"
        "Bounce:          0 kB\n"
        "WritebackTmp:    0 kB\n"
        "CommitLimit:     %lu kB\n"
        "Committed_AS:    0 kB\n"
        "VmallocTotal:    0 kB\n"
        "VmallocUsed:     0 kB\n"
        "VmallocChunk:    0 kB\n"
        "HardwareCorrupted: 0 kB\n"
        "AnonHugePages:   0 kB\n"
        "ShmemHugePages:  0 kB\n"
        "ShmemPmdMapped:  0 kB\n"
        "HugePages_Total: 0\n"
        "HugePages_Free:  0\n"
        "HugePages_Rsvd:  0\n"
        "HugePages_Surp:  0\n"
        "Hugepagesize:    2048 kB\n"
        "Hugetlb:         0 kB\n"
        "DirectMap4k:     %lu kB\n"
        "DirectMap2M:     %lu kB\n"
        "DirectMap1G:     0 kB\n",
        (unsigned long)(total_bytes / 1024),
        (unsigned long)(free_bytes / 1024),
        (unsigned long)((free_bytes + used_bytes/2) / 1024),
        (unsigned long long)(used_bytes * 3 / 100 / 1024),
        (unsigned long long)(used_bytes * 5 / 100 / 1024),
        (unsigned long)(used_bytes / 1024),
        (unsigned long)(used_bytes * 2 / 3 / 1024),
        (unsigned long)(used_bytes / 3 / 1024),
        (unsigned long)((heap_used + 1023) / 1024),
        (unsigned long)((heap_total + 1023) / 1024),
        (unsigned long)((total_bytes / 2) / 1024),
        (unsigned long)(total_bytes / 1024),
        (unsigned long)(total_bytes / 1024));
    proc_buf[pos] = 0;
    return proc_buf;
}

/* Generate /proc/uptime */
static const char* proc_generate_uptime(void) {
    uint32_t secs = timer_get_seconds();
    uint32_t idle = secs; /* Approximate idle = uptime for single task */
    sprintf(proc_buf, "%u.%02u %u.%02u\n", secs, 0, idle, 0);
    return proc_buf;
}

/* Generate /proc/version */
static const char* proc_generate_version(void) {
    sprintf(proc_buf,
        "Linux version 6.1.0-byo-os (root@byo-os) (gcc (Debian 12.2.0-14) 12.2.0) "
        "#1 SMP PREEMPT_DYNAMIC BYO-OS x86_64 GNU/Linux\n");
    return proc_buf;
}

/* Generate /proc/stat - simplified CPU stats */
static const char* proc_generate_stat(void) {
    uint32_t ticks = timer_get_ticks();
    uint32_t secs = timer_get_seconds();
    /* Simulate realistic looking /proc/stat */
    sprintf(proc_buf,
        "cpu  %u %u %u %u %u %u %u %u %u %u\n"
        "cpu0 %u %u %u %u %u %u %u %u %u %u\n"
        "intr %u %u %u %u %u %u %u %u\n"
        "ctxt %u\n"
        "btime %u\n"
        "processes %u\n"
        "procs_running 1\n"
        "procs_blocked 0\n",
        ticks/10, ticks/20, ticks/30, ticks*9/10, 0, 0, 0, 0, 0, 0,
        ticks/10, ticks/20, ticks/30, ticks*9/10, 0, 0, 0, 0, 0, 0,
        ticks/5, ticks/8, ticks/12, ticks/15, ticks/3, ticks/7, ticks/11, 0,
        ticks/2,
        secs,
        ticks/100);
    return proc_buf;
}

/* Generate /proc/loadavg */
static const char* proc_generate_loadavg(void) {
    uint32_t ticks = timer_get_ticks();
    float l1 = (float)(ticks % 100) / 100.0f;
    float l5 = (float)((ticks/5) % 100) / 100.0f;
    float l15 = (float)((ticks/15) % 100) / 100.0f;
    sprintf(proc_buf, "%.2f %.2f %.2f %u/%u %u\n",
        (double)l1, (double)l5, (double)l15, 1, 1, ticks % 10000);
    return proc_buf;
}

/* Generate /proc/self/status */
static const char* proc_generate_self_status(void) {
    sprintf(proc_buf,
        "Name:\tsh\n"
        "Umask:\t0022\n"
        "State:\tS (sleeping)\n"
        "Tgid:\t1\n"
        "Ngid:\t0\n"
        "Pid:\t1\n"
        "PPid:\t0\n"
        "TracerPid:\t0\n"
        "Uid:\t0\t0\t0\t0\n"
        "Gid:\t0\t0\t0\t0\n"
        "FDSize:\t64\n"
        "Groups:\t0 \n"
        "NSTgid:\t1\n"
        "NSpid:\t1\n"
        "NSpgid:\t1\n"
        "NSsid:\t1\n"
        "VmPeak:\t    16384 kB\n"
        "VmSize:\t    16384 kB\n"
        "VmLck:\t         0 kB\n"
        "VmPin:\t         0 kB\n"
        "VmHWM:\t      4096 kB\n"
        "VmRSS:\t      4096 kB\n"
        "RssAnon:\t     512 kB\n"
        "RssFile:\t    3584 kB\n"
        "RssShmem:\t       0 kB\n"
        "VmData:\t     4096 kB\n"
        "VmStk:\t       132 kB\n"
        "VmExe:\t      1024 kB\n"
        "VmLib:\t      2048 kB\n"
        "VmPTE:\t        72 kB\n"
        "VmSwap:\t         0 kB\n"
        "Threads:\t1\n"
        "SigQ:\t0/1000\n"
        "SigPnd:\t0000000000000000\n"
        "ShdPnd:\t0000000000000000\n"
        "SigBlk:\t0000000000000000\n"
        "SigIgn:\t0000000000000000\n"
        "SigCgt:\t0000000000000000\n"
        "CapInh:\t0000000000000000\n"
        "CapPrm:\t0000003fffffffff\n"
        "CapEff:\t0000003fffffffff\n"
        "CapBnd:\t0000003fffffffff\n"
        "CapAmb:\t0000000000000000\n"
        "NoNewPrivs:\t0\n"
        "Seccomp:\t0\n"
        "Seccomp_filters:\t0\n"
        "Speculation_Store_Bypass:\tthread vulnerable\n"
        "SpeculationIndirectBranch:\talways enabled\n"
        "Cpus_allowed:\t1\n"
        "Cpus_allowed_list:\t0\n"
        "Mems_allowed:\t1\n"
        "Mems_allowed_list:\t0\n"
        "voluntary_ctxt_switches:\t12\n"
        "nonvoluntary_ctxt_switches:\t3\n");
    return proc_buf;
}

/* Generate /proc/filesystems */
static const char* proc_generate_filesystems(void) {
    sprintf(proc_buf,
        "nodev\tsysfs\n"
        "nodev\ttmpfs\n"
        "nodev\tproc\n"
        "nodev\tdevtmpfs\n"
        "nodev\tdevpts\n"
        "\text2\n"
        "\text3\n"
        "\text4\n"
        "\tfat\n"
        "nodev\trpc_pipefs\n"
        "nodev\tnfsd\n");
    return proc_buf;
}

/* Generate /proc/devices */
static const char* proc_generate_devices(void) {
    sprintf(proc_buf,
        "Character devices:\n"
        "  1 mem\n"
        "  4 tty\n"
        "  5 /dev/tty\n"
        "  6 lp\n"
        "  7 vcs\n"
        " 10 misc\n"
        " 13 input\n"
        " 29 fb\n"
        " 90 mtd\n"
        "116 alsa\n"
        "180 usb\n"
        "189 usb_device\n"
        "253 vfio\n"
        "254 gpiochip\n\n"
        "Block devices:\n"
        "  1 ramdisk\n"
        "  2 fd\n"
        "  8 sd\n"
        " 11 sr\n"
        " 65 sd\n"
        "252 device-mapper\n"
        "253 virtblk\n");
    return proc_buf;
}

/* Generate /proc/self/environ */
static const char* proc_generate_self_environ(void) {
    sprintf(proc_buf,
        "HOME=/root\0"
        "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin\0"
        "LOGNAME=root\0"
        "USER=root\0"
        "SHELL=/bin/sh\0"
        "TERM=linux\0"
        "LANG=C\0"
        "PWD=/\0");
    return proc_buf;
}

/* Generate /proc/self/mounts */
static const char* proc_generate_self_mounts(void) {
    sprintf(proc_buf,
        "rootfs / rootfs rw 0 0\n"
        "proc /proc proc rw,relatime 0 0\n"
        "tmpfs /tmp tmpfs rw,nosuid,nodev 0 0\n"
        "sysfs /sys sysfs rw,nosuid,nodev,noexec 0 0\n");
    return proc_buf;
}

/* Generate /proc/self/cgroup */
static const char* proc_generate_cgroup(void) {
    sprintf(proc_buf,
        "0::/\n");
    return proc_buf;
}

/* Generate /proc/sched_debug */
static const char* proc_generate_sched_debug(void) {
    sprintf(proc_buf,
        "Sched Debug Version: v0.11, %s, nr_queues: 1\n"
        "now                    : %u.%06u\n\n"
        "CPU: 0\n"
        "  .nr_running          : 1\n"
        "  .nr_switches         : %u\n"
        "  .nr_load_updates    : %u\n"
        "  .nr_unintended       : 0\n"
        "  .next_balance        : 0.000000\n"
        "  .curr->pid           : 1\n"
        "  .clock               : %u\n"
        "  .avg_idle            : 1000000\n"
        "  .max_idle_balance_cost: 0\n"
        "  .idle_cpu            : 0\n"
        "  .idle_state          : IDLE\n"
        "  .blocked_load_avg    : 0.00\n"
        "  .avg_load_per_task   : 0.00\n",
        "x86_64 BYO-OS",
        timer_get_ticks(), timer_get_ticks() % 1000000,
        timer_get_ticks() / 10,
        timer_get_ticks() / 20,
        timer_get_ticks());
    return proc_buf;
}

/* ===== Public API ===== */

/* Main procfs read handler - called by fs_read_file for /proc paths */
int procfs_read(const char* path, char* buf, uint32_t max_len) {
    const char* content = NULL;
    
    if (strcmp(path, "/proc/cpuinfo") == 0)           content = proc_generate_cpuinfo();
    else if (strcmp(path, "/proc/meminfo") == 0)       content = proc_generate_meminfo();
    else if (strcmp(path, "/proc/uptime") == 0)        content = proc_generate_uptime();
    else if (strcmp(path, "/proc/version") == 0)       content = proc_generate_version();
    else if (strcmp(path, "/proc/stat") == 0)          content = proc_generate_stat();
    else if (strcmp(path, "/proc/loadavg") == 0)       content = proc_generate_loadavg();
    else if (strcmp(path, "/proc/self/status") == 0)   content = proc_generate_self_status();
    else if (strcmp(path, "/proc/filesystems") == 0)   content = proc_generate_filesystems();
    else if (strcmp(path, "/proc/devices") == 0)        content = proc_generate_devices();
    else if (strcmp(path, "/proc/self/environ") == 0)  content = proc_generate_self_environ();
    else if (strcmp(path, "/proc/self/mounts") == 0)   content = proc_generate_self_mounts();
    else if (strcmp(path, "/proc/self/cgroup") == 0)   content = proc_generate_cgroup();
    else if (strcmp(path, "/proc/sched_debug") == 0)   content = proc_generate_sched_debug();
    else return -1; /* Not found */

    if (!content) return -1;
    uint32_t len = strlen(content);
    if (len > max_len) len = max_len;
    memcpy(buf, content, len);
    return len;
}

/* Register /proc virtual files into the FS */
void procfs_init(void) {
    /* Create /proc directory */
    fs_create_dir("proc");
    fs_create_dir("proc/self");
    fs_create_dir("proc/sys");
    fs_create_dir("proc/sys/net");
    fs_create_dir("proc/sys/net/ipv4");
    fs_create_dir("proc/sys/kernel");
    fs_create_dir("proc/sys/vm");
    
    /* Create placeholder files - content generated dynamically */
    fs_create_file("/proc/cpuinfo", "dynamic", 8);
    fs_create_file("/proc/meminfo", "dynamic", 8);
    fs_create_file("/proc/uptime", "dynamic", 8);
    fs_create_file("/proc/version", "dynamic", 8);
    fs_create_file("/proc/stat", "dynamic", 8);
    fs_create_file("/proc/loadavg", "dynamic", 8);
    fs_create_file("/proc/filesystems", "dynamic", 8);
    fs_create_file("/proc/devices", "dynamic", 8);
    fs_create_file("/proc/sched_debug", "dynamic", 8);
    fs_create_file("/proc/self/status", "dynamic", 8);
    fs_create_file("/proc/self/environ", "dynamic", 8);
    fs_create_file("/proc/self/mounts", "dynamic", 8);
    fs_create_file("/proc/self/cgroup", "dynamic", 8);
    
    serial_puts("[PROCFS] Virtual /proc filesystem initialized\n");
    vga_puts("[PROCFS] /proc: cpuinfo, meminfo, stat, version...\n");
}
