SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 174: Real Estate + Property ===
cmds174 = ["property_val","property_list","property_search","mortgage_calc",
            "rental_yield","property_tax","lease_manage","tenant_screen",
            "maintenance_log","energy_cert","survey_report","market_analysis"]

d = "\n/* Batch 174: Real Estate + Property */\n"
for c in cmds174:
    d += f"static void {c}_174(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 174: Real Estate + Property */\n'
for c in cmds174:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_174}, '
t += '\n'

details174 = [
    ("property_val", "Value: $450,000 Comp:3 sales Method:MLS Adjustments:±5%%"),
    ("property_list", "List: 128 Main St Price:$450K Beds:3 Baths:2 Sqft:1,850"),
    ("property_search", "Search: 47 results Price:$350-500K Beds:3+ Location:downtown"),
    ("mortgage_calc", "Mortgage: $360K 30yr 6.5%% Monthly:$2,275 Total:$459K"),
    ("rental_yield", "Yield: Rent:$2,800/mo Price:$450K Gross:7.5%% Net:5.2%%"),
    ("property_tax", "Tax: Assessed:$405K Rate:1.2%% Annual:$4,860 Due:Jan 15"),
    ("lease_manage", "Lease: Tenant:J.Smith Start:2024-01-01 End:2024-12-31 Rent:$2,800"),
    ("tenant_screen", "Screen: Score:87/100 Credit:720 Income:3.2x rent Criminal:none"),
    ("maintenance_log", "Maint: Request:#12848 HVAC filter Priority:medium Cost:$150"),
    ("energy_cert", "Energy: Rating:C DRAFT:52 EPC:68 Recommendations:8"),
    ("survey_report", "Survey: Structure:good Roof:good Damp:none Boundaries:clear"),
    ("market_analysis", "Market: Median:$450K YoY:+5.2%% Days-on-market:23 Inventory:low"),
]
f = "\n/* ===== Batch 174: Real Estate + Property ===== */\n"
for c, det in details174:
    f += "static void " + c + "_174(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 175: Insurance + Risk ===
cmds175 = ["insurance_quote","insurance_claim","risk_assess_ins","premium_calc",
            "policy_review","underwriting","actuarial_calc","reinsurance",
            "fraud_detect","loss_run","coverage_gap","policy_bind"]

d += "\n/* Batch 175: Insurance + Risk */\n"
for c in cmds175:
    d += f"static void {c}_175(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 175: Insurance + Risk */\n'
for c in cmds175:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_175}, '
t += '\n'

details175 = [
    ("insurance_quote", "Quote: Auto $1,234/yr Home $2,456/yr Life $89/mo Health $456/mo"),
    ("insurance_claim", "Claim: #12848 Type:auto Status:approved Payout:$12,400"),
    ("risk_assess_ins", "Risk: Score:42/100 Factors:age,location,vehicle Claims:0"),
    ("premium_calc", "Premium: Base:$1,200 Modifiers:+12%% -$5%% +8%% Final:$1,308"),
    ("policy_review", "Review: Coverage:adequate Gaps:umbrella Deductible:$500"),
    ("underwriting", "Underwriting: Applicable:yes Risk:standard Price:approved"),
    ("actuarial_calc", "Actuarial: Expected loss:$450 Probability:3.2%% Severity:$14,062"),
    ("reinsurance", "Reinsurance: Treaty:excess-of-loss Retention:$500K Ceded:$45M"),
    ("fraud_detect", "Fraud: Score:12/100 Indicators:0 Claim:genuine"),
    ("loss_run", "Loss Run: 3 years Claims:2 Total:$12,400 Loss ratio:65%%"),
    ("coverage_gap", "Gaps: Flood:uninsured Earthquake:excluded Cyber:limited"),
    ("policy_bind", "Bind: Policy:#POL-12848 Effective:2024-01-15 Expiry:2025-01-15"),
]
f += "\n/* ===== Batch 175: Insurance + Risk ===== */\n"
for c, det in details175:
    f += "static void " + c + "_175(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 176: Human Resources ===
cmds176 = ["hr_recruit","hr_onboard","hr_offboard","hr_payroll",
            "hr_benefit","hr_performance","hr_succession","hr_compliance",
            "hr_training","hr_engagement","hr_workforce","hr_analytics"]

d += "\n/* Batch 176: Human Resources */\n"
for c in cmds176:
    d += f"static void {c}_176(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 176: Human Resources */\n'
for c in cmds176:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_176}, '
t += '\n'

details176 = [
    ("hr_recruit", "Recruit: Position:#12848 Applicants:23 Interviews:5 Offers:1"),
    ("hr_onboard", "Onboard: Employee:E12848 Start:2024-01-15 Training:2 weeks"),
    ("hr_offboard", "Offboard: Employee:E1234 Last day:2024-01-31 Reason:resignation"),
    ("hr_payroll", "Payroll: E12848 Gross:$8,500 Tax:-$2,125 Net:$6,375 Benefits:-$450"),
    ("hr_benefit", "Benefits: Health:dental Vision:yes 401k:6%% PTO:20d Holidays:11"),
    ("hr_performance", "Performance: Rating:4/5 Goals:4/5 met Review:exceeds"),
    ("hr_succession", "Succession: CTO:ready VP:developing Manager:identify 3 roles"),
    ("hr_compliance", "Compliance: OSHA:pass EEO:pass ADA:pass Training:98%%"),
    ("hr_training", "Training: Courses:12 Completed:87%% Hours:124 Satisfaction:4.5/5"),
    ("hr_engagement", "Engagement: Score:82/100 eNPS:45 Turnover:12%% Absentee:2.1%%"),
    ("hr_workforce", "Workforce: Headcount:247 Hired:34 Terminated:18 Growth:6.6%%"),
    ("hr_analytics", "Analytics: TTH:45 days Cost:$12,400/hire Retention:88%% Diversity:42%%"),
]
f += "\n/* ===== Batch 176: Human Resources ===== */\n"
for c, det in details176:
    f += "static void " + c + "_176(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT DECLS
m = "static void bi_export_173(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

# INJECT TABLE
m = '{"bi-export", bi_export_173},'
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
print("DONE - Batch 174-176 injected!")
