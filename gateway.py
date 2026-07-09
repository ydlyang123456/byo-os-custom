#!/usr/bin/env python3
"""BYO-OS Web Management Panel v10 - Fixed serial bridge + robust API."""
import socket, threading, time, json, urllib.parse, os, sys, traceback
from http.server import HTTPServer, BaseHTTPRequestHandler

SERIAL_PORT = 4321
HTTP_PORT = 7777
PANEL_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "panel.html")

class SerialBridge:
    def __init__(self):
        self.sock = None
        self.lock = threading.Lock()
        self.ok = False
        self._last_attempt = 0.0
        self._debug_log = []
        self._last_response = ""
        self._connecting = False
        self._send_count = 0
        self._recv_count = 0

    def _log(self, msg):
        ts = time.strftime("%H:%M:%S")
        entry = f"[{ts}] {msg}"
        self._debug_log.append(entry)
        if len(self._debug_log) > 500:
            self._debug_log = self._debug_log[-500:]
        print(entry, flush=True)

    def connect(self, retries=5):
        if self._connecting:
            return False
        self._connecting = True
        try:
            with self.lock:
                for attempt in range(retries):
                    try:
                        if self.sock:
                            try: self.sock.close()
                            except: pass
                    except: pass
                    self.sock = None
                    self.ok = False
                    self._last_attempt = time.time()
                    try:
                        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                        self.sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
                        self.sock.settimeout(5)
                        self._log(f"Connecting to serial 127.0.0.1:{SERIAL_PORT} (attempt {attempt+1}/{retries})...")
                        self.sock.connect(("127.0.0.1", SERIAL_PORT))
                        self.sock.settimeout(None)
                        self.ok = True
                        time.sleep(1.0)
                        self._drain()
                        self._log("Serial CONNECTED OK")
                        return True
                    except Exception as e:
                        self._log(f"Connect attempt {attempt+1} failed: {e}")
                        self.ok = False
                        time.sleep(0.5)
                self._log("All connect attempts failed")
                return False
        finally:
            self._connecting = False

    def _drain(self):
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
        if self._connecting:
            return False
        if time.time() - self._last_attempt < 2.0:
            return False
        return self.connect()

    def _safe_send(self, data):
        try:
            self.sock.sendall(data)
            return True
        except (BrokenPipeError, ConnectionResetError, OSError) as e:
            self._log(f"Send failed: {e}")
            self.ok = False
            try: self.sock.close()
            except: pass
            self.sock = None
            return False

    def _safe_recv(self, size=4096):
        try:
            return self.sock.recv(size)
        except (ConnectionResetError, OSError) as e:
            self._log(f"Recv failed: {e}")
            self.ok = False
            try: self.sock.close()
            except: pass
            self.sock = None
            return b""

    def send_command(self, cmd, timeout=10.0):
        if not self._ensure_connected():
            return "ERROR: Serial not connected.\nStart QEMU with: qemu-system-i386 -cdrom byo-os.iso -m 128 -serial tcp::4321,server,nowait"

        with self.lock:
            try:
                self._drain()
                self._log(f"SEND: {cmd}")
                self._send_count += 1

                raw = (cmd + "\n").encode("utf-8")
                if not self._safe_send(raw):
                    return "ERROR: Send failed"

                resp = b""
                end_time = time.time() + timeout
                self.sock.settimeout(0.5)
                idle = 0
                while time.time() < end_time:
                    try:
                        d = self._safe_recv(4096)
                        if d:
                            resp += d
                            idle = 0
                            self._recv_count += 1
                            text = resp.decode("utf-8", errors="ignore")
                            # Stop when we see the shell prompt
                            if "BYO-OS>" in text or "BYO-OS $" in text:
                                break
                            # Also stop on common error patterns
                            if text.endswith("BYO-OS> ") or text.endswith("BYO-OS>"):
                                break
                        else:
                            idle += 1
                            if idle > 30:
                                break
                    except socket.timeout:
                        idle += 1
                        if idle > 30:
                            break
                    except Exception as e:
                        self._log(f"Recv error: {e}")
                        break

                self.sock.settimeout(None)
                result = resp.decode("utf-8", errors="ignore").strip()
                self._last_response = result
                self._log(f"RECV ({len(result)} chars): {result[:200]}")
                return result

            except Exception as e:
                self._log(f"Command error: {e}")
                self.ok = False
                try: self.sock.close()
                except: pass
                self.sock = None
                return f"ERROR: {e}"


br = SerialBridge()

