#!/usr/bin/env python3
"""BYO-OS Web Management Gateway v15 - Full REST API for Web Panel."""
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
        self._last_cmd_time = 0.0
        self._min_cmd_interval = 0.05

    def _log(self, msg):
        ts = time.strftime("%H:%M:%S")
        entry = f"[{ts}] {msg}"
        self._debug_log.append(entry)
        if len(self._debug_log) > 500:
            self._debug_log = self._debug_log[-500:]
        print(entry, flush=True)

    def get_logs(self, n=100):
        return self._debug_log[-n:]

    def get_stats(self):
        return {
            "serial": self.ok,
            "send_count": self._send_count,
            "recv_count": self._recv_count,
            "last_response_len": len(self._last_response)
        }

    def connect(self, retries=5):
        if self._connecting:
            return False
        self._connecting = True
        try:
            with self.lock:
                for attempt in range(retries):
                    try:
                        if self.sock:
                            try:
                                self.sock.close()
                            except:
                                pass
                    except:
                        pass
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
                        time.sleep(0.3)
                        self._flush_buffer()
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

    def _flush_buffer(self):
        if not self.sock:
            return
        try:
            self.sock.settimeout(0.2)
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
            try:
                self.sock.close()
            except:
                pass
            self.sock = None
            return False

    def _safe_recv(self, size=4096):
        try:
            return self.sock.recv(size)
        except (ConnectionResetError, OSError) as e:
            self._log(f"Recv failed: {e}")
            self.ok = False
            try:
                self.sock.close()
            except:
                pass
            self.sock = None
            return b""

    def send_command(self, cmd, timeout=10.0):
        if not self._ensure_connected():
            return "ERROR: Serial not connected.\nStart QEMU with: -serial tcp::4321,server,nowait"

        now = time.time()
        elapsed = now - self._last_cmd_time
        if elapsed < self._min_cmd_interval:
            time.sleep(self._min_cmd_interval - elapsed)

        with self.lock:
            try:
                self._log(f"SEND: {cmd}")
                self._send_count += 1

                raw = (cmd + "\n").encode("utf-8")
                if not self._safe_send(raw):
                    return "ERROR: Send failed"

                resp = b""
                end_time = time.time() + timeout
                self.sock.settimeout(0.3)
                empty_reads = 0

                while time.time() < end_time:
                    try:
                        d = self._safe_recv(4096)
                        if d:
                            resp += d
                            self._recv_count += 1
                            empty_reads = 0
                            text = resp.decode("utf-8", errors="ignore")
                            if text.rstrip().endswith("BYO-OS>") or text.rstrip().endswith("$"):
                                break
                            if "BYO-OS>" in text:
                                break
                        else:
                            empty_reads += 1
                            if empty_reads > 25:
                                break
                    except socket.timeout:
                        empty_reads += 1
                        if empty_reads > 25:
                            break
                    except Exception as e:
                        self._log(f"Recv error: {e}")
                        break

                self.sock.settimeout(None)
                text = resp.decode("utf-8", errors="ignore")

                lines = text.split("\n")
                clean_lines = []
                for line in lines:
                    stripped = line.strip()
                    if stripped == cmd.strip():
                        continue
                    if stripped == "BYO-OS>" or stripped == "BYO-OS> ":
                        continue
                    if stripped.startswith("BYO-OS>"):
                        after = stripped[7:].strip()
                        if after:
                            clean_lines.append(after)
                        continue
                    clean_lines.append(line)

                result = "\n".join(clean_lines).strip()
                self._last_response = result[:500]
                self._log(f"RECV ({len(result)} bytes): {result[:100]}...")
                self._last_cmd_time = time.time()
                return result

            except Exception as e:
                self._log(f"send_command error: {e}")
                self.ok = False
                try:
                    self.sock.close()
                except:
                    pass
                self.sock = None
                return f"ERROR: {e}"


br = SerialBridge()


