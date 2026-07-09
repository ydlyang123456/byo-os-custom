#!/usr/bin/env python3
"""BYO-OS Web Management Panel v3."""
import socket, threading, time, json, urllib.parse
from http.server import HTTPServer, BaseHTTPRequestHandler

SERIAL_PORT = 4321
HTTP_PORT = 7777


class SerialBridge:
    """Thread-safe serial-over-TCP bridge with automatic reconnection."""

    def __init__(self):
        self.sock = None
        self.lock = threading.Lock()
        self.ok = False
        self._last_attempt = 0.0

    def connect(self):
        try:
            if self.sock:
                self.sock.close()
        except Exception:
            pass
        self.sock = None
        self.ok = False
        self._last_attempt = time.time()
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.settimeout(3)
            self.sock.connect(("127.0.0.1", SERIAL_PORT))
            self.ok = True
            time.sleep(0.2)
            try:
                self.sock.recv(4096)
            except Exception:
                pass
            return True
        except Exception:
            self.ok = False
            return False

    def _ensure_connected(self):
        """Try to reconnect if not connected, with cooldown."""
        if self.ok:
            return True
        if time.time() - self._last_attempt < 2.0:
            return False
        return self.connect()

    def send(self, cmd, timeout=8.0):
        """Send a command and return the response string."""
        for attempt in range(2):
            if not self._ensure_connected():
                if attempt == 0:
                    continue
                return ""
            with self.lock:
                try:
                    self.sock.settimeout(0.1)
                    try:
                        while self.sock.recv(4096):
                            pass
                    except Exception:
                        pass
                    self.sock.sendall((cmd + "\r\n").encode())
                    resp = ""
                    self.sock.settimeout(timeout)
                    end = time.time() + timeout
                    while time.time() < end:
                        try:
                            d = self.sock.recv(4096)
                            if d:
                                resp += d.decode("utf-8", errors="ignore")
                            else:
                                break
                        except socket.timeout:
                            break
                        except Exception:
                            self.ok = False
                            break
                    return resp
                except Exception:
                    self.ok = False
                    if attempt == 0:
                        self.connect()
                        continue
                    return ""
        return ""


br = SerialBridge()

