SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 153: Cybersecurity Offensive ===
cmds153 = ["pentest_scan","pentest_exploit","pentest_enum","pentest_privesc",
            "pentest_exfil","pentest_persist","pentest_c2","pentest_obfuscate",
            "pentest_encode","pentest_inject","pentest_bypass","pentest_cleanup"]

d = "\n/* Batch 153: Cybersecurity Offensive */\n"
for c in cmds153:
    d += f"static void {c}_153(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 153: Cybersecurity Offensive */\n'
for c in cmds153:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_153}, '
t += '\n'

details153 = [
    ("pentest_scan", "Scan: 1,247 ports 12 open 3 vulns found Services:8"),
    ("pentest_exploit", "Exploit: MS17-010 Target:10.0.2.15 Status:SUCCESS Shell:NT AUTHORITY"),
    ("pentest_enum", "Enum: Users:12 Groups:8 Shares:3 Domains:1 SID:S-1-5-21"),
    ("pentest_privesc", "Privesc: Token impersonation SYSTEM:yes Admin:yes"),
    ("pentest_exfil", "Exfil: 2.3MB data Encrypted:AES-256 Channel:DNS"),
    ("pentest_persist", "Persist: Registry Run key installed COM hijack active"),
    ("pentest_c2", "C2: Beacon 120s HTTP jitter:15%% Malleable profile:office"),
    ("pentest_obfuscate", "Obfuscate: AMSI bypass ETW patch APLib packed"),
    ("pentest_encode", "Encode: shellcode XOR+base64 Length:456 bytes Decoder:stub"),
    ("pentest_inject", "Inject: Process:notepad.exe PID:1247 Technique:CreateRemoteThread"),
    ("pentest_bypass", "Bypass: AppLocker WDAC Defender Exclusion:folder+extension"),
    ("pentest_cleanup", "Cleanup: Logs:cleared Artifacts:removed Persistence:removed"),
]
f = "\n/* ===== Batch 153: Cybersecurity Offensive ===== */\n"
for c, det in details153:
    f += "static void " + c + "_153(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 154: Cloud Native ===
cmds154 = ["serverless_invoke","serverless_logs","event_bridge","step_function",
            "sqs_send","sqs_receive","sns_publish","kinesis_stream",
            "dynamodb_query","s3_upload","cloudfront_invalidate","waf_rule"]

d += "\n/* Batch 154: Cloud Native */\n"
for c in cmds154:
    d += f"static void {c}_154(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 154: Cloud Native */\n'
for c in cmds154:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_154}, '
t += '\n'

details154 = [
    ("serverless_invoke", "Lambda: Invoke api-handler Duration:145ms Memory:128MB Cost:$0.000003"),
    ("serverless_logs", "Logs: api-handler 1,247 invocations Errors:3 Throttles:0"),
    ("event_bridge", "EventBridge: Rule:api-events Targets:3 Matched:1,247"),
    ("step_function", "StepFn: OrderFlow Executions:128 Success:125 Failed:3"),
    ("sqs_send", "SQS: Message sent Queue:orders Delay:0 Size:1.2KB"),
    ("sqs_receive", "SQS: Received 12 messages Visible:8 In-Flight:4"),
    ("sns_publish", "SNS: Published to alerts Topic:deploy Subscribers:24"),
    ("kinesis_stream", "Kinesis: Stream:events Shards:4 Write:156KB/s Read:312KB/s"),
    ("dynamodb_query", "DynamoDB: Query pk='user#123' Items:3 Latency:8ms RCU:5"),
    ("s3_upload", "S3: Upload report.pdf 2.3MB Bucket:artifacts Key:reports/"),
    ("cloudfront_invalidate", "CloudFront: Invalidated /* Status:Completed 128 paths"),
    ("waf_rule", "WAF: Rule:sql-injection Block:12 Challenge:47 Pass:1,247"),
]
f += "\n/* ===== Batch 154: Cloud Native ===== */\n"
for c, det in details154:
    f += "static void " + c + "_145(int argc, char args[][CMD_MAX_LEN]) {\n"  # Note: will fix below
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# Fix the function names for batch 154
content_temp = f
for c in cmds154:
    content_temp = content_temp.replace(f"{c}_145(", f"{c}_154(")
f = content_temp

# === BATCH 155: Data Pipeline ===
cmds155 = ["etl_extract","etl_transform","etl_load","etl_schedule",
            "stream_process","batch_process","data_lake","data_warehouse",
            "data_catalog","data_quality","data_lineage","data_govern"]

d += "\n/* Batch 155: Data Pipeline */\n"
for c in cmds155:
    d += f"static void {c}_155(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 155: Data Pipeline */\n'
for c in cmds155:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_155}, '
t += '\n'

details155 = [
    ("etl_extract", "ETL Extract: Source:MySQL Tables:12 Rows:1,247,893 Time:45s"),
    ("etl_transform", "ETL Transform: Clean:12,847 Dedup:234 Aggregate:ok"),
    ("etl_load", "ETL Load: Target:Redshift Rows:1,235,046 Time:12s Status:OK"),
    ("etl_schedule", "Schedule: Daily 02:00 UTC Next:2024-01-16 Retry:3 Timeout:2h"),
    ("stream_process", "Stream: Kafka 128 partitions Throughput:15,000 msg/s"),
    ("batch_process", "Batch: Spark 12 executors Data:2.3GB Time:45s Status:OK"),
    ("data_lake", "DataLake: Delta Lake Tables:47 Size:2.3TB Partitions:1,247"),
    ("data_warehouse", "Warehouse: Redshift Cluster:3 nodes Size:1.2TB Queries:12/day"),
    ("data_catalog", "Catalog: Tables:234 Columns:1,247 Tags:89 Owner:team-data"),
    ("data_quality", "Quality: Score:94.7%% Nulls:0.3%% Duplicates:0.1%% Schema:98%%"),
    ("data_lineage", "Lineage: 12 pipelines 47 transformations 3 sources 2 sinks"),
    ("data_govern", "Govern: PII:23 cols GDPR:compliant Retention:90d Access:RBAC"),
]
f += "\n/* ===== Batch 155: Data Pipeline ===== */\n"
for c, det in details155:
    f += "static void " + c + "_155(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void vision_detect_152(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"vision-detect", vision_detect_152},'
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + "\n" + t + content[i+len(m):]
    print("Table OK")
else: print("ERROR table!")

# INJECT FUNCS
m = "void shell_run(void)"
i = content.find(m)
if i >= 0:
    content = content[:i] + f + "\n" + content[i:]
    print("Funcs OK")
else: print("ERROR func!")

with open(SHELL_C, "w", encoding="utf-8") as fh:
    fh.write(content)
print("DONE - Batch 153-155 injected!")
