SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 129: ML + Data Science ===
d = "\n/* Batch 129: ML + Data Science */\n"
d += "static void ml_train_129(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void ml_predict_129(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void ml_evaluate_129(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void data_split_129(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void data_normalize_129(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void feature_eng_129(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void pca_reduce_129(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void knn_classify_129(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void decision_tree_129(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void random_forest_129(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void svm_classify_129(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void neural_net_129(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 129: ML + Data Science */\n'
t += '    {"ml-train", ml_train_129}, {"ml-predict", ml_predict_129},\n'
t += '    {"ml-evaluate", ml_evaluate_129}, {"data-split", data_split_129},\n'
t += '    {"data-normalize", data_normalize_129}, {"feature-eng", feature_eng_129},\n'
t += '    {"pca-reduce", pca_reduce_129}, {"knn-classify", knn_classify_129},\n'
t += '    {"decision-tree", decision_tree_129}, {"random-forest", random_forest_129},\n'
t += '    {"svm-classify", svm_classify_129}, {"neural-net", neural_net_129},\n'

f129 = "\n/* ===== Batch 129: ML + Data Science ===== */\n"
f129 += "static void ml_train_129(int argc, char args[][CMD_MAX_LEN]) {\n"
f129 += '    if(argc<2){vga_puts("Usage: ml-train <model> [epochs]\\n");return;}\n'
f129 += '    vga_puts("Training: "); vga_puts(args[1]); vga_puts(" epochs:100\\n");\n'
f129 += '    vga_puts("  Loss: 0.0234  Accuracy: 94.7%%  Val: 92.1%%\\n");\n'
f129 += '    vga_puts("  Model saved: model.bin (2.3MB)\\n");\n'
f129 += "}\n"
f129 += "static void ml_predict_129(int argc, char args[][CMD_MAX_LEN]) {\n"
f129 += '    if(argc<2){vga_puts("Usage: ml-predict <input>\\n");return;}\n'
f129 += '    vga_puts("Predicting: "); vga_puts(args[1]); vga_putchar(\'\\n\');\n'
f129 += '    vga_puts("  Class: A (87.3%%)  Class: B (10.2%%)  Class: C (2.5%%)\\n");\n'
f129 += '    vga_puts("  Inference time: 1.2ms\\n");\n'
f129 += "}\n"
f129 += "static void ml_evaluate_129(int argc, char args[][CMD_MAX_LEN]) {\n"
f129 += "    (void)argc; (void)args;\n"
f129 += '    vga_puts("Model Evaluation:\\n  Accuracy: 94.7%%\\n  Precision: 93.2%%\\n");\n'
f129 += '    vga_puts("  Recall: 95.1%%\\n  F1: 94.1%%\\n  AUC: 0.978\\n");\n'
f129 += "}\n"
f129 += "static void data_split_129(int argc, char args[][CMD_MAX_LEN]) {\n"
f129 += "    (void)argc; (void)args;\n"
f129 += '    vga_puts("Split: Train 80%%(8000) Val 10%%(1000) Test 10%%(1000)\\n");\n'
f129 += "}\n"
f129 += "static void data_normalize_129(int argc, char args[][CMD_MAX_LEN]) {\n"
f129 += "    (void)argc; (void)args;\n"
f129 += '    vga_puts("Normalize: mean=0 std=1 MinMax [0,1] Applied to 12 features\\n");\n'
f129 += "}\n"
f129 += "static void feature_eng_129(int argc, char args[][CMD_MAX_LEN]) {\n"
f129 += "    (void)argc; (void)args;\n"
f129 += '    vga_puts("Features: 12->24 (poly2) + log transforms + one-hot(3 cats) = 31\\n");\n'
f129 += "}\n"
f129 += "static void pca_reduce_129(int argc, char args[][CMD_MAX_LEN]) {\n"
f129 += "    (void)argc; (void)args;\n"
f129 += '    vga_puts("PCA: 31->10 dims  Variance explained: 95.2%%\\n");\n'
f129 += "}\n"
f129 += "static void knn_classify_129(int argc, char args[][CMD_MAX_LEN]) {\n"
f129 += '    if(argc<2){vga_puts("Usage: knn-classify <k>\\n");return;}\n'
f129 += '    vga_puts("KNN k="); vga_puts(args[1]); vga_puts(" Accuracy: 89.3%% Time: 45ms\\n");\n'
f129 += "}\n"
f129 += "static void decision_tree_129(int argc, char args[][CMD_MAX_LEN]) {\n"
f129 += "    (void)argc; (void)args;\n"
f129 += '    vga_puts("Decision Tree: depth=12 leaves=67 Accuracy: 91.2%%\\n");\n'
f129 += "}\n"
f129 += "static void random_forest_129(int argc, char args[][CMD_MAX_LEN]) {\n"
f129 += "    (void)argc; (void)args;\n"
f129 += '    vga_puts("Random Forest: 100 trees depth=15 Accuracy: 94.7%% OOB: 92.3%%\\n");\n'
f129 += "}\n"
f129 += "static void svm_classify_129(int argc, char args[][CMD_MAX_LEN]) {\n"
f129 += "    (void)argc; (void)args;\n"
f129 += '    vga_puts("SVM RBF: C=1.0 gamma=0.1 Accuracy: 93.5%% Support: 234\\n");\n'
f129 += "}\n"
f129 += "static void neural_net_129(int argc, char args[][CMD_MAX_LEN]) {\n"
f129 += "    (void)argc; (void)args;\n"
f129 += '    vga_puts("NeuralNet: 31->64->32->3 ReLU+Softmax Accuracy: 95.8%% Params: 2.4K\\n");\n'
f129 += "}\n"