# ---------------------------------------------------------------------------
# HTML Panel
# ---------------------------------------------------------------------------
HTML = r''''
<!DOCTYPE html>
<html><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>BYO-OS Panel</title>
<style>
*{margin:0;padding:0;box-sizing:border-box}
body{font-family:system-ui,-apple-system,sans-serif;background:#0a0e1a;color:#e2e8f0;min-height:100vh}
#sb{position:fixed;width:210px;height:100%;background:#111827;border-right:1px solid #1e293b;display:flex;flex-direction:column;z-index:100}
#sb .logo{padding:18px;text-align:center;border-bottom:1px solid #1e293b}
#sb .logo h1{color:#38bdf8;font-size:17px;letter-spacing:1px}
#sb .logo p{color:#64748b;font-size:10px;margin-top:3px}
#sb nav{flex:1;overflow-y:auto;padding:8px 0}
#sb nav a{display:flex;align-items:center;gap:8px;padding:9px 16px;color:#94a3b8;text-decoration:none;font-size:13px;border-left:3px solid transparent;transition:all .15s}
#sb nav a:hover{background:#1e293b;color:#e2e8f0}
#sb nav a.on{color:#38bdf8;background:rgba(56,189,248,.08);border-left-color:#38bdf8}
#sb nav .sep{padding:4px 16px;font-size:10px;color:#475569;text-transform:uppercase;letter-spacing:1px;margin-top:8px}
#sb .ft{padding:10px 16px;border-top:1px solid #1e293b;font-size:10px;color:#475569}
#mn{margin-left:210px;padding:20px}
.pg{display:none}.pg.on{display:block}
h2{font-size:18px;margin-bottom:14px;font-weight:600}
.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(260px,1fr));gap:12px;margin-bottom:16px}
.card{background:#111827;border-radius:10px;padding:14px;border:1px solid #1e293b}
.card h3{color:#64748b;font-size:11px;text-transform:uppercase;margin-bottom:8px;letter-spacing:.5px}
.big{font-size:24px;font-weight:700}
.row{display:flex;justify-content:space-between;padding:6px 0;border-bottom:1px solid #1e293b;font-size:12px}
.row:last-child{border:none}
.lbl{color:#64748b}.val{color:#e2e8f0;font-weight:500}
.bar{background:#1e293b;border-radius:3px;height:5px;margin:6px 0}
.fill{height:100%;border-radius:3px;background:linear-gradient(90deg,#22c55e,#16a34a);transition:width .5s}
.fill.y{background:linear-gradient(90deg,#eab308,#ca8a04)}
.fill.r{background:linear-gradient(90deg,#ef4444,#dc2626)}
.g{color:#22c55e}.y{color:#eab308}.r{color:#ef4444}.b{color:#38bdf8}.dim{color:#64748b}
table{width:100%;border-collapse:collapse;font-size:12px}
th{text-align:left;padding:8px;color:#64748b;border-bottom:2px solid #1e293b;font-size:11px;text-transform:uppercase}
td{padding:7px 8px;border-bottom:1px solid #1e293b}
tr:hover td{background:rgba(56,189,248,.03)}
.btn{padding:5px 12px;border-radius:5px;border:none;cursor:pointer;font-size:11px;font-weight:600;transition:all .15s}
.bp{background:#38bdf8;color:#0f172a}.bp:hover{background:#0ea5e9}
.bd{background:#ef4444;color:#fff}.bd:hover{background:#dc2626}
.bg{background:#22c55e;color:#fff}.bg:hover{background:#16a34a}
.bk{background:#1e293b;color:#e2e8f0;border:1px solid #334155}.bk:hover{background:#334155}
.term{background:#0c0c0c;border-radius:8px;padding:12px;font-family:'Cascadia Code','Fira Code',monospace;font-size:12px;height:400px;overflow-y:auto;border:1px solid #1e293b;scroll-behavior:smooth}
.ti{display:flex;gap:6px;margin-top:8px}
.ti input{flex:1;background:#0c0c0c;border:1px solid #1e293b;color:#e2e8f0;padding:8px 12px;border-radius:6px;font-family:inherit;font-size:13px;outline:none}
.ti input:focus{border-color:#38bdf8}
.ti button{padding:8px 16px;background:#38bdf8;color:#0f172a;border:none;border-radius:6px;font-weight:600;cursor:pointer;font-size:13px}
.ti button:hover{background:#0ea5e9}
.c1{color:#38bdf8;font-weight:600}.c2{color:#e2e8f0}.c3{color:#ef4444}.c4{color:#22c55e}.c5{color:#eab308}
.bdg{display:inline-block;padding:2px 8px;border-radius:4px;font-size:10px;font-weight:700;background:#22c55e;color:#000;margin-left:8px;vertical-align:middle}
.bdg.off{background:#ef4444}
.dot{display:inline-block;width:8px;height:8px;border-radius:50%;background:#22c55e;margin-right:4px;vertical-align:middle;animation:pulse 2s infinite}
@keyframes pulse{0%,100%{opacity:1}50%{opacity:.4}}
.badge{display:inline-block;padding:1px 6px;border-radius:3px;font-size:9px;font-weight:600}
.badge.ok{background:#16a34a;color:#fff}
.badge.off{background:#64748b;color:#fff}
.mt{margin-top:10px}.mb{margin-bottom:10px}
pre{font-family:'Cascadia Code','Fira Code',monospace;white-space:pre-wrap;word-break:break-all;font-size:12px;line-height:1.5;color:#e2e8f0;margin:0}
.toast{position:fixed;bottom:20px;right:20px;background:#1e293b;border:1px solid #334155;border-radius:8px;padding:10px 16px;font-size:12px;color:#e2e8f0;z-index:999;opacity:0;transition:opacity .3s}
.toast.show{opacity:1}
.toast.err{border-color:#ef4444;color:#ef4444}
.fview{background:#0c0c0c;border-radius:8px;padding:12px;max-height:500px;overflow:auto;border:1px solid #1e293b}
.fview pre{margin:0}
</style>
</head><body>
<div id="sb">
<div class="logo"><h1>BYO-OS</h1><p>v0.2 Beta Panel</p></div>
<nav>
<a href="#" class="on" onclick="go('dash',this);return false">&#9632; Dashboard</a>
<a href="#" onclick="go('term',this);return false">&#9654; Terminal</a>
<div class="sep">System</div>
<a href="#" onclick="go('proc',this);return false">&#9881; Processes</a>
<a href="#" onclick="go('mon',this);return false">&#9734; Monitor</a>
<a href="#" onclick="go('file',this);return false">&#128193; File Manager</a>
<a href="#" onclick="go('log',this);return false">&#9998; System Logs</a>
<div class="sep">Network</div>
<a href="#" onclick="go('net',this);return false">&#9729; Network Config</a>
<a href="#" onclick="go('netmon',this);return false">&#9879; Connections</a>
<div class="sep">Admin</div>
<a href="#" onclick="go('user',this);return false">&#9775; Users</a>
<a href="#" onclick="go('svc',this);return false">&#9881; Services</a>
<a href="#" onclick="go('cron',this);return false">&#9200; Scheduler</a>
<div class="sep">Tools</div>
<a href="#" onclick="go('pkg',this);return false">&#128230; Packages</a>
<a href="#" onclick="go('backup',this);return false">&#9878; Backup</a>
<a href="#" onclick="go('set',this);return false">&#9881; Settings</a><div class="sep">Security</div>
<a href="#" onclick="go('sec',this);return false">&#128274; Security</a>
<div class="sep">Development</div>
<a href="#" onclick="go('dev',this);return false">&#128187; Dev Tools</a>
<div class="sep">Containers</div>
<a href="#" onclick="go('cont',this);return false">&#128230; Containers</a>
<div class="sep">Media</div>
<a href="#" onclick="go('media',this);return false">&#127909; Multimedia</a>
</nav>
<div class="ft" id="sfoot">Serial: checking...</div>
</div>

<div id="mn">
<!-- ===== Dashboard ===== -->
<div class="pg on" id="p-dash">
<h2>Dashboard <span class="dot"></span><span class="bdg" id="dashSt">ONLINE</span></h2>
<div class="grid">
<div class="card"><h3>System</h3><div class="big" id="di">--</div><div class="dim" style="font-size:11px;margin-top:2px">BYO-OS v0.2 Beta</div></div>
<div class="card"><h3>Uptime</h3><div class="big" id="du">--</div></div>
<div class="card"><h3>Tasks</h3><div class="big" id="dt">--</div></div>
<div class="card"><h3>User</h3><div class="big" id="dusr">--</div></div>
</div>
<div class="grid">
<div class="card" style="grid-column:span 2"><h3>Memory Usage</h3>
<div class="row"><span class="lbl">Used</span><span class="val" id="dmt">--</span></div>
<div class="row"><span class="lbl">Percent</span><span class="val" id="dmp">--</span></div>
<div class="bar"><div class="fill" id="dmb" style="width:0%"></div></div></div>
<div class="card"><h3>Platform</h3><div class="big" id="dplat">--</div><div class="dim" style="font-size:11px;margin-top:2px" id="darch">--</div></div>
<div class="card"><h3>Load Average</h3><div class="big" id="dload">--</div><div class="dim" style="font-size:11px;margin-top:2px">1 / 5 / 15 min</div></div>
</div>
<div class="card"><h3>Quick System Info</h3><pre id="dinfo" style="max-height:200px;overflow:auto">Loading...</pre></div>
</div>
<!-- ===== Terminal ===== -->
<div class="pg" id="p-term">
<h2>Web Terminal</h2>
<div class="term" id="tout"><div class="c4">=== BYO-OS Web Terminal ===</div><div class="c4">Type commands. Try: help, ls, cat, ps aux, free, uname, df, journal, awk, sed, strace, systemctl, netstat, awk, sed, strace, objdump, nice, watch, time, dmesg, lscpu, ip addr, ifconfig, diff, seq, base64, md5sum, factor</div><div class="c4">---</div></div>
<div class="ti"><input type="text" id="tinp" placeholder="Enter command..." onkeydown="if(event.key==='Enter')send()"><button onclick="send()">Send</button></div>
</div>
<!-- ===== Processes ===== -->
<div class="pg" id="p-proc">
<h2>Process Manager</h2>
<div style="display:flex;gap:8px;margin-bottom:12px">
<button class="btn bp" onclick="rproc()">Refresh</button>
<button class="btn bk" onclick="rcmd('ps aux','pcon')">ps aux</button>
<button class="btn bk" onclick="rcmd('top','pcon')">top</button>
<button class="btn bd" onclick="var p=prompt('PID to kill:');if(p)rcmd('kill '+p,'pcon')">Kill</button>
</div>
<div class="card" id="pcon"><p class="dim">Loading processes...</p></div>
</div>
<!-- ===== Monitor ===== -->
<div class="pg" id="p-mon">
<h2>System Monitor</h2>
<div class="grid">
<div class="card"><h3>CPU</h3><div class="big" id="mcu">x86 TCG</div><div class="dim" style="font-size:11px">QEMU emulated</div></div>
<div class="card"><h3>Memory</h3><div class="big" id="mmem">--</div>
<div class="bar"><div class="fill" id="mmb" style="width:0%"></div></div></div>
<div class="card"><h3>Heap</h3><div class="big" id="mheap">--</div></div>
<div class="card"><h3>Uptime</h3><div class="big" id="mup">--</div></div>
</div>
<div style="display:flex;gap:8px;margin-bottom:12px">
<button class="btn bp" onclick="rmon()">Refresh</button>
<button class="btn bk" onclick="rcmd('free','mcon')">free</button>
<button class="btn bk" onclick="rcmd('df','mcon')">df</button>
<button class="btn bk" onclick="rcmd('uptime','mcon')">uptime</button>
<button class="btn bk" onclick="rcmd('cat /proc/meminfo','mcon')">meminfo</button>
</div>
<div class="card" id="mcon"><p class="dim">Loading monitor data...</p></div>
</div>
<!-- ===== File Manager ===== -->
<div class="pg" id="p-file">
<h2>File Manager</h2>
<div style="display:flex;gap:8px;margin-bottom:12px">
<button class="btn bp" onclick="rfiles()">Refresh</button>
<button class="btn bk" onclick="mkfile()">New File</button>
<button class="btn bk" onclick="mkdir()">New Dir</button>
<button class="btn bk" onclick="rcmd('du','fcon')">du</button>
<button class="btn bk" onclick="rcmd('ls -la','fcon')">ls -la</button>
</div>
<div class="card" id="fcon"><p class="dim">Loading...</p></div>
<div id="fpreview" style="display:none"><div class="card mt"><h3 id="fprevTitle">File Content</h3><div class="fview"><pre id="fprevContent"></pre></div><div style="margin-top:8px"><button class="btn bk" onclick="document.getElementById('fpreview').style.display='none'">Close</button></div></div></div>
</div>
<!-- ===== System Logs ===== -->
<div class="pg" id="p-log">
<h2>System Logs</h2>
<div style="display:flex;gap:8px;margin-bottom:12px">
<button class="btn bp" onclick="rcmd('journal','lout')">Refresh</button>
<button class="btn bd" onclick="if(confirm('Clear logs?'))rcmd('journal clear','lout')">Clear Logs</button>
<button class="btn bk" onclick="rcmd('dmesg','lout')">dmesg</button>
<button class="btn bk" onclick="rcmd('journal error','lout')">Errors only</button>
</div>
<div class="term" id="lout"><div class="dim">Loading logs...</div></div>
</div>
<!-- ===== Network Config ===== -->
<div class="pg" id="p-net">
<h2>Network Configuration</h2>
<div id="netCards"><div class="dim">Loading network info...</div></div>
<div style="display:flex;gap:8px;margin-bottom:12px">
<button class="btn bp" onclick="rnet()">Refresh</button>
<button class="btn bk" onclick="rcmd('net','ncon')">net</button>
<button class="btn bk" onclick="rcmd('ifconfig','ncon')">ifconfig</button>
<button class="btn bk" onclick="rcmd('ip addr','ncon')">ip addr</button>
<button class="btn bk" onclick="rcmd('ip route','ncon')">ip route</button>
<button class="btn bk" onclick="rcmd('ping 10.0.2.2 -c 3','ncon')">ping gateway</button>
<button class="btn bk" onclick="rcmd('traceroute 8.8.8.8','ncon')">traceroute</button>
<button class="btn bk" onclick="rcmd('nslookup google.com','ncon')">nslookup</button>
</div>
<div class="card" id="ncon"><p class="dim">Network details loaded on page visit.</p></div>
</div>
<!-- ===== Connections ===== -->
<div class="pg" id="p-netmon">
<h2>Network Connections</h2>
<div style="display:flex;gap:8px;margin-bottom:12px">
<button class="btn bp" onclick="rcmd('net','nmcon')">Refresh</button>
<button class="btn bk" onclick="rcmd('netstat','nmcon')">netstat</button>
<button class="btn bk" onclick="rcmd('ss','nmcon')">ss</button>
<button class="btn bk" onclick="rcmd('cat /proc/net/tcp','nmcon')">raw TCP</button>
</div>
<div class="card" id="nmcon"><p class="dim">Loading connections...</p></div>
</div>
<!-- ===== Users ===== -->
<div class="pg" id="p-user">
<h2>User Management</h2>
<div style="display:flex;gap:8px;margin-bottom:12px">
<button class="btn bp" onclick="rcmd('users','ucon')">Refresh</button>
<button class="btn bk" onclick="rcmd('whoami','ucon')">whoami</button>
<button class="btn bk" onclick="rcmd('id','ucon')">id</button>
<button class="btn bk" onclick="rcmd('groups','ucon')">groups</button>
<button class="btn bk" onclick="rcmd('cat /etc/passwd','ucon')">passwd</button>
</div>
<div class="card" id="ucon"><p class="dim">Loading users...</p></div>
</div>
<!-- ===== Services ===== -->
<div class="pg" id="p-svc">
<h2>Service Management</h2>
<div style="display:flex;gap:8px;margin-bottom:12px">
<button class="btn bp" onclick="rcmd('service status','scon')">Refresh</button>
<button class="btn bk" onclick="rcmd('ps aux','scon')">All processes</button>
<button class="btn bk" onclick="rcmd('service list','scon')">Service list</button>
</div>
<div class="card" id="scon"><p class="dim">Loading services...</p></div>
</div>
<!-- ===== Scheduler ===== -->
<div class="pg" id="p-cron">
<h2>Task Scheduler</h2>
<div style="display:flex;gap:8px;margin-bottom:12px">
<button class="btn bp" onclick="rcmd('uptime','ccon')">Refresh</button>
<button class="btn bk" onclick="rcmd('date','ccon')">date</button>
<button class="btn bk" onclick="rcmd('ps aux','ccon')">ps aux</button>
<button class="btn bk" onclick="rcmd('cat /proc/uptime','ccon')">raw uptime</button>
</div>
<div class="card" id="ccon"><p class="dim">Scheduler info loaded from OS</p></div>
</div>
<!-- ===== Packages ===== -->
<div class="pg" id="p-pkg">
<h2>Package Manager</h2>
<div style="display:flex;gap:8px;margin-bottom:12px">
<button class="btn bp" onclick="rcmd('ls /bin','pkcon')">Refresh</button>
<button class="btn bk" onclick="rcmd('ls /bin','pkcon')">List /bin</button>
<button class="btn bk" onclick="rcmd('which ls','pkcon')">which ls</button>
<button class="btn bk" onclick="rcmd('cat /etc/os-release','pkcon')">os-release</button>
</div>
<div class="card" id="pkcon"><p class="dim">Loading packages...</p></div>
</div>
<!-- ===== Backup ===== -->
<div class="pg" id="p-backup">
<h2>Backup &amp; Restore</h2>
<div class="grid">
<div class="card"><h3>Quick Backup</h3>
<p class="dim" style="font-size:12px;margin-bottom:10px">Export filesystem listing</p>
<button class="btn bg" onclick="backup()">Backup Files</button></div>
<div class="card"><h3>System Info</h3>
<button class="btn bk" onclick="rcmd('uname -a','bsnap')">uname -a</button>
<button class="btn bk" onclick="rcmd('neofetch','bsnap')">neofetch</button>
<button class="btn bk" onclick="rcmd('df','bsnap')">df</button>
<button class="btn bk" onclick="rcmd('free','bsnap')">free</button>
</div>
<div class="card"><h3>Disk Usage</h3>
<button class="btn bk" onclick="rcmd('du -sh *','bsnap')">du -sh</button>
<button class="btn bk" onclick="rcmd('df -h','bsnap')">df -h</button>
</div>
</div>
<div class="card"><h3>Snapshot</h3><div id="bsnap"><p class="dim">Click Backup Files to capture a snapshot.</p></div></div>
</div>
<!-- ===== Settings ===== -->
<div class="pg" id="p-set">
<h2>Settings</h2>
<div class="grid">
<div class="card"><h3>System</h3>
<div class="row"><span>OS</span><span class="val">BYO-OS v0.2 Beta</span></div>
<div class="row"><span>Arch</span><span class="val">x86 (i686)</span></div>
<div class="row"><span>Boot</span><span class="val">GRUB 2.12</span></div>
<div class="row"><span>Display</span><span class="val">VGA Text 80x25</span></div></div>
<div class="card"><h3>Hardware</h3>
<div class="row"><span>CPU</span><span class="val">x86 QEMU TCG</span></div>
<div class="row"><span>RAM</span><span class="val">64 MB</span></div>
<div class="row"><span>Disk</span><span class="val">QEMU HDD</span></div>
<div class="row"><span>Network</span><span class="val">RTL8139</span></div></div>
<div class="card"><h3>Panel</h3>
<div class="row"><span>Serial Port</span><span class="val">127.0.0.1:4321</span></div>
<div class="row"><span>HTTP Port</span><span class="val">7777</span></div>
<div class="row"><span>Version</span><span class="val">v3.0</span></div>
<div class="row"><span>Refresh</span><span class="val">10s auto</span></div></div>
</div>
<div style="display:flex;gap:8px;margin-bottom:12px">
<button class="btn bp" onclick="rset()">Refresh Settings</button>
<button class="btn bk" onclick="rcmd('uname -a','setcon')">uname -a</button>
<button class="btn bk" onclick="rcmd('cat /etc/os-release','setcon')">os-release</button>
<button class="btn bk" onclick="rcmd('ls /sys','setcon')">/sys</button>
</div>
<div class="card" id="setcon"><p class="dim">Dynamic system info loaded on page visit.</p></div>
</div>
</div><!-- /mn -->

<!-- Toast -->
<div class="toast" id="toast"></div>
<!-- ===== System Info ===== -->

<div class="pg" id="p-sec">
<div class="card"><h2>&#128274; Security Center</h2>
<p>Firewall, authentication, and security scanning tools.</p>
<div class="row">
<button class="btn" onclick="rcmd('iptables -L','secout')">iptables -L</button>
<button class="btn" onclick="rcmd('nft list','secout')">nft list</button>
<button class="btn" onclick="rcmd('nmap 192.168.1.1','secout')">nmap scan</button>
<button class="btn" onclick="rcmd('nikto','secout')">nikto scan</button>
<button class="btn" onclick="rcmd('tcpdump','secout')">tcpdump</button>
<button class="btn" onclick="rcmd('passwd root','secout')">passwd root</button>
<button class="btn" onclick="rcmd('getent passwd','secout')">getent passwd</button>
<button class="btn" onclick="rcmd('getent group','secout')">getent group</button>
</div>
<div class="card mt"><pre id="secout" class="fview">Security tools output.</pre></div></div>
</div>

<div class="pg" id="p-dev">
<div class="card"><h2>&#128187; Development Tools</h2>
<p>Compilers, interpreters, editors, and debuggers.</p>
<div class="row">
<button class="btn" onclick="rcmd('gcc --version','devout')">gcc</button>
<button class="btn" onclick="rcmd('make --version','devout')">make</button>
<button class="btn" onclick="rcmd('git status','devout')">git status</button>
<button class="btn" onclick="rcmd('git log','devout')">git log</button>
<button class="btn" onclick="rcmd('python --version','devout')">python</button>
<button class="btn" onclick="rcmd('nodejs --version','devout')">node</button>
<button class="btn" onclick="rcmd('gdb --version','devout')">gdb</button>
<button class="btn" onclick="rcmd('valgrind --version','devout')">valgrind</button>
<button class="btn" onclick="rcmd('vim --version','devout')">vim</button>
<button class="btn" onclick="rcmd('strace ls','devout')">strace</button>
<button class="btn" onclick="rcmd('lsof','devout')">lsof</button>
</div>
<div class="card mt"><pre id="devout" class="fview">Dev tools output.</pre></div></div>
</div>

<div class="pg" id="p-cont">
<div class="card"><h2>&#128230; Containers & Virtualization</h2>
<p>Docker, Podman, and container management.</p>
<div class="row">
<button class="btn" onclick="rcmd('docker ps','contout')">docker ps</button>
<button class="btn" onclick="rcmd('docker images','contout')">docker images</button>
<button class="btn" onclick="rcmd('podman ps','contout')">podman ps</button>
<button class="btn" onclick="rcmd('systemd-nspawn','contout')">systemd-nspawn</button>
<button class="btn" onclick="rcmd('qemu-img','contout')">qemu-img</button>
</div>
<div class="card mt"><pre id="contout" class="fview">Container tools output.</pre></div></div>
</div>

<div class="pg" id="p-media">
<div class="card"><h2>&#127909; Multimedia</h2>
<p>Audio, video, and image processing tools.</p>
<div class="row">
<button class="btn" onclick="rcmd('ffmpeg -version','mediaout')">ffmpeg</button>
<button class="btn" onclick="rcmd('convert -version','mediaout')">ImageMagick</button>
<button class="btn" onclick="rcmd('mplayer','mediaout')">mplayer</button>
<button class="btn" onclick="rcmd('alsamixer','mediaout')">alsamixer</button>
</div>
<div class="card mt"><pre id="mediaout" class="fview">Multimedia output.</pre></div></div>
</div>
<div class="pg" id="p-sysinfo">
<h2>System Information</h2>
<div style="display:flex;gap:8px;margin-bottom:12px">
<button class="btn bp" onclick="rsysinfo()">Refresh</button>
<button class="btn bk" onclick="rcmd('uname -a','sicon')">uname -a</button>
<button class="btn bk" onclick="rcmd('lscpu','sicon')">lscpu</button>
<button class="btn bk" onclick="rcmd('lsblk','sicon')">lsblk</button>
<button class="btn bk" onclick="rcmd('fdisk','sicon')">fdisk</button>
<button class="btn bk" onclick="rcmd('mount','sicon')">mount</button>
<button class="btn bk" onclick="rcmd('dmesg','sicon')">dmesg</button>
<button class="btn bk" onclick="rcmd('neofetch','sicon')">neofetch</button>
<button class="btn bk" onclick="rcmd('cal','sicon')">cal</button>
</div>
<div class="card" id="sicon"><p class="dim">Loading system info...</p></div>
</div>
<!-- ===== Dev Tools ===== -->
<div class="pg" id="p-devtools">
<h2>Development Tools</h2>
<div style="display:flex;gap:8px;margin-bottom:12px;flex-wrap:wrap">
<button class="btn bp" onclick="rcmd('strace ls','dtout')">strace ls</button>
<button class="btn bk" onclick="rcmd('ltrace ls','dtout')">ltrace ls</button>
<button class="btn bk" onclick="rcmd('objdump kernel','dtout')">objdump</button>
<button class="btn bk" onclick="rcmd('readelf kernel','dtout')">readelf</button>
<button class="btn bk" onclick="rcmd('nm kernel','dtout')">nm</button>
<button class="btn bk" onclick="rcmd('file /bin/sh','dtout')">file</button>
<button class="btn bk" onclick="rcmd('awk \'{print}\' /etc/hostname','dtout')">awk</button>
<button class="btn bk" onclick="rcmd("sed 's/a/b/' /etc/hostname",'dtout')">sed</button>
<button class="btn bk" onclick="rcmd('base64 hello','dtout')">base64</button>
<button class="btn bk" onclick="rcmd('md5sum /etc/hostname','dtout')">md5sum</button>
<button class="btn bk" onclick="rcmd('time ls','dtout')">time</button>
<button class="btn bk" onclick="rcmd('which ls','dtout')">which</button>
<button class="btn bk" onclick="rcmd('seq 1 10','dtout')">seq</button>
<button class="btn bk" onclick="rcmd('factor 100','dtout')">factor</button>
<button class="btn bk" onclick="rcmd('expr 2 + 3','dtout')">expr</button>
</div>
<div class="card" id="dtout"><p class="dim">Click a button to run a command.</p></div>
</div>
<script>
var hist=[],hidx=-1,retryCount=0,MAX_RETRY=3;

/* ---- Toast notifications ---- */
function toast(msg,err){
var t=document.getElementById("toast");
t.textContent=msg;t.className=err?"toast show err":"toast show";
setTimeout(function(){t.className="toast"},3000);
}

/* ---- Navigation ---- */
function go(id,el){
var ps=document.querySelectorAll(".pg");
for(var i=0;i<ps.length;i++)ps[i].className="pg";
var ls=document.querySelectorAll("#sb nav a");
for(var i=0;i<ls.length;i++)ls[i].className="";
if(el)el.className="on";
var p=document.getElementById("p-"+id);
if(p)p.className="pg on";
if(id==='dash')rdash();
if(id==='proc')rproc();
if(id==='file')rfiles();
if(id==='user')rcmd('users','ucon');
if(id==='svc')rcmd('service status','scon');
if(id==='log')rcmd('journal','lout');
if(id==='net')rnet();
if(id==='devtools')rcmd('help','dtout');
if(id==='sysinfo')rsysinfo();
if(id==='netmon')rcmd('net','nmcon');
if(id==='cron'){rcmd('uptime','ccon');rcmd('date','ccon');}
if(id==='mon')rmon();
if(id==='sec'){rcmd('iptables -L','secout');rcmd('getent passwd','secout');}
if(id==='dev'){rcmd('gcc --version','devout');rcmd('git status','devout');}
if(id==='cont'){rcmd('docker ps','contout');}
if(id==='media'){rcmd('ffmpeg -version','mediaout');}
if(id==='pkg')rcmd('ls /bin','pkcon');
if(id==='set')rset();
}

/* ---- Terminal helpers ---- */
function addL(t,c,o){
var d=document.createElement("div");
d.className=c||"c2";
d.textContent=t;
var el=document.getElementById(o||"tout");
el.appendChild(d);
el.scrollTop=el.scrollHeight;
}
function clr(id){document.getElementById(id||"tout").innerHTML="";}

/* ---- Send command (Terminal) ---- */
function send(){
var i=document.getElementById("tinp");
var c=i.value.trim();
if(!c)return;
addL("$ "+c,"c1");
hist.unshift(c);hidx=-1;i.value="";
fetch("/api/exec",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({cmd:c})})
.then(function(r){if(!r.ok)throw new Error("HTTP "+r.status);return r.json()})
.then(function(d){
if(d.output)d.output.split("\n").forEach(function(l){if(l.trim())addL(l)});
if(d.error)addL("Error: "+d.error,"c3");
retryCount=0;
}).catch(function(e){
addL("Error: "+e,"c3");
toast("Network error: "+e,true);
retryCount++;
if(retryCount<MAX_RETRY)setTimeout(send,1000);
});
}

/* ---- Generic command runner ---- */
function rcmd(c,outid){
fetch("/api/exec",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({cmd:c})})
.then(function(r){if(!r.ok)throw new Error("HTTP "+r.status);return r.json()})
.then(function(d){
var el=document.getElementById(outid);
if(!el)el=document.getElementById("mcon");
if(d.output){
if(outid==='lout'){
el.innerHTML="";
d.output.split("\n").forEach(function(l){
var div=document.createElement("div");
if(l.indexOf("ERROR")>=0||l.indexOf("error")>=0)div.className="c3";
else if(l.indexOf("WARN")>=0||l.indexOf("warn")>=0)div.className="c5";
else div.className="c2";
div.textContent=l;el.appendChild(div);
});
}else{
el.innerHTML="<pre>"+escHtml(d.output)+"</pre>";
}
}else if(d.error){
el.innerHTML="<p class=\"r\">Error: "+escHtml(d.error)+"</p>";
}
}).catch(function(e){
var el=document.getElementById(outid);
if(el)el.innerHTML="<p class=\"r\">Network error: "+escHtml(String(e))+"</p>";
toast("Request failed",true);
});
}
function escHtml(s){return s.replace(/&/g,"&amp;").replace(/</g,"&lt;").replace(/>/g,"&gt;");}

function run(c){rcmd(c,"tout");}

/* ---- Dashboard refresh ---- */
function rdash(){
fetch("/api/sysinfo").then(function(r){if(!r.ok)throw new Error("HTTP "+r.status);return r.json()})
.then(function(d){
if(d.error){document.getElementById("dinfo").textContent="Error: "+d.error;return;}
if(d.ip)document.getElementById("di").textContent=d.ip;
if(d.uptime!==undefined){var h=Math.floor(d.uptime/3600),m=Math.floor((d.uptime%3600)/60),s=d.uptime%60;
document.getElementById("du").textContent=h+"h "+m+"m "+s+"s";
document.getElementById("mup").textContent=h+"h "+m+"m "+s+"s";
}
if(d.tasks!==undefined)document.getElementById("dt").textContent=d.tasks;
if(d.user)document.getElementById("dusr").textContent=d.user;
if(d.platform)document.getElementById("dplat").textContent=d.platform;
if(d.arch)document.getElementById("darch").textContent=d.arch;
if(d.load!==undefined)document.getElementById("dload").textContent=d.load;
if(d.mem_total&&d.mem_free!==undefined){
var u=d.mem_total-d.mem_free,p=Math.round(u/Math.max(d.mem_total,1)*100);
document.getElementById("dmt").textContent=u+"/"+d.mem_total+" MB";
document.getElementById("dmp").textContent=p+"%";
document.getElementById("dmb").style.width=p+"%";
document.getElementById("dmb").className="fill"+(p>80?" r":p>60?" y":"");
var mm=document.getElementById("mmem");if(mm)mm.textContent=u+"/"+d.mem_total+" MB";
var mb=document.getElementById("mmb");if(mb){mb.style.width=p+"%";mb.className="fill"+(p>80?" r":p>60?" y":"");}
}
if(d.heap_used!==undefined){var hh=document.getElementById("mheap");if(hh)hh.textContent=d.heap_used+" B";}
var info="Platform: "+(d.platform||"?")+"\nArch: "+(d.arch||"?")+"\nUser: "+(d.user||"?")+"\nUptime: "+(d.uptime||0)+"s\nTasks: "+(d.tasks||"?")+"\nLoad: "+(d.load||"-");
if(d.mem_total)info+="\nMemory: "+(d.mem_total-d.mem_free)+"/"+d.mem_total+" MB";
if(d.heap_used)info+="\nHeap: "+d.heap_used+" B";
document.getElementById("dinfo").textContent=info;
var ok=d.serial!==false;
document.getElementById("dashSt").textContent=ok?"ONLINE":"OFFLINE";
document.getElementById("dashSt").className=ok?"bdg":"bdg off";
document.getElementById("sfoot").textContent="Serial: "+(ok?"connected":"offline");
}).catch(function(e){
document.getElementById("dinfo").textContent="Failed to load: "+e;
document.getElementById("dashSt").textContent="ERROR";
document.getElementById("dashSt").className="bdg off";
toast("Dashboard refresh failed",true);
});
}

/* ---- Monitor refresh ---- */
function rmon(){
rdash();
rcmd('free','mcon');
}

/* ---- Process refresh ---- */
function rproc(){rcmd("ps aux","pcon");}

/* ---- File Manager ---- */
function rfiles(){
var el=document.getElementById("fcon");
el.innerHTML="<p class=\"dim\">Loading...</p>";
rcmd('ls','fcon');
setTimeout(function(){
fetch("/api/exec",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({cmd:"ls"})})
.then(function(r){if(!r.ok)throw new Error("HTTP "+r.status);return r.json()})
.then(function(d){
if(d.output){
var h="<table><tr><th>Name</th><th>Type</th><th>Actions</th></tr>";
d.output.split("\n").forEach(function(l){
l=l.trim();if(l){
var isDir=l.indexOf("DIR")>=0;
var name=l.replace(/\[DIR\]\s*/,"").replace(/\[FILE\]\s*/,"").trim();
h+="<tr><td>"+(isDir?"<span class=\"b\">"+escHtml(name)+"</span>":escHtml(name))+"</td>";
h+="<td>"+(isDir?"<span class=\"badge ok\">DIR</span>":"<span class=\"badge off\">FILE</span>")+"</td>";
h+="<td><button class=\"btn bk\" onclick=\"viewFile('"+escHtml(name)+"')\">View</button> ";
h+="<button class=\"btn bk\" onclick=\"rcmd('cat "+escHtml(name)+"','fcon')\">Raw</button> ";
h+="<button class=\"btn bd\" onclick=\"delFile('"+escHtml(name)+"')\">Delete</button></td></tr>";
});
h+="</table>";
el.innerHTML=h;
}
}).catch(function(){
el.innerHTML="<p class=\"r\">Failed to list files.</p>";
toast("File list failed",true);
});
},200);
}
function viewFile(name){
document.getElementById("fprevTitle").textContent="File: "+name;
document.getElementById("fpreview").style.display="block";
document.getElementById("fprevContent").textContent="Loading...";
fetch("/api/exec",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({cmd:"cat "+name})})
.then(function(r){return r.json()})
.then(function(d){
document.getElementById("fprevContent").textContent=d.output||d.error||"(empty)";
}).catch(function(e){
document.getElementById("fprevContent").textContent="Error: "+e;
});
}
function delFile(name){
if(!confirm('Delete "'+name+'"?'))return;
rcmd('rm '+name,'fcon');
setTimeout(rfiles,500);
}
function mkfile(){var n=prompt('File name:');if(n){var c=prompt('Content:');if(c!==null){rcmd('write '+n+' '+c,'fcon');setTimeout(rfiles,500);}}}
function mkdir(){var n=prompt('Directory name:');if(n){rcmd('mkdir '+n,'fcon');setTimeout(rfiles,500);}}

/* ---- Network info ---- */
function rnet(){
fetch("/api/exec",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({cmd:"ifconfig"})})
.then(function(r){return r.json()})
.then(function(d){
var el=document.getElementById("netCards");
if(d.output){
var h="<div class=\"grid\"><div class=\"card\"><h3>Interface Info</h3><pre>"+escHtml(d.output)+"</pre></div></div>";
el.innerHTML=h;
}else{
el.innerHTML="<p class=\"dim\">No network info available</p>";
}
rcmd('ifconfig','ncon');
}).catch(function(){
document.getElementById("netCards").innerHTML="<p class=\"r\">Failed to load network info</p>";
});
}

/* ---- Settings refresh ---- */
function rset(){
rcmd('uname -a','setcon');
}

/* ---- Backup snapshot ---- */
function backup(){
fetch("/api/exec",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({cmd:"ls"})})
.then(function(r){return r.json()})
.then(function(d){
var el=document.getElementById("bsnap");
if(d.output){
var lines=d.output.split("\n");
var h="<pre style=\"font-size:12px\">";
lines.forEach(function(l){h+=escHtml(l)+"\n";});
h+="</pre><p class=\"dim mt\">Snapshot captured at "+new Date().toLocaleTimeString()+"</p>";
el.innerHTML=h;
toast("Snapshot captured");
}
}).catch(function(){
toast("Backup failed",true);
});
}

/* ---- Serial ping ---- */
function pingSerial(){
fetch("/api/ping").then(function(r){return r.json()}).then(function(d){
var ok=d.serial;
document.getElementById("sfoot").textContent="Serial: "+(ok?"connected":"offline");
}).catch(function(){
document.getElementById("sfoot").textContent="Serial: error";
});
}

/* ---- Global refresh ---- */
function refresh(){
rdash();
pingSerial();
}

/* ---- Terminal history navigation ---- */
document.getElementById('tinp').addEventListener('keydown',function(e){
if(e.key==='ArrowUp'){e.preventDefault();if(hidx<hist.length-1){hidx++;this.value=hist[hidx];}}
if(e.key==='ArrowDown'){e.preventDefault();if(hidx>0){hidx--;this.value=hist[hidx];}else{hidx=-1;this.value='';}}
});

/* ---- Init ---- */
refresh();
setInterval(refresh,10000);

function rsysinfo(){
  var el=document.getElementById("sicon");
  el.innerHTML="<p class=\"dim\">Loading...</p>";
  fetch("/api/exec",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({cmd:"sysinfo"})})
  .then(r=>r.json()).then(d=>{
    if(d.output){
      var h="<pre>"+escHtml(d.output)+"</pre>";
      fetch("/api/exec",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({cmd:"uname -a"})})
      .then(r=>r.json()).then(d2=>{
        if(d2.output)h+="<hr style=\"border-color:#1e293b\"><pre>"+escHtml(d2.output)+"</pre>";
        el.innerHTML=h;
      }).catch(()=>el.innerHTML=h);
    } else el.innerHTML="<p class=\"r\">Failed</p>";
  }).catch(e=>el.innerHTML="<p class=\"r\">"+escHtml(String(e))+"</p>");
}
</script></body></html>

'''


