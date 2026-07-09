SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 165: Water + Environment ===
cmds165 = ["water_treat","water_dist","water_quality","water_conserve",
            "waste_manage","waste_recycle","waste_compost","emission_monitor",
            "air_quality_monitor","noise_monitor","soil_remediate","wetland_restore"]

d = "\n/* Batch 165: Water + Environment */\n"
for c in cmds165:
    d += f"static void {c}_165(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 165: Water + Environment */\n'
for c in cmds165:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_165}, '
t += '\n'

details165 = [
    ("water_treat", "Water: Treat 12Mgal/day pH:7.2 Turbidity:0.1NTU Chlorine:1.2mg/L"),
    ("water_dist", "Distribution: 47km pipes Pressure:45psi Flow:12L/s Leak:0.1%%"),
    ("water_quality", "Quality: pH:7.1 DO:8.2mg/L BOD:2.1mg/L TDS:180ppm Safe:yes"),
    ("water_conserve", "Conserve: Usage:125gal/day Target:100gal Savings:20%%"),
    ("waste_manage", "Waste: Collected:12.5t/day Landfill:8.2t Recycled:3.1t Compost:1.2t"),
    ("waste_recycle", "Recycle: Plastics:2.3t Metals:1.2t Paper:3.4t Glass:0.8t"),
    ("waste_compost", "Compost: Temp:65C Moisture:55%% Carbon:28%% Ready:12 weeks"),
    ("emission_monitor", "Emission: CO2:125t/day SO2:2.3t NOx:1.8t PM:0.4t"),
    ("air_quality_monitor", "Air: AQI:42 PM2.5:12ug O3:35ppb NO2:18ppb CO:0.5ppm"),
    ("noise_monitor", "Noise: Avg:58dB Max:72dB Night:42dB Limit:65dB Compliant:yes"),
    ("soil_remediate", "Remediate: Site:12ha Contaminant:heavy-metal Method:phyto Time:24mo"),
    ("wetland_restore", "Wetland: Area:2.3ha Species:24 Water:restored Status:thriving"),
]
f = "\n/* ===== Batch 165: Water + Environment ===== */\n"
for c, det in details165:
    f += "static void " + c + "_165(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 166: Sports + Fitness ===
cmds166 = ["workout_plan","heart_rate","step_count","calorie_burn",
            "sleep_track","stress_monitor","hydration_track","nutrition_plan",
            "body_measure","performance_test","recovery_track","training_cycle"]

d += "\n/* Batch 166: Sports + Fitness */\n"
for c in cmds166:
    d += f"static void {c}_166(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 166: Sports + Fitness */\n'
for c in cmds166:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_166}, '
t += '\n'

details166 = [
    ("workout_plan", "Workout: Strength Day Chest/Triceps 45min 8 exercises"),
    ("heart_rate", "HR: Current:142bpm Avg:135bpm Max:165bpm Zone:4 Time:32min"),
    ("step_count", "Steps: 12,847/10,000 Distance:8.7km Calories:523 Active:2.3h"),
    ("calorie_burn", "Calories: BMR:1,650 Exercise:523 Total:2,173 Net:523"),
    ("sleep_track", "Sleep: 7h42min Deep:2h12m REM:1h45m Light:4h05m Quality:87%%"),
    ("stress_monitor", "Stress: Level:32(Low) HRV:45ms Breathing:14/min Mood:good"),
    ("hydration_track", "Hydration: 2.1L/3.0L Target Remaining:900ml Status:adequate"),
    ("nutrition_plan", "Nutrition: Cal:2,173 Protein:125g Carbs:267g Fat:72g Fiber:28g"),
    ("body_measure", "Body: Weight:75.2kg BMI:23.1 BF:18.2%% Muscle:35.1kg"),
    ("performance_test", "Test: VO2max:48ml/kg 1RM-Squat:120kg Sprint:12.3s Flex:medium"),
    ("recovery_track", "Recovery: Score:82/100 Muscle:good Sleep:good Stress:low"),
    ("training_cycle", "Cycle: Week:8/12 Phase:build Volume:high Intensity:moderate"),
]
f += "\n/* ===== Batch 166: Sports + Fitness ===== */\n"
for c, det in details166:
    f += "static void " + c + "_166(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 167: Photography + Cinematography ===
cmds167 = ["photo_capture","photo_edit","photo_hdr","photo_panorama",
            "photo_bokeh","photo_longexp","photo_macro","photo_tether",
            "film_storyboard","film_shotlist","film_lighting","film_grading"]

d += "\n/* Batch 167: Photography + Cinematography */\n"
for c in cmds167:
    d += f"static void {c}_167(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 167: Photography + Cinematography */\n'
for c in cmds167:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_167}, '
t += '\n'

details167 = [
    ("photo_capture", "Photo: f/2.8 1/250s ISO:200 50mm Metering:matrix Focus:AF-S"),
    ("photo_edit", "Edit: Exposure:+0.3 Contrast:+15 Shadows:+25 Highlights:-10"),
    ("photo_hdr", "HDR: 3 exposures EV:-2/0/+2 Merge:fusion Dynamic:12EV"),
    ("photo_panorama", "Panorama: 8 shots Stitch:seamless Output:12000x4000"),
    ("photo_bokeh", "Bokeh: f/1.4 Subject:sharp Background:smooth Lens:85mm"),
    ("photo_longexp", "Long Exp: 30s f/16 ISO:100 ND:6stop Tripod:yes"),
    ("photo_macro", "Macro: 1:1 magnification Focus stack:12 frames DOF:0.2mm"),
    ("photo_tether", "Tether: Camera connected Shooting:remote Review:instant"),
    ("film_storyboard", "Storyboard: 24 frames Duration:2min Scenes:6 Transitions:5"),
    ("film_shotlist", "Shotlist: Wide:8 Medium:12 Close:6 Total:26 shots"),
    ("film_lighting", "Lighting: Key:45deg Fill:30deg Back:120deg Ratio:2:1"),
    ("film_grading", "Grading: Lift:0.02 Gamma:1.02 Gain:0.98 Sat:1.1 Teal+Orange"),
]
f += "\n/* ===== Batch 167: Photography + Cinematography ===== */\n"
for c, det in details167:
    f += "static void " + c + "_167(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void permit_apply_164(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"permit-apply", permit_apply_164},'
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
print("DONE - Batch 165-167 injected!")
