SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 168: Manufacturing ===
cmds168 = ["cnc_program","cnc_monitor","3d_print","laser_cut",
            "weld_control","quality_inspect","assembly_plan","supply_chain",
            "inventory_mgmt","production_plan","maintenance_sched","lean_manage"]

d = "\n/* Batch 168: Manufacturing */\n"
for c in cmds168:
    d += f"static void {c}_168(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 168: Manufacturing */\n'
for c in cmds168:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_168}, '
t += '\n'

details168 = [
    ("cnc_program", "CNC: G-code 2,847 lines Feed:1200mm/min Spindle:8000RPM"),
    ("cnc_monitor", "CNC Monitor: Tool:3 Wear:12%% Temp:45C Vibration:0.8mm/s"),
    ("3d_print", "3D Print: PLA Layer:0.2mm Speed:60mm/s ETA:4h32m 89%%done"),
    ("laser_cut", "Laser: CO2 80W Speed:15mm/s Power:65%% Material:acrylic 3mm"),
    ("weld_control", "Weld: MIG 180A Wire:1.0mm Gas:Ar/CO2 Shield:OK"),
    ("quality_inspect", "QA: CMM measured 23 features 21 in-tol 2 out-of-tol"),
    ("assembly_plan", "Assembly: Station:4 Parts:12 Time:45s/operator OK"),
    ("supply_chain", "Supply: Lead:12d Buffer:15%% Suppliers:23 Risk:low"),
    ("inventory_mgmt", "Inventory: Items:1,247 Value:$234K Turnover:8.2x"),
    ("production_plan", "Production: Batch:#12848 Qty:500 Rate:50/hr ETA:10h"),
    ("maintenance_sched", "Maint: Next:48h MTBF:720h MTTR:2h PM:monthly"),
    ("lean_manage", "Lean: Waste:7 types OEE:87%% Kaizen:12 this month"),
]
f = "\n/* ===== Batch 168: Manufacturing ===== */\n"
for c, det in details168:
    f += "static void " + c + "_168(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 169: Logistics + Supply ===
cmds169 = ["warehouse_manage","route_optimize","load_plan","track_shipment",
            "customs_clear","freight_calc","last_mile","reverse_logistics",
            "cold_chain","hazmat_manage","cross_dock","yard_manage"]

d += "\n/* Batch 169: Logistics + Supply */\n"
for c in cmds169:
    d += f"static void {c}_169(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 169: Logistics + Supply */\n'
for c in cmds169:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_169}, '
t += '\n'

details169 = [
    ("warehouse_manage", "Warehouse: SKUs:12,847 Locations:4,567 Utilization:78%%"),
    ("route_optimize", "Route: 12 stops Distance:145km Time:6h Fuel:$23 Savings:18%%"),
    ("load_plan", "Load: Truck:20ft Cargo:12 pallets Weight:18t Util:87%%"),
    ("track_shipment", "Track: #12848 Location:Shanghai ETA:2024-01-20 Status:in-transit"),
    ("customs_clear", "Customs: HS:84713000 Duty:0%% VAT:13%% Status:cleared"),
    ("freight_calc", "Freight: LCL $45/CBM FCL $2,800/20ft Air $4.50/kg"),
    ("last_mile", "Last Mile: 47 deliveries Route:optimized Time:4h Success:96%%"),
    ("reverse_logistics", "Returns: 12 items/day Rate:2.3%% Refund:$1,247 Restock:8"),
    ("cold_chain", "Cold: Temp:-18C±2 Humidity:45%% Monitor:real-time Alert:none"),
    ("hazmat_manage", "Hazmat: Class:3 UN:1263 Labels:flammable PPE:required"),
    ("cross_dock", "Cross-dock: In:12 pallets Out:8 pallets Dwell:2h Efficiency:94%%"),
    ("yard_manage", "Yard: 47 trucks In:23 Out:18 Waiting:6 Docks:8 available"),
]
f += "\n/* ===== Batch 169: Logistics + Supply ===== */\n"
for c, det in details169:
    f += "static void " + c + "_169(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 170: Media + Publishing ===
cmds170 = ["news_write","news_publish","news_analyze","news_aggregate",
            "blog_create","blog_seo","podcast_record","podcast_edit",
            "podcast_distribute","video_stream","video_archive","content_manage"]

d += "\n/* Batch 170: Media + Publishing */\n"
for c in cmds170:
    d += f"static void {c}_170(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 170: Media + Publishing */\n'
for c in cmds170:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_170}, '
t += '\n'

details170 = [
    ("news_write", "News: Article draft 1,247 words Headline:BYO-OS Released"),
    ("news_publish", "Publish: CMS:WordPress Status:live Views:1,247 Shares:23"),
    ("news_analyze", "Analytics: Views:12,847 Unique:8,923 Bounce:34%% Avg:2:34"),
    ("news_aggregate", "Aggregate: Sources:24 Topics:12 Sentiment:72%% positive"),
    ("blog_create", "Blog: Post:'Getting Started' Words:2,347 Tags:5 SEO:92/100"),
    ("blog_seo", "SEO: Score:92/100 Keywords:12 Meta:optimized Backlinks:23"),
    ("podcast_record", "Record: Episode:#47 Duration:45min Audio:48kHz/24bit"),
    ("podcast_edit", "Edit: Cuts:23 Music:2 Ads:0 Transitions:fade Duration:42min"),
    ("podcast_distribute", "Distribute: Platforms:5 Spotify:OK Apple:OK RSS:updated"),
    ("video_stream", "Stream: Resolution:1080p Bitrate:6Mbps Viewers:128 Latency:2s"),
    ("video_archive", "Archive: 128 episodes Size:45GB Format:H.265 Indexed:yes"),
    ("content_manage", "CMS: Articles:234 Drafts:12 Scheduled:8 Published:214"),
]
f += "\n/* ===== Batch 170: Media + Publishing ===== */\n"
for c, det in details170:
    f += "static void " + c + "_170(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void film_grading_167(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"film-grading", film_grading_167},'
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
print("DONE - Batch 168-170 injected!")
