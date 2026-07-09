SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 150: Blockchain Advanced ===
cmds150 = ["chain_deploy","token_deploy","nft_create","defi_lend",
            "defi_borrow","swap_tokens","bridge_assets","dao_govern",
            "multisig_create","oracle_query","layer2_bridge","gas_optimize"]

d = "\n/* Batch 150: Blockchain Advanced */\n"
for c in cmds150:
    d += f"static void {c}_150(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 150: Blockchain Advanced */\n'
for c in cmds150:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_150}, '
t += '\n'

details150 = [
    ("chain_deploy", "Chain: Deploy ERC-721 Contract:0x1234 Gas:2.1M Cost:$42"),
    ("token_deploy", "Token: ERC-20 BYO Name:BYO Supply:1M Decimals:18"),
    ("nft_create", "NFT: #12848 Metadata:Qm... Owner:0x5678 Listed:false"),
    ("defi_lend", "Lend: 1000 USDC APY:8.2%% Pool:Aave Status:deposited"),
    ("defi_borrow", "Borrow: 500 ETH Collateral:2000 USDC Health:185%%"),
    ("swap_tokens", "Swap: 100 USDC -> 0.047 ETH Price:2127 Slippage:0.1%%"),
    ("bridge_assets", "Bridge: 100 USDC ETH->Polygon Time:~15min Fee:$2.30"),
    ("dao_govern", "DAO: Proposal #47 Quorum:65%% For:78%% Against:22%%"),
    ("multisig_create", "Multisig: 3/5 signers Created Balance:12.5 ETH"),
    ("oracle_query", "Oracle: ETH/USD:2127.45 Source:Chainlink Confirmed:12 blocks"),
    ("layer2_bridge", "L2: Bridge to Optimism 100 USDC Time:~2min Fee:$0.50"),
    ("gas_optimize", "Gas: Current:25 gwei Optimal:18 gwei Savings:28%%"),
]
f = "\n/* ===== Batch 150: Blockchain Advanced ===== */\n"
for c, det in details150:
    f += "static void " + c + "_150(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 151: AR/VR Advanced ===
cmds151 = ["xr_scene","xr_spawn","xr_physics","xr_shader",
            "xr_audio","xr_haptic","xr_gesture","xr_eye_track",
            "xr_hand_track","xr_body_track","xr_space_map","xr_collab"]

d += "\n/* Batch 151: AR/VR Advanced */\n"
for c in cmds151:
    d += f"static void {c}_151(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 151: AR/VR Advanced */\n'
for c in cmds151:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_151}, '
t += '\n'

details151 = [
    ("xr_scene", "XR Scene: 128 objects Lighting:PBR Resolution:4K/eye Refresh:90Hz"),
    ("xr_spawn", "XR Spawn: Object placed at (1.2,0.8,-2.1) Scale:1.0 Rot:0,0,0"),
    ("xr_physics", "XR Physics: Mass:1.0 Friction:0.5 Restitution:0.3 Gravity:9.81"),
    ("xr_shader", "XR Shader: PBR Metallic:0.8 Roughness:0.2 Albedo:#FF5733"),
    ("xr_audio", "XR Audio: Spatial audio 3D position (1.2,0.8,-2.1) Volume:0.8"),
    ("xr_haptic", "XR Haptic: Pattern:pulse Intensity:0.7 Duration:200ms"),
    ("xr_gesture", "XR Gesture: Pinch detected Confidence:94%% Action:grab"),
    ("xr_eye_track", "XR Eye: Gaze point (0.3,0.4) Pupil:4.2mm Blink:false"),
    ("xr_hand_track", "XR Hand: 21 joints Palm:(0.1,0.2,-0.3) Gesture:open"),
    ("xr_body_track", "XR Body: 18 joints Head:(0,1.6,0) Hands:tracking"),
    ("xr_space_map", "XR Map: Room 5x4x3m Mesh:12,847 vertices Planes:6"),
    ("xr_collab", "XR Collab: 3 users Synced Latency:12ms Avatars:active"),
]
f += "\n/* ===== Batch 151: AR/VR Advanced ===== */\n"
for c, det in details151:
    f += "static void " + c + "_151(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 152: Robotics Advanced ===
cmds152 = ["ros_init","ros_topic","ros_service","ros_param",
            "motor_pid","servo_sweep","imu_calibrate","lidar_slam",
            "nav_goal","grasp_plan","force_control","vision_detect"]

d += "\n/* Batch 152: Robotics Advanced */\n"
for c in cmds152:
    d += f"static void {c}_152(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 152: Robotics Advanced */\n'
for c in cmds152:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_152}, '
t += '\n'

details152 = [
    ("ros_init", "ROS2: Node:byo_control Namespace:/ Msgs:12 Srvs:3 Active:true"),
    ("ros_topic", "Topic: /cmd_vel Hz:50 Type:geometry_msgs/Twist Subscribers:3"),
    ("ros_service", "Service: /get_pose Type:geometry_msgs/Pose Latency:2ms"),
    ("ros_param", "Param: /robot/max_speed=1.5 /robot/robot_radius=0.2"),
    ("motor_pid", "Motor PID: Kp=2.5 Ki=0.8 Kd=0.3 Error:0.02 Output:54.3%%"),
    ("servo_sweep", "Servo Sweep: Min:0 Max:180 Step:1 Speed:60deg/s"),
    ("imu_calibrate", "IMU Calib: Accel:offset(0.01,-0.02,0.03) Gyro:bias(0.5,-0.3,0.1)"),
    ("lidar_slam", "SLAM: Map:128x128 Robot:pos(5.2,3.1) Pose:x=5.2 y=3.1 theta=1.57"),
    ("nav_goal", "Nav: Goal(8.0,5.0) Path:12.3m ETA:15.2s Obstacles:4 Status:navigating"),
    ("grasp_plan", "Grasp: Object:cube Approach:top Force:5N Grip:parallel Points:4"),
    ("force_control", "Force: Fx:2.3N Fy:-1.1N Fz:8.7N Torque:0.5Nm Mode:impedance"),
    ("vision_detect", "Vision: Objects:3 Class:box(cyl,plate) Conf:94%% Pose:(0.5,0.3,0.2)"),
]
f += "\n/* ===== Batch 152: Robotics Advanced ===== */\n"
for c, det in details152:
    f += "static void " + c + "_152(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT
m = "static void video_export_149(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

m = '{"video-export", video_export_149},'
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
print("DONE - Batch 150-152 injected!")
