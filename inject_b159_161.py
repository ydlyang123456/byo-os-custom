SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 159: Material Science ===
cmds159 = ["mat_simulate","mat_analyze","mat_optimize","mat_test",
            "mat_fatigue","mat_corrosion","mat_thermal","mat_composite",
            "mat_ceramic","mat_polymer","mat_metal","mat_nano"]

d = "\n/* Batch 159: Material Science */\n"
for c in cmds159:
    d += f"static void {c}_159(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 159: Material Science */\n'
for c in cmds159:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_159}, '
t += '\n'

details159 = [
    ("mat_simulate", "MD Sim: 12,847 atoms T=300K P=1atm Steps:100000 Energy:-45.2eV"),
    ("mat_analyze", "XRD: 2theta:15-80 Peaks:12 Phase:alpha Phase:beta Purity:98.7%%"),
    ("mat_optimize", "Optimize: Alloy Al-Cu-Mg Strength:450MPa Density:2.71 Cost:$12/kg"),
    ("mat_test", "Tensile: UTS:520MPa YS:450MPa Elongation:12%% Hardness:HV145"),
    ("mat_fatigue", "Fatigue: S-N curve Nf:1e6 at 200MPa Endurance:180MPa"),
    ("mat_corrosion", "Corrosion: Rate:0.02mm/yr Type:pitting Passivity:stable"),
    ("mat_thermal", "Thermal: Conductivity:237W/mK Expansion:23e-6/C Melting:660C"),
    ("mat_composite", "Composite: CF-Epoxy Vf:60%% Longitudinal:150GPa Transverse:10GPa"),
    ("mat_ceramic", "Ceramic: Al2O3 Hardness:HV2000 Toughness:3.5MPa.m^0.5"),
    ("mat_polymer", "Polymer: PE Tg:-120C Tm:135C MFI:2.3g/10min"),
    ("mat_metal", "Metal: Ti-6Al-4V UTS:950MPa Density:4.43g/cm3 Biocompat:excellent"),
    ("mat_nano", "Nano: Particle:12nm Surface:45m2/g Distribution:sigma:1.2nm"),
]
f = "\n/* ===== Batch 159: Material Science ===== */\n"
for c, det in details159:
    f += "static void " + c + "_159(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 160: Textiles + Fashion ===
cmds160 = ["fabric_design","fabric_weave","fabric_knit","fabric_dye",
            "fabric_print","pattern_make","pattern_grade","pattern_nest",
            "garment_construct","garment_fit","garment_cost","garment_sustain"]

d += "\n/* Batch 160: Textiles + Fashion */\n"
for c in cmds160:
    d += f"static void {c}_160(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 160: Textiles + Fashion */\n'
for c in cmds160:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_160}, '
t += '\n'

details160 = [
    ("fabric_design", "Design: Pattern:geometric Colors:3 repeat:12cm Width:150cm"),
    ("fabric_weave", "Weave: Plain/Twill/Satin Picks:45/cm Ends:56/cm Density:OK"),
    ("fabric_knit", "Knit: Jersey/Gauge:18 Weight:180gsm Stretch:45%% Recovery:92%%"),
    ("fabric_dye", "Dye: Reactive Color:navy Fastness:4-5 Levelness:excellent"),
    ("fabric_print", "Print: Digital Resolution:600dpi Colors:12 Wash:fast"),
    ("pattern_make", "Pattern: Size:S-M-L-XL Pieces:12 Seam:1.5cm Ease:2cm"),
    ("pattern_grade", "Grade: S->M delta:1.2cm M->L delta:1.2cm L->XL delta:1.2cm"),
    ("pattern_nest", "Nest: Efficiency:87%% Waste:13%% Marker:128cm Layout:optimized"),
    ("garment_construct", "Construct: Seam:felled Collar:spread Closure:buttons Lining:yes"),
    ("garment_fit", "Fit: Bust:+1cm Waist:+0.5cm Hip:+1.5cm Overall:good"),
    ("garment_cost", "Cost: Fabric:$12 Labor:$8 Trim:$3 Total:$23 Wholesale:$46"),
    ("garment_sustain", "Sustain: Organic:yes Recycled:30%% Water:-45%% Carbon:-32%%"),
]
f += "\n/* ===== Batch 160: Textiles + Fashion ===== */\n"
for c, det in details160:
    f += "static void " + c + "_160(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 161: Agriculture + Food ===
cmds161 = ["crop_monitor","crop_irrigate","crop_fertilize","crop_harvest",
            "soil_analyze","pest_detect","livestock_track","dairy_monitor",
            "food_process","food_safety","food_packaging","supply_optimize"]

d += "\n/* Batch 161: Agriculture + Food */\n"
for c in cmds161:
    d += f"static void {c}_161(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 161: Agriculture + Food */\n'
for c in cmds161:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_161}, '
t += '\n'

details161 = [
    ("crop_monitor", "Crop: Wheat Growth:stage-4 NDVI:0.78 Health:good Area:12ha"),
    ("crop_irrigate", "Irrigate: Soil moisture:32%% Target:60%% Flow:2.3L/min Schedule:daily"),
    ("crop_fertilize", "Fertilize: N:P:K = 100:50:80 kg/ha Method:foliar Timing:VE"),
    ("crop_harvest", "Harvest: Wheat Yield:6.2t/ha Moisture:14%% Quality:grade-A"),
    ("soil_analyze", "Soil: pH:6.8 N:45ppm P:23ppm K:180ppm OM:3.2%% Texture:loam"),
    ("pest_detect", "Pest: Aphids detected Field:B3 Severity:moderate Action:spray"),
    ("livestock_track", "Livestock: Cattle:124 Weight:avg520kg Health:good Location:pasture-2"),
    ("dairy_monitor", "Dairy: Cows milking:89 Milk:22L/cow/day Quality:3.8%%fat Somatic:180K"),
    ("food_process", "Process: Batch:#12848 Product:yogurt Volume:5000L Temp:42C Time:6h"),
    ("food_safety", "Safety: HACCP:compliant Temp:4C pH:4.2 Pathogen:none Expiry:2024-02-15"),
    ("food_packaging", "Packaging: Material:PP Size:500ml Seal:heat Weight:45g Label:OK"),
    ("supply_optimize", "Supply: Routes:12 Trucks:8 Capacity:85%% Cost:$12,400/week"),
]
f += "\n/* ===== Batch 161: Agriculture + Food ===== */\n"
for c, det in details161:
    f += "static void " + c + "_161(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void audio_compressor_158(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"audio-compressor", audio_compressor_158},'
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
print("DONE - Batch 159-161 injected!")
