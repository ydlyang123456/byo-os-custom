SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 183: Space Exploration ===
cmds183 = ["mars_colony","lunar_base","asteroid_mine","space_elevator",
            "solar_sail","ion_drive","fusion_reactor","antimatter",
            "wormhole_calc","dyson_sphere","bertrand_russell","kardashev"]

d = "\n/* Batch 183: Space Exploration */\n"
for c in cmds183:
    d += f"static void {c}_183(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 183: Space Exploration */\n'
for c in cmds183:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_183}, '
t += '\n'

details183 = [
    ("mars_colony", "Mars Colony: Pop:24 Habitats:6 Power:120kW Water:recycled Air:98%%"),
    ("lunar_base", "Lunar Base: Crater:Shackleton Modules:3 Pressurized:1,200m2"),
    ("asteroid_mine", "Asteroid Mine: Target:2014 MU39 Metals:platinum 12t Water:100t"),
    ("space_elevator", "Space Elevator: Height:36,000km Cable:carbon nanotube Capacity:20t"),
    ("solar_sail", "Solar Sail: Area:12,000m2 Thrust:9.1N/m2 Max Speed:0.1c"),
    ("ion_drive", "Ion Drive: Thrust:0.5N Isp:3,100s Power:10kW Mars ETA:180 days"),
    ("fusion_reactor", "Fusion: D-T plasma T:150M K Power:500MW Efficiency:40%%"),
    ("antimatter", "Antimatter: Stored:1g Production:1ng/day Cost:$62.5T/g"),
    ("wormhole_calc", "Wormhole: Stable:needs exotic matter Mass:-M_sun Size:1m"),
    ("dyson_sphere", "Dyson Sphere: Coverage:67%% Power:3.8e26W Stars:12 candidates"),
    ("bertrand_russell", "Russell: Paradox:Self-reference Set:all-sets Notation:ZFC"),
    ("kardashev", "Kardashev: Humanity:0.73 Type I target:10^16W ETA:2300"),
]
f = "\n/* ===== Batch 183: Space Exploration ===== */\n"
for c, det in details183:
    f += "static void " + c + "_183(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 184: Biology + Genetics ===
cmds184 = ["genome_seq","gene_edit","protein_synth","cell_sim",
            "crispr_design","microbiome","stem_cell","cloning",
            "biotech_ferment","dna_storage","synthetic_bio","bioethics"]

d += "\n/* Batch 184: Biology + Genetics */\n"
for c in cmds184:
    d += f"static void {c}_184(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 184: Biology + Genetics */\n'
for c in cmds184:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_184}, '
t += '\n'

details184 = [
    ("genome_seq", "Genome: 3.2B base pairs Coding:20,000 genes Assembly:99.9%%"),
    ("gene_edit", "CRISPR: Target:BRCA1 Exon:11 Guide:GCAGC Efficiency:87%%"),
    ("protein_synth", "Protein: Insulin 51aa MW:5,808Da Fold:correct Yield:12mg/L"),
    ("cell_sim", "Cell Sim: 12,847 genes 156 pathways Time:2.3s Cells:1,247"),
    ("crispr_design", "CRISPR: SpCas9 Guide:20nt PAM:NGG Off-target:0.3%%"),
    ("microbiome", "Microbiome: Diversity:4.2 Shannon Bacteria:12phyla Ratio:firm/bacto:2:1"),
    ("stem_cell", "Stem Cell: iPSC Passage:12 Differentiation:cardiomyocyte Purity:94%%"),
    ("cloning", "Cloning: Somatic cell nuclear transfer Efficiency:2%% Viable:3/150"),
    ("biotech_ferment", "Ferment: E.coli 37C 48h Product:1.2g/L Yield:85%%"),
    ("dna_storage", "DNA Storage: 12GB data -> 1.2mg DNA Encoding:error-correction"),
    ("synthetic_bio", "SynBio: Circuit:3 genes Logic:AND Gate:inducible Output:GFP"),
    ("bioethics", "Ethics: Review:approved Risk:BSL-2 Compliance:NIH Guidelines"),
]
f += "\n/* ===== Batch 184: Biology + Genetics ===== */\n"
for c, det in details184:
    f += "static void " + c + "_184(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 185: Psychology + Neuroscience ===
cmds185 = ["eeg_read","fmri_analyze","neural_decode","brain_computer",
            "cognitive_test","memory_train","attention_test","emotion_rec",
            "behavior_model","neuro_stim","brain_map","consciousness"]

d += "\n/* Batch 185: Psychology + Neuroscience */\n"
for c in cmds185:
    d += f"static void {c}_185(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 185: Psychology + Neuroscience */\n'
for c in cmds185:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_185}, '
t += '\n'

details185 = [
    ("eeg_read", "EEG: 64 channels Alpha:12Hz Beta:22Hz Gamma:40Hz Artifacts:none"),
    ("fmri_analyze", "fMRI: Voxel:2x2x2mm Activation:prefrontal Talairach:(32,45,12)"),
    ("neural_decode", "Decoding: Accuracy:87%% Features:128 Classifier:SVM Stimulus:visual"),
    ("brain_computer", "BCI: Commands:4 Speed:12bits/min Accuracy:92%% Latency:200ms"),
    ("cognitive_test", "CogTest: IQ:128 Memory:95th Verbal:90th Processing:85th"),
    ("memory_train", "Memory: Technique:method-of-loki Score:72/100 Improvement:+15%%"),
    ("attention_test", "Attention: Sustained:12min Selective:94%% Divided:78%%"),
    ("emotion_rec", "Emotion: Happy:45%% Neutral:35%% Sad:12%% Angry:5%% Surprised:3%%"),
    ("behavior_model", "Behavior: Model:RL Reward:delay-discounting Rate:0.95"),
    ("neuro_stim", "TMS: Target:DLPFC Intensity:80%% Motor threshold Frequency:1Hz"),
    ("brain_map", "Brain: Atlas:MNI152 Parcels:84 Regions:activated:12"),
    ("consciousness", "Consciousness: Theory:IIT Phi:4.7 Integrated:high Awareness:67%%"),
]
f += "\n/* ===== Batch 185: Psychology + Neuroscience ===== */\n"
for c, det in details185:
    f += "static void " + c + "_185(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void docker_logs_182(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"docker-logs", docker_logs_182},'
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
print("DONE - Batch 183-185 injected!")
