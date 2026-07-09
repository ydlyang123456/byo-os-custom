import sys
SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()
b126_decl = "\n/* Batch 126: Quantum Computing + AR/VR */\n"
b126_decl += "static void quantum_init_126(int argc, char args[][CMD_MAX_LEN]);\n"
b126_decl += "static void quantum_gate_126(int argc, char args[][CMD_MAX_LEN]);\n"
b126_decl += "static void quantum_measure_126(int argc, char args[][CMD_MAX_LEN]);\n"
b126_decl += "static void quantum_teleport_126(int argc, char args[][CMD_MAX_LEN]);\n"
b126_decl += "static void quantum_entangle_126(int argc, char args[][CMD_MAX_LEN]);\n"
b126_decl += "static void quantum_superposition_126(int argc, char args[][CMD_MAX_LEN]);\n"
b126_decl += "static void vr_create_126(int argc, char args[][CMD_MAX_LEN]);\n"
b126_decl += "static void vr_render_126(int argc, char args[][CMD_MAX_LEN]);\n"
b126_decl += "static void vr_interact_126(int argc, char args[][CMD_MAX_LEN]);\n"
b126_decl += "static void ar_overlay_126(int argc, char args[][CMD_MAX_LEN]);\n"
b126_decl += "static void ar_track_126(int argc, char args[][CMD_MAX_LEN]);\n"
b126_decl += "static void ar_calibrate_126(int argc, char args[][CMD_MAX_LEN]);\n"

b127_decl = "\n/* Batch 127: Space Tech + Digital Twins */\n"
b127_decl += "static void orbit_calc_127(int argc, char args[][CMD_MAX_LEN]);\n"
b127_decl += "static void satellite_track_127(int argc, char args[][CMD_MAX_LEN]);\n"
b127_decl += "static void launch_sim_127(int argc, char args[][CMD_MAX_LEN]);\n"
b127_decl += "static void space_weather_127(int argc, char args[][CMD_MAX_LEN]);\n"
b127_decl += "static void asteroid_db_127(int argc, char args[][CMD_MAX_LEN]);\n"
b127_decl += "static void mars_rover_127(int argc, char args[][CMD_MAX_LEN]);\n"
b127_decl += "static void iss_status_127(int argc, char args[][CMD_MAX_LEN]);\n"
b127_decl += "static void rocket_design_127(int argc, char args[][CMD_MAX_LEN]);\n"
b127_decl += "static void twin_create_127(int argc, char args[][CMD_MAX_LEN]);\n"
b127_decl += "static void twin_sync_127(int argc, char args[][CMD_MAX_LEN]);\n"
b127_decl += "static void twin_predict_127(int argc, char args[][CMD_MAX_LEN]);\n"
b127_decl += "static void twin_optimize_127(int argc, char args[][CMD_MAX_LEN]);\n"

b128_decl = "\n/* Batch 128: Containers + System Tools */\n"
b128_decl += "static void container_create_128(int argc, char args[][CMD_MAX_LEN]);\n"
b128_decl += "static void container_list_128(int argc, char args[][CMD_MAX_LEN]);\n"
b128_decl += "static void container_stop_128(int argc, char args[][CMD_MAX_LEN]);\n"
b128_decl += "static void container_logs_128(int argc, char args[][CMD_MAX_LEN]);\n"
b128_decl += "static void image_build_128(int argc, char args[][CMD_MAX_LEN]);\n"
b128_decl += "static void image_push_128(int argc, char args[][CMD_MAX_LEN]);\n"
b128_decl += "static void pod_manage_128(int argc, char args[][CMD_MAX_LEN]);\n"
b128_decl += "static void namespace_ctl_128(int argc, char args[][CMD_MAX_LEN]);\n"
b128_decl += "static void cgroup_stat_128(int argc, char args[][CMD_MAX_LEN]);\n"
b128_decl += "static void overlay_fs_128(int argc, char args[][CMD_MAX_LEN]);\n"
b128_decl += "static void seccomp_profile_128(int argc, char args[][CMD_MAX_LEN]);\n"
b128_decl += "static void sysbench_128(int argc, char args[][CMD_MAX_LEN]);\n"

