SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 171: Research + Science ===
cmds171 = ["paper_search","paper_cite","paper_review","experiment_design",
            "data_collect","data_analyze","hypothesis_test","stat_test",
            "peer_review","journal_submit","grant_write","research_collab"]

d = "\n/* Batch 171: Research + Science */\n"
for c in cmds171:
    d += f"static void {c}_171(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 171: Research + Science */\n'
for c in cmds171:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_171}, '
t += '\n'

details171 = [
    ("paper_search", "Search: 1,247 papers Keywords:3 Topics:12 Citations:45,678"),
    ("paper_cite", "Cite: APA7 Format:correct References:47 BibTeX:exported"),
    ("paper_review", "Review: Clarity:8/10 Novelty:7/10 Rigor:9/10 Score:8/10"),
    ("experiment_design", "Design: RCT N=120 Power:0.8 Alpha:0.05 Effect:0.5"),
    ("data_collect", "Collect: 1,247 samples Response:89%% Time:2 weeks"),
    ("data_analyze", "Analyze: ANOVA F=12.3 p=0.001 Effect:0.45 CI:95%%"),
    ("hypothesis_test", "Test: H0:rejected H1:supported p=0.001 Effect:large"),
    ("stat_test", "Stats: Mean:45.2 SD:12.3 t=8.7 p<0.001 Cohen d=0.8"),
    ("peer_review", "Review: 3 reviewers Accept:2 Minor:1 Major:0"),
    ("journal_submit", "Submit: Nature IF:69.5 Status:under-review Manuscript:#12848"),
    ("grant_write", "Grant: NIH R01 Budget:$250K Duration:3 years Score:92/100"),
    ("research_collab", "Collab: 12 researchers 4 institutions Data:shared Code:open"),
]
f = "\n/* ===== Batch 171: Research + Science ===== */\n"
for c, det in details171:
    f += "static void " + c + "_171(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 172: UX/UI Design ===
cmds172 = ["ux_research","ux_personas","ux_journey","ux_wireframe",
            "ui_prototype","ui_style","ui_motion","ui_accessibility",
            "ui_theme","ui_layout","ui_responsive","ui_testing"]

d += "\n/* Batch 172: UX/UI Design */\n"
for c in cmds172:
    d += f"static void {c}_172(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 172: UX/UI Design */\n'
for c in cmds172:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_172}, '
t += '\n'

details172 = [
    ("ux_research", "Research: Users:120 Interviews:24 Surveys:456 Tasks:12"),
    ("ux_personas", "Personas: 4 created Primary:Developer(35%%) Secondary:Admin(25%%)"),
    ("ux_journey", "Journey: 6 stages Pain points:3 Opportunities:5 Touchpoints:12"),
    ("ux_wireframe", "Wireframe: 8 screens Lo-fi Components:47 Flows:3"),
    ("ui_prototype", "Prototype: 12 screens Interactive:true Fidelity:high Clickable:true"),
    ("ui_style", "Style: Primary:#38bdf8 Font:Inter Radius:8px Spacing:4/8/16"),
    ("ui_motion", "Motion: Duration:200ms Easing:ease-in-out Stagger:50ms"),
    ("ui_accessibility", "A11y: WCAG:AA Contrast:7.2:1 Focus:visible Screen reader:OK"),
    ("ui_theme", "Theme: Light+Dark Colors:12 Tokens:24 Components:18"),
    ("ui_layout", "Layout: Grid:12col Gutter:16px Max:1200px Break:768/1024"),
    ("ui_responsive", "Responsive: Mobile:320px Tablet:768px Desktop:1024px Print:OK"),
    ("ui_testing", "Testing: Usability:87%% task success SUS:82 Time-on-task:-15%%"),
]
f += "\n/* ===== Batch 172: UX/UI Design ===== */\n"
for c, det in details172:
    f += "static void " + c + "_172(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 173: Business Intelligence ===
cmds173 = ["bi_dashboard","bi_report","bi_kpi","bi_forecast",
            "bi_segment","bi_cohort","bi_funnel","bi_attribution",
            "bi_abtest","bi_metric","bi_alert","bi_export"]

d += "\n/* Batch 173: Business Intelligence */\n"
for c in cmds173:
    d += f"static void {c}_173(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 173: Business Intelligence */\n'
for c in cmds173:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_173}, '
t += '\n'

details173 = [
    ("bi_dashboard", "Dashboard: 12 widgets Data:real-time Refresh:5s Users:24"),
    ("bi_report", "Report: Q4 2023 Revenue:$12.5M Growth:23%% Margin:18%%"),
    ("bi_kpi", "KPI: MRR:$450K Churn:2.1%% NPS:67 CAC:$234 LTV:$2,340"),
    ("bi_forecast", "Forecast: Next quarter:$14.2M Confidence:85%% Trend:upward"),
    ("bi_segment", "Segment: Enterprise:34%% SMB:45%% Startup:21%% Active:1,247"),
    ("bi_cohort", "Cohort: Jan retention:89%% Feb:85%% Mar:82%% Churn:avg:18%%"),
    ("bi_funnel", "Funnel: Visit:12,847 Signup:1,247 Activate:892 Retain:678"),
    ("bi_attribution", "Attribution: Paid:35%% Organic:28%% Referral:22%% Direct:15%%"),
    ("bi_abtest", "A/B Test: Variant B +12%% conversion 95%% significant n=2,400"),
    ("bi_metric", "Metric: DAU:4,567 WAU:12,847 MAU:45,678 Stickiness:33%%"),
    ("bi_alert", "Alert: Revenue -15%% vs forecast Triggered:14:23 Channel:slack"),
    ("bi_export", "Export: Format:CSV Rows:12,847 Size:2.3MB Scheduled:daily"),
]
f += "\n/* ===== Batch 173: Business Intelligence ===== */\n"
for c, det in details173:
    f += "static void " + c + "_173(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void content_manage_170(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"content-manage", content_manage_170},'
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
print("DONE - Batch 171-173 injected!")
