#!/usr/bin/env python3
"""BYO-OS Batch 316: Docker, Database, Web Server, SSL, DevOps"""
import re, sys, io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')

BATCH = 316
NS = str(BATCH)

COMMANDS = [
    # Docker
    ("docker", "Docker container manager", [
        'if (argc < 2) { vga_puts("Usage: docker <command>\\n"); vga_puts("  run, ps, images, pull, stop, rm\\n"); return; }',
        'vga_printf("docker: executing %s\\n", args[1]);',
    ]),
    ("docker_ps", "List containers", [
        'vga_puts("CONTAINER ID  IMAGE  STATUS  PORTS\\n");',
        'vga_puts("a1b2c3d4e5f6  nginx  Up  0.0.0.0:80->80\\n");',
    ]),
    ("docker_run", "Run container", [
        'if (argc < 2) { vga_puts("Usage: docker run <image>\\n"); return; }',
        'vga_printf("docker run: starting %s\\n", args[1]);',
    ]),
    ("docker_images", "List images", [
        'vga_puts("REPOSITORY  TAG  SIZE\\n");',
        'vga_puts("nginx       latest  142MB\\n");',
        'vga_puts("mysql       8.0     514MB\\n");',
        'vga_puts("redis       7       138MB\\n");',
    ]),
    ("docker_stop", "Stop container", [
        'if (argc < 2) { vga_puts("Usage: docker stop <id>\\n"); return; }',
        'vga_printf("docker stop: stopping %s\\n", args[1]);',
    ]),
    ("docker_rm", "Remove container", [
        'if (argc < 2) { vga_puts("Usage: docker rm <id>\\n"); return; }',
        'vga_printf("docker rm: removing %s\\n", args[1]);',
    ]),
    ("docker_pull", "Pull image", [
        'if (argc < 2) { vga_puts("Usage: docker pull <image>\\n"); return; }',
        'vga_printf("docker pull: pulling %s\\n", args[1]);',
    ]),
    ("docker_logs", "Container logs", [
        'if (argc < 2) { vga_puts("Usage: docker logs <id>\\n"); return; }',
        'vga_printf("docker logs: %s\\n", args[1]);',
    ]),
    # Database
    ("mysql", "MySQL client", [
        'if (argc < 2) { vga_puts("Usage: mysql -e \\"QUERY\\"\\n"); return; }',
        'vga_puts("MySQL 8.0\\nConnected to localhost:3306\\n");',
    ]),
    ("mysql_dump", "Database backup", [
        'if (argc < 2) { vga_puts("Usage: mysqldump <db>\\n"); return; }',
        'vga_printf("mysqldump: backing up %s\\n", args[1]);',
    ]),
    ("redis_cli", "Redis client", [
        'vga_puts("Redis 7.0\\nConnected to localhost:6379\\n");',
    ]),
    ("redis_set", "Set Redis key", [
        'if (argc < 3) { vga_puts("Usage: redis-cli SET key value\\n"); return; }',
        'vga_printf("OK: %s = %s\\n", args[1], args[2]);',
    ]),
    ("redis_get", "Get Redis key", [
        'if (argc < 2) { vga_puts("Usage: redis-cli GET key\\n"); return; }',
        'vga_printf("(nil)\\n");',
    ]),
    ("psql", "PostgreSQL client", [
        'if (argc < 2) { vga_puts("Usage: psql -c \\"QUERY\\"\\n"); return; }',
        'vga_puts("PostgreSQL 15.0\\nConnected to localhost:5432\\n");',
    ]),
    # Web Server
    ("nginx", "Nginx control", [
        'if (argc < 2) { vga_puts("Usage: nginx <start|stop|reload>\\n"); return; }',
        'vga_printf("nginx: %s\\n", args[1]);',
    ]),
    ("nginx_test", "Test nginx config", [
        'vga_puts("nginx: configuration file test successful\\n");',
    ]),
    ("apache", "Apache control", [
        'if (argc < 2) { vga_puts("Usage: apache <start|stop>\\n"); return; }',
        'vga_printf("apache: %s\\n", args[1]);',
    ]),
    ("php_fpm", "PHP-FPM control", [
        'if (argc < 2) { vga_puts("Usage: php-fpm <start|stop>\\n"); return; }',
        'vga_printf("php-fpm: %s\\n", args[1]);',
    ]),
    # SSL
    ("openssl", "OpenSSL toolkit", [
        'if (argc < 2) { vga_puts("Usage: openssl <genrsa|req|x509>\\n"); return; }',
        'vga_printf("openssl: %s\\n", args[1]);',
    ]),
    ("certbot", "Let\'s Encrypt client", [
        'if (argc < 2) { vga_puts("Usage: certbot --nginx -d domain\\n"); return; }',
        'vga_puts("certbot: requesting certificate...\\n");',
    ]),
    # DevOps
    ("git_op", "Git operations", [
        'if (argc < 2) { vga_puts("Usage: git <clone|pull|push|commit>\\n"); return; }',
        'vga_printf("git: %s\\n", args[1]);',
    ]),
    ("ci_pipeline", "CI/CD pipeline", [
        'vga_puts("CI/CD Pipeline\\n");',
        'vga_puts("  Stage 1: Build      [OK]\\n");',
        'vga_puts("  Stage 2: Test       [OK]\\n");',
        'vga_puts("  Stage 3: Deploy     [OK]\\n");',
    ]),
    ("ansible", "Ansible playbook", [
        'if (argc < 2) { vga_puts("Usage: ansible-playbook site.yml\\n"); return; }',
        'vga_puts("ansible: running playbook...\\n");',
    ]),
    ("terraform", "Terraform IaC", [
        'if (argc < 2) { vga_puts("Usage: terraform <plan|apply|destroy>\\n"); return; }',
        'vga_printf("terraform: %s\\n", args[1]);',
    ]),
    ("kubectl", "Kubernetes CLI", [
        'if (argc < 2) { vga_puts("Usage: kubectl <get|apply|delete>\\n"); return; }',
        'vga_printf("kubectl: %s\\n", args[1]);',
    ]),
    # System Services
    ("systemctl_op", "System service control", [
        'if (argc < 2) { vga_puts("Usage: systemctl <start|stop|status> <service>\\n"); return; }',
        'vga_printf("systemctl: %s %s\\n", args[1], args[2] ? args[2] : "");',
    ]),
    ("journalctl_op", "View system logs", [
        'vga_puts("Jul 10 10:00:01 localhost kernel: System initialized\\n");',
        'vga_puts("Jul 10 10:00:02 localhost shell: Shell ready\\n");',
        'vga_puts("Jul 10 10:00:03 localhost network: Network configured\\n");',
    ]),
    # Monitoring
    ("htop_op", "Interactive process viewer", [
        'vga_puts("PID USER  CPU%  MEM%  COMMAND\\n");',
        'vga_puts("  1 root  0.0   0.1   /init\\n");',
        'vga_puts(" 12 root  0.1   0.3   shell\\n");',
        'vga_puts(" 15 root  0.2   0.5   gateway\\n");',
    ]),
    ("glances", "System monitor", [
        'vga_puts("CPU:    2.1%   MEM: 16.4MB/128MB   DISK: 20MB/128MB\\n");',
        'vga_puts("LOAD:   0.00   TASKS: 5   SWAP: 0MB\\n");',
    ]),
    ("nmon", "Performance monitor", [
        'vga_puts("CPU  [####        ] 32.1%%\\n");',
        'vga_puts("MEM  [##          ] 16.4%%\\n");',
        'vga_puts("DISK [##          ] 15.6%%\\n");',
    ]),
    # Backup
    ("bt_backup", "BT Panel backup", [
        'vga_puts("bt_backup: starting backup...\\n");',
        'vga_puts("  Backing up databases... OK\\n");',
        'vga_puts("  Backing up websites... OK\\n");',
        'vga_puts("  Backup complete: 15.2MB\\n");',
    ]),
    ("bt_restore", "BT Panel restore", [
        'if (argc < 2) { vga_puts("Usage: bt-restore <backup-file>\\n"); return; }',
        'vga_printf("bt-restore: restoring from %s\\n", args[1]);',
    ]),
    ("snap", "Snapshot manager", [
        'vga_puts("snap: creating snapshot...\\n");',
        'vga_puts("  Snapshot: snap-2025-07-10-001 (12.5MB)\\n");',
    ]),
    ("rsync_op", "Remote sync", [
        'if (argc < 3) { vga_puts("Usage: rsync -avz src dest\\n"); return; }',
        'vga_printf("rsync: syncing %s -> %s\\n", args[1], args[2]);',
    ]),
    # Firewall
    ("ufw", "Uncomplicated Firewall", [
        'if (argc < 2) { vga_puts("Usage: ufw <allow|deny|status>\\n"); return; }',
        'vga_printf("ufw: %s\\n", args[1]);',
    ]),
    ("iptables_op", "Firewall rules", [
        'vga_puts("Chain INPUT (policy ACCEPT)\\n");',
        'vga_puts("  target  prot  opt  source      destination\\n");',
        'vga_puts("  ACCEPT  tcp   --   0.0.0.0/0   0.0.0.0/0   tcp dpt:22\\n");',
        'vga_puts("  ACCEPT  tcp   --   0.0.0.0/0   0.0.0.0/0   tcp dpt:80\\n");',
        'vga_puts("  ACCEPT  tcp   --   0.0.0.0/0   0.0.0.0/0   tcp dpt:443\\n");',
    ]),
    # Package managers
    ("pip_op", "Python package manager", [
        'if (argc < 2) { vga_puts("Usage: pip <install|list>\\n"); return; }',
        'vga_printf("pip: %s\\n", args[1]);',
    ]),
    ("npm_op", "Node.js package manager", [
        'if (argc < 2) { vga_puts("Usage: npm <install|list>\\n"); return; }',
        'vga_printf("npm: %s\\n", args[1]);',
    ]),
    # Disk management
    ("lvm_op", "Logical Volume Manager", [
        'vga_puts("LVM Status\\n");',
        '  vga_puts("  VG: vg0  Size: 128GB  Free: 108GB\\n");',
        '  vga_puts("  LV: root Size: 20GB   Path: /dev/vg0/root\\n");',
    ]),
    ("zpool", "ZFS pool manager", [
        'vga_puts("zpool: no pools available\\n");',
    ]),
    # Load balancer
    ("haproxy", "HAProxy load balancer", [
        'if (argc < 2) { vga_puts("Usage: haproxy <start|stop|check>\\n"); return; }',
        'vga_printf("haproxy: %s\\n", args[1]);',
    ]),
    ("keepalived", "Keepalived VRRP", [
        'vga_puts("keepalived: VRRP instance MASTER\\n");',
        'vga_puts("  VIP: 192.168.1.100\\n");',
    ]),
    # Message queue
    ("rabbitmq", "RabbitMQ control", [
        'if (argc < 2) { vga_puts("Usage: rabbitmqctl <status>\\n"); return; }',
        'vga_puts("RabbitMQ 3.12\\nStatus: running\\nConnections: 0\\nQueues: 0\\n");',
    ]),
    ("kafka", "Apache Kafka", [
        'if (argc < 2) { vga_puts("Usage: kafka <topics|produce|consume>\\n"); return; }',
        'vga_printf("kafka: %s\\n", args[1]);',
    ]),
]