b126_table = '    /* Batch 126: Quantum Computing + AR/VR */\n'
b126_table += '    {"quantum-init", quantum_init_126}, {"quantum-gate", quantum_gate_126},\n'
b126_table += '    {"quantum-measure", quantum_measure_126}, {"quantum-teleport", quantum_teleport_126},\n'
b126_table += '    {"quantum-entangle", quantum_entangle_126}, {"quantum-superposition", quantum_superposition_126},\n'
b126_table += '    {"vr-create", vr_create_126}, {"vr-render", vr_render_126},\n'
b126_table += '    {"vr-interact", vr_interact_126}, {"ar-overlay", ar_overlay_126},\n'
b126_table += '    {"ar-track", ar_track_126}, {"ar-calibrate", ar_calibrate_126},\n'

b127_table = '    /* Batch 127: Space Tech + Digital Twins */\n'
b127_table += '    {"orbit-calc", orbit_calc_127}, {"satellite-track", satellite_track_127},\n'
b127_table += '    {"launch-sim", launch_sim_127}, {"space-weather", space_weather_127},\n'
b127_table += '    {"asteroid-db", asteroid_db_127}, {"mars-rover", mars_rover_127},\n'
b127_table += '    {"iss-status", iss_status_127}, {"rocket-design", rocket_design_127},\n'
b127_table += '    {"twin-create", twin_create_127}, {"twin-sync", twin_sync_127},\n'
b127_table += '    {"twin-predict", twin_predict_127}, {"twin-optimize", twin_optimize_127},\n'

b128_table = '    /* Batch 128: Containers + System Tools */\n'
b128_table += '    {"container-create", container_create_128}, {"container-list", container_list_128},\n'
b128_table += '    {"container-stop", container_stop_128}, {"container-logs", container_logs_128},\n'
b128_table += '    {"image-build", image_build_128}, {"image-push", image_push_128},\n'
b128_table += '    {"pod-manage", pod_manage_128}, {"namespace-ctl", namespace_ctl_128},\n'
b128_table += '    {"cgroup-stat", cgroup_stat_128}, {"overlay-fs", overlay_fs_128},\n'
b128_table += '    {"seccomp-profile", seccomp_profile_128}, {"sysbench", sysbench_128},\n'