# ── Helper: build /api/status dict from multiple serial commands ──
def get_status_dict():
    """Run multiple serial commands and build a unified status dict."""
    status = {
        "serial": br.ok,
        "uptime": "0:00:00",
        "memory_total": 0, "memory_used": 0, "memory_free": 0,
        "disk_total": 0, "disk_used": 0, "disk_free": 0,
        "processes": 0, "cpu_load": "0.00",
        "hostname": "byo-os", "os": "BYO-OS x86_64"
    }
    if not br.ok:
        return status

    # ── free (memory) ──
    raw = br.send_command("free", 5.0)
    for line in raw.split("\n"):
        parts = line.split()
        if len(parts) < 2:
            continue
        low = line.lower()
        if low.startswith("mem:") or "mem:" in low:
            try:
                status["memory_total"] = int(parts[1]) if len(parts) > 1 else 0
                status["memory_used"] = int(parts[2]) if len(parts) > 2 else 0
                status["memory_free"] = int(parts[3]) if len(parts) > 3 else 0
            except:
                pass

    # ── df / (disk) ──
    raw = br.send_command("df /", 5.0)
    for line in raw.split("\n"):
        parts = line.split()
        if len(parts) >= 6 and parts[0].startswith("/"):
            try:
                status["disk_total"] = int(parts[1])
                status["disk_used"] = int(parts[2])
                status["disk_free"] = int(parts[3])
            except:
                pass

    # ── uptime ──
    raw = br.send_command("uptime", 5.0)
    status["uptime"] = raw.strip()[:80]
    # try to extract load from uptime output
    for line in raw.split("\n"):
        if "load average:" in line.lower():
            parts = line.split("load average:")
            if len(parts) > 1:
                status["cpu_load"] = parts[1].strip().split(",")[0].strip()

    # ── ps (process count) ──
    raw = br.send_command("ps aux 2>/dev/null | wc -l", 5.0)
    try:
        count = int(raw.strip().split("\n")[-1].strip())
        status["processes"] = max(0, count - 1)
    except:
        pass

    # ── hostname ──
    raw = br.send_command("cat /etc/hostname 2>/dev/null || hostname", 5.0)
    hostname = raw.strip().split("\n")[0].strip()
    if hostname:
        status["hostname"] = hostname

    # ── os-release ──
    raw = br.send_command("cat /etc/os-release 2>/dev/null | head -5", 5.0)
    for line in raw.split("\n"):
        low = line.strip().lower()
        if low.startswith("pretty_name=") or low.startswith("name="):
            status["os"] = line.split("=", 1)[1].strip().strip('"').strip("'")
        elif low.startswith("id="):
            if status["os"] == "BYO-OS x86_64":
                status["os"] = line.split("=", 1)[1].strip().strip('"').strip("'")

    return status


