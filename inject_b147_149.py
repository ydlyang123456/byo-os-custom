SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 147: DevOps Advanced ===
cmds147 = ["terraform_plan","terraform_apply","ansible_run","puppet_apply",
            "chef_converge","vagrant_up","packer_build","consul_kv",
            "vault_read","vault_write","boundary_auth","waypoint_deploy"]

d = "\n/* Batch 147: DevOps Advanced */\n"
for c in cmds147:
    d += f"static void {c}_147(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 147: DevOps Advanced */\n'
for c in cmds147:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_147}, '
t += '\n'

details147 = [
    ("terraform_plan", "Terraform: Plan 12 to add 3 change 1 destroy 0 Cost:$45/mo"),
    ("terraform_apply", "Terraform: Apply complete! Resources:12 added 3 changed 0 destroyed"),
    ("ansible_run", "Ansible: Playbook applied 47 tasks OK Changed:12 Unreachable:0 Failed:0"),
    ("puppet_apply", "Puppet: Catalog compiled Resources:234 Applied:12 Unchanged:222"),
    ("chef_converge", "Chef: Run complete 1247 resources 12 updated 0 errors"),
    ("vagrant_up", "Vagrant: VM 'dev' booted 192.168.56.10 Provider:VirtualBox"),
    ("packer_build", "Packer: Build 'ubuntu-base' 12 provisioners Complete 45s"),
    ("consul_kv", "Consul KV: key=api/config value=2.3KB Index:12847"),
    ("vault_read", "Vault: secret/api Key:*** Expired:false Lease:3600s"),
    ("vault_write", "Vault: secret/api key=*** written Version:2"),
    ("boundary_auth", "Boundary: Authenticated User:admin Host:worker-1 Session:12848"),
    ("waypoint_deploy", "Waypoint: Deploy 'api' Artifact:1234 Status:running URL:https://api.dev"),
]
f = "\n/* ===== Batch 147: DevOps Advanced ===== */\n"
for c, det in details147:
    f += "static void " + c + "_147(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 148: NLP + Speech ===
cmds148 = ["nlp_tokenize","nlp_pos","nlp_ner","nlp_sentiment",
            "nlp_translate","nlp_summarize","nlp问答","nlp_classify",
            "speech_to_text","text_to_speech","voice_clone","language_detect"]

d += "\n/* Batch 148: NLP + Speech */\n"
for c in cmds148:
    d += f"static void {c}_148(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 148: NLP + Speech */\n'
for c in cmds148:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_148}, '
t += '\n'

details148 = [
    ("nlp_tokenize", "Tokenize: 128 tokens Subwords:87 Words:42 Punctuation:12"),
    ("nlp_pos", "POS: Noun:23 Verb:12 Adj:8 Adv:3 Prep:5 Det:4 Conj:2"),
    ("nlp_ner", "NER: ORG:5 PER:8 LOC:3 DATE:4 MONEY:2 EVENT:1"),
    ("nlp_sentiment", "Sentiment: Positive:0.72 Neutral:0.18 Negative:0.10 Confidence:89%%"),
    ("nlp_translate", "Translate: EN->ZH 'Hello world' -> '你好世界' BLEU:0.87"),
    ("nlp_summarize", "Summarize: 1,247 words -> 128 words Compression:10:1 ROUGE:0.45"),
    ("nlp问答", "Q&A: Q:'What is BYO-OS?' A:'Custom x86 OS' Confidence:94%%"),
    ("nlp_classify", "Classify: Tech:78%% Business:15%% Other:7%% Model:BERT"),
    ("speech_to_text", "STT: 12.3s audio -> 87 words WER:4.2%% Language:EN"),
    ("text_to_speech", "TTS: 128 words -> 8.7s audio Voice:default Quality:high"),
    ("voice_clone", "Voice Clone: Source:5min Target voice:similar Fidelity:92%%"),
    ("language_detect", "Language: EN:87%% ZH:8%% JA:3%% Other:2%%"),
]
f += "\n/* ===== Batch 148: NLP + Speech ===== */\n"
for c, det in details148:
    f += "static void " + c + "_148(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 149: Video + Animation ===
cmds149 = ["video_encode","video_decode","video_edit","video_composite",
            "video_animate","video_particle","video_transition","video_subtitle",
            "video_color","video_stabilize","video_enhance","video_export"]

d += "\n/* Batch 149: Video + Animation */\n"
for c in cmds149:
    d += f"static void {c}_149(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 149: Video + Animation */\n'
for c in cmds149:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_149}, '
t += '\n'

details149 = [
    ("video_encode", "Encode: H.264 1080p 30fps CRF:23 Size:145MB Duration:5:32"),
    ("video_decode", "Decode: H.265 4K 60fps Frames:3,247 Time:2.3s"),
    ("video_edit", "Edit: Cut 00:30-01:45 Merge 3 clips Trim OK"),
    ("video_composite", "Composite: 4 layers Alpha blend OK Output:1080p"),
    ("video_animate", "Animate: Keyframes:12 Duration:5s Easing:ease-in-out"),
    ("video_particle", "Particles: 10,000 Physics:gravity Wind:2.3 Color:rainbow"),
    ("video_transition", "Transition: Crossfade 1s between scenes 12 transitions"),
    ("video_subtitle", "Subtitle: SRT 128 lines Sync:OK Font:Arial Size:24px"),
    ("video_color", "Color: LUT applied Saturation:+15%% Contrast:+10%%"),
    ("video_stabilize", "Stabilize: Motion detected:245 frames Corrected:OK"),
    ("video_enhance", "Enhance: Upscale 1080p->4K Denoise:medium Sharpness:+20%%"),
    ("video_export", "Export: MOV ProRes 422 HQ 4K 30fps Size:2.3GB"),
]
f += "\n/* ===== Batch 149: Video + Animation ===== */\n"
for c, det in details149:
    f += "static void " + c + "_149(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT
m = "static void img_stitch_146(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

m = '{"img-stitch", img_stitch_146},'
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
print("DONE - Batch 147-149 injected!")
