SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 135: IoT + Smart Home ===
cmds135 = ["iot_discover","iot_pair","iot_control","iot_status","smart_light",
            "smart_lock","smart_thermostat","smart_camera","smart_speaker","smart_plug",
            "zigbee_pair","mqtt_sub"]

d = "\n/* Batch 135: IoT + Smart Home */\n"
for c in cmds135:
    d += f"static void {c}_135(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 135: IoT + Smart Home */\n'
for c in cmds135:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_135}, '
t += '\n'

details135 = [
    ("iot_discover", "IoT Discover: 7 devices Zigbee:3 BLE:2 WiFi:2"),
    ("iot_pair", "Pair: Philips Hue Bridge MAC:00:17:88:01:02:03 OK"),
    ("iot_control", "Control: Light set to 75%% warm-white"),
    ("iot_status", "Status: 5/7 online Battery avg:72%% Signal:-45dBm"),
    ("smart_light", "Light: ON Brightness:75%% Color:2700K Scene:Reading"),
    ("smart_lock", "Lock: LOCKED Battery:89%% Last:Front door 14:23"),
    ("smart_thermostat", "Thermostat: 22C Mode:Auto Humidity:45%% Schedule:Home"),
    ("smart_camera", "Camera: Front-Door Recording:1080p Motion:detected 14:23"),
    ("smart_speaker", "Speaker: Playing Spotify Volume:40%% EQ:Balanced"),
    ("smart_plug", "Plug: ON Power:245W Today:1.2kWh Cost:$0.18"),
    ("zigbee_pair", "Zigbee: Paired sensor Temp:21C Humidity:52%% Batt:100%%"),
    ("mqtt_sub", "MQTT Sub: 12 topics Active QoS:1 Messages:1,247"),
]
f = "\n/* ===== Batch 135: IoT + Smart Home ===== */\n"
for c, det in details135:
    f += "static void " + c + "_135(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 136: Automotive + Robotics ===
cmds136 = ["obd_read","obd_clear","can_bus","motor_control","servo_pos",
            "pid_tune","imu_read","lidar_scan","camera_detect","arm_inverse",
            "path_plan","collision_avoid"]

d += "\n/* Batch 136: Automotive + Robotics */\n"
for c in cmds136:
    d += f"static void {c}_136(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 136: Automotive + Robotics */\n'
for c in cmds136:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_136}, '
t += '\n'

details136 = [
    ("obd_read", "OBD: RPM:2450 Speed:65km/h Coolant:89C MAF:12.3g/s"),
    ("obd_clear", "OBD: DTC cleared P0301 P0302 Erased:2 codes"),
    ("can_bus", "CAN: 128 msgs/s ID:0x18FEF100 DLC:8 Bus:500kbps"),
    ("motor_control", "Motor: DC 12V PWM:75%% RPM:3200 Direction:CW"),
    ("servo_pos", "Servo: Ch1:90deg Ch2:45deg Ch3:120deg Ch4:0deg"),
    ("pid_tune", "PID: Kp=2.5 Ki=0.8 Kd=0.3 Error:0.02 Output:54.3%%"),
    ("imu_read", "IMU: Accel:(0.1,-0.2,9.78) Gyro:(0.5,-0.3,0.1) Mag:(23,-45,12)"),
    ("lidar_scan", "LiDAR: 360deg 10Hz Points:7200 Min:0.3m Max:12.5m"),
    ("camera_detect", "Camera: 640x480 Objects:3 Car:1 Ped:1 Cyclist:1"),
    ("arm_inverse", "IK: Joint1:45 J2:-30 J3:60 J4:0 J5:-45 J6:90 Pos:(0.5,0.3,0.2)"),
    ("path_plan", "Path: A* nodes:247 Length:3.2m Time:12ms Obstacles:4"),
    ("collision_avoid", "Avoid: Velocity:0.5m/s Heading:45deg Safety:0.8m gap"),
]
f += "\n/* ===== Batch 136: Automotive + Robotics ===== */\n"
for c, det in details136:
    f += "static void " + c + "_136(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 137: Music + Audio ===
cmds137 = ["music_compose","music_play","music_mix","music_eq","music_record",
            "beat_make","chord_gen","melody_gen","bass_line","drum_pattern",
            "vocal_process","audio_fft"]

d += "\n/* Batch 137: Music + Audio */\n"
for c in cmds137:
    d += f"static void {c}_137(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 137: Music + Audio */\n'
for c in cmds137:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_137}, '
t += '\n'

details137 = [
    ("music_compose", "Compose: Key:Am BPM:120 Time:4/4 Bars:32 Instruments:4"),
    ("music_play", "Play: 'Moonlight Sonata' BPM:60 Duration:4:32 Vol:75%%"),
    ("music_mix", "Mix: 8 tracks Master:-3dB LUFS:-14 True Peak:-1.5dB"),
    ("music_eq", "EQ: Low:0dB Mid:+2dB High:-1dB Shelf:80Hz"),
    ("music_record", "Record: 48kHz 24bit Stereo Channels:2 Peak:-6dBFS"),
    ("beat_make", "Beat: 120BPM Pattern:4/4 Kick:1,5 Snare:3,7 HiHat:every"),
    ("chord_gen", "Chords: Am-F-C-G (I-VI-III-VII) Voicing:root Position:closed"),
    ("melody_gen", "Melody: C4-E4-G4-A4-G4-E4-C4 Rhythm:8th Notes Key:C"),
    ("bass_line", "Bass: C2-G2-A2-F2 Pattern:8th Riff:walking Style:smooth"),
    ("drum_pattern", "Drums: Kick:4/snare:2/hihat:8/crash:1 Fill:bar4 Pattern:verse"),
    ("vocal_process", "Vocal: Tune:0.3ms Reverb:plate Decay:1.8s Compress:4:1"),
    ("audio_fft", "FFT: 44100Hz Peaks:250Hz(-12dB) 1kHz(-6dB) 4kHz(-3dB) 8kHz(-8dB)"),
]
f += "\n/* ===== Batch 137: Music + Audio ===== */\n"
for c, det in details137:
    f += "static void " + c + "_137(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT
m = "static void tax_calc_134(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

m = '{"tax-calc", tax_calc_134},'
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
print("DONE - Batch 135-137 injected!")