def build_fwd(name):
    return f"static void cmd_{name}{NS}(int argc, char args[][CMD_MAX_LEN]);\n"

def build_entry(name):
    return f'    {{"{name}", cmd_{name}{NS}}},\n'

def build_func(name, body):
    lines = [f"static void cmd_{name}{NS}(int argc, char args[][CMD_MAX_LEN]) {{\n"]
    for bl in body:
        lines.append(f"    {bl}\n")
    lines.append("}\n")
    return "".join(lines)

with open("kernel/shell.c", "r", encoding="utf-8", errors="replace") as f:
    code = f.read()

orig = code.count("\n")
print(f"Original: {orig} lines")

# 1. Forward declarations
fwd_pat = r'static void cmd_\w+\(int argc, char args\[\]\[CMD_MAX_LEN\]\);'
fwd_matches = list(re.finditer(fwd_pat, code))
if not fwd_matches:
    print("ERROR: no forward declarations"); sys.exit(1)
fwd_ins = fwd_matches[-1].end()
fwd_block = "\n" + "".join(build_fwd(n) for n, d, b in COMMANDS)
code = code[:fwd_ins] + fwd_block + code[fwd_ins:]
print(f"+{len(COMMANDS)} forward declarations")

# 2. Command table entries
tbl_start = code.find("static const cmd_entry commands[]")
tbl_entries = list(re.finditer(r'\{"(\w+)",\s*cmd_\w+\}', code[tbl_start:]))
last_entry = tbl_entries[-1]
tbl_ins = tbl_start + last_entry.end()
needs_comma = code[tbl_ins] != ","
tbl_block = ("," if needs_comma else "") + "\n" + "".join(build_entry(n) for n, d, b in COMMANDS)
code = code[:tbl_ins] + tbl_block + code[tbl_ins:]
print(f"+{len(COMMANDS)} table entries")

# 3. Function implementations
shell_run = code.find("void shell_run(void)")
func_block = "\n" + "".join(build_func(n, b) for n, d, b in COMMANDS) + "\n"
code = code[:shell_run] + func_block + code[shell_run:]
print(f"+{len(COMMANDS)} function implementations")

print(f"New: {code.count(chr(10))} lines")

with open("kernel/shell.c", "w", encoding="utf-8", newline="\n") as f:
    f.write(code)
print("Done!")