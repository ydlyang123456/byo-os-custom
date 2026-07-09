#!/usr/bin/env python3
"""BYO-OS Web Management Panel v4."""
import socket, threading, time, json, urllib.parse
from http.server import HTTPServer, BaseHTTPRequestHandler

SERIAL_PORT = 4321
HTTP_PORT = 7777

class SerialBridge:
    def __init__(self):
        self.sock = None
        self.lock = threading.Lock()
        self.ok = False
        self._last_attempt = 0.0

    def connect(self):
        try:
            if self.sock: self.sock.close()
        except: pass
        self.sock = None
        self.ok = False
        self._last_attempt = time.time()
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.settimeout(5)
            self.sock.connect(("127.0.0.1", SERIAL_PORT))
            self.sock.settimeout(None)
            self.ok = True
            time.sleep(0.3)
            try:
                self.sock.settimeout(0.2)
                while True:
                    d = self.sock.recv(4096)
                    if not d: break
            except: pass
            self.sock.settimeout(None)
            return True
        except Exception as e:
            self.ok = False
            return False

    def _ensure_connected(self):
        if self.ok: return True
        if time.time() - self._last_attempt < 2.0: return False
        return self.connect()

    def send_command(self, cmd, timeout=10.0):
        for attempt in range(3):
            if not self._ensure_connected():
                if attempt < 2: time.sleep(0.5); continue
                return "ERROR: Serial not connected"
            with self.lock:
                try:
                    try:
                        self.sock.settimeout(0.1)
                        while True:
                            d = self.sock.recv(4096)
                            if not d: break
                    except: pass
                    self.sock.settimeout(5)
                    self.sock.sendall((cmd + "\n").encode())
                    resp = b""
                    end_time = time.time() + timeout
                    self.sock.settimeout(1.0)
                    idle = 0
                    while time.time() < end_time:
                        try:
                            d = self.sock.recv(4096)
                            if d:
                                resp += d
                                idle = 0
                                text = resp.decode("utf-8", errors="ignore")
                                if "BYO-OS>" in text: break
                            else:
                                idle += 1
                                if idle > 5: break
                        except socket.timeout:
                            idle += 1
                            if idle > 5: break
                        except Exception:
                            self.ok = False
                            break
                    return resp.decode("utf-8", errors="ignore")
                except Exception as e:
                    self.ok = False
                    if attempt < 2: self.connect(); continue
                    return "ERROR: " + str(e)
        return "ERROR: Max retries"

br = SerialBridge()

HTML = open('/mnt/e/aisystem/byo-os/panel.html', 'r').read()

class H(BaseHTTPRequestHandler):
    def do_GET(self):
        p = urllib.parse.urlparse(self.path).path
        if p == "/" or p == "":
            self.send_response(200)
            self.send_header("Content-Type","text/html; charset=utf-8")
            self.end_headers()
            self.wfile.write(HTML.encode("utf-8"))
        elif p == "/api/sysinfo":
            raw = br.send_command("sysinfo", 5.0)
            info = {"serial": br.ok, "os": "BYO-OS v1.0.0", "arch": "x86", "user": "root",
                    "free_pages": 0, "total_pages": 0, "heap_used": 0, "uptime": 0,
                    "platform": "BYO-OS", "tasks": 8, "load": "0.15", "ip": "10.0.2.15",
                    "mem_total": 128, "mem_free": 128}
            for line in raw.split("\n"):
                l = line.strip()
                if "OS:" in l: info["os"] = l.split("OS:")[1].strip(); info["platform"] = info["os"]
                elif "Arch:" in l: info["arch"] = l.split("Arch:")[1].strip()
                elif "User:" in l: info["user"] = l.split("User:")[1].strip()
                elif "Free:" in l:
                    try:
                        fp = int(l.split("Free:")[1].strip().split()[0])
                        info["free_pages"] = fp; info["mem_free"] = fp * 4 // 1024
                    except: pass
                elif "Total:" in l:
                    try:
                        tp = int(l.split("Total:")[1].strip().split()[0])
                        info["total_pages"] = tp; info["mem_total"] = tp * 4 // 1024
                    except: pass
                elif "Heap:" in l:
                    try: info['heap_used'] = int(l.split('Heap:')[1].strip().split()[0])
                    except: pass
                elif "Uptime:" in l:
                    try: info["uptime"] = int(l.split("Uptime:")[1].strip().replace("s",""))
                    except: pass
            self.j(info)
        elif p == "/api/ping":
            self.j({"ok": True, "serial": br.ok})
        elif p == "/api/reconnect":
            ok = br.connect()
            self.j({"ok": ok})
        else:
            self.send_response(404)
            self.end_headers()

    def do_POST(self):
        p = urllib.parse.urlparse(self.path).path
        cl = int(self.headers.get("Content-Length", 0))
        body = self.rfile.read(cl).decode("utf-8", errors="ignore") if cl > 0 else ""
        if p == "/api/exec":
            try:
                data = json.loads(body) if body else {}
                cmd = data.get("cmd", "").strip()
                if not cmd:
                    self.j({"error": "no command"})
                    return
                resp = br.send_command(cmd, 10.0)
                lines_resp = resp.split("\n")
                clean = []
                for l in lines_resp:
                    ls = l.strip()
                    if not ls: continue
                    if ls.startswith("BYO-OS"): continue
                    if ls == "BYO-OS>": continue
                    clean.append(l)
                self.j({"output": "\n".join(clean)})
            except json.JSONDecodeError:
                self.j({"error": "invalid JSON"})
            except Exception as e:
                self.j({'error': str(e)})
        else:
            self.send_response(404)
            self.end_headers()

    def do_OPTIONS(self):
        self.send_response(204)
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.end_headers()

    def j(self, d):
        b = json.dumps(d, ensure_ascii=False).encode("utf-8")
        self.send_response(200)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()
        self.wfile.write(b)

    def log_message(self, *a): pass

if __name__ == "__main__":
    print("=== BYO-OS Web Management Panel v4 ===")
    print("Connecting to serial on 127.0.0.1:" + str(SERIAL_PORT) + "...")
    br.connect()
    print("Serial: " + ("CONNECTED" if br.ok else "OFFLINE"))
    srv = HTTPServer(("0.0.0.0", HTTP_PORT), H)
    print("Panel: http://localhost:" + str(HTTP_PORT))
    try:
        srv.serve_forever()
    except KeyboardInterrupt:
        print("Stopped.")
