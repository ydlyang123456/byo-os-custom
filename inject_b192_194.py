SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 192: Medical Imaging ===
cmds192 = ["mri_analyze","ct_scan","xray_detect","ultrasound",
            "pet_scan","mammogram","retinal_scan","bone_density",
            "tumor_detect","organ_segment","3d_reconstruct","ai_diagnose"]

d = "\n/* Batch 192: Medical Imaging */\n"
for c in cmds192:
    d += f"static void {c}_192(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 192: Medical Imaging */\n'
for c in cmds192:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_192}, '
t += '\n'

details192 = [
    ("mri_analyze", "MRI: Brain 3T T1/T2 FLAIR Lesions:0 Atrophy:none Normal"),
    ("ct_scan", "CT: Chest Abdomen Contrast:yes Dose:8mSv Findings:1 nodule 4mm"),
    ("xray_detect", "X-ray: Chest PA Findings:No acute abnormality Cardiac:silhouette normal"),
    ("ultrasound", "Ultrasound: Abdomen Liver:normal Kidney:normal Gallbladder:sludge"),
    ("pet_scan", "PET-CT: FDG Uptake:SUVmax:2.3 Lesion:right lung Biopsy:recommended"),
    ("mammogram", "Mammogram: BI-RADS:2 Benign calcifications No mass No architectural distortion"),
    ("retinal_scan", "Retina: OCT Macula:normal Optic disc:C/D=0.3 No hemorrhage"),
    ("bone_density", "DEXA: Lumbar T-score:-1.2 Osteopenia Hip T-score:-0.8 Normal"),
    ("tumor_detect", "Tumor: Detection:confidence:94%% Size:1.2cm Location:segment VI"),
    ("organ_segment", "Segment: Liver:1,247ml Kidney:145ml Spleen:189ml Pancreas:78ml"),
    ("3d_reconstruct", "3D: Reconstructed CT Points:1.2M Mesh:456K Faces Render:real-time"),
    ("ai_diagnose", "AI Dx: pneumonia:87%% normal:11%% other:2%% Confidence:high"),
]
f = "\n/* ===== Batch 192: Medical Imaging ===== */\n"
for c, det in details192:
    f += "static void " + c + "_192(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 193: Legal Compliance ===
cmds193 = ["kyc_check","aml_scan","sanctions_screen","pep_check",
            "transaction_monitor","suspicious_report","compliance_train",
            "policy_enforce","audit_trail","regulatory_filing","breach_notify","data_retain"]

d += "\n/* Batch 193: Legal Compliance */\n"
for c in cmds193:
    d += f"static void {c}_193(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 193: Legal Compliance */\n'
for c in cmds193:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_193}, '
t += '\n'

details193 = [
    ("kyc_check", "KYC: Customer:C12848 Identity:verified Risk:low Tier:standard"),
    ("aml_scan", "AML: Transaction:12,847 Flagged:12 Cleared:11 Pending:1"),
    ("sanctions_screen", "Sanctions: OFAC:clear EU:clear UN:clear PEP:no Match:0"),
    ("pep_check", "PEP: Customer not politically exposed Risk:low"),
    ("transaction_monitor", "Monitor: 12,847 txns 24h Threshold:>$10k Alerts:3"),
    ("suspicious_report", "SAR: Filed:23 YTD Review:pending Filing deadline:30d"),
    ("compliance_train", "Training: 89%% completed 12 employees pending deadline:Jan 31"),
    ("policy_enforce", "Policy: InfoSec:active Acceptable Use:active Data Privacy:active"),
    ("audit_trail", "Trail: 12,847 events logged 24h Integrity:SHA-256 verified"),
    ("regulatory_filing", "Filing: SEC 10-Q filed on time FINRA:compliant State:registered"),
    ("breach_notify", "Breach: None active Last incident:never Notification:NA"),
    ("data_retain", "Retention: Financial:7yr Medical:10yr Personal:3yr Purge:automated"),
]
f += "\n/* ===== Batch 193: Legal Compliance ===== */\n"
for c, det in details193:
    f += "static void " + c + "_193(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 194: Smart City ===
cmds194 = ["traffic_signal","parking_sensor","air_monitor","water_quality_city",
            "waste_collection","street_light","noise_map","green_space",
            "public_safety","emergency_response","citizen_portal","city_dashboard"]

d += "\n/* Batch 194: Smart City */\n"
for c in cmds194:
    d += f"static void {c}_194(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 194: Smart City */\n'
for c in cmds194:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_194}, '
t += '\n'

details194 = [
    ("traffic_signal", "Signal: Main-12:Green Time:45s Queue:12 vehicles Optimization:active"),
    ("parking_sensor", "Parking: 47/200 spots available Nearest:50m Rate:$2/hr"),
    ("air_monitor", "Air: AQI:42 PM2.5:12ug O3:35ppb Station:Central Park"),
    ("water_quality_city", "Water: pH:7.2 Chlorine:1.2mg/L Turbidity:0.1NTU Safe:yes"),
    ("waste_collection", "Waste: Route:optimized Bins:47 Collected:12.5t Efficiency:94%%"),
    ("street_light", "Street: 12/47 dimmed Energy:35%% saved Motion:activated"),
    ("noise_map", "Noise: Avg:58dB Max:72dB Hotspots:3 Compliance:97%%"),
    ("green_space", "Green: Parks:12 Trees:2,347 Coverage:34%% Air quality:improved"),
    ("public_safety", "Safety: Incidents:12 Response:3.2min Cameras:47 Coverage:89%%"),
    ("emergency_response", "Emergency: Calls:12 Ambulance:4 Fire:2 Police:6 Avg:4.2min"),
    ("citizen_portal", "Portal: Users:12,847 Requests:234 Resolved:89%% Satisfaction:4.2/5"),
    ("city_dashboard", "Dashboard: Population:234,000 Traffic:moderate Air:good Events:2"),
]
f += "\n/* ===== Batch 194: Smart City ===== */\n"
for c, det in details194:
    f += "static void " + c + "_194(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void env_optimize_191(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"env-optimize", env_optimize_191},'
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
print("DONE - Batch 192-194 injected!")