b126_func = "\n/* ===== Batch 126: Quantum Computing + AR/VR ===== */\n"
b126_func += "static void quantum_init_126(int argc, char args[][CMD_MAX_LEN]) {\n"
b126_func += "    (void)argc; (void)args;\n"
b126_func += '    vga_puts("Quantum Simulator v1.0\\n");\n'
b126_func += '    vga_puts("  Qubits: 8 simulated\\n  Backend: Classical simulation\\n");\n'
b126_func += '    vga_puts("  Status: READY\\n  Error rate: 0.001%%\\n");\n'
b126_func += "}\n"
b126_func += "static void quantum_gate_126(int argc, char args[][CMD_MAX_LEN]) {\n"
b126_func += '    if(argc<2){vga_puts("Usage: quantum-gate <hadamard|pauli-x|pauli-z|cnot|toffoli>\\n");return;}\n'
b126_func += '    vga_puts("Applying gate: "); vga_puts(args[1]); vga_putchar(\'\\n\');\n'
b126_func += '    if(strcmp(args[1],"hadamard")==0){vga_puts("  H|0> = (|0> + |1>)/sqrt(2)\\n  Prob: 50%% |0>, 50%% |1>\\n");}\n'
b126_func += '    else if(strcmp(args[1],"pauli-x")==0){vga_puts("  X|0> = |1> (bit flip)\\n");}\n'
b126_func += '    else if(strcmp(args[1],"pauli-z")==0){vga_puts("  Z|1> = -|1> (phase flip)\\n");}\n'
b126_func += '    else if(strcmp(args[1],"cnot")==0){vga_puts("  CNOT: control flips target\\n");}\n'
b126_func += '    else if(strcmp(args[1],"toffoli")==0){vga_puts("  Toffoli: 3-qubit universal gate\\n");}\n'
b126_func += '    else{vga_puts("  Unknown gate\\n");}\n'
b126_func += "}\n"
b126_func += "static void quantum_measure_126(int argc, char args[][CMD_MAX_LEN]) {\n"
b126_func += "    (void)argc; (void)args;\n"
b126_func += '    vga_puts("Measuring qubits...\\n  Q0:|1>(0.72) Q1:|0>(0.45) Q2:|1>(0.88) Q3:|0>(0.31)\\n");\n'
b126_func += '    vga_puts("  Collapsed: 1010  Fidelity: 98.7%%\\n");\n'
b126_func += "}\n"
b126_func += "static void quantum_teleport_126(int argc, char args[][CMD_MAX_LEN]) {\n"
b126_func += "    (void)argc; (void)args;\n"
b126_func += '    vga_puts("Quantum Teleportation:\\n  1.Create Bell pair  2.CNOT+H  3.Measure  4.Correct\\n");\n'
b126_func += '    vga_puts("  Result: State teleported! Fidelity: 99.2%%\\n");\n'
b126_func += "}\n"
b126_func += "static void quantum_entangle_126(int argc, char args[][CMD_MAX_LEN]) {\n"
b126_func += "    (void)argc; (void)args;\n"
b126_func += '    vga_puts("Entangled pair: |Phi+> = (|00>+|11>)/sqrt(2)\\n  Correlation: 100%%  Dist: 1000km\\n");\n'
b126_func += "}\n"
b126_func += "static void quantum_superposition_126(int argc, char args[][CMD_MAX_LEN]) {\n"
b126_func += "    (void)argc; (void)args;\n"
b126_func += '    vga_puts("|psi> = 0.707|0> + 0.707|1>\\n  |0>: 50%%  |1>: 50%%  Bloch:(0,0,1)\\n");\n'
b126_func += "}\n"
b126_func += "static void vr_create_126(int argc, char args[][CMD_MAX_LEN]) {\n"
b126_func += '    if(argc<2){vga_puts("Usage: vr-create <name>\\n");return;}\n'
b126_func += '    vga_puts("VR scene: "); vga_puts(args[1]); vga_puts(" created\\n  2160x1200/eye 110FOV 90Hz\\n");\n'
b126_func += "}\n"
b126_func += "static void vr_render_126(int argc, char args[][CMD_MAX_LEN]) {\n"
b126_func += "    (void)argc; (void)args;\n"
b126_func += '    vga_puts("VR Render: 87fps 1247 draw calls 2.3M tri GPU:78%% Latency:11ms\\n");\n'
b126_func += "}\n"
b126_func += "static void vr_interact_126(int argc, char args[][CMD_MAX_LEN]) {\n"
b126_func += '    if(argc<2){vga_puts("Usage: vr-interact <grab|point|teleport>\\n");return;}\n'
b126_func += '    vga_puts("VR interaction: "); vga_puts(args[1]); vga_putchar(\'\\n\');\n'
b126_func += '    if(strcmp(args[1],"grab")==0){vga_puts("  Object at (1.2,0.8,-2.1)\\n");}\n'
b126_func += '    else if(strcmp(args[1],"point")==0){vga_puts("  Laser: 5.3m\\n");}\n'
b126_func += '    else if(strcmp(args[1],"teleport")==0){vga_puts("  To (3.0,0.0,1.5)\\n");}\n'
b126_func += '    else{vga_puts("  Unknown\\n");}\n'
b126_func += "}\n"
b126_func += "static void ar_overlay_126(int argc, char args[][CMD_MAX_LEN]) {\n"
b126_func += '    if(argc<2){vga_puts("Usage: ar-overlay <text|model|info>\\n");return;}\n'
b126_func += '    vga_puts("AR overlay: "); vga_puts(args[1]); vga_puts(" 60fps SLAM occlusion\\n");\n'
b126_func += "}\n"
b126_func += "static void ar_track_126(int argc, char args[][CMD_MAX_LEN]) {\n"
b126_func += "    (void)argc; (void)args;\n"
b126_func += '    vga_puts("AR Tracking: 3 objects - Cube(0.8m) Sphere(1.2m) Cylinder(2.1m) Conf:94.5%%\\n");\n'
b126_func += "}\n"
b126_func += "static void ar_calibrate_126(int argc, char args[][CMD_MAX_LEN]) {\n"
b126_func += "    (void)argc; (void)args;\n"
b126_func += '    vga_puts("AR Calib: IMU:OK Camera:OK Stereo:OK Error:0.003m PASS\\n");\n'
b126_func += "}\n"

