/* ===== Batch 48: Security, Container, Dev, DB, Media ===== */
static void cmd_iptables48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("iptables: firewall administration\nUsage: iptables -L\n"); return; }
    if (strcmp(args[1], "-L") == 0) {
        vga_puts("Chain INPUT (policy ACCEPT)\ntarget  prot opt source      destination\nACCEPT  all  --  anywhere    anywhere\n");
        vga_puts("Chain FORWARD (policy ACCEPT)\ntarget  prot opt source      destination\n");
        vga_puts("Chain OUTPUT (policy ACCEPT)\ntarget  prot opt source      destination\n");
    } else { vga_puts("iptables: option not supported\n"); }
}
static void cmd_nft48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("nftables v1.0.7\n");
    vga_puts("table ip filter {\n  chain input { type filter hook input priority 0; }\n  chain forward { type filter hook forward priority 0; }\n}\n");
}
static void cmd_ufw48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ufw <status|enable|disable|allow|deny>\n"); return; }
    if (strcmp(args[1], "status") == 0) vga_puts("Status: active\n\nTo                         Action      From\n--                         ------      ----\n22/tcp                     ALLOW       Anywhere\n80/tcp                     ALLOW       Anywhere\n");
    else if (strcmp(args[1], "allow") == 0) { vga_puts("Rule added\n"); }
    else if (strcmp(args[1], "deny") == 0) { vga_puts("Rule added\n"); }
    else vga_puts("ufw: unknown command\n");
}
static void cmd_fail2ban48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Status\n|- Number of jail:      1\n- Filter\n   |- Currently failed:  0\n   |- Total failed:      0\n   - Journal list:      empty\n");
}
static void cmd_auditctl48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("auditctl: audit rule management\nUsage: auditctl -l\n"); return; }
    vga_puts("-w /etc/passwd -p wa -k passwd_changes\n-w /etc/shadow -p wa -k shadow_changes\n-w /var/log -p wa -k log_access\n");
}
static void cmd_aureport48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Summary Report\nDate Range  Event Range\n----------- ----------------\n2025-01-15  2025-01-15\n\nTotal: 0 events\nFailed: 0 events\n");
}
static void cmd_pamtester48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("pamtester: PAM authentication tester\nUsage: pamtester <service> <user> authenticate\n");
}
static void cmd_sssd48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("SSSD version: 2.9.1\nDomain status: online\nId Provider: ldap\nAuth Provider: ldap\n");
}
static void cmd_selinux48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("SELinux status: enabled\nSELinuxfs mount: /sys/fs/selinux\nSELinux root directory: /etc/selinux\nCurrent mode: enforcing\nMode from config file: enforcing\n");
}
static void cmd_apparmor48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("apparmor module is loaded.\n18 profiles are loaded.\n17 profiles are in enforce mode.\n1 profiles are in complain mode.\n");
}

