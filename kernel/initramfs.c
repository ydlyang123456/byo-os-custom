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
        " BYO-OS 2.1 - Build Your Own Operating System\n"
        " Debian 12 (bookworm) Compatible - BT Panel Ready\n"
        "\n";

    /* ---------- /etc/shells ---------- */
    static const char shells[] =
        "# /etc/shells: valid login shells\n"
        "/bin/sh\n"
        "/bin/bash\n"
        "/bin/dash\n"
        "/bin/zsh\n"
        "/bin/fish\n";

    /* ---------- /etc/issue ---------- */
    static const char issue[] =
        "\nDebian GNU/Linux 12 (bookworm) \\n \\l\n\n";

    /* ---------- /etc/apt/sources.list ---------- */
    static const char apt_sources[] =
        "deb http://deb.debian.org/debian bookworm main contrib non-free non-free-firmware\n"
        "deb http://deb.debian.org/debian bookworm-updates main contrib non-free non-free-firmware\n"
        "deb http://security.debian.org/debian-security bookworm-security main contrib non-free non-free-firmware\n"
        "deb http://deb.debian.org/debian bookworm-backports main contrib non-free non-free-firmware\n";

    /* ---------- /etc/apt/sources.list.d/bt.list ---------- */
    static const char bt_sources[] =
        "deb http://download.bt.cn/bt debian main\n";

    /* ---------- /etc/dpkg/origins/default ---------- */
    static const char dpkg_origins[] =
        "Vendor: Debian\n"
        "Vendor-URL: https://www.debian.org/\n"
        "Bugs: debbugs://bugs.debian.org/\n";

    /* ---------- /etc/apt/apt.conf.d/01apt-debian ---------- */
    static const char apt_conf[] =
        "APT::Get::AllowUnauthenticated \"false\";\n"
        "APT::Get::Assume-Yes \"false\";\n"
        "APT::Install-Recommends \"true\";\n"
        "Acquire::Retries \"3\";\n"
        "Acquire::http::Timeout \"10\";\n";

    /* ---------- /etc/ssh/sshd_config ---------- */
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
        "17 * * * * root\tcd / && run-parts --report /etc/cron.hourly\n"
        "25 6 * * * root\ttest -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.daily )\n"
        "47 6 * * 7 root\ttest -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.weekly )\n"
        "52 6 1 * * root\ttest -x /usr/sbin/anacron || ( cd / && run-parts --report /etc/cron.monthly )\n";

    /* ---------- /etc/nsswitch.conf ---------- */
    static const char nsswitch[] =
        "# /etc/nsswitch.conf\n"
        "passwd:         files systemd\n"
        "group:          files systemd\n"
        "shadow:         files\n"
        "gshadow:        files\n"
        "hosts:          files dns\n"
        "networks:       files\n"
        "protocols:      db files\n"
        "services:       db files\n"
        "ethers:         db files\n"
        "rpc:            db files\n"
        "netgroup:       nis\n";

    /* ---------- /etc/resolv.conf ---------- */
    static const char resolv[] =
        "nameserver 8.8.8.8\n"
        "nameserver 8.8.4.4\n"
        "nameserver 1.1.1.1\n"
        "search localdomain\n";

    /* ---------- /etc/inputrc ---------- */
    static const char inputrc[] =
        "# /etc/inputrc\n"
        "set meta-flag on\n"
        "set input-meta on\n"
        "set convert-meta off\n"
        "set bell-style none\n"
        "$include /etc/inputrc.d/\n";

    /* ---------- /etc/security/limits.conf ---------- */
    static const char limits[] =
        "# /etc/security/limits.conf\n"
        "*               soft    nofile          65535\n"
        "*               hard    nofile          65535\n"
        "root            soft    nofile          65535\n"
        "root            hard    nofile          65535\n";

    /* ---------- /etc/sysctl.conf ---------- */
    static const char sysctl[] =
        "# /etc/sysctl.conf\n"
        "net.ipv4.ip_forward=1\n"
        "net.ipv4.conf.all.rp_filter=1\n"
        "net.ipv4.tcp_syncookies=1\n"
        "vm.swappiness=10\n"
        "fs.file-max=100000\n";

    /* ---------- /etc/timezone ---------- */
    static const char timezone[] = "Asia/Shanghai\n";

    /* ---------- /etc/locale.conf ---------- */
    static const char locale_conf[] =
        "LANG=en_US.UTF-8\n"
        "LC_CTYPE=en_US.UTF-8\n"
        "LC_NUMERIC=en_US.UTF-8\n"
        "LC_TIME=en_US.UTF-8\n"
        "LC_COLLATE=en_US.UTF-8\n"
        "LC_MONETARY=en_US.UTF-8\n"
        "LC_MESSAGES=en_US.UTF-8\n"
        "LC_PAPER=en_US.UTF-8\n"
        "LC_NAME=en_US.UTF-8\n"
        "LC_ADDRESS=en_US.UTF-8\n"
        "LC_TELEPHONE=en_US.UTF-8\n"
        "LC_MEASUREMENT=en_US.UTF-8\n"
        "LC_IDENTIFICATION=en_US.UTF-8\n"
        "LC_ALL=\n";

    /* ---------- /etc/profile ---------- */
    static const char profile[] =
        "# /etc/profile: system-wide .profile file \n"
        "if [ \"${BASH-}\" ] && [ \"$BASH\" != \"/bin/sh\" ]; then\n"
        "    [ -f /etc/bash.bashrc ] && . /etc/bash.bashrc\n"
        "fi\n"
        "if [ \"`id -u`\" -eq 0 ]; then\n"
        "    PATH=\"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin\"\n"
        "else\n"
        "    PATH=\"/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games\"\n"
        "fi\n"
        "export PATH\n"
        "if [ -d /etc/profile.d ]; then\n"
        "    for i in /etc/profile.d/*.sh; do\n"
        "        if [ -r $i ]; then\n"
        "            . $i\n"
        "        fi\n"
        "    done\n"
        "    unset i\n"
        "fi\n";

    /* ---------- /etc/bash.bashrc ---------- */
    static const char bashrc[] =
        "# /etc/bash.bashrc: system-wide bashrc\n"
        "if [ -f /etc/bash_completion ]; then\n"
        "    . /etc/bash_completion\n"
        "fi\n"
        "alias ll='ls -l'\n"
        "alias la='ls -A'\n"
        "alias l='ls -CF'\n";

    /* ---------- /root/.bashrc ---------- */
    static const char root_bashrc[] =
        "# ~/.bashrc: root user bashrc\n"
        "alias ll='ls -l'\n"
        "alias la='ls -A'\n"
        "alias l='ls -CF'\n"
        "alias rm='rm -i'\n"
        "alias cp='cp -i'\n"
        "alias mv='mv -i'\n"
        "export PS1='\[\\033[01;31m\]\h\[\\033[01;34m\] \W \$\\\\[\\033[00m\] '\n";

    /* ---------- /home/byo/.bashrc ---------- */
    static const char byo_bashrc[] =
        "# ~/.bashrc: byo user bashrc\n"
        "alias ll='ls -l'\n"
        "alias la='ls -A'\n"
        "alias l='ls -CF'\n"
        "export PS1='\[\\033[01;32m\]us@er@host\[\\033[00m\]:\[\\033[01;34m\]\w\[\\033[00m\]\$ '\n";

    /* ---------- /etc/sudoers ---------- */
    static const char sudoers[] =
        "# /etc/sudoers\n"
        "# This file MUST be edited with the 'visudo' command as root.\n"
        "# See the man page for details on how to write a sudoers file.\n"
        "Defaults\tenv_reset\n"
        "Defaults\tmail_badpass\n"
        "Defaults\tsecure_path=\"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin\"\n"
        "root\tALL=(ALL:ALL) ALL\n"
        "%sudo\tALL=(ALL:ALL) ALL\n"
        "%admin\tALL=(ALL:ALL) ALL\n"
        "byo\tALL=(ALL:ALL) NOPASSWD:ALL\n"
        "#includedir /etc/sudoers.d\n";

    /* ---------- /etc/sudoers.d/bt ---------- */
    /* BT Panel sudo permissions */
    static const char sudoers_bt[] =
        "# BT Panel sudo permissions\n"
        "www-data ALL=(ALL) NOPASSWD: /etc/init.d/bt\n"
        "www-data ALL=(ALL) NOPASSWD: /usr/local/btpanel/*\n";


    /* ---------- /etc/init.d/bt ---------- */
    /* Enhanced BT Panel init script with full LSB headers */
    static const char bt_init[] =
        "#!/bin/bash\n"
        "# BT Panel init script\n"
        "### BEGIN INIT INFO\n"
        "# Provides:          bt\n"
        "# Required-Start:    $network $remote_fs $syslog\n"
        "# Required-Stop:     $network $remote_fs $syslog\n"
        "# Should-Start:      $named\n"
        "# Should-Stop:       $named\n"
        "# Default-Start:     2 3 4 5\n"
        "# Default-Stop:      0 1 6\n"
        "# Short-Description: BT Panel Service\n"
        "# Description:       Start or stop the BT Panel (BaoTa) service\n"
        "### END INIT INFO\n"
        "\n"
        "NAME=btpanel\n"
        "DAEMON=/usr/local/btpanel/btpanel\n"
        "PIDFILE=/var/run/$NAME.pid\n"
        "\n"
        "case \"$1\" in\n"
        "  start)\n"
        "    echo \"Starting BT Panel...\"\n"
        "    if [ -x $DAEMON ]; then\n"
        "        $DAEMON start\n"
        "        echo \"BT Panel started.\"\n"
        "    else\n"
        "        echo \"$DAEMON not found.\"\n"
        "    fi\n"
        "    ;;\n"
        "  stop)\n"
        "    echo \"Stopping BT Panel...\"\n"
        "    if [ -f $PIDFILE ]; then\n"
        "        kill \"`cat $PIDFILE`\"\n"
        "        rm -f $PIDFILE\n"
        "    fi\n"
        "    ;;\n"
        "  restart)\n"
        "    $0 stop\n"
        "    sleep 1\n"
        "    $0 start\n"
        "    ;;\n"
        "  status)\n"
        "    if [ -f $PIDFILE ]; then\n"
        "        echo \"BT Panel is running (pid `cat $PIDFILE`)\"\n"
        "    else\n"
        "        echo \"BT Panel is not running\"\n"
        "    fi\n"
        "    ;;\n"
        "  *)\n"
        "    echo \"Usage: $0 {start|stop|restart|status}\"\n"
        "    exit 2\n"
        "    ;;\n"
        "esac\n"
        "exit 0\n";



    /* ========== Networking ========== */

    /* ---------- /etc/network/interfaces ---------- */
    static const char network_interfaces[] =
        "auto lo\n"
        "iface lo inet loopback\n"
        "\n"
        "auto eth0\n"
        "iface eth0 inet dhcp\n";

    /* ---------- /etc/cron.d/bt ---------- */
    /* BT Panel cron job */
    static const char cron_bt[] =
        "# BT Panel cron jobs\n"
        "* * * * * root /etc/init.d/bt status >/dev/null 2>&1 || /etc/init.d/bt start\n"
        "0 3 * * * root /usr/local/btpanel/cleanup.sh >/dev/null 2>&1\n";

    /* ========== Default Files ========== */

    /* ---------- /etc/default/locale ---------- */
    static const char default_locale[] =
        "LANG=en_US.UTF-8\n";

    /* ---------- /etc/default/keyboard ---------- */
    static const char default_keyboard[] =
        "XKBLAYOUT=us\n"
        "XKBMODEL=pc105\n"
        "XKBVARIANT=\n"
        "XKBOPTIONS=\n"
        "BACKSPACE=guess\n";

    /* ---------- /etc/default/grub ---------- */
    static const char default_grub[] =
        "# If you change this file, run 'update-grub' afterwards to update\n"
        "# /boot/grub/grub.cfg.\n"
        "GRUB_DEFAULT=0\n"
        "GRUB_TIMEOUT=5\n"
        "GRUB_DISTRIBUTOR=\n"
        "GRUB_CMDLINE_LINUX_DEFAULT=\"quiet\"\n"
        "GRUB_CMDLINE_LINUX=\"\"\n";

    /* ========== SSL Certificates ========== */

    /* ---------- /etc/ssl/certs/ca-certificates.crt ---------- */
    /* Simulated CA certificate bundle */
    static const char ca_certs[] =
        "# CA certificate bundle for BYO-OS\n"
        "# This is a placeholder simulating /etc/ssl/certs/ca-certificates.crt\n"
        "# Real certificates should be installed via: apt install ca-certificates\n"
        "\n"
        "-----BEGIN CERTIFICATE-----\n"
        "MIIBtjCCAVugAwIBAgITBmyf1XSXNmN/8nJ8lH3BMEgwCgYIKoZIzj0EAwMw\n"
        "SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNV\n"
        "BAMTGkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMB4XDTI0MDEwMTAwMDAw\n"
        "-----END CERTIFICATE-----\n";

    /* ========== Nginx Configuration ========== */

    /* ---------- /etc/nginx/nginx.conf ---------- */
    static const char nginx_conf[] =
        "user www-data;\n"
        "worker_processes auto;\n"
        "pid /run/nginx.pid;\n"
        "error_log /var/log/nginx/error.log;\n"
        "\n"
        "events {\n"
        "    worker_connections 768;\n"
        "    multi_accept on;\n"
        "}\n"
        "\n"
        "http {\n"
        "    sendfile on;\n"
        "    tcp_nopush on;\n"
        "    tcp_nodelay on;\n"
        "    keepalive_timeout 65;\n"
        "    types_hash_max_size 2048;\n"
        "    include /etc/nginx/mime.types;\n"
        "    default_type application/octet-stream;\n"
        "\n"
        "    ssl_protocols TLSv1.2 TLSv1.3;\n"
        "    ssl_prefer_server_ciphers on;\n"
        "    access_log /var/log/nginx/access.log;\n"
        "    gzip on;\n"
        "    include /etc/nginx/conf.d/*.conf;\n"
        "    include /etc/nginx/sites-enabled/*;\n"
        "}\n";

    /* ========== Web Content ========== */

    /* ---------- /var/www/html/index.html ---------- */
    static const char index_html[] =
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "<meta charset=\"UTF-8\">\n"
        "<title>Welcome to BYO-OS</title>\n"
        "<style>\n"
        "body{font-family:DejaVu Sans,sans-serif;display:flex;justify-content:center;\n"
        "align-items:center;height:100vh;margin:0;background:#f4f4f4;}\n"
        ".container{text-align:center;padding:2rem;background:#fff;\n"
        "border-radius:8px;box-shadow:0 2px 10px rgba(0,0,0,.1);}\n"
        "h1{color:#333;}p{color:#666;}\n"
        "</style>\n"
        "</head>\n"
        "<body>\n"
        "<div class=\"container\">\n"
        "<h1>Welcome to BYO-OS</h1>\n"
        "<p>Debian 12 (bookworm) Compatible | BT Panel Ready</p>\n"
        "</div>\n"
        "</body>\n"
        "</html>\n";

    /* ========== Log Files ========== */

    /* ---------- /var/log/syslog ---------- */
    static const char log_syslog[] =
        "Jul 10 08:00:01 byo-os kernel: BYO-OS kernel booting...\n"
        "Jul 10 08:00:01 byo-os kernel: Initramfs mounted\n"
        "Jul 10 08:00:02 byo-os systemd[1]: Starting system...\n"
        "Jul 10 08:00:05 byo-os systemd[1]: Reached target Basic System\n"
        "Jul 10 08:00:10 byo-os systemd[1]: Started BT Panel service\n";

    /* ---------- /var/log/auth.log ---------- */
    static const char log_auth[] =
        "Jul 10 08:00:01 byo-os login[1]: root login on console\n"
        "Jul 10 08:00:05 byo-os sudo: root : TTY=console ; USER=root ; COMMAND=/sbin/init\n";

    /* ---------- /var/log/bt.log ---------- */
    static const char log_bt[] =
        "2025-07-10 08:00:01 [INFO] BT Panel starting...\n"
        "2025-07-10 08:00:02 [INFO] Panel initialized successfully\n"
        "2025-07-10 08:00:05 [INFO] Listening on port 8888\n";

    /* ---------- /var/log/bt_panel.log ---------- */
    static const char log_bt_panel[] =
        "2025-07-10 08:00:01 [INFO] BT Panel v8.2.0 starting...\n"
        "2025-07-10 08:00:02 [INFO] Loading configuration...\n"
        "2025-07-10 08:00:03 [INFO] Database connected\n"
        "2025-07-10 08:00:05 [INFO] HTTP server started on 0.0.0.0:8888\n";

    /* ========== BT Panel Data ========== */

    /* ---------- /var/lib/bt/install.log ---------- */
    static const char bt_install_log[] =
        "[2025-07-10 08:00:00] BT Panel installer started\n"
        "[2025-07-10 08:00:01] Checking system... Debian 12 detected\n"
        "[2025-07-10 08:00:02] Installing dependencies... OK\n"
        "[2025-07-10 08:00:05] BT Panel installed successfully (v8.2.0)\n";

    /* ---------- /var/lib/bt/setup.pl ---------- */
    static const char bt_setup_pl[] =
        "#!/usr/bin/perl\n"
        "# BT Panel setup configuration\n"
        "our $BT_VERSION = '8.2.0';\n"
        "our $BT_PANEL_DIR = '/usr/local/btpanel';\n"
        "our $BT_DATA_DIR = '/var/lib/bt';\n"
        "our $BT_LOG_DIR = '/var/log';\n"
        "our $BT_PORT = 8888;\n"
        "1;\n";



    
    /* ========== BT Panel Install Directory ========== */

    /* ---------- /opt/btpanel/install.sh ---------- */
    static const char bt_install_sh[] =
        "#!/bin/bash\n"
        "# BT Panel installer for BYO-OS\n"
        "echo '========================================'\n"
        "echo '  BT Panel Installer v8.2.0'\n"
        "echo '  Debian 12 (bookworm) Compatible'\n"
        "echo '========================================'\n"
        "echo 'Installing dependencies...'\n"
        "echo '[OK] All dependencies satisfied'\n"
        "echo 'Installing BT Panel...'\n"
        "echo '[OK] BT Panel installed successfully'\n"
        "echo 'Panel URL: http://localhost:8888'\n";

    /* ---------- /opt/btpanel/version.pl ---------- */
    static const char bt_version_pl[] =
        "#!/usr/bin/perl\n"
        "$BT_VERSION = '8.2.0';\n"
        "$BT_RELEASE_DATE = '2025-07-10';\n"
        "$BT_ARCH = 'x86_64-linux-gnu';\n"
        "$BT_OS = 'Debian 12 (bookworm)';\n"
        "print \"BT Panel v$BT_VERSION\\n\";\n"
        "print \"Release: $BT_RELEASE_DATE\\n\";\n"
        "print \"Arch: $BT_ARCH\\n\";\n"
        "print \"OS: $BT_OS\\n\";\n";

    /* ========== Profile.d Scripts ========== */

    /* ---------- /etc/profile.d/bt.sh ---------- */
    static const char profile_bt[] =
        "# BT Panel environment setup\n"
        "export BT_HOME=\"/usr/local/btpanel\"\n"
        "export PATH=\"$PATH:$BT_HOME/bin\"\n";

    /* ---------- /etc/profile.d/colors.sh ---------- */
    static const char profile_colors[] =
        "# colored GCC warnings and errors\n"
        "export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'\n";

    /* ---------- /etc/bash_completion.d/bt-completion ---------- */
    static const char bt_bash_completion[] =
        "# bash completion for BT Panel commands\n"
        "_bt()\n"
        "{\n"
        "    local cur prev opts\n"
        "    COMPREPLY=()\n"
        "    cur=\"${COMP_WORDS[COMP_CWORD]}\"\n"
        "    prev=\"${COMP_WORDS[COMP_CWORD-1]}\"\n"
        "    opts=\"start stop restart status\"\n"
        "    COMPREPLY=( $(compgen -W \"${opts}\" -- ${cur}) )\n"
        "    return 0\n"
        "}\n"
        "complete -F _bt bt\n";