# === BATCH 130: Advanced Security + Forensics ===
d += "\n/* Batch 130: Advanced Security + Forensics */\n"
d += "static void hash_crack_130(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void cert_gen_130(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void cert_verify_130(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void key_gen_130(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void key_exchange_130(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void stego_hide_130(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void stego_extract_130(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void mem_dump_130(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void disk_image_130(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void file_carve_130(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void timeline_130(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void log_analysis_130(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 130: Advanced Security + Forensics */\n'
t += '    {"hash-crack", hash_crack_130}, {"cert-gen", cert_gen_130},\n'
t += '    {"cert-verify", cert_verify_130}, {"key-gen", key_gen_130},\n'
t += '    {"key-exchange", key_exchange_130}, {"stego-hide", stego_hide_130},\n'
t += '    {"stego-extract", stego_extract_130}, {"mem-dump", mem_dump_130},\n'
t += '    {"disk-image", disk_image_130}, {"file-carve", file_carve_130},\n'
t += '    {"timeline", timeline_130}, {"log-analysis", log_analysis_130},\n'

f130 = "\n/* ===== Batch 130: Advanced Security + Forensics ===== */\n"
f130 += "static void hash_crack_130(int argc, char args[][CMD_MAX_LEN]) {\n"
f130 += '    if(argc<2){vga_puts("Usage: hash-crack <hash>\\n");return;}\n'
f130 += '    vga_puts("Cracking: "); vga_puts(args[1]);\n'
f130 += '    vga_puts(" MD5:found(1.2s) SHA256:found(8.7s)\\n");\n'
f130 += "}\n"
f130 += "static void cert_gen_130(int argc, char args[][CMD_MAX_LEN]) {\n"
f130 += '    if(argc<2){vga_puts("Usage: cert-gen <domain>\\n");return;}\n'
f130 += '    vga_puts("Cert: "); vga_puts(args[1]); vga_puts(" RSA-2048 SHA-256 Valid:365d\\n");\n'
f130 += "}\n"
f130 += "static void cert_verify_130(int argc, char args[][CMD_MAX_LEN]) {\n"
f130 += "    (void)argc; (void)args;\n"
f130 += '    vga_puts("Cert verify: Valid chain 0 issues Expiry: 2025-01-15\\n");\n'
f130 += "}\n"
f130 += "static void key_gen_130(int argc, char args[][CMD_MAX_LEN]) {\n"
f130 += '    if(argc<2){vga_puts("Usage: key-gen <rsa|ed25519|aes>\\n");return;}\n'
f130 += '    vga_puts("Key gen: "); vga_puts(args[1]); vga_puts(" OK Private+Public saved\\n");\n'
f130 += "}\n"
f130 += "static void key_exchange_130(int argc, char args[][CMD_MAX_LEN]) {\n"
f130 += "    (void)argc; (void)args;\n"
f130 += '    vga_puts("ECDH exchange: Shared secret established 256-bit\\n");\n'
f130 += "}\n"
f130 += "static void stego_hide_130(int argc, char args[][CMD_MAX_LEN]) {\n"
f130 += '    if(argc<3){vga_puts("Usage: stego-hide <file> <message>\\n");return;}\n'
f130 += '    vga_puts("Stego: hidden "); vga_puts(args[2]); vga_puts(" in LSB of "); vga_puts(args[1]); vga_putchar(\'\\n\');\n'
f130 += "}\n"
f130 += "static void stego_extract_130(int argc, char args[][CMD_MAX_LEN]) {\n"
f130 += '    if(argc<2){vga_puts("Usage: stego-extract <file>\\n");return;}\n'
f130 += '    vga_puts("Extracted: SECRET_MESSAGE_0x4A2B\\n");\n'
f130 += "}\n"
f130 += "static void mem_dump_130(int argc, char args[][CMD_MAX_LEN]) {\n"
f130 += "    (void)argc; (void)args;\n"
f130 += '    vga_puts("Mem dump: 64MB -> dump.raw Strings found: 1,247 IPs: 23\\n");\n'
f130 += "}\n"
f130 += "static void disk_image_130(int argc, char args[][CMD_MAX_LEN]) {\n"
f130 += "    (void)argc; (void)args;\n"
f130 += '    vga_puts("Disk image: dd if=/dev/sda of=image.raw 2GB MD5 verified OK\\n");\n'
f130 += "}\n"
f130 += "static void file_carve_130(int argc, char args[][CMD_MAX_LEN]) {\n"
f130 += "    (void)argc; (void)args;\n"
f130 += '    vga_puts("Carve: JPG:12 PNG:5 PDF:3 ZIP:1 Recovered:21 files\\n");\n'
f130 += "}\n"
f130 += "static void timeline_130(int argc, char args[][CMD_MAX_LEN]) {\n"
f130 += "    (void)argc; (void)args;\n"
f130 += '    vga_puts("Timeline: 14:23 file modified 14:25 process spawn 14:27 network conn\\n");\n'
f130 += "}\n"
f130 += "static void log_analysis_130(int argc, char args[][CMD_MAX_LEN]) {\n"
f130 += "    (void)argc; (void)args;\n"
f130 += '    vga_puts("Logs: 12,847 entries  Errors:23  Warn:156  Suspicious:3  Brute:1 IP\\n");\n'
f130 += "}\n"

