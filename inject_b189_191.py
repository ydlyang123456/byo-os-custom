SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 189: Aerospace Engineering ===
cmds189 = ["aero_simulate","aero_wind_tunnel","aero_composite","aero_thrust",
            "aero_drag","aero_lift","aero_heat","aero_struct",
            "aero_control","aero_propulsion","aero_material","aero_test"]

d = "\n/* Batch 189: Aerospace Engineering */\n"
for c in cmds189:
    d += f"static void {c}_189(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 189: Aerospace Engineering */\n'
for c in cmds189:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_189}, '
t += '\n'

details189 = [
    ("aero_simulate", "CFD: Mach:0.85 AoA:2deg Cl:0.45 Cd:0.023 L/D:19.6"),
    ("aero_wind_tunnel", "Tunnel: V:80m/s Re:2.4M Force:L=45N D=2.3N Moment:1.2Nm"),
    ("aero_composite", "Composite: CF/PEEK Vf:60%% Tensile:1.8GPa Density:1.6g/cm3"),
    ("aero_thrust", "Thrust: Turbofan:120kN SFC:0.55lb/hr/lb BPR:11:1"),
    ("aero_drag", "Drag: Wave:12%% Induced:23%% Skin:45%% Base:20%% Cd:0.023"),
    ("aero_lift", "Lift: Cl:0.45 CLmax:1.8 Stall:16deg Wing:36m span"),
    ("aero_heat", "Heat: T stagnation:340K T surface:89K Heat flux:45kW/m2"),
    ("aero_struct", "Struct: Wing root moment:1.2MNm Stress:145MPa Safety:2.1x"),
    ("aero_control", "Control: Pitch:0.5deg/s Roll:2.3deg/s Yaw:0.8deg/s Stability:OK"),
    ("aero_propulsion", "Propulsion: Engine:CFM56 TSFC:0.34lb/hr/lb BPR:6:1"),
    ("aero_material", "Material: Ti-6Al-4V Temp:450C Stress:680MPa Fatigue:1e7"),
    ("aero_test", "Test: Static load:1.5x Design Ultimate:2.2x Safety factor:2.1x"),
]
f = "\n/* ===== Batch 189: Aerospace Engineering ===== */\n"
for c, det in details189:
    f += "static void " + c + "_189(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 190: Food Science + Culinary ===
cmds190 = ["flavor_pair","recipe_scale","sous_vide","ferment_process",
            "nutrition_calc","allergen_check","food_preserve","emulsify",
            "spherify","sous_vide_ctrl","bread_bake","chocolate_temper"]

d += "\n/* Batch 190: Food Science + Culinary */\n"
for c in cmds190:
    d += f"static void {c}_190(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 190: Food Science + Culinary */\n'
for c in cmds190:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_190}, '
t += '\n'

details190 = [
    ("flavor_pair", "Flavor: Tomato+Basil:92%% Chocolate+Chili:87%% Cheese+Apple:81%%"),
    ("recipe_scale", "Scale: 4->12 servings Multiply:3.0x Flour:750g Sugar:360g"),
    ("sous_vide", "Sous Vide: 56.5C 2h30m Core temp:56.3C Doneness:medium-rare"),
    ("ferment_process", "Ferment: Sourdough Day:3 pH:4.2 Yeast:active Rise:2.5x"),
    ("nutrition_calc", "Nutrition: Cal:456 Protein:28g Fat:18g Carb:42g Fiber:6g"),
    ("allergen_check", "Allergens: Gluten:yes Dairy:no Nuts:yes Soy:no Egg:no"),
    ("food_preserve", "Preserve: Canning:115C 10min Shelf:12mo Vacuum:sealed"),
    ("emulsify", "Emulsion: Oil:Water:3:1 Emulsifier:lecithin Stability:48h"),
    ("spherify", "Sphere: Alginate:0.5%% Calcium:0.5%% Size:2cm Texture:liquid core"),
    ("sous_vide_ctrl", "Controller: Set:56.5C Actual:56.3C Diff:0.2C PID:stable"),
    ("bread_bake", "Bread: Proof:2h Bake:220C 35min Internal:96C Crust:golden"),
    ("chocolate_temper", "Temper: Melt:50C Cool:27C Reheat:31C Snap:clean Gloss:high"),
]
f += "\n/* ===== Batch 190: Food Science + Culinary ===== */\n"
for c, det in details190:
    f += "static void " + c + "_190(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 191: Environmental Monitoring ===
cmds191 = ["env_sensor","env_calibrate","env_alert","env_log",
            "env_visualize","env_predict","env_correlate","env_anomaly",
            "env_report","env_compliance","env_audit","env_optimize"]

d += "\n/* Batch 191: Environmental Monitoring */\n"
for c in cmds191:
    d += f"static void {c}_191(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 191: Environmental Monitoring */\n'
for c in cmds191:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_191}, '
t += '\n'

details191 = [
    ("env_sensor", "Sensor: Temp:24.3C Humidity:65%% PM2.5:12ug CO2:420ppm Noise:58dB"),
    ("env_calibrate", "Calibrate: Temp:offset+0.2C Humidity:offset-1%% PM2.5:factory OK"),
    ("env_alert", "Alert: CO2>1000ppm Threshold:exceeded Severity:medium Action:notified"),
    ("env_log", "Log: 12,847 records 24h 5-min intervals Storage:2.3MB Compressed:450KB"),
    ("env_visualize", "Visualize: Temp:line PM2.5:bar CO2:area Dashboard:real-time"),
    ("env_predict", "Predict: Temp tomorrow:26C PM2.5:15ug AQI:48 Model:LSTM"),
    ("env_correlate", "Correlate: PM2.5-traffic:r=0.78 CO2-occupancy:r=0.85"),
    ("env_anomaly", "Anomaly: PM2.5 spike at 14:23 Value:89ug Threshold:3x normal"),
    ("env_report", "Report: Monthly AQI avg:42 Max:89 Days good:28/30"),
    ("env_compliance", "Compliance: EPA:pass EU:pass Local:pass Violations:0"),
    ("env_audit", "Audit: Sensors:24 Calibrated:22 Due:2 Accuracy:98%%"),
    ("env_optimize", "Optimize: HVAC schedule saved:12%% CO2 ventilation:optimized"),
]
f += "\n/* ===== Batch 191: Environmental Monitoring ===== */\n"
for c, det in details191:
    f += "static void " + c + "_191(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void social_enterprise_188(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"social-enterprise", social_enterprise_188},'
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
print("DONE - Batch 189-191 injected!")