/* Ensure directories exist */
    fs_create_dir("etc");
    fs_create_dir("etc/apt");
    fs_create_dir("etc/apt/sources.list.d");
    fs_create_dir("etc/apt/apt.conf.d");
    fs_create_dir("etc/apt/preferences.d");
    fs_create_dir("etc/dpkg");
    fs_create_dir("etc/dpkg/origins");
    fs_create_dir("etc/ssh");
    fs_create_dir("etc/ssh/sshd_config.d");
    fs_create_dir("etc/security");
    fs_create_dir("etc/security/limits.d");
    fs_create_dir("etc/profile.d");
    fs_create_dir("etc/bash_completion.d");
    fs_create_dir("etc/init.d");
    fs_create_dir("etc/cron.d");
    fs_create_dir("etc/cron.hourly");
    fs_create_dir("etc/cron.daily");
    fs_create_dir("etc/cron.weekly");
    fs_create_dir("etc/cron.monthly");
    fs_create_dir("etc/inputrc.d");
    fs_create_dir("etc/sysctl.d");
    fs_create_dir("etc/udev");
    fs_create_dir("etc/udev/rules.d");
    fs_create_dir("etc/modprobe.d");
    fs_create_dir("etc/modules-load.d");
    fs_create_dir("etc/systemd");
    fs_create_dir("etc/systemd/system");
    fs_create_dir("home");
    fs_create_dir("home/byo");
    fs_create_dir("tmp");
    fs_create_dir("root");
    fs_create_dir("var");
    fs_create_dir("var/log");
    fs_create_dir("var/run");
    fs_create_dir("var/tmp");
    fs_create_dir("var/spool");
    fs_create_dir("var/spool/cron");
    fs_create_dir("var/spool/cron/crontabs");
    fs_create_dir("var/lib");
    fs_create_dir("var/lib/apt");
    fs_create_dir("var/lib/dpkg");
    fs_create_dir("var/www");
    fs_create_dir("usr");
    fs_create_dir("usr/bin");
    fs_create_dir("usr/sbin");
    fs_create_dir("usr/lib");
    fs_create_dir("usr/local");
    fs_create_dir("usr/local/bin");
    fs_create_dir("usr/local/sbin");
    fs_create_dir("usr/local/lib");
    fs_create_dir("usr/local/bt");
    fs_create_dir("opt");
    fs_create_dir("opt/btpanel");

    /* --- Network directories --- */
    fs_create_dir("etc/network");
    fs_create_dir("etc/network/if-down.d");
    fs_create_dir("etc/network/if-post-down.d");
    fs_create_dir("etc/network/if-pre-up.d");
    fs_create_dir("etc/network/if-up.d");

    /* --- Default / Environment directories --- */
    fs_create_dir("etc/default");

    /* --- SSL directories --- */
    fs_create_dir("etc/ssl");
    fs_create_dir("etc/ssl/certs");

    /* --- Sudo directories --- */
    fs_create_dir("etc/sudoers.d");

    /* --- PHP version directories --- */
    fs_create_dir("etc/php");
    fs_create_dir("etc/php/8.2");
    fs_create_dir("etc/php/8.2/fpm");
    fs_create_dir("etc/php/8.2/fpm/pool.d");
    fs_create_dir("etc/php/8.2/cli");
    fs_create_dir("etc/php/8.2/cli/conf.d");
    fs_create_dir("etc/php/8.2/mods-available");

    /* --- Nginx directories --- */
    fs_create_dir("etc/nginx");
    fs_create_dir("etc/nginx/sites-enabled");
    fs_create_dir("etc/nginx/sites-available");
    fs_create_dir("etc/nginx/conf.d");

    /* --- Extended /var directories --- */
    fs_create_dir("var/log/nginx");
    fs_create_dir("var/lib/apt/lists");
    fs_create_dir("var/lib/apt/periodic");
    fs_create_dir("var/lib/dpkg/info");
    fs_create_dir("var/lib/dpkg/parts");
    fs_create_dir("var/lib/dpkg/updates");
    fs_create_dir("var/lib/bt");
    fs_create_dir("var/www/html");
    fs_create_dir("var/cache");
    fs_create_dir("var/cache/apt");
    fs_create_dir("var/cache/apt/archives");
    fs_create_dir("var/cache/apt/archives/partial");
    fs_create_dir("var/mail");

    /* --- Extended /usr directories --- */
    fs_create_dir("usr/lib/x86_64-linux-gnu");
    fs_create_dir("usr/lib/btpanel");
    fs_create_dir("usr/local/btpanel");
    fs_create_dir("usr/local/btpanel/bin");
    fs_create_dir("usr/local/btpanel/conf");
    fs_create_dir("usr/local/btpanel/logs");
    fs_create_dir("usr/share");
    fs_create_dir("usr/share/doc");
    fs_create_dir("usr/share/man");
    fs_create_dir("usr/share/man/man1");
    fs_create_dir("usr/share/man/man8");
    fs_create_dir("usr/share/zoneinfo");
    fs_create_dir("usr/share/zoneinfo/Asia");
    fs_create_dir("usr/share/zoneinfo/America");
    fs_create_dir("usr/share/zoneinfo/Europe");
    fs_create_dir("usr/include");
    fs_create_dir("usr/src");

    /* --- /www (BT Panel default) directories --- */
    fs_create_dir("www");
    fs_create_dir("www/server");
    fs_create_dir("www/server/nginx");
    fs_create_dir("www/server/nginx/sbin");
    fs_create_dir("www/server/mysql");
    fs_create_dir("www/server/mysql/bin");
    fs_create_dir("www/server/php");
    fs_create_dir("www/server/panel");
    fs_create_dir("www/server/panel/vhost");
    fs_create_dir("www/server/panel/vhost/nginx");
    fs_create_dir("www/server/panel/vhost/apache");
    fs_create_dir("www/wwwroot");
    fs_create_dir("www/wwwroot/default");

    /* --- Additional system directories --- 

    fs_create_dir("run");
    fs_create_dir("mnt");
    fs_create_dir("media");
    fs_create_dir("srv");

        fs_create_dir("dev");
    fs_create_dir("proc");
    fs_create_dir("sys");

    /* Create all configuration files */
    fs_create_file("etc/os-release",  os_release,  sizeof(os_release) - 1);
    fs_create_file("etc/debian_version", debian_version, sizeof(debian_version) - 1);
    fs_create_file("etc/lsb-release", lsb_release, sizeof(lsb_release) - 1);
    fs_create_file("etc/hostname",     hostname,    sizeof(hostname) - 1);
    fs_create_file("etc/hosts",        hosts,       sizeof(hosts) - 1);
    fs_create_file("etc/passwd",       passwd,      sizeof(passwd) - 1);
    fs_create_file("etc/group",        group,       sizeof(group) - 1);
    fs_create_file("etc/shadow",       "root:$6$xyz:20000:0:99999:7:::", 36);
    fs_create_file("etc/fstab",        fstab,       sizeof(fstab) - 1);
    fs_create_file("etc/motd",         motd,        sizeof(motd) - 1);
    fs_create_file("etc/shells",       shells,      sizeof(shells) - 1);
    fs_create_file("etc/issue",        issue,       sizeof(issue) - 1);
    fs_create_file("etc/apt/sources.list", apt_sources, sizeof(apt_sources) - 1);
    fs_create_file("etc/apt/sources.list.d/bt.list", bt_sources, sizeof(bt_sources) - 1);
    fs_create_file("etc/dpkg/origins/default", dpkg_origins, sizeof(dpkg_origins) - 1);
    fs_create_file("etc/apt/apt.conf.d/01apt-debian", apt_conf, sizeof(apt_conf) - 1);
    fs_create_file("etc/ssh/sshd_config", sshd_config, sizeof(sshd_config) - 1);
    fs_create_file("etc/crontab",      crontab,     sizeof(crontab) - 1);
    fs_create_file("etc/nsswitch.conf", nsswitch,   sizeof(nsswitch) - 1);
    fs_create_file("etc/resolv.conf",  resolv,      sizeof(resolv) - 1);
    fs_create_file("etc/inputrc",      inputrc,     sizeof(inputrc) - 1);
    fs_create_file("etc/security/limits.conf", limits, sizeof(limits) - 1);
    fs_create_file("etc/sysctl.conf",  sysctl,      sizeof(sysctl) - 1);
    fs_create_file("etc/timezone",     timezone,    sizeof(timezone) - 1);
    fs_create_file("etc/locale.conf",  locale_conf,      sizeof(locale_conf) - 1);
    fs_create_file("etc/profile",      profile,     sizeof(profile) - 1);
    fs_create_file("etc/bash.bashrc",  bashrc,      sizeof(bashrc) - 1);

    fs_create_file("etc/network/interfaces", network_interfaces, sizeof(network_interfaces) - 1);
    fs_create_file("etc/cron.d/bt",   cron_bt,      sizeof(cron_bt) - 1);
    fs_create_file("root/.bashrc",    root_bashrc,   sizeof(root_bashrc) - 1);
    fs_create_file("home/byo/.bashrc", byo_bashrc,   sizeof(byo_bashrc) - 1);
    fs_create_file("etc/sudoers",     sudoers,       sizeof(sudoers) - 1);
    fs_create_file("etc/sudoers.d/bt", sudoers_bt,   sizeof(sudoers_bt) - 1);
    fs_create_file("etc/default/locale",  default_locale,   sizeof(default_locale) - 1);
    fs_create_file("etc/default/keyboard", default_keyboard, sizeof(default_keyboard) - 1);
    fs_create_file("etc/default/grub",    default_grub,     sizeof(default_grub) - 1);
    fs_create_file("etc/ssl/certs/ca-certificates.crt", ca_certs, sizeof(ca_certs) - 1);
    fs_create_file("etc/nginx/nginx.conf", nginx_conf, sizeof(nginx_conf) - 1);
    fs_create_file("var/www/html/index.html", index_html, sizeof(index_html) - 1);
    fs_create_file("var/log/syslog",   log_syslog,    sizeof(log_syslog) - 1);
    fs_create_file("var/log/auth.log", log_auth,      sizeof(log_auth) - 1);
    fs_create_file("var/log/bt.log",   log_bt,        sizeof(log_bt) - 1);
    fs_create_file("var/log/bt_panel.log", log_bt_panel,  sizeof(log_bt_panel) - 1);
    fs_create_file("var/lib/bt/install.log", bt_install_log, sizeof(bt_install_log) - 1);
    fs_create_file("var/lib/bt/setup.pl",    bt_setup_pl,    sizeof(bt_setup_pl) - 1);
    fs_create_file("opt/btpanel/install.sh", bt_install_sh, sizeof(bt_install_sh) - 1);
    fs_create_file("opt/btpanel/version.pl", bt_version_pl, sizeof(bt_version_pl) - 1);
    fs_create_file("etc/profile.d/bt.sh",     profile_bt,     sizeof(profile_bt) - 1);
    fs_create_file("etc/profile.d/colors.sh", profile_colors, sizeof(profile_colors) - 1);
    fs_create_file("etc/bash_completion.d/bt-completion", bt_bash_completion, sizeof(bt_bash_completion) - 1);

        fs_create_file("etc/init.d/bt",    bt_init,     sizeof(bt_init) - 1);

    serial_puts("[BOOT] Initramfs: Debian 12 compat files created\n");
    vga_puts("[BOOT] Initramfs: /etc populated (Debian 12 / BT Panel ready)\n");
}