# ── HTTP Request Handler ──────────────────────────────────────────
class H(BaseHTTPRequestHandler):
    def do_GET(self):
        p = urllib.parse.urlparse(self.path).path
        q = urllib.parse.parse_qs(urllib.parse.urlparse(self.path).query)

        if p == "/" or p == "/index.html":
            try:
                with open(PANEL_FILE, "rb") as f:
                    data = f.read()
                self.send_response(200)
                self.send_header("Content-Type", "text/html; charset=utf-8")
                self.send_header("Access-Control-Allow-Origin", "*")
                self.send_header("Cache-Control", "no-cache, no-store, must-revalidate")
                self.end_headers()
                self.wfile.write(data)
            except Exception as e:
                self.send_response(500)
                self.end_headers()
                self.wfile.write(str(e).encode())

        elif p == "/api/status":
            self._json(get_status_dict())

        elif p == "/api/logs":
            logs = br.get_logs(100)
            self._json({"logs": logs, "serial": br.ok})

        elif p == "/api/panel":
            result = {"services": [], "ports": [], "serial": br.ok}
            if br.ok:
                for svc in ["nginx", "mysql", "bt_panel"]:
                    raw = br.send_command(f"service {svc} status 2>/dev/null", 5.0)
                    running = "running" in raw.lower() or "active" in raw.lower()
                    result["services"].append({
                        "name": svc, "running": running, "raw": raw[:200]
                    })
                port_defs = [
                    (80, "HTTP (nginx)"), (443, "HTTPS"),
                    (8888, "宝塔面板"), (3306, "MySQL"), (22, "SSH")
                ]
                raw_net = br.send_command("netstat -tlnp 2>/dev/null || ss -tlnp 2>/dev/null || echo no_netstat", 5.0)
                for port_num, svc_name in port_defs:
                    result["ports"].append({
                        "port": port_num,
                        "service": svc_name,
                        "status": "listening" if str(port_num) in raw_net else "closed"
                    })
            self._json(result)

        elif p == "/api/network_stats":
            result = {"interfaces": [], "serial": br.ok}
            if br.ok:
                raw = br.send_command("ip addr show 2>/dev/null || ifconfig 2>/dev/null || echo no_ip", 5.0)
                result["raw"] = raw
                current_iface = None
                for line in raw.split("\n"):
                    s = line.strip()
                    if s and not s.startswith(" ") and not s.startswith("\t"):
                        if ":" in s and ("mtu" in s.lower() or "flags" in s.lower()):
                            name_part = s.split(":")[1].strip() if len(s.split(":")) > 1 else s.split()[0]
                            name = name_part.split()[0] if name_part else s.split()[0]
                            current_iface = {"name": name, "ip": "", "mac": "", "status": "down"}
                            result["interfaces"].append(current_iface)
                            if "UP" in s.upper() or "LOWER_UP" in s.upper():
                                current_iface["status"] = "up"
                    else:
                        if current_iface:
                            if "inet " in s:
                                parts = s.split()
                                if len(parts) > 1:
                                    current_iface["ip"] = parts[1].split("/")[0]
                            elif "ether " in s or "link/ether" in s:
                                parts = s.split()
                                for i, p in enumerate(parts):
                                    if p in ("ether", "link/ether") and i + 1 < len(parts):
                                        current_iface["mac"] = parts[i + 1]
            self._json(result)

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

        elif p == "/api/commands":
            raw = br.send_command("help", 5.0)
            self._json({"output": raw, "serial": br.ok})

        elif p == "/api/services":
            raw = br.send_command("service list 2>/dev/null || ls /etc/init.d/ 2>/dev/null || echo no_services", 3.0)
            self._json({"output": raw, "serial": br.ok})

        elif p == "/api/network":
            raw = br.send_command("net", 3.0)
            self._json({"output": raw, "serial": br.ok})

        elif p == "/api/users":
            raw = br.send_command("cat /etc/passwd 2>/dev/null || users", 3.0)
            self._json({"output": raw, "serial": br.ok})

        elif p == "/api/disk":
            raw = br.send_command("df -h 2>/dev/null || df", 3.0)
            self._json({"output": raw, "serial": br.ok})

        elif p == "/api/processes":
            raw = br.send_command("ps aux 2>/dev/null || ps", 3.0)
            self._json({"output": raw, "serial": br.ok})

        elif p == "/api/bt_panel":
            raw = br.send_command("bt_panel status 2>/dev/null || echo bt_panel_not_found", 3.0)
            self._json({"output": raw, "serial": br.ok})

        elif p == "/api/debian_info":
            raw = br.send_command("cat /etc/os-release 2>/dev/null || cat /etc/issue 2>/dev/null || echo unknown", 3.0)
            self._json({"output": raw, "serial": br.ok})

        elif p == "/api/sysinfo":
            raw = br.send_command("sysinfo 2>/dev/null || uname -a", 5.0)
            self._json({"output": raw, "serial": br.ok})

        elif p == "/api/file/download":
            try:
                path = q.get("path", [""])[0]
                if not path:
                    self.send_response(400)
                    self.end_headers()
                    self.wfile.write(b"missing path")
                    return
                resp = br.send_command(f"cat {path} 2>&1", 10.0)
                self.send_response(200)
                self.send_header("Content-Type", "application/octet-stream")
                self.send_header("Content-Disposition", f'attachment; filename="{os.path.basename(path)}"')
                self.send_header("Access-Control-Allow-Origin", "*")
                self.end_headers()
                self.wfile.write(resp.encode("utf-8"))
            except Exception as e:
                self.send_response(500)
                self.end_headers()
                self.wfile.write(str(e).encode())

        else:
            self.send_response(404)
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(b'{"error":"not found"}')

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

        elif p == "/api/terminal":
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

        elif p == "/api/service_control":
            try:
                data = json.loads(body) if body else {}
                action = data.get("action", "").strip()
                service = data.get("service", "").strip()
                if action in ("start", "stop", "restart") and service:
                    resp = br.send_command(f"service {service} {action} 2>&1", 10.0)
                elif action == "status" and service:
                    resp = br.send_command(f"service {service} status 2>&1", 5.0)
                else:
                    resp = f"ERROR: invalid action '{action}' or service '{service}'"
                self._json({"output": resp, "action": action, "service": service})
            except Exception as e:
                self._json({"error": str(e)})

        elif p == "/api/user_manage":
            try:
                data = json.loads(body) if body else {}
                action = data.get("action", "").strip()
                username = data.get("username", "").strip()
                password = data.get("password", "").strip()
                if not action or not username:
                    self._json({"error": "missing action or username"})
                    return
                if action == "add":
                    if password:
                        cmd = f"useradd -m {username} 2>&1 && echo '{username}:{password}' | chpasswd 2>&1"
                    else:
                        cmd = f"useradd -m {username} 2>&1"
                elif action == "delete":
                    cmd = f"userdel -r {username} 2>&1"
                else:
                    cmd = f"echo unknown action: {action}"
                resp = br.send_command(cmd, 10.0)
                self._json({"output": resp, "action": action, "username": username})
            except Exception as e:
                self._json({"error": str(e)})

        elif p == "/api/bt_install":
            try:
                data = json.loads(body) if body else {}
                action = data.get("action", "install").strip()
                if action == "install":
                    resp = br.send_command("bt_panel install 2>&1", 30.0)
                elif action == "start":
                    resp = br.send_command("bt_panel start 2>&1", 5.0)
                elif action == "stop":
                    resp = br.send_command("bt_panel stop 2>&1", 5.0)
                elif action == "restart":
                    resp = br.send_command("bt_panel restart 2>&1", 5.0)
                else:
                    resp = br.send_command(f"bt_panel {action} 2>&1", 10.0)
                self._json({"output": resp, "serial": br.ok})
            except Exception as e:
                self._json({"error": str(e)})

        elif p == "/api/file/list":
            try:
                data = json.loads(body) if body else {}
                path = data.get("path", "/")
                resp = br.send_command(f"ls -la {path} 2>&1", 5.0)
                files = []
                for line in resp.split("\n"):
                    line = line.strip()
                    if not line or line.startswith("total ") or line.startswith("总计"):
                        continue
                    parts = line.split()
                    if len(parts) >= 9:
                        name = " ".join(parts[8:])
                        if name in (".", ".."):
                            continue
                        perms = parts[0]
                        is_dir = perms.startswith("d")
                        try:
                            size = int(parts[4])
                        except:
                            size = 0
                        files.append({
                            "name": name,
                            "size": size,
                            "is_dir": is_dir,
                            "perms": perms,
                            "modified": " ".join(parts[5:8])
                        })
                self._json({"files": files, "path": path, "count": len(files)})
            except Exception as e:
                self._json({"error": str(e)})

        elif p == "/api/file/read":
            try:
                data = json.loads(body) if body else {}
                path = data.get("path", "")
                if not path:
                    self._json({"error": "missing path"})
                    return
                resp = br.send_command(f"cat {path} 2>&1", 5.0)
                self._json({"content": resp, "path": path})
            except Exception as e:
                self._json({"error": str(e)})

        elif p == "/api/file/write":
            try:
                data = json.loads(body) if body else {}
                path = data.get("path", "")
                content = data.get("content", "")
                if not path:
                    self._json({"error": "missing path"})
                    return
                # Use a heredoc approach
                escaped = content.replace("'", "'\\''")
                cmd = f"cat > {path} << 'ENDOFFILE'\n{content}\nENDOFFILE"
                resp = br.send_command(cmd, 10.0)
                self._json({"output": resp, "path": path, "size": len(content)})
            except Exception as e:
                self._json({"error": str(e)})

        elif p == "/api/file/delete":
            try:
                data = json.loads(body) if body else {}
                path = data.get("path", "")
                is_dir = data.get("is_dir", False)
                if not path:
                    self._json({"error": "missing path"})
                    return
                cmd = f"rm -rf {path} 2>&1" if is_dir else f"rm -f {path} 2>&1"
                resp = br.send_command(cmd, 5.0)
                self._json({"output": resp or "deleted", "path": path})
            except Exception as e:
                self._json({"error": str(e)})

        elif p == "/api/file/mkdir":
            try:
                data = json.loads(body) if body else {}
                path = data.get("path", "")
                if not path:
                    self._json({"error": "missing path"})
                    return
                resp = br.send_command(f"mkdir -p {path} 2>&1", 5.0)
                self._json({"output": resp or "created", "path": path})
            except Exception as e:
                self._json({"error": str(e)})

        else:
            self.send_response(404)
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(b'{"error":"endpoint not found"}')

    def do_OPTIONS(self):
        self.send_response(204)
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type, Authorization")
        self.send_header("Access-Control-Max-Age", "86400")
        self.end_headers()

    def _json(self, obj):
        data = json.dumps(obj, ensure_ascii=False).encode("utf-8")
        self.send_response(200)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Cache-Control", "no-cache")
        self.end_headers()
        self.wfile.write(data)

    def log_message(self, format, *args):
        pass


if __name__ == "__main__":
    print("=" * 60)
    print("  BYO-OS Web Management Gateway v15")
    print("=" * 60)
    print(f"  Panel file : {PANEL_FILE}")
    print(f"  Serial     : 127.0.0.1:{SERIAL_PORT}")
    print(f"  HTTP       : http://localhost:{HTTP_PORT}")
    print("=" * 60)
    br.connect()
    print(f"  Ready! Open http://localhost:{HTTP_PORT}")
    print("=" * 60)
    HTTPServer(("0.0.0.0", HTTP_PORT), H).serve_forever()
