#include "kernel.h"

static void cmd_httpd54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: httpd54 <start|stop|status|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[httpd] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("httpd/1.27.0 started on :8080 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("httpd service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("pid=4821, port=8080, uptime=3d:14h:22m\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/httpd/httpd.conf (DocumentRoot /var/www/html)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_nginx54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: nginx54 <start|stop|reload|status|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[nginx] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("nginx/1.26.1 started on :80 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("nginx service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active (master+2 workers), connections=1024\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/nginx/nginx.conf (conf.d/*.conf)\n");
    } else if (strcmp(args[1], "reload") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("config reloaded, pid=3007 - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_lighttpd54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: lighttpd54 <start|stop|status|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[lighttpd] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("lighttpd/1.4.71 started on :80 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("lighttpd service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, pid=2190, max-connections=1024\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/lighttpd/lighttpd.conf\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_caddy54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: caddy54 <start|stop|status|config|validate>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[caddy] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("caddy v2.7.6 started on :443 + :80 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("caddy service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, pid=4120, auto-TLS=on\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/caddy/Caddyfile\n");
    } else if (strcmp(args[1], "validate") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("Valid configuration - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_haproxy54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: haproxy54 <start|stop|reload|status|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[haproxy] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("haproxy/2.9.6 started on :80,:443 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("haproxy service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, sessions=1204, bytes_in=4.2MB/s\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/haproxy/haproxy.cfg\n");
    } else if (strcmp(args[1], "reload") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("zero-downtime reload - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_varnish54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: varnish54 <start|stop|status|config|purge>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[varnish] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("varnish/7.4.2 started on :80 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("varnish service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("hit_rate=87.3%, obj_count=34102, free=1.2GB\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/varnish/default.vcl (VCL 4.1)\n");
    } else if (strcmp(args[1], "purge") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("all objects purged from cache - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_squid54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: squid54 <start|stop|status|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[squid] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("squid/6.8 started on :3128 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("squid service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, cache_objects=52130, cpu=12.4%\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/squid/squid.conf (mem_cache=512MB)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_postfix54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: postfix54 <start|stop|reload|status|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[postfix] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("postfix/3.9.1 started on :25,:587 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("postfix service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, queue=23 deferred, smtp_sasl=on\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/postfix/main.cf (myhostname=mail.example.com)\n");
    } else if (strcmp(args[1], "reload") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("master configuration reloaded - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_dovecot54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: dovecot54 <start|stop|reload|status|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[dovecot] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("dovecot/2.3.21 started on :993,:995 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("dovecot service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, imap=42 users, pop3=11 users\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/dovecot/dovecot.conf (ssl=required)\n");
    } else if (strcmp(args[1], "reload") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("config reloaded without disconnecting - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_roundcube54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: roundcube54 <start|stop|status|config|upgrade>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[roundcube] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("roundcube/1.6.7 started on :9090 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("roundcube service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("v1.6.7, active_sessions=18, db=sqlite\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /var/www/roundcube/config/config.inc.php\n");
    } else if (strcmp(args[1], "upgrade") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("schema updated, plugin index rebuilt - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_vsftpd54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: vsftpd54 <start|stop|status|config|users>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[vsftpd] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("vsftpd/3.0.5 started on :21 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("vsftpd service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, connections=5, anon=off, ssl=on\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/vsftpd.conf (chroot_local_user=YES)\n");
    } else if (strcmp(args[1], "users") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("Users: ftpadmin(online), backups(offline), deploy(idle)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_proftpd54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: proftpd54 <start|stop|status|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[proftpd] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("proftpd/1.3.8 started on :21 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("proftpd service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, sessions=8, max_clients=64\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/proftpd/proftpd.conf (SQLAuthTypes=SHA1)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_samba54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: samba54 <start|stop|reload|status|shares>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[samba] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("samba/4.20.2 started on :445 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("samba service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, workgroup=WORKGROUP, clients=3\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/samba/smb.conf\n");
    } else if (strcmp(args[1], "reload") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("reload - OK\n");
    } else if (strcmp(args[1], "shares") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("/home/data(public), /srv/backups(private), /opt/apps(ro)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_nfs54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: nfs54 <start|stop|status|exports|add>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[nfs] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("nfs-server/2.6.3 started on :2049 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("nfs service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, exports=4, clients=12, r/w=1.8MB/s\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/exports\n");
    } else if (strcmp(args[1], "exports") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("/srv/data 192.168.1.0/24(rw,sync)\n");
    } else if (strcmp(args[1], "add") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("export added and rpcexport updated - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_iscsi54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: iscsi54 <start|stop|status|discovery|login>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[iscsi] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("open-iscsi/2.1.10 started on :3260 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("iscsi service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, sessions=2, targets=1\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/iscsi/initiatorname.iscsi\n");
    } else if (strcmp(args[1], "discovery") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("Target: 192.168.1.50:3260,1 iqn.2024-01.local.lun0\n");
    } else if (strcmp(args[1], "login") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("login successful, LUN0 mapped to /dev/sdb - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_openvpn54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: openvpn54 <start|stop|status|config|clients>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[openvpn] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("openvpn/2.6.10 started on UDP:1194 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("openvpn service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, clients=5, bytes=24.3MB\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/openvpn/server.conf (auth SHA256)\n");
    } else if (strcmp(args[1], "clients") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("10.8.0.2 dev1 192.168.1.101 4d:12h (connected)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_wireguard54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: wireguard54 <start|stop|status|peers|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[wireguard] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("wg/1.0.20210914 started on :51820 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("wireguard service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("wg0 active, peers=4, latest_rx=2s ago\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/wireguard/wg0.conf (MTU=1420)\n");
    } else if (strcmp(args[1], "peers") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("Peer abc1... endpoint=1.2.3.4:51820 allowed=10.200.200.2/32\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_ipsec54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: ipsec54 <start|stop|status|config|restart>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[ipsec] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("strongswan/5.9.14 started on :500,:4500 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("ipsec service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, tunnels=2, SAs=8, bytes=128MB\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/ipsec.conf + secrets\n");
    } else if (strcmp(args[1], "restart") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("restarted, all connections re-established - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_pptp54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: pptp54 <start|stop|status|config|clients>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[pptp] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("pptpd/1.4.0 started on :1723 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("pptp service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, clients=2, pool=192.168.100.0/24\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/pptpd.conf (localip=192.168.100.1)\n");
    } else if (strcmp(args[1], "clients") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("192.168.100.2 user=vpnuser1 uptime=1:23:45\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_l2tp54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: l2tp54 <start|stop|status|config|clients>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[l2tp] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("xl2tpd/1.3.18 started on :1701 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("l2tp service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, tunnels=3, sessions=6, ipsec=yes\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/xl2tpd/xl2tpd.conf (IPsec=yes)\n");
    } else if (strcmp(args[1], "clients") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("Client 172.16.0.2 username=remote1 status=connected\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_fail2ban54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: fail2ban54 <start|stop|status|jails|ban>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[fail2ban] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("fail2ban/1.0.2 started - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("fail2ban service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, banned=47, failed=213, jails=12\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/fail2ban/jail.local (bantime=3600)\n");
    } else if (strcmp(args[1], "jails") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("sshd(42 banned) nginx-http-auth(5 banned) postfix-sasl(0)\n");
    } else if (strcmp(args[1], "ban") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("IP 203.0.113.42 banned in sshd jail - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_suricata54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: suricata54 <start|stop|status|rules|alerts>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[suricata] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("suricata/7.0.4 started - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("suricata service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, pkts=1.2M, alerts=84, drops=0\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/suricata/suricata.yaml (threads=4)\n");
    } else if (strcmp(args[1], "rules") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("ET Open 32014, ET Pro 18532, local rules 217\n");
    } else if (strcmp(args[1], "alerts") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("ET TROJAN Cobalt Strike Beacon (sid:2024312) x3\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_snort54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: snort54 <start|stop|status|rules|alerts>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[snort] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("snort/3.1.64 started - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("snort service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, pkts=2.4M, alerts=31, latency=0.2ms\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/snort/snort.conf (interface=eth0)\n");
    } else if (strcmp(args[1], "rules") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("Community 47281, Openappid 28462, Local 142\n");
    } else if (strcmp(args[1], "alerts") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("PROTOCOL-DNS named DoS attempt (sid:19861) x2\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_zeek54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: zeek54 <start|stop|status|logs|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[zeek] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("zeek/6.0.2 started - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("zeek service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, conn_log=482K, notices=12\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /opt/zeek/etc/zeekctl.cfg\n");
    } else if (strcmp(args[1], "logs") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("conn.log(482K) http.log(124K) dns.log(89K) notice.log(12)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_wazuh54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: wazuh54 <start|stop|status|agents|alerts>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[wazuh] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("wazuh-manager/4.8.0 started - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("wazuh service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, agents=18 online, alerts_today=342\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /var/ossec/etc/ossec.conf\n");
    } else if (strcmp(args[1], "agents") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("ID=001 web-server1 Active 192.168.1.10 | ID=002 db-server1 Active 192.168.1.20\n");
    } else if (strcmp(args[1], "alerts") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("Critical=2 High=14 Medium=38 Low=88 Total=342\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_osquery54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: osquery54 <start|stop|status|query|tables>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[osquery] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("osqueryd/5.13.1 started - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("osquery service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, uptime=5d:18h, queries=2408\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/osquery/osquery.conf\n");
    } else if (strcmp(args[1], "query") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("SELECT * FROM uptime; => 481523 (6d:17h:45m)\n");
    } else if (strcmp(args[1], "tables") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("257 tables loaded: processes, users, listening_ports, uptime...\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_elasticagent54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: elasticagent54 <start|stop|status|enroll|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[elastic-agent] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("elastic-agent/8.14.3 started - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("elastic-agent service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, fleet=connected, uptime=12d:04h\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/elastic-agent/elastic-agent.yml\n");
    } else if (strcmp(args[1], "enroll") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("enrolled in fleet, policy=production - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_prometheus54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: prometheus54 <start|stop|status|config|targets>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[prometheus] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("prometheus/2.52.0 started on :9090 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("prometheus service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, targets=18, series=248012, uptime=28d\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/prometheus/prometheus.yml\n");
    } else if (strcmp(args[1], "targets") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("18 targets up, 0 down, 3 job groups: node, app, db\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_grafana54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: grafana54 <start|stop|status|dashboards|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[grafana] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("grafana/10.4.1 started on :3000 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("grafana service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, dashboards=42, users=12, plugins=8\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/grafana/grafana.ini (auth.anonymous=false)\n");
    } else if (strcmp(args[1], "dashboards") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("Node Exporter Full | System Overview | DB Metrics | K8s Cluster\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_alertmanager54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: alertmanager54 <start|stop|status|silences|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[alertmanager] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("alertmanager/0.27.0 started on :9093 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("alertmanager service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, firing=3, suppressed=1, silences=2\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/alertmanager/alertmanager.yml\n");
    } else if (strcmp(args[1], "silences") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("#1 maintenance-window expires_in=2h:14m match=job=db\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_loki54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: loki54 <start|stop|status|labels|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[loki] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("loki/2.9.6 started on :3100 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("loki service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, streams=14238, ingested=2.4GB/day\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/loki/loki-config.yaml (retention=30d)\n");
    } else if (strcmp(args[1], "labels") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("Labels: app, namespace, level, job, instance, filename\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_tempo54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: tempo54 <start|stop|status|traces|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[tempo] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("tempo/2.5.0 started on :3200 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("tempo service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, traces=128490, spans=1.8M\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/tempo/config.yaml (storage=local)\n");
    } else if (strcmp(args[1], "traces") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("Recent: 3f2a1b.. (api-gateway, 84 spans, 23ms)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_mimir54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: mimir54 <start|stop|status|rulers|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[mimir] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("mimir/2.12.0 started on :8080 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("mimir service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, series=12.4M, tenants=8, ingesters=3\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/mimir/config.yaml (max_series=5M)\n");
    } else if (strcmp(args[1], "rulers") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("Ruler groups=14, active=12, pending=2, rule_files=28\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_thanos54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: thanos54 <start|stop|status|compact|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[thanos] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("thanos/0.35.1 started on :9090 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("thanos service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, blocks=24812, downsampling=5m\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: bucket=s3://thanos-metrics\n");
    } else if (strcmp(args[1], "compact") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("24 blocks compacted, 8 deleted - OK\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_clickhouse54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: clickhouse54 <start|stop|status|tables|query>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[clickhouse] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("clickhouse-server/24.3 started on :8123,:9000 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("clickhouse service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, tables=84, rows=1.2B, size=248GB\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/clickhouse-server/config.xml\n");
    } else if (strcmp(args[1], "tables") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("events(500M) metrics(400M) logs(280M) sessions(20M)\n");
    } else if (strcmp(args[1], "query") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("SELECT count(*) FROM events => 500,241,088 (0.34s)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_timescaledb54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: timescaledb54 <start|stop|status|hypertables|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[timescaledb] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("timescaledb/2.15.1 started on :5432 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("timescaledb service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, hypertables=6, chunks=2481, size=52GB\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/postgresql/16/main/postgresql.conf\n");
    } else if (strcmp(args[1], "hypertables") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("sensor_data(500M rows) metrics(280M) events(120M)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_questdb54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: questdb54 <start|stop|status|tables|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[questdb] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("questdb/7.4.3 started on :9000,:9009 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("questdb service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, tables=4, rows=820M, size=38GB\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/questdb/questdb.conf\n");
    } else if (strcmp(args[1], "tables") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("trades(400M) ohlcv(200M) ticks(180M) signals(40M)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_duckdb54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: duckdb54 <start|stop|status|tables|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[duckdb] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("duckdb/0.10.3 started - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("duckdb service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, tables=12, size=8.2GB, memory=2.1GB\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: in-process analytics engine\n");
    } else if (strcmp(args[1], "tables") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("parquet_files(48) csv_imports(12) query_results(8)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_surrealdb54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: surrealdb54 <start|stop|status|tables|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[surrealdb] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("surrealdb/1.5.4 started on :8000 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("surrealdb service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, namespaces=3, tables=18, records=241K\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: /etc/surrealdb/surrealdb.toml\n");
    } else if (strcmp(args[1], "tables") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("user(12K) post(45K) comment(89K) session(3K) event(92K)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

static void cmd_planetscale54(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: planetscale54 <start|stop|status|branches|config>\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("[planetscale] ");
    if (strcmp(args[1], "start") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("ps-connect/1.0 started on :3306 - OK\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_set_color(VGA_YELLOW, VGA_BLACK);
        vga_puts("planetscale service stopped - OK\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts("active, db=myapp, branch=main, replicas=2\n");
    } else if (strcmp(args[1], "config") == 0) {
        vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK);
        vga_puts("Config: ~/.planetscale/config.yaml\n");
    } else if (strcmp(args[1], "branches") == 0) {
        vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
        vga_puts("main(deployed) add-payments(PR #42) fix-index(open)\n");
    } else {
        vga_set_color(VGA_RED, VGA_BLACK);
        vga_puts("Unknown subcommand\n");
    }
}

