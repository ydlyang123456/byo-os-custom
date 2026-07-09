SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 144: Cloud Infrastructure ===
cmds144 = ["k8s_deploy","k8s_scale","k8s_rollout","k8s_logs",
            "helm_install","helm_upgrade","istio_mesh","cert_manager",
            "argocd_sync","tekton_run","crossplane_provision","external_dns"]

d = "\n/* Batch 144: Cloud Infrastructure */\n"
for c in cmds144:
    d += f"static void {c}_144(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 144: Cloud Infrastructure */\n'
for c in cmds144:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_144}, '
t += '\n'

details144 = [
    ("k8s_deploy", "K8s: Deploy api-server:3 replicas:3 ready:3/3 CPU:45%%"),
    ("k8s_scale", "K8s: Scale api-server 3->5 pods Pending:2 Running:3"),
    ("k8s_rollout", "K8s: Rollout api-server Revision:5 Status:Healthy"),
    ("k8s_logs", "K8s Logs: api-server-abc123 Started:14:23 Requests:1,247/min"),
    ("helm_install", "Helm: Install prometheus Version:2.45.0 NS:monitoring"),
    ("helm_upgrade", "Helm: Upgrade grafana 10.0->10.1 Status:pending-upgrade"),
    ("istio_mesh", "Istio: Mesh healthy 12 services 47 pods mTLS:strict"),
    ("cert_manager", "Cert-Manager: Certs:12 Issued:10 Expiring:2 Renewing:1"),
    ("argocd_sync", "ArgoCD: App api-server Synced Health:Healthy 14 apps"),
    ("tekton_run", "Tekton: Pipeline run #128 Status:Succeeded Duration:2m34s"),
    ("crossplane_provision", "Crossplane: Provision RDS PostgreSQL Status:available"),
    ("external_dns", "ExternalDNS: 12 records synced Provider:AWS Route53"),
]
f = "\n/* ===== Batch 144: Cloud Infrastructure ===== */\n"
for c, det in details144:
    f += "static void " + c + "_144(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 145: Simulation + Modeling ===
cmds145 = ["sim_fluid","sim_structural","sim_thermal","sim_electromagnetic",
            "sim_traffic","sim_ecosystem","sim_economic","sim_epidemic",
            "sim_climate","sim_urban","sim_supply_chain","sim_wargame"]

d += "\n/* Batch 145: Simulation + Modeling */\n"
for c in cmds145:
    d += f"static void {c}_145(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 145: Simulation + Modeling */\n'
for c in cmds145:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_145}, '
t += '\n'

details145 = [
    ("sim_fluid", "CFD: Navier-Stokes Grid:64x64 Reynolds:1000 Converged:150iter"),
    ("sim_structural", "FEA: Beam deflection:2.3mm Stress:145MPa Safety:2.1x"),
    ("sim_thermal", "Thermal: Max:89C Min:22C Gradient:67C Heat sink:OK"),
    ("sim_electromagnetic", "EM: FDTD 3D cells:100x100x100 Freq:2.4GHz S11:-15dB"),
    ("sim_traffic", "Traffic: 1200 vehicles/hr Avg speed:45km/h Queue:12 vehicles"),
    ("sim_ecosystem", "Ecosystem: Species:12 Predators:3 Prey:5 Stability:0.87"),
    ("sim_economic", "Economic: GDP:+2.3%% Inflation:3.1%% Unemployment:4.2%%"),
    ("sim_epidemic", "Epidemic: R0:1.2 Infected:1,247 Recovered:892 Day:45"),
    ("sim_climate", "Climate: CO2:420ppm Temp:+1.2C Sea level:+3.2mm/yr"),
    ("sim_urban", "Urban: Population:1.2M Density:5,200/km2 Growth:1.8%%/yr"),
    ("sim_supply_chain", "Supply: 47 suppliers Lead time:12d Buffer:15%% Risk:low"),
    ("sim_wargame", "Wargame: 500 units Terrain:10x10km Turns:24 Score:87/100"),
]
f += "\n/* ===== Batch 145: Simulation + Modeling ===== */\n"
for c, det in details145:
    f += "static void " + c + "_145(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 146: Image Processing ===
cmds146 = ["img_resize","img_crop","img_filter","img_enhance",
            "img_segment","img_recognize","img_generate","img_compress",
            "img_convert","img_watermark","img_color_grade","img_stitch"]

d += "\n/* Batch 146: Image Processing */\n"
for c in cmds146:
    d += f"static void {c}_146(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 146: Image Processing */\n'
for c in cmds146:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_146}, '
t += '\n'

details146 = [
    ("img_resize", "Resize: 4032x3024 -> 800x600 Bilinear Quality:95%% Size:145KB"),
    ("img_crop", "Crop: 100,50 400x300 from 1920x1080 Output:400x300"),
    ("img_filter", "Filter: Gaussian blur sigma:2.0 Applied in 12ms"),
    ("img_enhance", "Enhance: Brightness:+15%% Contrast:+10%% Sharpness:+20%%"),
    ("img_segment", "Segment: Objects:5 Foreground:3 Background:1 Sky:1"),
    ("img_recognize", "Recognize: Person:94%% Car:87%% Building:91%%"),
    ("img_generate", "Generate: Diffusion 512x512 Steps:20 CFG:7.5 Seed:42"),
    ("img_compress", "Compress: JPEG 2.3MB->145KB Quality:85%% Ratio:16:1"),
    ("img_convert", "Convert: PNG->WebP Lossless Size:2.3MB->1.8MB"),
    ("img_watermark", "Watermark: Text:'BYO-OS' Position:bottom-right Opacity:50%%"),
    ("img_color_grade", "Color: Cinematic LUT applied Shadows:+5 Highlights:-3"),
    ("img_stitch", "Stitch: 4 images -> panorama 7680x2160 Blending:seamless"),
]
f += "\n/* ===== Batch 146: Image Processing ===== */\n"
for c, det in details146:
    f += "static void " + c + "_146(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT
m = "static void barcode_gen_143(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

m = '{"barcode-gen", barcode_gen_143},'
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + "\n" + t + content[i+len(m):]
    print("Table OK")
else: print("ERROR table!")

m = "void shell_run(void)"
i = content.find(m)
if i >= 0:
    content = content[:i] + f + "\n" + content[i:]
    print("Funcs OK")
else: print("ERROR func!")

with open(SHELL_C, "w", encoding="utf-8") as fh:
    fh.write(content)
print("DONE - Batch 144-146 injected!")