/* Container tools */
static void cmd_docker48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("docker: container runtime\nUsage: docker <run|ps|images|pull|stop|rm>\n"); return; }
    if (strcmp(args[1], "ps") == 0) {
        vga_puts("CONTAINER ID  IMAGE         COMMAND        STATUS        PORTS\na1b2c3d4e5f6  nginx:latest  /docker-entry  Up 2 hours    80/tcp\n");
    } else if (strcmp(args[1], "images") == 0) {
        vga_puts("REPOSITORY   TAG     IMAGE ID      SIZE\nnginx        latest  a1b2c3d4e5f6  187MB\nubuntu       22.04   f6e7c3d4e5f6  77.8MB\n");
    } else if (strcmp(args[1], "run") == 0) {
        if (argc < 3) { vga_puts("docker: image name required\n"); return; }
        vga_puts("Unable to find image '"); vga_puts(args[2]); vga_puts("' locally\nPulling from library/"); vga_puts(args[2]); vga_puts("\n");
        vga_puts("Status: Downloaded newer image\n");
        vga_puts("CONTAINER ID  IMAGE         COMMAND        STATUS\nb2c3d4e5f6a7  "); vga_puts(args[2]); vga_puts("   /bin/bash     Up 0 seconds\n");
    } else if (strcmp(args[1], "pull") == 0) {
        vga_puts("Using default tag: latest\nPulling from library/"); vga_puts(argc > 2 ? args[2] : "nginx"); vga_puts("\nPull complete\nStatus: Downloaded\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_puts("Stopped container\n");
    } else if (strcmp(args[1], "rm") == 0) {
        vga_puts("Removed container\n");
    } else { vga_puts("docker: unknown command\n"); }
}
static void cmd_podman48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("podman: daemonless container engine\nUsage: podman <run|ps|images|pull>\n"); return; }
    if (strcmp(args[1], "ps") == 0) {
        vga_puts("CONTAINER ID  IMAGE         COMMAND        STATUS        PORTS\nc3d4e5f6a7b8  alpine:latest /bin/sh         Up 1 hour\n");
    } else if (strcmp(args[1], "images") == 0) {
        vga_puts("REPOSITORY   TAG     IMAGE ID      SIZE\nalpine       latest  c3d4e5f6a7b8  7.8MB\n");
    } else vga_puts("podman: unknown command\n");
}
static void cmd_lxc48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("lxc: Linux container management\nUsage: lxc <list|info|start|stop|create>\n"); return; }
    if (strcmp(args[1], "list") == 0) {
        vga_puts("+---------+---------+------+-----------+-----------+\n| NAME    | STATE   | IPV4 | AUTOSTART | GROUPS    |\n+---------+---------+------+-----------+-----------+\n| web     | RUNNING | 10.0 | yes       |           |\n| db      | RUNNING | 10.1 | yes       |           |\n+---------+---------+------+-----------+-----------+\n");
    } else vga_puts("lxc: command executed\n");
}
static void cmd_lxd48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("lxd: container and VM management daemon\nUsage: lxd init|list|launch|start|stop\n");
}
static void cmd_kubectl48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("kubectl: Kubernetes CLI\nUsage: kubectl <get|describe|logs|exec|create>\n"); return; }
    if (strcmp(args[1], "get") == 0 && argc > 2 && strcmp(args[2], "pods") == 0) {
        vga_puts("NAME                    READY   STATUS    RESTARTS   AGE\nnginx-6d7b8c9f4-x2j5k   1/1     Running   0          2h\nredis-5d7f8b9c4-m3n6p    1/1     Running   0          1h\n");
    } else if (strcmp(args[1], "get") == 0 && argc > 2 && strcmp(args[2], "nodes") == 0) {
        vga_puts("NAME       STATUS   ROLES           AGE   VERSION\nnode-1     Ready    control-plane   30d   v1.28.0\nnode-2     Ready    <none>          30d   v1.28.0\n");
    } else if (strcmp(args[1], "get") == 0 && argc > 2 && strcmp(args[2], "services") == 0) {
        vga_puts("NAME         TYPE        CLUSTER-IP     PORT(S)   AGE\nkubernetes   ClusterIP   10.96.0.1       443/TCP   30d\nnginx-svc    NodePort    10.96.100.200   80:30080  2h\n");
    } else { vga_puts("kubectl: command executed\n"); }
}
static void cmd_helm48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("helm: Kubernetes package manager\nUsage: helm <list|search|install|upgrade|rollback>\n"); return; }
    if (strcmp(args[1], "list") == 0) {
        vga_puts("NAME        NAMESPACE  REVISION  STATUS    CHART       APP VERSION\nmy-release  default    1         deployed  nginx-1.0   1.24.0\n");
    } else { vga_puts("helm: command executed\n"); }
}

/* Virtualization */
static void cmd_virsh48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("virsh: libvirt management\nUsage: virsh <list|start|shutdown|reboot|info>\n"); return; }
    if (strcmp(args[1], "list") == 0) {
        vga_puts(" Id   Name         State\n---------------------------\n  1   byo-vm       running\n  2   test-vm      shut off\n");
    } else if (strcmp(args[1], "info") == 0) {
        vga_puts("CPU model: x86_64\nCPU(s): 4\nCPU frequency: 2400 MHz\nTotal memory: 8192 MiB\nFree memory: 4096 MiB\n");
    } else { vga_puts("virsh: command executed\n"); }
}
static void cmd_virt48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("virt-install: create VM\nUsage: virt-install --name <vm> --memory <mb> --disk <size>\n");
}
static void cmd_virtmanager48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("virt-manager: desktop GUI for managing virtual machines\n");
}

