import urllib.request, json, sys

def test(name, func):
    try:
        ok, detail = func()
        status = "PASS" if ok else "FAIL"
        print("  [" + status + "] " + name)
        if detail:
            for line in str(detail).split("\n")[:5]:
                print("        " + line)
        return ok
    except Exception as e:
        print("  [FAIL] " + name + ": " + str(e))
        return False

print("=" * 50)
print("  BYO-OS Final System Test")
print("=" * 50)
print()

results = []

# 1. Web panel serves HTML
def test_html():
    r = urllib.request.urlopen("http://localhost:7777/", timeout=5)
    h = r.read().decode()
    has = all(x in h for x in ["page-dashboard", "page-term", "page-file", "/api/exec"])
    return has, "HTML length: " + str(len(h)) + " bytes"
results.append(test("Web panel serves HTML", test_html))

# 2. sysinfo API returns live data
def test_sysinfo():
    r = urllib.request.urlopen("http://localhost:7777/api/sysinfo", timeout=5)
    d = json.loads(r.read().decode())
    has = d.get("os") and d.get("ip") and d.get("uptime") is not None
    return has, "OS=" + str(d.get("os")) + " IP=" + str(d.get("ip")) + " Up=" + str(d.get("uptime")) + "s"
results.append(test("Sysinfo API (live data)", test_sysinfo))

# 3. exec ls
def test_ls():
    req = urllib.request.Request("http://localhost:7777/api/exec",
        data=json.dumps({"cmd": "ls"}).encode(),
        headers={"Content-Type": "application/json"})
    r = urllib.request.urlopen(req, timeout=5)
    d = json.loads(r.read().decode())
    return bool(d.get("output")), d.get("output", "")[:200]
results.append(test("exec ls", test_ls))

# 4. exec mem
def test_mem():
    req = urllib.request.Request("http://localhost:7777/api/exec",
        data=json.dumps({"cmd": "mem"}).encode(),
        headers={"Content-Type": "application/json"})
    r = urllib.request.urlopen(req, timeout=5)
    d = json.loads(r.read().decode())
    return bool(d.get("output")), d.get("output", "")[:200]
results.append(test("exec mem", test_mem))

# 5. exec whoami
def test_whoami():
    req = urllib.request.Request("http://localhost:7777/api/exec",
        data=json.dumps({"cmd": "whoami"}).encode(),
        headers={"Content-Type": "application/json"})
    r = urllib.request.urlopen(req, timeout=5)
    d = json.loads(r.read().decode())
    return bool(d.get("output")), d.get("output", "")[:200]
results.append(test("exec whoami", test_whoami))

# 6. exec net
def test_net():
    req = urllib.request.Request("http://localhost:7777/api/exec",
        data=json.dumps({"cmd": "net"}).encode(),
        headers={"Content-Type": "application/json"})
    r = urllib.request.urlopen(req, timeout=5)
    d = json.loads(r.read().decode())
    return bool(d.get("output")), d.get("output", "")[:200]
results.append(test("exec net", test_net))

# 7. exec uptime
def test_uptime():
    req = urllib.request.Request("http://localhost:7777/api/exec",
        data=json.dumps({"cmd": "uptime"}).encode(),
        headers={"Content-Type": "application/json"})
    r = urllib.request.urlopen(req, timeout=5)
    d = json.loads(r.read().decode())
    return bool(d.get("output")), d.get("output", "")[:200]
results.append(test("exec uptime", test_uptime))

# 8. exec users
def test_users():
    req = urllib.request.Request("http://localhost:7777/api/exec",
        data=json.dumps({"cmd": "users"}).encode(),
        headers={"Content-Type": "application/json"})
    r = urllib.request.urlopen(req, timeout=5)
    d = json.loads(r.read().decode())
    return bool(d.get("output")), d.get("output", "")[:200]
results.append(test("exec users", test_users))

print()
passed = sum(results)
total = len(results)
print("=" * 50)
print("  Result: " + str(passed) + "/" + str(total) + " passed")
if passed == total:
    print("  ALL TESTS PASSED!")
print("=" * 50)