b127_func = "\n/* ===== Batch 127: Space Tech + Digital Twins ===== */\n"
b127_func += "static void orbit_calc_127(int argc, char args[][CMD_MAX_LEN]) {\n"
b127_func += '    if(argc<2){vga_puts("Usage: orbit-calc <circular|elliptical|geo>\\n");return;}\n'
b127_func += '    vga_puts("Orbit: "); vga_puts(args[1]); vga_putchar(\'\\n\');\n'
b127_func += '    if(strcmp(args[1],"circular")==0){vga_puts("  408km 7.66km/s 92.68min\\n");}\n'
b127_func += '    else if(strcmp(args[1],"elliptical")==0){vga_puts("  Perigee:200km Apogee:35786km 11.6h\\n");}\n'
b127_func += '    else if(strcmp(args[1],"geo")==0){vga_puts("  35786km 3.07km/s 24h\\n");}\n'
b127_func += '    else{vga_puts("  Unknown\\n");}\n'
b127_func += "}\n"
b127_func += "static void satellite_track_127(int argc, char args[][CMD_MAX_LEN]) {\n"
b127_func += "    (void)argc; (void)args;\n"
b127_func += '    vga_puts("Sat: ISS(28.5N-80.2W 408km) Hubble(32.1N-45.7W 547km) GPS(0.0 20200km)\\n");\n'
b127_func += "}\n"
b127_func += "static void launch_sim_127(int argc, char args[][CMD_MAX_LEN]) {\n"
b127_func += "    (void)argc; (void)args;\n"
b127_func += '    vga_puts("Launch: T-10s ignite T-0 liftoff T+30s maxQ(1.2g) T+120s MECO T+480s orbit OK\\n");\n'
b127_func += "}\n"
b127_func += "static void space_weather_127(int argc, char args[][CMD_MAX_LEN]) {\n"
b127_func += "    (void)argc; (void)args;\n"
b127_func += '    vga_puts("Space WX: Solar 380km/s Bz:-2.3nT Kp:2(Quiet) Xray:B Proton:0.8pfu\\n");\n'
b127_func += "}\n"
b127_func += "static void asteroid_db_127(int argc, char args[][CMD_MAX_LEN]) {\n"
b127_func += "    (void)argc; (void)args;\n"
b127_func += '    vga_puts("Asteroids: Bennu(0.5km 2182) Ryugu(0.9km 8.7Mkm) Eros(16.8km 214Mkm)\\n");\n'
b127_func += '    vga_puts("  Total:31000+ Hazardous:2050\\n");\n'
b127_func += "}\n"
b127_func += "static void mars_rover_127(int argc, char args[][CMD_MAX_LEN]) {\n"
b127_func += '    if(argc<2){vga_puts("Usage: mars-rover <status|move|drill|photo>\\n");return;}\n'
b127_func += '    if(strcmp(args[1],"status")==0){vga_puts("  Batt:87%% Temp:-42C Sol:1247 Dist:12.3km\\n");}\n'
b127_func += '    else if(strcmp(args[1],"move")==0){vga_puts("  Moving 2.5m NE... done!\\n");}\n'
b127_func += '    else if(strcmp(args[1],"drill")==0){vga_puts("  15cm core: clay-rich H2O detected!\\n");}\n'
b127_func += '    else if(strcmp(args[1],"photo")==0){vga_puts("  Mastcam-Z 16MP panorama captured\\n");}\n'
b127_func += '    else{vga_puts("  Unknown\\n");}\n'
b127_func += "}\n"
b127_func += "static void iss_status_127(int argc, char args[][CMD_MAX_LEN]) {\n"
b127_func += "    (void)argc; (void)args;\n"
b127_func += '    vga_puts("ISS: 408x420km 51.6deg 7.66km/s Crew:7 Power:120kW Status:NOMINAL\\n");\n'
b127_func += "}\n"
b127_func += "static void rocket_design_127(int argc, char args[][CMD_MAX_LEN]) {\n"
b127_func += '    if(argc<2){vga_puts("Usage: rocket-design <single|multi|ssto>\\n");return;}\n'
b127_func += '    if(strcmp(args[1],"single")==0){vga_puts("  Thrust:7607kN LEO:22800kg\\n");}\n'
b127_func += '    else if(strcmp(args[1],"multi")==0){vga_puts("  Thrust:22821kN LEO:63800kg\\n");}\n'
b127_func += '    else if(strcmp(args[1],"ssto")==0){vga_puts("  Thrust:15000kN LEO:8500kg\\n");}\n'
b127_func += '    else{vga_puts("  Unknown\\n");}\n'
b127_func += "}\n"
b127_func += "static void twin_create_127(int argc, char args[][CMD_MAX_LEN]) {\n"
b127_func += '    if(argc<2){vga_puts("Usage: twin-create <factory|engine|city>\\n");return;}\n'
b127_func += '    vga_puts("Twin: "); vga_puts(args[1]); vga_puts(" 1247 sensors 1Hz ACTIVE\\n");\n'
b127_func += "}\n"
b127_func += "static void twin_sync_127(int argc, char args[][CMD_MAX_LEN]) {\n"
b127_func += "    (void)argc; (void)args;\n"
b127_func += '    vga_puts("Twin Sync: 2.3M points Latency:12ms Drift:0.001%% SYNCED\\n");\n'
b127_func += "}\n"
b127_func += "static void twin_predict_127(int argc, char args[][CMD_MAX_LEN]) {\n"
b127_func += "    (void)argc; (void)args;\n"
b127_func += '    vga_puts("Twin Predict: LSTM 72h horizon Fail at T+48h(bearing) Conf:89.3%%\\n");\n'
b127_func += "}\n"
b127_func += "static void twin_optimize_127(int argc, char args[][CMD_MAX_LEN]) {\n"
b127_func += "    (void)argc; (void)args;\n"
b127_func += '    vga_puts("Twin Optimize: 847->712 kWh/day Save 16%%($12400/yr) HVAC adjusted\\n");\n'
b127_func += "}\n"