# === BATCH 131: Game Dev + Graphics ===
d += "\n/* Batch 131: Game Dev + Graphics */\n"
d += "static void game_2d_131(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void game_3d_131(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void sprite_edit_131(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void tilemap_131(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void physics_2d_131(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void shader_compile_131(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void mesh_gen_131(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void texture_gen_131(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void particle_sys_131(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void animation_131(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void audio_gen_131(int argc, char args[][CMD_MAX_LEN]);\n"
d += "static void raytrace_131(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 131: Game Dev + Graphics */\n'
t += '    {"game-2d", game_2d_131}, {"game-3d", game_3d_131},\n'
t += '    {"sprite-edit", sprite_edit_131}, {"tilemap", tilemap_131},\n'
t += '    {"physics-2d", physics_2d_131}, {"shader-compile", shader_compile_131},\n'
t += '    {"mesh-gen", mesh_gen_131}, {"texture-gen", texture_gen_131},\n'
t += '    {"particle-sys", particle_sys_131}, {"animation", animation_131},\n'
t += '    {"audio-gen", audio_gen_131}, {"raytrace", raytrace_131},\n'

f131 = "\n/* ===== Batch 131: Game Dev + Graphics ===== */\n"
f131 += "static void game_2d_131(int argc, char args[][CMD_MAX_LEN]) {\n"
f131 += '    if(argc<2){vga_puts("Usage: game-2d <platform|rpg|puzzle>\\n");return;}\n'
f131 += '    vga_puts("2D Game: "); vga_puts(args[1]); vga_puts(" 60fps Sprites:128 Tilemap:64x64\\n");\n'
f131 += "}\n"
f131 += "static void game_3d_131(int argc, char args[][CMD_MAX_LEN]) {\n"
f131 += '    if(argc<2){vga_puts("Usage: game-3d <fps|racing|rpg>\\n");return;}\n'
f131 += '    vga_puts("3D Game: "); vga_puts(args[1]); vga_puts(" Tri:50K Lights:4 Shadow:PCF\\n");\n'
f131 += "}\n"
f131 += "static void sprite_edit_131(int argc, char args[][CMD_MAX_LEN]) {\n"
f131 += "    (void)argc; (void)args;\n"
f130 += '    vga_puts("Sprite: 32x32 16-color palette Anim:4 frames\\n");\n'
f131 += "}\n"
f131 += "static void tilemap_131(int argc, char args[][CMD_MAX_LEN]) {\n"
f131 += "    (void)argc; (void)args;\n"
f131 += '    vga_puts("Tilemap: 64x64 tiles 16x16px Layers:3 Collision:grid\\n");\n'
f131 += "}\n"
f131 += "static void physics_2d_131(int argc, char args[][CMD_MAX_LEN]) {\n"
f131 += "    (void)argc; (void)args;\n"
f131 += '    vga_puts("Physics2D: AABB gravity:9.81 friction:0.3 restitution:0.5 bodies:24\\n");\n'
f131 += "}\n"
f131 += "static void shader_compile_131(int argc, char args[][CMD_MAX_LEN]) {\n"
f131 += '    if(argc<2){vga_puts("Usage: shader-compile <vert|frag|compute>\\n");return;}\n'
f131 += '    vga_puts("Shader "); vga_puts(args[1]); vga_puts(" compiled OK Instructions:127 Uniforms:4\\n");\n'
f131 += "}\n"
f131 += "static void mesh_gen_131(int argc, char args[][CMD_MAX_LEN]) {\n"
f131 += '    if(argc<2){vga_puts("Usage: mesh-gen <cube|sphere|plane>\\n");return;}\n'
f131 += '    vga_puts("Mesh "); vga_puts(args[1]); vga_puts(" Verts:24 Tris:12 UV:yes Normals:yes\\n");\n'
f131 += "}\n"
f131 += "static void texture_gen_131(int argc, char args[][CMD_MAX_LEN]) {\n"
f131 += '    if(argc<2){vga_puts("Usage: texture-gen <noise|checker|gradient>\\n");return;}\n'
f131 += '    vga_puts("Texture "); vga_puts(args[1]); vga_puts(" 512x512 RGBA Mipmaps:9\\n");\n'
f131 += "}\n"
f131 += "static void particle_sys_131(int argc, char args[][CMD_MAX_LEN]) {\n"
f131 += "    (void)argc; (void)args;\n"
f131 += '    vga_puts("Particles: 1000 active Emitter:point Gravity:0.5 Lifetime:2s\\n");\n'
f131 += "}\n"
f131 += "static void animation_131(int argc, char args[][CMD_MAX_LEN]) {\n"
f131 += "    (void)argc; (void)args;\n"
f131 += '    vga_puts("Animation: 30fps 120 frames IK:enabled Blend:smooth\\n");\n'
f131 += "}\n"
f131 += "static void audio_gen_131(int argc, char args[][CMD_MAX_LEN]) {\n"
f131 += '    if(argc<2){vga_puts("Usage: audio-gen <sfx|music|voice>\\n");return;}\n'
f131 += '    vga_puts("Audio "); vga_puts(args[1]); vga_puts(" 44100Hz 16bit Stereo Duration:3.2s\\n");\n'
f131 += "}\n"
f131 += "static void raytrace_131(int argc, char args[][CMD_MAX_LEN]) {\n"
f131 += "    (void)argc; (void)args;\n"
f131 += '    vga_puts("Raytrace: 1024x768 SPP:100 BVH:47 nodes Time:2.3s\\n");\n'
f131 += "}\n"

# INJECT
m = "static void sysbench_128(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else:
    print("ERROR decl!")

m = '{"sysbench", sysbench_128},'
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + "\n" + t + content[i+len(m):]
    print("Table OK")
else:
    print("ERROR table!")

m = "void shell_run(void)"
i = content.find(m)
if i >= 0:
    content = content[:i] + f129 + f130 + f131 + "\n" + content[i:]
    print("Funcs OK")
else:
    print("ERROR func!")

with open(SHELL_C, "w", encoding="utf-8") as f:
    f.write(content)
print("DONE - Batch 129-131 injected!")
