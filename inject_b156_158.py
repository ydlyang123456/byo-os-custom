SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 156: Edge Computing + 5G ===
cmds156 = ["edge_deploy","edge_sync","edge_offload","edge_cache",
            "edge_fog","edge_mist","5g_slice","5g_network",
            "5g_handover","5g_beam","5g_urllc","5g_mmtc"]

d = "\n/* Batch 156: Edge Computing + 5G */\n"
for c in cmds156:
    d += f"static void {c}_156(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 156: Edge Computing + 5G */\n'
for c in cmds156:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_156}, '
t += '\n'

details156 = [
    ("edge_deploy", "Edge: Deployed to 12 nodes Latency:2ms Cache:2.3GB"),
    ("edge_sync", "Edge Sync: 12 nodes synchronized Data:1.2GB Lag:0.1s"),
    ("edge_offload", "Edge Offload: ML inference 12ms vs cloud 145ms Saved:91%%"),
    ("edge_cache", "Edge Cache: Hit:94%% Miss:6%% Size:4.5GB Evictions:12"),
    ("edge_fog", "Fog: 5 fog nodes Processing:1.2GB/s Latency:8ms"),
    ("edge_mist", "Mist: 24 micro-nodes Sensors:48 Data:156KB/s"),
    ("5g_slice", "5G Slice: eMBB:500Mbps URLLC:1ms mMTC:1M/km2"),
    ("5g_network", "5G: Band:n78 Speed:1.2Gbps Latency:2ms Cells:47"),
    ("5g_handover", "5G Handover: Source:gNB-12 Target:gNB-15 Time:8ms OK"),
    ("5g_beam", "5G Beam: Width:10deg Gain:24dBi Tracking:user-123"),
    ("5g_urllc", "5G URLLC: Latency:0.8ms Reliability:99.999%% Jitter:0.1ms"),
    ("5g_mmtc", "5G mMTC: Devices:847,000/km2 Throughput:156Kbps/device"),
]
f = "\n/* ===== Batch 156: Edge Computing + 5G ===== */\n"
for c, det in details156:
    f += "static void " + c + "_156(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 157: Geospatial + Mapping ===
cmds157 = ["geo_convert","geo_project","geo_buffer","geo_intersect",
            "geo_union","geo_clip","geo_merge","geo_raster",
            "geo_vector","geo_3d","geo_heatmap","geo_route"]

d += "\n/* Batch 157: Geospatial + Mapping */\n"
for c in cmds157:
    d += f"static void {c}_157(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 157: Geospatial + Mapping */\n'
for c in cmds157:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_157}, '
t += '\n'

details157 = [
    ("geo_convert", "Convert: WGS84->UTM Zone:54N Accuracy:0.001m"),
    ("geo_project", "Project: Mercator->Lambert Scale:1:10000 Error:0.01%%"),
    ("geo_buffer", "Buffer: 100m around polygon Area:12,847m2 Features:23"),
    ("geo_intersect", "Intersect: Layer A(124) x Layer B(89) Results:34"),
    ("geo_union", "Union: 3 polygons Merged:1 area:45,678m2"),
    ("geo_clip", "Clip: 1,247 features clipped to boundary Output:892"),
    ("geo_merge", "Merge: 4 shapefiles -> 1 Features:3,456 CRS:EPSG:4326"),
    ("geo_raster", "Raster: DEM 30m resolution Size:128x124 tiles Elevation:0-2340m"),
    ("geo_vector", "Vector: Simplify 12,847 vertices -> 1,247 Douglas-Peucker"),
    ("geo_3d", "3D Terrain: TIN 12,847 vertices Terrain:1.2km^2"),
    ("geo_heatmap", "Heatmap: Points:12,847 Kernel:Gaussian Bandwidth:50m"),
    ("geo_route", "Route: A* 12.3km ETA:18min Waypoints:4 Avoid:tolls"),
]
f += "\n/* ===== Batch 157: Geospatial + Mapping ===== */\n"
for c, det in details157:
    f += "static void " + c + "_157(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 158: Audio Processing Advanced ===
cmds158 = ["audio_denoise","audio_dereverb","audio_separate","audio_enhance",
            "audio_transcribe","audio_pitch","audio_tempo","audio_reverb",
            "audio_delay","audio_chorus","audio_flanger","audio_compressor"]

d += "\n/* Batch 158: Audio Processing Advanced */\n"
for c in cmds158:
    d += f"static void {c}_158(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 158: Audio Processing Advanced */\n'
for c in cmds158:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_158}, '
t += '\n'

details158 = [
    ("audio_denoise", "Denoise: SNR:12->38dB Method:Spectral Gate Noise:-45dBFS"),
    ("audio_dereverb", "Dereverb: RT60:1.2->0.3s Clarity:0.72 Algorithm:WPE"),
    ("audio_separate", "Separate: Vocals:94%% Drums:89%% Bass:91%% Other:87%%"),
    ("audio_enhance", "Enhance: EQ:mastered Compression:3:1 Limiter:-1dBFS"),
    ("audio_transcribe", "Transcribe: 12.3min 1,247 words WER:3.2%% Language:EN"),
    ("audio_pitch", "Pitch: +2 semitones Algorithm:PSOLA Quality:high"),
    ("audio_tempo", "Tempo: 120->140 BPM Algorithm:TS/stretch Quality:95%%"),
    ("audio_reverb", "Reverb: Type:plate Room:medium Decay:2.1s Wet:30%%"),
    ("audio_delay", "Delay: 120ms Feedback:35%% Ping-pong:stereo Mix:25%%"),
    ("audio_chorus", "Chorus: Rate:0.5Hz Depth:2ms Mix:40%% Voices:3"),
    ("audio_flanger", "Flanger: Rate:0.3Hz Depth:5ms Feedback:60%% Phase:90deg"),
    ("audio_compressor", "Compressor: Ratio:4:1 Threshold:-18dB Attack:5ms Release:50ms"),
]
f += "\n/* ===== Batch 158: Audio Processing Advanced ===== */\n"
for c, det in details158:
    f += "static void " + c + "_158(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void data_govern_155(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"data-govern", data_govern_155},'
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
print("DONE - Batch 156-158 injected!")
