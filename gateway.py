#!/usr/bin/env python3
"""BYO-OS Web Management Panel v6 - Robust serial bridge."""
import socket, threading, time, json, urllib.parse, os, sys
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
        with self.lock:
            try:
                if self.sock:
                    self.sock.close()
            except:
                pass
            self.sock = None
            self.ok = False
            self._last_attempt = time.time()
            try:
                self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.sock.settimeout(5)
                self.sock.connect(("127.0.0.1", SERIAL_PORT))
                self.sock.settimeout(None)
                self.ok = True
                time.sleep(0.5)
                self._drain()
                return True
            except Exception as e:
                print(f"[WARN] Serial connect failed: {e}")
                self.ok = False
                return False

    def _drain(self):
        """Drain any pending data from serial buffer."""
        if not self.sock:
            return
        try:
            self.sock.settimeout(0.3)
            while True:
                d = self.sock.recv(4096)
                if not d:
                    break
        except:
            pass
        finally:
            try:
                self.sock.settimeout(None)
            except:
                pass

    def _ensure_connected(self):
        if self.ok:
            return True
        if time.time() - self._last_attempt < 3.0:
            return False
        return self.connect()

    def send_command(self, cmd, timeout=8.0):
        """Send command to BYO-OS via serial and wait for response."""
        if not self._ensure_connected():
            return "ERROR: Serial not connected to BYO-OS"

        with self.lock:
            try:
                # Drain stale data first
                self._drain()

                # Send command
                self.sock.settimeout(3)
                self.sock.sendall((cmd + "\n").encode())

                # Read response until BYO-OS> marker
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
                            # Check for command completion markers
                            if "BYO-OS>" in text or "BYO-OS $" in text:
                                break
                        else:
                            idle += 1
                            if idle > 8:
                                break
                    except socket.timeout:
                        idle += 1
                        if idle > 8:
                            break
                    except Exception:
                        self.ok = False
                        break

                result = resp.decode("utf-8", errors="ignore")
                # Clean up response: remove markers and prompt echoes
                clean_lines = []
                for line in result.split("\n"):
                    ls = line.strip()
                    if not ls:
                        continue
                    if ls in ("BYO-OS>", "BYO-OS $", "BYO-OS $ "):
                        continue
                    if ls.startswith("BYO-OS>"):
                        continue
                    clean_lines.append(line)
                return "\n".join(clean_lines)

            except Exception as e:
                self.ok = False
                try:
                    self.connect()
                except:
                    pass
                return f"ERROR: {e}"

br = SerialBridge()

# Load panel HTML
_panel_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'panel.html')
with open(_panel_path, 'r', encoding='utf-8') as _f:
    HTML = _f.read()

class H(BaseHTTPRequestHandler):
    def do_GET(self):
        p = urllib.parse.urlparse(self.path).path
        if p == "/" or p == "":
            self.send_response(200)
            self.send_header("Content-Type", "text/html; charset=utf-8")
            self.end_headers()
            self.wfile.write(HTML.encode("utf-8"))
        elif p == "/api/sysinfo":
            raw = br.send_command("sysinfo", 5.0)
            info = {
                "serial": br.ok,
                "os": "BYO-OS", "arch": "x86", "user": "root",
                "free_pages": 0, "total_pages": 0, "heap_used": 0,
                "uptime": 0, "platform": "BYO-OS",
                "tasks": 0, "load": "0.00", "ip": "10.0.2.15",
                "mem_total": 0, "mem_free": 0
            }
            for line in raw.split("\n"):
                l = line.strip()
                if "OS:" in l:
                    try: info["os"] = l.split("OS:")[1].strip(); info["platform"] = info["os"]
                    except: pass
                elif "Arch:" in l:
                    try: info["arch"] = l.split("Arch:")[1].strip()
                    except: pass
                elif "User:" in l:
                    try: info["user"] = l.split("User:")[1].strip()
                    except: pass
                elif "Free:" in l:
                    try:
                        fp = int(l.split("Free:")[1].strip().split()[0])
                        info["free_pages"] = fp
                        info["mem_free"] = fp * 4 // 1024
                    except: pass
                elif "Total:" in l:
                    try:
                        tp = int(l.split("Total:")[1].strip().split()[0])
                        info["total_pages"] = tp
                        info["mem_total"] = tp * 4 // 1024
                    except: pass
                elif "Heap:" in l:
                    try: info["heap_used"] = int(l.split("Heap:")[1].strip().split()[0])
                    except: pass
                elif "Uptime:" in l:
                    try: info["uptime"] = int(l.split("Uptime:")[1].strip().replace("s", ""))
                    except: pass
            # Also get task count
            task_raw = br.send_command("ps", 3.0)
            task_count = 0
            for tl in task_raw.split("\n"):
                tl = tl.strip()
                if tl and tl[0].isdigit():
                    task_count += 1
            if task_count > 0:
                info["tasks"] = task_count
            self.j(info)
        elif p == "/api/tasks":
            raw = br.send_command("ps", 3.0)
            self.j({"output": raw})
        elif p == "/api/files":
            raw = br.send_command("ls /", 3.0)
            self.j({"output": raw})
        elif p == "/api/network":
            raw = br.send_command("ifconfig", 3.0)
            self.j({"output": raw})
        elif p == "/api/logs":
            raw = br.send_command("journal", 3.0)
            self.j({"output": raw})
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
                self.j({"output": resp})
            except json.JSONDecodeError:
                self.j({"error": "invalid JSON"})
            except Exception as e:
                self.j({"error": str(e)})
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

    def log_message(self, *a):
        pass

if __name__ == "__main__":
    print("=" * 50)
    print("  BYO-OS Web Management Panel v6")
    print("=" * 50)
    print(f"Connecting to serial on 127.0.0.1:{SERIAL_PORT}...")
    br.connect()
    print(f"Serial: {'CONNECTED' if br.ok else 'OFFLINE'}")
    srv = HTTPServer(("0.0.0.0", HTTP_PORT), H)
    print(f"Panel:  http://localhost:{HTTP_PORT}")
    print("=" * 50)
    try:
        srv.serve_forever()
    except KeyboardInterrupt:
        print("\nStopped.")