class H(BaseHTTPRequestHandler):
    def do_GET(self):
        p = urllib.parse.urlparse(self.path).path
        q = urllib.parse.urlparse(self.path).query

        if p == "/" or p == "/index.html" or p == "/panel.html":
            try:
                with open(PANEL_FILE, "r", encoding="utf-8") as f:
                    html = f.read()
                self.send_response(200)
                self.send_header("Content-Type", "text/html; charset=utf-8")
                self.send_header("Cache-Control", "no-cache")
                self.end_headers()
                self.wfile.write(html.encode("utf-8"))
            except Exception as e:
                self.send_response(500)
                self.end_headers()
                self.wfile.write(str(e).encode())

        elif p == "/api/sysinfo":
            raw = br.send_command("sysinfo", 5.0)
            info = {
                "os": "BYO-OS", "arch": "x86 (i686)", "user": "root",
                "free_pages": 0, "total_pages": 0, "heap_used": 0,
                "uptime": 0, "platform": "BYO-OS", "tasks": 0,
                "load": "0.00", "ip": "10.0.2.15", "mem_total": 0, "mem_free": 0,
                "serial": br.ok, "raw": raw
            }
            for line in raw.split("\n"):
                l = line.strip()
                if l.startswith("OS:"):
                    try: info["os"] = l.split("OS:",1)[1].strip(); info["platform"] = info["os"]
                    except: pass
                elif l.startswith("Arch:"):
                    try: info["arch"] = l.split("Arch:",1)[1].strip()
                    except: pass
                elif l.startswith("User:"):
                    try: info["user"] = l.split("User:",1)[1].strip()
                    except: pass
                elif l.startswith("Free:"):
                    try:
                        fp = int(l.split("Free:",1)[1].strip().split()[0])
                        info["free_pages"] = fp; info["mem_free"] = fp * 4 // 1024
                    except: pass
                elif l.startswith("Total:"):
                    try:
                        tp = int(l.split("Total:",1)[1].strip().split()[0])
                        info["total_pages"] = tp; info["mem_total"] = tp * 4 // 1024
                    except: pass
                elif l.startswith("Heap:"):
                    try: info["heap_used"] = int(l.split("Heap:",1)[1].strip().split()[0])
                    except: pass
                elif l.startswith("Uptime:"):
                    try: info["uptime"] = int(l.split("Uptime:",1)[1].strip().replace("s","").strip())
                    except: pass
                elif l.startswith("Tasks:"):
                    try: info["tasks"] = int(l.split("Tasks:",1)[1].strip().split()[0])
                    except: pass
                elif l.startswith("Load:"):
                    try: info["load"] = l.split("Load:",1)[1].strip()
                    except: pass
                elif l.startswith("IP:"):
                    try: info["ip"] = l.split("IP:",1)[1].strip()
                    except: pass
            self._json(info)

        elif p == "/api/ping":
            self._json({"ok": True, "serial": br.ok, "send_count": br._send_count, "recv_count": br._recv_count})

        elif p == "/api/reconnect":
            ok = br.connect()
            self._json({"ok": ok, "serial": br.ok})

        elif p == "/api/debug":
            self._json({
                "serial": br.ok,
                "log": br._debug_log[-100:],
                "last_response": br._last_response[:500],
                "send_count": br._send_count,
                "recv_count": br._recv_count
            })

        elif p == "/api/shell":
            raw = br.send_command("help", 3.0)
            self._json({"output": raw, "serial": br.ok})

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
                    self._json({"error": "no command"})
                    return
                resp = br.send_command(cmd, 10.0)
                self._json({"output": resp})
            except json.JSONDecodeError:
                self._json({"error": "invalid JSON"})
            except Exception as e:
                self._json({"error": str(e)})
        else:
            self.send_response(404)
            self.end_headers()

    def do_OPTIONS(self):
        self.send_response(204)
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        self.end_headers()

    def _json(self, d):
        b = json.dumps(d, ensure_ascii=False).encode("utf-8")
        self.send_response(200)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()
        self.wfile.write(b)

    def log_message(self, *a):
        pass


def serial_retry_thread():
    while True:
        time.sleep(5)
        if not br.ok:
            br._log("Auto-retry: attempting reconnect...")
            br.connect(retries=2)


if __name__ == "__main__":
    print("=" * 60)
    print("  BYO-OS Web Management Panel v10")
    print("=" * 60)
    print(f"Panel file: {PANEL_FILE}")
    print(f"Connecting to serial on 127.0.0.1:{SERIAL_PORT}...")
    br.connect(retries=5)
    print(f"Serial: {'CONNECTED' if br.ok else 'OFFLINE (start QEMU first)'}")

    t = threading.Thread(target=serial_retry_thread, daemon=True)
    t.start()

    srv = HTTPServer(("0.0.0.0", HTTP_PORT), H)
    print(f"Panel:  http://localhost:{HTTP_PORT}")
    print(f"Debug:  http://localhost:{HTTP_PORT}/api/debug")
    print("=" * 60)
    try:
        srv.serve_forever()
    except KeyboardInterrupt:
        print("\nStopped.")