/* Development tools */
static void cmd_git48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("git: version control\nUsage: git <clone|init|add|commit|push|pull|status|log|diff>\n"); return; }
    if (strcmp(args[1], "status") == 0) {
        vga_puts("On branch master\nnothing to commit, working tree clean\n");
    } else if (strcmp(args[1], "log") == 0) {
        vga_puts("commit a1b2c3d4e5f6 (HEAD -> master)\nAuthor: root <root@byo-os>\nDate: Mon Jan 15 12:00:00 2025\n\n    Initial commit\n");
    } else if (strcmp(args[1], "diff") == 0) {
        vga_puts("No diff - working tree clean\n");
    } else { vga_puts("git: command executed\n"); }
}
static void cmd_make48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("make: build automation\nUsage: make <target>\n"); return; }
    if (strcmp(args[1], "-j4") == 0 || argc == 1) {
        vga_puts("make: Entering directory '/build'\ngcc -o main main.c\nmake: Leaving directory '/build'\n");
    } else {
        vga_puts("make: '"); vga_puts(args[1]); vga_puts("' is up to date.\n");
    }
}
static void cmd_cmake48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("CMake version 3.25.1\n-- Configuring done\n-- Generating done\n-- Build files have been written to: /build\n");
}
static void cmd_gdb48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("gdb: GNU debugger\nUsage: gdb <executable>\n"); return; }
    vga_puts("GNU gdb (GDB) 13.2\nReading symbols from "); vga_puts(args[1]); vga_puts("...\n(gdb) run\nStarting program: "); vga_puts(args[1]); vga_puts("\n");
}
static void cmd_valgrind48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: valgrind <program>\n"); return; }
    vga_puts("==1234== Memcheck, a memory error detector\n==1234== HEAP SUMMARY:\n==1234==   in use at exit: 0 bytes in 0 blocks\n==1234==   total heap usage: 42 allocs, 42 frees, 1,024 bytes allocated\n==1234== All heap blocks were freed -- no leaks are possible\n==1234== ERROR SUMMARY: 0 errors from 0 contexts\n");
}
static void cmd_strace3(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: strace <command>\n"); return; }
    vga_puts("execve(\""); vga_puts(args[1]); vga_puts("\", [\""); vga_puts(args[1]); vga_puts("\"], 0x7ffe...) = 0\n");
    vga_puts("brk(NULL)                               = 0x555555559000\n");
    vga_puts("access(\"/etc/ld.so.preload\", R_OK)      = -1 ENOENT\n");
    vga_puts("openat(AT_FDCWD, \"/etc/ld.so.cache\", O_RDONLY|O_CLOEXEC) = 3\n");
    vga_puts("read(3, \"\\177ELF\\2\\1\\1\", 832)         = 832\n");
    vga_puts("write(1, \"hello\\n\", 6)                  = 6\n");
    vga_puts("exit_group(0)                           = ?\n+++ exited with 0 +++\n");
}
static void cmd_ltrace3(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ltrace <command>\n"); return; }
    vga_puts("__libc_start_main(0x555555555149, 2, 0x7ffe..., 0x555555555210, 0x555555555200 <unfinished>\n");
    vga_puts("printf(\"hello\")                           = 5\n");
    vga_puts("exit(0)                                   = <void>\n");
    vga_puts("--- called 2 times ---\n");
}
static void cmd_perf48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Performance counter stats for 'system wide':\n\n");
    vga_puts("     10000.12 msec  task-clock\n         42         context-switches\n          3         cpu-migrations\n        128         page-faults\n");
    vga_puts("  12345678.90       cycles\n  23456789.01       instructions\n");
}
static void cmd_gcov48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("File 'main.c'\nLines executed: 85.71% of 14\nmain.c:creating main program\n");
}

/* Database tools */
static void cmd_mysql48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("mysql: MySQL client\nUsage: mysql <connect|select|show|status>\n"); return; }
    if (strcmp(args[1], "status") == 0 || strcmp(args[1], "connect") == 0) {
        vga_puts("Welcome to the MySQL monitor.\nServer version: 8.0.35 MySQL\n\nmysql> SELECT VERSION();\n+--------+\n| VERSION() |\n+--------+\n| 8.0.35   |\n+--------+\n");
    } else if (strcmp(args[1], "show") == 0) {
        vga_puts("+--------------------+\n| Database           |\n+--------------------+\n| information_schema |\n| mysql              |\n| performance_schema |\n| sys                |\n+--------------------+\n");
    } else { vga_puts("mysql> "); vga_puts(args[1]); vga_puts(";\nQuery OK\n"); }
}
static void cmd_psql48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("psql: PostgreSQL client\nUsage: psql <connect|select|list>\n"); return; }
    vga_puts("psql (15.4)\nType \"help\" for help.\n\n# \\l\n                            List of databases\n Name     | Owner  | Encoding\n----------+--------+----------\n postgres | pguser | UTF8\n testdb   | pguser | UTF8\n");
}
static void cmd_redis48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("redis: Redis client\nUsage: redis <get|set|keys|info|ping>\n"); return; }
    if (strcmp(args[1], "ping") == 0) { vga_puts("PONG\n"); }
    else if (strcmp(args[1], "info") == 0) {
        vga_puts("# Server\nredis_version:7.2.3\nredis_mode:standalone\nuptime_in_seconds:3600\n# Keyspace\n# Memory\nused_memory:1048576\n");
    } else if (strcmp(args[1], "set") == 0) { vga_puts("OK\n"); }
    else if (strcmp(args[1], "get") == 0) { vga_puts("(nil)\n"); }
    else if (strcmp(args[1], "keys") == 0) { vga_puts("(empty array)\n"); }
    else { vga_puts("redis> command executed\n"); }
}
static void cmd_mongo48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("mongosh: MongoDB shell\nUsage: mongosh <connect|show|find>\n"); return; }
    vga_puts("Current Mongosh Log ID: 65a4b3c2d4e5f6a7b8c9d0e1\nConnecting to: mongodb://localhost:27017\nUsing MongoDB: 7.0.4\n\n[direct: primary] test> db\n");
    vga_puts("test> show dbs\nadmin    0.000GB\nconfig   0.000GB\nlocal    0.000GB\n");
}
static void cmd_sqlite48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("sqlite3: SQLite CLI\nUsage: sqlite3 <database>\n"); return; }
    vga_puts("SQLite version 3.41.2\nEnter \".help\" for usage hints.\nsqlite> .tables\nsqlite> .schema\nsqlite> SELECT sqlite_version();\n3.41.2\n");
}

