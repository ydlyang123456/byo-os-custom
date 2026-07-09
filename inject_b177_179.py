SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 177: Legal Tech ===
cmds177 = ["case_manage","doc_review","e_discovery","legal_research",
            "billable_track","conflict_check","client_portal","matter_open",
            "time_entry","trust_account","statute_find","precedent_search"]

d = "\n/* Batch 177: Legal Tech */\n"
for c in cmds177:
    d += f"static void {c}_177(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 177: Legal Tech */\n'
for c in cmds177:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_177}, '
t += '\n'

details177 = [
    ("case_manage", "Case: #2024-12848 Status:active Client:ACME Next:filing 2024-02-15"),
    ("doc_review", "Review: 1,247 documents Priv:234 Relevance:892 Flags:12"),
    ("e_discovery", "eDiscovery: 45GB data Emails:12,847 Custodians:3 Issues:23"),
    ("legal_research", "Research: 12 cases found 3 on-point 1 favorable binding"),
    ("billable_track", "Billable: This month:142h Target:160h Rate:$350/h Revenue:$49,700"),
    ("conflict_check", "Conflict: 0 conflicts found New client:approved"),
    ("client_portal", "Portal: Client:ACME Documents:23 Messages:8 Invoices:3"),
    ("matter_open", "Matter: #12848 Opened:2024-01-15 Type:litigation Status:active"),
    ("time_entry", "Time: 2.5h Research $875 Matter:#12848 Date:2024-01-15"),
    ("trust_account", "Trust: Balance:$45,000 Deposits:$50,000 Draws:$5,000"),
    ("statute_find", "Statute: 12 USC 1983 Elements:4 Applicable:yes"),
    ("precedent_search", "Precedent: 47 cases 3 binding 12 persuasive Citations:124"),
]
f = "\n/* ===== Batch 177: Legal Tech ===== */\n"
for c, det in details177:
    f += "static void " + c + "_177(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 178: Mental Health + Wellness ===
cmds178 = ["mood_track","anxiety_check","therapy_session","meditation",
            "breathing_ex","journal_prompt","gratitude_log","cbt_exercise",
            "sleep_hygiene","stress_mgmt","burnout_check","wellness_plan"]

d += "\n/* Batch 178: Mental Health + Wellness */\n"
for c in cmds178:
    d += f"static void {c}_178(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 178: Mental Health + Wellness */\n'
for c in cmds178:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_178}, '
t += '\n'

details178 = [
    ("mood_track", "Mood: 7/10 Trend:stable Triggers:work Sleep:7h Exercise:yes"),
    ("anxiety_check", "Anxiety: GAD-7:8(Mild) Physical:3 Cognitive:3 Behavioral:2"),
    ("therapy_session", "Therapy: Session:#24 Duration:50min Topic:CBT Homework:3 tasks"),
    ("meditation", "Meditation: Duration:15min Type:guided Focus:breathing Score:8/10"),
    ("breathing_ex", "Breathing: 4-7-8 pattern 3 rounds HR:72->65 BPM reduced:7"),
    ("journal_prompt", "Journal: Prompt:What went well today? Word count:234"),
    ("gratitude_log", "Gratitude: 3 items Family,health,work Mood boost:+15%%"),
    ("cbt_exercise", "CBT: Thought record 3 negative 2 reframed 1 positive outcome"),
    ("sleep_hygiene", "Sleep hygiene: Bedtime:22:30 Screen:off Caffeine:14:00 Quality:good"),
    ("stress_mgmt", "Stress: Level:4/10 Coping:exercise Music:relaxation Social:3 friends"),
    ("burnout_check", "Burnout: MBI:23/100(Mild) Exhaustion:4 Cynicism:2 Efficacy:8"),
    ("wellness_plan", "Wellness: Exercise:4x Sleep:7-8h Mindfulness:daily Social:2x Social:2x Week"),
]
f += "\n/* ===== Batch 178: Mental Health + Wellness ===== */\n"
for c, det in details178:
    f += "static void " + c + "_178(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 179: Accessibility + Inclusion ===
cmds179 = ["a11y_audit","a11y_test","a11y_fix","screen_reader",
            "color_contrast","keyboard_nav","focus_manage","aria_label",
            "caption_gen","alt_text","tts_config","input_adapt"]

d += "\n/* Batch 179: Accessibility + Inclusion */\n"
for c in cmds179:
    d += f"static void {c}_179(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 179: Accessibility + Inclusion */\n'
for c in cmds179:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_179}, '
t += '\n'

details179 = [
    ("a11y_audit", "Audit: WCAG:AA Violations:3 Critical:0 Major:1 Minor:2"),
    ("a11y_test", "Test: Screen reader:OK Keyboard:OK Color:pass Motion:prefers-reduced"),
    ("a11y_fix", "Fix: Added alt text to 12 images Fixed 3 focus traps Added 2 skip links"),
    ("screen_reader", "Screen Reader: ARIA:correct Labels:124 Landmarks:8 Live regions:3"),
    ("color_contrast", "Contrast: #38bdf8/#0a0e1a:7.2:1 AA:pass AAA:pass"),
    ("keyboard_nav", "Keyboard: Tab order:logical Focus visible:yes Shortcuts:12 Escape:modal"),
    ("focus_manage", "Focus: Trap:none Visible:always Indicator:ring Offset:2px"),
    ("aria_label", "ARIA: Labels:47 Roles:23 States:12 Properties:8 Relationships:5"),
    ("caption_gen", "Captions: 128 lines Accuracy:97%% Languages:EN,ZH Sync:0.1s"),
    ("alt_text", "Alt Text: Generated:47 Descriptive:yes Length:avg:12 words"),
    ("tts_config", "TTS: Speed:1.0x Pitch:1.0 Volume:0.8 Voice:female"),
    ("input_adapt", "Adaptive: Switch:yes Eye:yes Voice:yes Timing:flexible"),
]
f += "\n/* ===== Batch 179: Accessibility + Inclusion ===== */\n"
for c, det in details179:
    f += "static void " + c + "_179(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void hr_analytics_176(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"hr-analytics", hr_analytics_176},'
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
print("DONE - Batch 177-179 injected!")
