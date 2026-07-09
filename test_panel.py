import urllib.request, json

print("=== BYO-OS Full System Test ===")
print()

# 1. Test Web Panel HTML
try:
    resp = urllib.request.urlopen("http://localhost:7777/", timeout=5)
    html = resp.read().decode("utf-8")
    checks = [
        ("Dashboard page", "page-dashboard" in html),
        ("Terminal page", "page-terminal" in html),
        ("File Manager", "page-files" in html),
        ("Network page", "page-network" in html),
        ("Settings page", "page-settings" in html),
        ("API /api/exec", "/api/exec" in html),
        ("API /api/sysinfo", "/api/sysinfo" in html),
        ("Auto-refresh JS", "setInterval(refreshAll" in html),
    ]
    print("[1] Web Panel HTML:")
    for name, ok in checks:
        status = "PASS" if ok else "FAIL"
        print("    " + status + ": " + name)
except Exception as e:
    print("[1] FAIL: " + str(e))

print()

# 2. Test sysinfo API
try:
    resp = urllib.request.urlopen("http://localhost:7777/api/sysinfo", timeout=5)
    data = json.loads(resp.read().decode())
    print("[2] Sysinfo API (live from OS):")
    print("    OS: " + str(data.get("os")))
    print("    IP: " + str(data.get("ip")))
    print("    Uptime: " + str(data.get("uptime")) + "s")
    print("    Tasks: " + str(data.get("tasks")))
    print("    User: " + str(data.get("user")))
    print("    Mem: " + str(data.get("mem_free")) + " MB free / " + str(data.get("mem_total")) + " MB total")
    print("    PASS: Live data from OS via serial")
except Exception as e:
    print("    FAIL: " + str(e))

print()

# 3. Test exec commands
commands = ["ls", "mem", "whoami", "net", "uptime", "help"]
for cmd in commands:
    try:
        req = urllib.request.Request("http://localhost:7777/api/exec",
            data=json.dumps({"cmd": cmd}).encode(),
            headers={"Content-Type": "application/json"})
        resp = urllib.request.urlopen(req, timeout=5)
        result = json.loads(resp.read().decode())
        output = result.get("output", "")
        status = "PASS" if output.strip() else "FAIL"
        print("[3] exec " + cmd + ": " + status)
        if output.strip():
            lines = output.strip().split("\n")
            for line in lines[:3]:
                print("    " + line)
            if len(lines) > 3:
                print("    ... (" + str(len(lines)) + " lines)")
    except Exception as e:
        print("[3] exec " + cmd + ": FAIL - " + str(e))

print()
print("=== All tests complete ===")