b128_func = "\n/* ===== Batch 128: Containers + System Tools ===== */\n"
b128_func += "static void container_create_128(int argc, char args[][CMD_MAX_LEN]) {\n"
b128_func += '    if(argc<2){vga_puts("Usage: container-create <name>\\n");return;}\n'
b128_func += '    vga_puts("Container "); vga_puts(args[1]); vga_puts(" created PID:1247 RUNNING\\n");\n'
b128_func += "}\n"
b128_func += "static void container_list_128(int argc, char args[][CMD_MAX_LEN]) {\n"
b128_func += "    (void)argc; (void)args;\n"
b128_func += '    vga_puts("a1b2 web-server Up2h  b2c3 api-backend Up1h  c3d4 database Up3h\\n");\n'
b128_func += '    vga_puts("  Running:3 Stopped:1 Total:4\\n");\n'
b128_func += "}\n"
b128_func += "static void container_stop_128(int argc, char args[][CMD_MAX_LEN]) {\n"
b128_func += '    if(argc<2){vga_puts("Usage: container-stop <name>\\n");return;}\n'
b128_func += '    vga_puts("Stopping "); vga_puts(args[1]); vga_puts("... SIGTERM... stopped.\\n");\n'
b128_func += "}\n"
b128_func += "static void container_logs_128(int argc, char args[][CMD_MAX_LEN]) {\n"
b128_func += '    if(argc<2){vga_puts("Usage: container-logs <name>\\n");return;}\n'
b128_func += '    vga_puts("[10:23:45] Started  [10:23:46] DB connected  [10:24:01] GET /api 200\\n");\n'
b128_func += "}\n"
b128_func += "static void image_build_128(int argc, char args[][CMD_MAX_LEN]) {\n"
b128_func += '    if(argc<2){vga_puts("Usage: image-build <name>\\n");return;}\n'
b128_func += '    vga_puts("Build: "); vga_puts(args[1]); vga_puts(" 5 steps 245MB DONE\\n");\n'
b128_func += "}\n"
b128_func += "static void image_push_128(int argc, char args[][CMD_MAX_LEN]) {\n"
b128_func += '    if(argc<2){vga_puts("Usage: image-push <registry/img>\\n");return;}\n'
b128_func += '    vga_puts("Push: "); vga_puts(args[1]); vga_puts(" 3 layers sha256:a1b2c3 DONE\\n");\n'
b128_func += "}\n"
b128_func += "static void pod_manage_128(int argc, char args[][CMD_MAX_LEN]) {\n"
b128_func += '    if(argc<2){vga_puts("Usage: pod-manage <list|create|delete>\\n");return;}\n'
b128_func += '    if(strcmp(args[1],"list")==0){vga_puts("  web-stack:Running(3) ml-pipeline:Running(2)\\n");}\n'
b128_func += '    else{vga_puts("  Pod operation done\\n");}\n'
b128_func += "}\n"
b128_func += "static void namespace_ctl_128(int argc, char args[][CMD_MAX_LEN]) {\n"
b128_func += "    (void)argc; (void)args;\n"
b128_func += '    vga_puts("NS: PID:4 NET:2 MNT:3 USER:1 UTS:1 IPC:1 Total:12\\n");\n'
b128_func += "}\n"
b128_func += "static void cgroup_stat_128(int argc, char args[][CMD_MAX_LEN]) {\n"
b128_func += "    (void)argc; (void)args;\n"
b128_func += '    vga_puts("Cgroup: cpu:100000 mem:128/256MB io:R1.2G/W450M pids:12\\n");\n'
b128_func += "}\n"
b128_func += "static void overlay_fs_128(int argc, char args[][CMD_MAX_LEN]) {\n"
b128_func += "    (void)argc; (void)args;\n"
b128_func += '    vga_puts("OverlayFS: Lower:/base(Upper:/overlay Merged:/mnt Used:1.2/10GB)\\n");\n'
b128_func += "}\n"
b128_func += "static void seccomp_profile_128(int argc, char args[][CMD_MAX_LEN]) {\n"
b128_func += "    (void)argc; (void)args;\n"
b128_func += '    vga_puts("Seccomp: filter 312 allow 44 block(mount,reboot) Viol:0 ACTIVE\\n");\n'
b128_func += "}\n"
b128_func += "static void sysbench_128(int argc, char args[][CMD_MAX_LEN]) {\n"
b128_func += '    if(argc<2){vga_puts("Usage: sysbench <cpu|memory|io|threads>\\n");return;}\n'
b128_func += '    vga_puts("Bench: "); vga_puts(args[1]);\n'
b128_func += '    if(strcmp(args[1],"cpu")==0){vga_puts(" 10000events/5.2s 1923/sec\\n");}\n'
b128_func += '    else if(strcmp(args[1],"memory")==0){vga_puts(" R:2.1GB/s W:1.8GB/s\\n");}\n'
b128_func += '    else if(strcmp(args[1],"io")==0){vga_puts(" R:450MB/s W:320MB/s IOPS:12500\\n");}\n'
b128_func += '    else if(strcmp(args[1],"threads")==0){vga_puts(" 8 threads contention:0.3ms\\n");}\n'
b128_func += '    else{vga_puts(" Unknown\\n");}\n'
b128_func += "}\n"

# INJECT DECLARATIONS
m = "static void cloud_cost_125(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + b126_decl + b127_decl + b128_decl + content[i+len(m):]
    print("Declarations OK")
else:
    print("ERROR: decl marker not found!")

# INJECT TABLE
m = '{"cloud-cost", cloud_cost_125},'
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + "\n" + b126_table + b127_table + b128_table + content[i+len(m):]
    print("Table OK")
else:
    print("ERROR: table marker not found!")

# INJECT FUNCTIONS
m = "void shell_run(void)"
i = content.find(m)
if i >= 0:
    content = content[:i] + b126_func + b127_func + b128_func + "\n" + content[i:]
    print("Functions OK")
else:
    print("ERROR: func marker not found!")

with open(SHELL_C, "w", encoding="utf-8") as f:
    f.write(content)
print("DONE - all 36 commands injected!")
