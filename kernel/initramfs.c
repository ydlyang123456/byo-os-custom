/* BYO-OS - Initramfs: Debian 12 Compatible Memory Filesystem
 *
 * Populates /etc/ with standard Linux files so that userland
 * tools expecting a Debian-like layout find what they need.
 * BT Panel compatible - reports as Debian 12 bookworm.
 */
#include <kernel.h>

void initramfs_init(void) {
    /* ---------- /etc/os-release ---------- */
    static const char os_release[] =
        "PRETTY_NAME=\"Debian GNU/Linux 12 (bookworm)\"\n"
        "NAME=\"Debian GNU/Linux\"\n"
        "VERSION_ID=\"12\"\n"
        "VERSION=\"12 (bookworm)\"\n"
        "VERSION_CODENAME=bookworm\n"
        "ID=debian\n"
        "HOME_URL=\"https://www.debian.org/\"\n"
        "SUPPORT_URL=\"https://www.debian.org/support\"\n"
        "BUG_REPORT_URL=\"https://bugs.debian.org/\"\n";

    /* ---------- /etc/debian_version ---------- */
    static const char debian_version[] = "12.0\n";

    /* ---------- /etc/lsb-release ---------- */
    static const char lsb_release[] =
        "DISTRIB_ID=Debian\n"
        "DISTRIB_RELEASE=12\n"
        "DISTRIB_CODENAME=bookworm\n"
        "DISTRIB_DESCRIPTION=\"Debian GNU/Linux 12 (bookworm)\"\n";

    /* ---------- /etc/hostname ---------- */
    static const char hostname[] = "byo-os\n";

    /* ---------- /etc/hosts ---------- */
    static const char hosts[] =
        "127.0.0.1\tlocalhost\n"
        "127.0.1.1\tbyo-os\n"
        "\n"
        "::1\t\tlocalhost ip6-localhost ip6-loopback\n"
        "ff02::1\t\tip6-allnodes\n"
        "ff02::2\t\tip6-allrouters\n";

    /* ---------- /etc/passwd ---------- */
    static const char passwd[] =
        "root:x:0:0:root:/root:/bin/sh\n"
        "daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin\n"
        "bin:x:2:2:bin:/bin:/usr/sbin/nologin\n"
        "sys:x:3:3:sys:/dev:/usr/sbin/nologin\n"
        "sync:x:4:65534:sync:/bin:/bin/sync\n"
        "games:x:5:60:games:/usr/games:/usr/sbin/nologin\n"
        "man:x:6:12:man:/var/cache/man:/usr/sbin/nologin\n"
        "lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin\n"
        "mail:x:8:8:mail:/var/mail:/usr/sbin/nologin\n"
        "news:x:9:9:news:/var/spool/news:/usr/sbin/nologin\n"
        "uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin\n"
        "proxy:x:13:13:proxy:/bin:/usr/sbin/nologin\n"
        "www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin\n"
        "backup:x:34:34:backup:/var/backups:/usr/sbin/nologin\n"
        "list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin\n"
        "irc:x:39:39:ircd:/run/ircd:/usr/sbin/nologin\n"
        "gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin\n"
        "nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin\n"
        "_apt:x:100:65534::/nonexistent:/usr/sbin/nologin\n"
        "systemd-network:x:101:102::/run/systemd:/usr/sbin/nologin\n"
        "systemd-resolve:x:102:103::/run/systemd:/usr/sbin/nologin\n"
        "messagebus:x:103:106::/nonexistent:/usr/sbin/nologin\n"
        "syslog:x:104:108::/home/syslog:/usr/sbin/nologin\n"
        "_apt:x:105:65534::/nonexistent:/usr/sbin/nologin\n"
        "tcpdump:x:106:113::/nonexistent:/usr/sbin/nologin\n"
        "sshd:x:107:65534::/run/sshd:/usr/sbin/nologin\n"
        "byo:x:1000:1000:BYO User:/home/byo:/bin/sh\n";

    /* ---------- /etc/group ---------- */
    static const char group[] =
        "root:x:0:\n"
        "daemon:x:1:\n"
        "bin:x:2:\n"
        "sys:x:3:\n"
        "adm:x:4:\n"
        "tty:x:5:\n"
        "disk:x:6:\n"
        "lp:x:7:\n"
        "mail:x:8:\n"
        "news:x:9:\n"
        "uucp:x:10:\n"
        "man:x:12:\n"
        "proxy:x:13:\n"
        "kmem:x:15:\n"
        "dialout:x:20:\n"
        "fax:x:21:\n"
        "voice:x:22:\n"
        "cdrom:x:24:\n"
        "floppy:x:25:\n"
        "tape:x:26:\n"
        "sudo:x:27:\n"
        "audio:x:29:\n"
        "dip:x:30:\n"
        "www-data:x:33:\n"
        "backup:x:34:\n"
        "operator:x:37:\n"
        "list:x:38:\n"
        "irc:x:39:\n"
        "src:x:40:\n"
        "gnats:x:41:\n"
        "shadow:x:42:\n"
        "utmp:x:43:\n"
        "video:x:44:\n"
        "sasl:x:45:\n"
        "plugdev:x:46:\n"
        "staff:x:50:\n"
        "games:x:60:\n"
        "users:x:100:\n"
        "nogroup:x:65534:\n"
        "systemd-journal:x:101:\n"
        "systemd-network:x:102:\n"
        "systemd-resolve:x:103:\n"
        "crontab:x:104:\n"
        "syslog:x:108:\n"
        "input:x:109:\n"
        "kvm:x:110:\n"
        "render:x:111:\n"
        "sgx:x:112:\n"
        "tcpdump:x:113:\n"
        "ssh:x:114:\n"
        "byo:x:1000:\n";

    /* ---------- /etc/fstab ---------- */
    static const char fstab[] =
        "# /etc/fstab: static file system information.\n"
        "# <file system>  <mount point>  <type>  <options>  <dump>  <pass>\n"
        "/dev/ram0        /               auto    defaults   0       1\n"
        "proc             /proc           proc    defaults   0       0\n"
        "sysfs            /sys            sysfs   defaults   0       0\n"
        "tmpfs            /tmp            tmpfs   defaults   0       0\n"
        "tmpfs            /run            tmpfs   defaults   0       0\n"
        "devpts           /dev/pts        devpts  defaults   0       0\n";

    /* ---------- /etc/motd ---------- */
    static const char motd[] =
        "\n"
        "  ____  _   _ ____   ____ \n"
        " | __ )| | | |  _ \\ / ___|\n"
        " |  _ \\| | | | |_) | |    \n"
        " | |_) | |_| |  __/| |___ \n"
        " |____/ \\___/|_|    \\____|\n"
        "\n"
        " BYO-OS 2.0 - Build Your Own Operating System\n"
        " Debian 12 (bookworm) Compatible\n"
        " BT Panel Ready\n"
        "\n";

    /* ---------- /etc/shells ---------- */
    static const char shells[] =
        "# /etc/shells: valid login shells\n"
        "/bin/sh\n"
        "/bin/bash\n"
        "/bin/dash\n";

    /* ---------- /etc/issue ---------- */
    static const char issue[] =
        "\nDebian GNU/Linux 12 (bookworm) \\n \\l\n\n";

    /* ---------- /etc/apt/sources.list ---------- */
    static const char apt_sources[] =
        "# deb http://deb.debian.org/debian bookworm main contrib non-free non-free-firmware\n"
        "# deb http://deb.debian.org/debian-security bookworm-security main contrib non-free non-free-firmware\n"
        "# deb http://deb.debian.org/debian bookworm-updates main contrib non-free non-free-firmware\n";

    /* ---------- /etc/dpkg/origins/default ---------- */
    static const char dpkg_origins[] =
        "Vendor: Debian\n"
        "Vendor-URL: https://www.debian.org/\n"
        "Bugs: debbugs://bugs.debian.org/\n";

    /* ---------- /etc/apt/apt.conf.d/01apt-debian ---------- */
    static const char apt_conf[] =
        "APT::Get::AllowUnauthenticated \"false\";\n"
        "APT::Install-Recommends \"true\";\n";

    /* ---------- /etc/ssh/sshd_config (minimal) ---------- */
    static const char sshd_config[] =
        "Port 22\n"
        "ListenAddress 0.0.0.0\n"
        "PermitRootLogin yes\n"
        "PubkeyAuthentication yes\n"
        "PasswordAuthentication yes\n"
        "UsePAM yes\n"
        "X11Forwarding yes\n"
        "PrintMotd no\n"
        "AcceptEnv LANG LC_*\n"
        "Subsystem sftp /usr/lib/openssh/sftp-server\n";

    /* ---------- /etc/crontab ---------- */
    static const char crontab[] =
        "# /etc/crontab: system cron jobs\n"
        "SHELL=/bin/sh\n"
        "PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin\n"
        "m h dom mon dow user\tcommand\n"
        "17 * * * * root\tdate > /dev/null\n";

    /* Ensure directories exist */
    fs_create_dir("etc");
    fs_create_dir("etc/apt");
    fs_create_dir("etc/apt/apt.conf.d");
    fs_create_dir("etc/dpkg");
    fs_create_dir("etc/dpkg/origins");
    fs_create_dir("etc/ssh");
    fs_create_dir("home");
    fs_create_dir("tmp");
    fs_create_dir("root");
    fs_create_dir("var");
    fs_create_dir("var/log");
    fs_create_dir("var/run");
    fs_create_dir("var/tmp");
    fs_create_dir("usr");
    fs_create_dir("usr/bin");
    fs_create_dir("usr/sbin");
    fs_create_dir("usr/lib");
    fs_create_dir("opt");

    /* Create all files */
    fs_create_file("etc/os-release",  os_release,  sizeof(os_release) - 1);
    fs_create_file("etc/debian_version", debian_version, sizeof(debian_version) - 1);
    fs_create_file("etc/lsb-release", lsb_release, sizeof(lsb_release) - 1);
    fs_create_file("etc/hostname",     hostname,    sizeof(hostname) - 1);
    fs_create_file("etc/hosts",        hosts,       sizeof(hosts) - 1);
    fs_create_file("etc/passwd",       passwd,      sizeof(passwd) - 1);
    fs_create_file("etc/group",        group,       sizeof(group) - 1);
    fs_create_file("etc/fstab",        fstab,       sizeof(fstab) - 1);
    fs_create_file("etc/motd",         motd,        sizeof(motd) - 1);
    fs_create_file("etc/shells",       shells,      sizeof(shells) - 1);
    fs_create_file("etc/issue",        issue,       sizeof(issue) - 1);
    fs_create_file("etc/apt/sources.list", apt_sources, sizeof(apt_sources) - 1);
    fs_create_file("etc/dpkg/origins/default", dpkg_origins, sizeof(dpkg_origins) - 1);
    fs_create_file("etc/apt/apt.conf.d/01apt-debian", apt_conf, sizeof(apt_conf) - 1);
    fs_create_file("etc/ssh/sshd_config", sshd_config, sizeof(sshd_config) - 1);
    fs_create_file("etc/crontab",      crontab,     sizeof(crontab) - 1);

    serial_puts("[BOOT] Initramfs: Debian 12 compat files created\n");
    vga_puts("[BOOT] Initramfs: /etc populated (Debian 12 / BT Panel ready)\n");
}