/* Media tools */
static void cmd_ffmpeg48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("ffmpeg: media converter\nUsage: ffmpeg -i <input> <output>\n"); return; }
    vga_puts("ffmpeg version 6.0\nbuilt with gcc 12.2.0\nconfiguration: --enable-gpl\n");
    vga_puts("Input #0 from '"); vga_puts(argc > 2 ? args[2] : "input.mp4"); vga_puts("':\n  Duration: 00:02:30.12\n  Stream #0:0: Video: h264\n");
    vga_puts("Output #0 to 'output.mp4':\n  Stream #0:0: Video: libx264\n  frame= 3750 fps=30 q=28.0 size=12345kB\n");
    vga_puts("Processed 3750 frames\n");
}
static void cmd_ffprobe48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("ffprobe version 6.0\nInput #0: video, h264, 1920x1080, 30fps\nDuration: 00:02:30.12\nBitrate: 5000 kb/s\n");
}
static void cmd_convert48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("ImageMagick 7.1.1\nUsage: convert <input> <output>\n");
}
static void cmd_identify48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: identify <image>\n"); return; }
    vga_puts(args[1]); vga_puts(" JPEG 1920x1080 1920x1080+0+0 8-bit sRGB 2.1MB 0.010u 0:00.009\n");
}
static void cmd_mplayer48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("mplayer: media player\nUsage: mplayer <file>\n"); return; }
    vga_puts("MPlayer dev-SVN-r38552\nPlaying "); vga_puts(args[1]); vga_puts(".\n");
    vga_puts("Video: h264 1920x1080 30fps\nAudio: aac 44100Hz stereo\n");
    vga_puts("Starting playback...\n");
}
static void cmd_vlc48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("VLC media player 3.0.20 Vetinari\nUsage: vlc <file>\n");
}
static void cmd_mpv48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("mpv: media player\nUsage: mpv <file>\n"); return; }
    vga_puts("mpv v0.35.1\nPlaying: "); vga_puts(args[1]); vga_puts("\nVideo: h264 1920x1080@30\nAudio: aac 44100Hz stereo\n");
}
static void cmd_yt_dlp48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("yt-dlp: video downloader\nUsage: yt-dlp <url>\n"); return; }
    vga_puts("[youtube] Extracting URL: "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("[download] Destination: video.mp4\n[download] 100% of 12.34MiB in 00:00\n");
}
static void cmd_aria2c48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("aria2c: download utility\nUsage: aria2c <url>\n"); return; }
    vga_puts(" *** Download Progress Summary ***\n[#a1b2c3 4.5MiB/12.3MiB(36%) CN:4 DL:2.1MiB/s\n");
}
static void cmd_rsync48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: rsync -avz <source> <dest>\n"); return; }
    vga_puts("sending incremental file list\n");
    vga_puts("file1.txt\nfile2.txt\n\nsent 1234 bytes  received 42 bytes  2552.00 bytes/sec\ntotal size is 12345  speedup is 9.71\n");
}
static void cmd_scp48(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: scp <file> <dest>\n"); return; }
    vga_puts("file1.txt                            100% 1234    1.2MB/s   00:00\n");
}
static void cmd_ftp48(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("ftp: file transfer protocol client\nUsage: ftp <host>\n");
}
