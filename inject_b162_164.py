SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 162: Energy + Power ===
cmds162 = ["solar_manage","wind_manage","battery_manage","grid_balance",
            "energy_audit","power_monitor","inverter_ctrl","charger_ctrl",
            "microgrid","smart_grid","energy_storage","demand_response"]

d = "\n/* Batch 162: Energy + Power */\n"
for c in cmds162:
    d += f"static void {c}_162(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 162: Energy + Power */\n'
for c in cmds162:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_162}, '
t += '\n'

details162 = [
    ("solar_manage", "Solar: 12kW system Output:8.4kW Efficiency:22%% Today:42kWh"),
    ("wind_manage", "Wind: 3 turbines Output:4.5MW Speed:12m/s Availability:97%%"),
    ("battery_manage", "Battery: 85%% SOC 48V 200Ah Charge:12A Discharge:45A"),
    ("grid_balance", "Grid: Import:2.3kW Export:1.2kW Net:1.1kW surplus"),
    ("energy_audit", "Audit: Building:125kWh/day Solar:42kWh Grid:67kWh Battery:16kWh"),
    ("power_monitor", "Power: Total:8.4kW Solar:6.2kW Grid:2.2kW Factor:0.95"),
    ("inverter_ctrl", "Inverter: 5kW Output:230V 50Hz Efficiency:96%% Status:normal"),
    ("charger_ctrl", "Charger: EV 7.4kW SOC:67%% ETA:1h23m Cost:$4.50"),
    ("microgrid", "Microgrid: 3 DERs Load:45kW Generation:52kW Storage:200kWh"),
    ("smart_grid", "SmartGrid: Demand:125kW Supply:128kW Frequency:50.01Hz"),
    ("energy_storage", "Storage: Battery:200kWh Pumped:50MWh Compressed:12MWh"),
    ("demand_response", "DR: Event:peak-shaving Reduction:15%% Duration:2h Incentive:$45"),
]
f = "\n/* ===== Batch 162: Energy + Power ===== */\n"
for c, det in details162:
    f += "static void " + c + "_162(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 163: Transportation ===
cmds163 = ["route_plan","traffic_predict","fleet_manage","vehicle_diag",
            "fuel_monitor","emission_track","parking_manage","toll_calc",
            "ride_share","delivery_opt","public_trans","autonomous_drive"]

d += "\n/* Batch 163: Transportation */\n"
for c in cmds163:
    d += f"static void {c}_163(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 163: Transportation */\n'
for c in cmds163:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_163}, '
t += '\n'

details163 = [
    ("route_plan", "Route: 12.3km ETA:18min Fuel:0.8L Cost:$1.20 Traffic:moderate"),
    ("traffic_predict", "Predict: 14:00 Congestion:high Speed:25km/h Delay:+12min"),
    ("fleet_manage", "Fleet: 12 vehicles Active:8 Idle:2 Maintenance:1 Off:1"),
    ("vehicle_diag", "Diag: Engine:OK Transmission:OK Brakes:85%% Tires:OK Battery:92%%"),
    ("fuel_monitor", "Fuel: Level:67%% Rate:8.2L/100km Range:487km Cost:$45.20"),
    ("emission_track", "Emission: CO2:125g/km NOx:0.02g/km PM:0.001g/km Euro:6d"),
    ("parking_manage", "Parking: Available:127/500 Nearest:50m Rate:$2/hr"),
    ("toll_calc", "Toll: Route cost:$3.50 Highway:$2.80 Bridge:$0.70"),
    ("ride_share", "Ride: Driver:5min away ETA:12min Cost:$12.50 Pool:2/4"),
    ("delivery_opt", "Delivery: 12 stops Route:optimized Time:2h30m Cost:$45"),
    ("public_trans", "Bus: Route:42 Next:3min Stops:24 Frequency:15min"),
    ("autonomous_drive", "Auto: Level:4 Speed:60km/h Objects:12 Confidence:99.2%%"),
]
f += "\n/* ===== Batch 163: Transportation ===== */\n"
for c, det in details163:
    f += "static void " + c + "_163(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 164: Construction + Architecture ===
cmds164 = ["bim_model","bim_clash","bim_quantify","structural_calc",
            "hvac_design","electrical_plan","plumbing_plan","fire_safety",
            "cost_estimate","schedule_plan","quality_check","permit_apply"]

d += "\n/* Batch 164: Construction + Architecture */\n"
for c in cmds164:
    d += f"static void {c}_164(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 164: Construction + Architecture */\n'
for c in cmds164:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_164}, '
t += '\n'

details164 = [
    ("bim_model", "BIM: Model:12-story building Elements:45,000 LOD:400 Format:IFC"),
    ("bim_clash", "Clash: 23 conflicts MEP-Struct:12 MEP-Arch:8 Structural:3"),
    ("bim_quantify", "Quantify: Concrete:1,245m3 Steel:234t Brick:45,000 blocks"),
    ("structural_calc", "Struct: Beam:W24x68 Load:45kN Deflection:L/360 OK"),
    ("hvac_design", "HVAC: Load:125kW Heating:85kW Cooling:40kW Zones:12"),
    ("electrical_plan", "Electrical: Panel:200A Circuits:24 Load:156kW Demand:125kW"),
    ("plumbing_plan", "Plumbing: Fixtures:48 Hot:2.3L/min Cold:3.1L/min Drain:OK"),
    ("fire_safety", "Fire: Sprinklers:128 Extinguishers:24 Egress:4 exits Alarm:OK"),
    ("cost_estimate", "Cost: Total:$2.3M Structure:$890k MEP:$450k Finish:$340k"),
    ("schedule_plan", "Schedule: Duration:18months Critical:12 tasks Float:45 days"),
    ("quality_check", "Quality: Concrete:pass Steel:pass MEP:pass Inspection:87%%"),
    ("permit_apply", "Permit: Building:#12848 Status:approved Valid:24months Fee:$12,400"),
]
f += "\n/* ===== Batch 164: Construction + Architecture ===== */\n"
for c, det in details164:
    f += "static void " + c + "_164(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void supply_optimize_161(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"supply-optimize", supply_optimize_161},'
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
print("DONE - Batch 162-164 injected!")