class H(BaseHTTPRequestHandler):
    def do_GET(self):
        p = urllib.parse.urlparse(self.path).path
        if p == '/':
            self.send_response(200)
            self.send_header('Content-Type','text/html; charset=utf-8')
            self.end_headers()
            self.wfile.write(HTML.encode('utf-8'))
        elif p == '/api/sysinfo':
            raw = br.send("sysinfo", 2.0)
            info = None
            for line in raw.split('\n'):
                l = line.strip()
                if l.startswith('{') and l.endswith('}'):
                    try:
                        info = json.loads(l)
                    except Exception:
                        pass
            if info is None:
                info = {"error": "no data", "serial": br.ok}
            else:
                info["serial"] = br.ok
            self.j(info)
        elif p == '/api/ping':
            self.j({"ok": True, "serial": br.ok})
        else:
            self.send_response(404)
            self.end_headers()

    def do_POST(self):
        p = urllib.parse.urlparse(self.path).path
        cl = int(self.headers.get('Content-Length', 0))
        body = self.rfile.read(cl).decode('utf-8', errors='ignore')
        if p == '/api/exec':
            try:
                data = json.loads(body) if body else {}
                cmd = data.get('cmd', '')
                if not cmd:
                    self.j({"error": "no command"})
                    return
                resp = br.send(cmd, 8.0)
                lines_resp = resp.strip().split('\n')
                clean = '\n'.join(
                    l for l in lines_resp
                    if not l.startswith('root@byo-os>') and l.strip()
                )
                self.j({"output": clean})
            except json.JSONDecodeError:
                self.j({"error": "invalid JSON"})
            except Exception as e:
                self.j({"error": str(e)})
        else:
            self.send_response(404)
            self.end_headers()

    def do_OPTIONS(self):
        """Handle CORS preflight requests."""
        self.send_response(204)
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        self.end_headers()

    def j(self, d):
        b = json.dumps(d, ensure_ascii=False).encode('utf-8')
        self.send_response(200)
        self.send_header('Content-Type','application/json; charset=utf-8')
        self.send_header('Access-Control-Allow-Origin','*')
        self.end_headers()
        self.wfile.write(b)

    def log_message(self, *a):
        pass


if __name__ == '__main__':
    print("=== BYO-OS Web Management Panel v3 ===")
    print(f"Connecting to serial on 127.0.0.1:{SERIAL_PORT}...")
    br.connect()
    print("Serial: " + ("CONNECTED" if br.ok else "OFFLINE"))
    srv = HTTPServer(('0.0.0.0', HTTP_PORT), H)
    print(f"Panel: http://localhost:{HTTP_PORT}")
    try:
        srv.serve_forever()
    except KeyboardInterrupt:
        print("Stopped.")
