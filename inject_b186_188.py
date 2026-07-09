SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 186: Quantum Computing ===
cmds186 = ["qubit_create","qubit_entangle","qubit_measure","circuit_design",
            "error_correct","grover_search","shor_factor","quantum_sim",
            "variational","quantum_ml","topo_qubit","quantum_net"]

d = "\n/* Batch 186: Quantum Computing */\n"
for c in cmds186:
    d += f"static void {c}_186(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 186: Quantum Computing */\n'
for c in cmds186:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_186}, '
t += '\n'

details186 = [
    ("qubit_create", "Qubit: Initialized |0> Fidelity:99.7%% T1:50us T2:70us"),
    ("qubit_entangle", "Entangle: Bell pair |Phi+> Fidelity:99.2%% Distance:100km"),
    ("qubit_measure", "Measure: Q0:|1>(0.72) Q1:|0>(0.45) Collapsed:10"),
    ("circuit_design", "Circuit: 8 qubits 12 gates Depth:5 CNOT:4 Classical:8"),
    ("error_correct", "Error Correction: Surface code d=5 Logical error:1e-6"),
    ("grover_search", "Grover: N=1,024 Found:iteration 23 Confidence:99.8%%"),
    ("shor_factor", "Shor: Factoring 15 = 3 x 5 Qubits:8 Depth:12"),
    ("quantum_sim", "Sim: 20 qubits State:2^20=1M amplitudes Time:2.3s"),
    ("variational", "VQE: Ansatz:UCCSD Parameters:47 Converged:iteration 89 Energy:-7.6Ha"),
    ("quantum_ml", "QML: QSVM Accuracy:94.7%% Features:8 Qubits:6"),
    ("topo_qubit", "Topo: Majorana braided T=50mK Non-Abelian:confirmed"),
    ("quantum_net", "QNet: QKD:BB84 Key rate:1kbps Distance:100km Error:1.2%%"),
]
f = "\n/* ===== Batch 186: Quantum Computing ===== */\n"
for c, det in details186:
    f += "static void " + c + "_186(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 187: Climate + Sustainability ===
cmds187 = ["carbon_track","carbon_offset","lca_assess","green_build",
            "renewable_int","circular_econ","waste_zero","water_footprint",
            "biodiversity","deforestation","ocean_health","climate_model"]

d += "\n/* Batch 187: Climate + Sustainability */\n"
for c in cmds187:
    d += f"static void {c}_187(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 187: Climate + Sustainability */\n'
for c in cmds187:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_187}, '
t += '\n'

details187 = [
    ("carbon_track", "Carbon: Scope1:125t Scope2:340t Scope3:2,340t Total:2,805t"),
    ("carbon_offset", "Offset: Credits:500t Cost:$12/t Trees:12,000 Renewable:45%%"),
    ("lca_assess", "LCA: Product:12kg CO2e Hotspot:manufacturing(67%%) Use:23%%"),
    ("green_build", "Green: LEED:Gold Energy:-35%% Water:-40%% Materials:recycled"),
    ("renewable_int", "Renewable: Solar:42%% Wind:23%% Hydro:12%% Total:77%%"),
    ("circular_econ", "Circular: Recycled:45%% Reused:23%% Composted:12%% Landfill:20%%"),
    ("waste_zero", "Zero Waste: Achieved:92%% Diverted:11.5t Landfill:1t/month"),
    ("water_footprint", "Water: Blue:125gal Green:234gal Grey:45gal Total:404gal"),
    ("biodiversity", "Biodiversity: Index:0.78 Species:124 Endangered:3 Protected:67%%"),
    ("deforestation", "Forest: Coverage:67%% Loss:0.3%%/yr Protected:45%% Reforest:12ha"),
    ("ocean_health", "Ocean: pH:8.1 Temp:+0.5C Coral:bleaching Plastic:reducing"),
    ("climate_model", "Climate: RCP:4.5 Temp:+2.1C by 2100 Sea level:+0.5m"),
]
f += "\n/* ===== Batch 187: Climate + Sustainability ===== */\n"
for c, det in details187:
    f += "static void " + c + "_187(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 188: Social Impact ===
cmds188 = ["ngo_track","donor_manage","volunteer_coord","grant_manage",
            "impact_measure","community_engage","education_outreach",
            "health_program","poverty_reduce","equality_index",
            "sustainability_score","social_enterprise"]

d += "\n/* Batch 188: Social Impact */\n"
for c in cmds188:
    d += f"static void {c}_188(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 188: Social Impact */\n'
for c in cmds188:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_188}, '
t += '\n'

details188 = [
    ("ngo_track", "NGO: Programs:12 Beneficiaries:45,678 Budget:$2.3M Efficiency:92%%"),
    ("donor_manage", "Donors: 1,247 Active:892 Revenue:$1.2M Retention:78%%"),
    ("volunteer_coord", "Volunteers: 234 Active:189 Hours:12,847 Impact:high"),
    ("grant_manage", "Grants: 12 active 3 pending Awarded:$4.5M Spent:67%%"),
    ("impact_measure", "Impact: SDG:5 goals aligned M&E:quarterly Report:published"),
    ("community_engage", "Community: Events:24 Participants:1,247 Feedback:4.5/5"),
    ("education_outreach", "Education: Students:2,347 Teachers:12 Schools:8"),
    ("health_program", "Health: Patients:4,567 Clinics:3 Surgeries:124"),
    ("poverty_reduce", "Poverty: Households:234 Income:+45%% Self-sustaining:78%%"),
    ("equality_index", "Equality: GGI:0.78 PGI:0.65 Pay gap:-12%% Diversity:42%%"),
    ("sustainability_score", "SDG: Score:78/100 Goals:8 aligned Projects:24"),
    ("social_enterprise", "Enterprise: Revenue:$450K Impact:1,247 lives Profit:12%%"),
]
f += "\n/* ===== Batch 188: Social Impact ===== */\n"
for c, det in details188:
    f += "static void " + c + "_188(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void consciousness_185(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"consciousness", consciousness_185},'
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
print("DONE - Batch 186-188 injected!")
