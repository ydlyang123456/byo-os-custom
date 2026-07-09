SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# === BATCH 138: Education + Learning ===
cmds138 = ["learn_math","learn_physics","learn_chemistry","learn_biology",
            "learn_economics","learn_psychology","learn_philosophy","learn_art",
            "learn_history","learn_geography","learn_literature","learn_music_theory"]

d = "\n/* Batch 138: Education + Learning */\n"
for c in cmds138:
    d += f"static void {c}_138(int argc, char args[][CMD_MAX_LEN]);\n"

t = '    /* Batch 138: Education + Learning */\n'
for c in cmds138:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_138}, '
t += '\n'

details138 = [
    ("learn_math", "Math: Calculus Limits 2/4 Derivatives 1/4 Integrals 0/4 Progress:12.5%%"),
    ("learn_physics", "Physics: Mechanics 3/5 Electromagnetism 1/5 Optics 0/5 Progress:26.7%%"),
    ("learn_chemistry", "Chemistry: Organic 2/4 Inorganic 1/4 Physical 0/4 Progress:16.7%%"),
    ("learn_biology", "Biology: Cell Bio 4/4 Genetics 3/4 Ecology 2/4 Progress:66.7%%"),
    ("learn_economics", "Economics: Micro 2/3 Macro 1/3 Econometrics 0/3 Progress:33.3%%"),
    ("learn_psychology", "Psychology: Cognitive 3/4 Social 2/4 Development 1/4 Progress:41.7%%"),
    ("learn_philosophy", "Philosophy: Ethics 2/3 Logic 3/3 Metaphysics 1/3 Progress:55.6%%"),
    ("learn_art", "Art: Drawing 2/4 Painting 1/4 Sculpture 0/4 Progress:16.7%%"),
    ("learn_history", "History: Ancient 4/4 Medieval 3/4 Modern 2/4 Progress:66.7%%"),
    ("learn_geography", "Geography: Physical 2/3 Human 1/3 GIS 0/3 Progress:33.3%%"),
    ("learn_literature", "Literature: Classic 3/4 Modern 2/4 Poetry 1/4 Progress:41.7%%"),
    ("learn_music_theory", "Music Theory: Scales 3/3 Chords 2/3 Harmony 1/3 Progress:55.6%%"),
]
f = "\n/* ===== Batch 138: Education + Learning ===== */\n"
for c, det in details138:
    f += "static void " + c + "_138(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 139: Weather + Environment ===
cmds139 = ["weather_now","weather_forecast","weather_alert","air_quality",
            "uv_index","solar_irradiance","wind_forecast","rain_prediction",
            "humidity_level","barometric_pressure","fog_detection","storm_track"]

d += "\n/* Batch 139: Weather + Environment */\n"
for c in cmds139:
    d += f"static void {c}_139(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 139: Weather + Environment */\n'
for c in cmds139:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_139}, '
t += '\n'

details139 = [
    ("weather_now", "Now: 24C Partly Cloudy Humidity:65%% Wind:12km/h NE"),
    ("weather_forecast", "Forecast: Mon:26C Sun Tue:22C Rain Wed:20C Cloudy"),
    ("weather_alert", "Alert: HEAT WAVE WARNING 35C+ until Thursday 6PM"),
    ("air_quality", "AQI: 42 (Good) PM2.5:12ug O3:35ppb NO2:18ppb"),
    ("uv_index", "UV: 7 (High) Peak:12:30-14:30 Protection: SPF30+ needed"),
    ("solar_irradiance", "Solar: 850W/m2 Clear sky Efficiency:22%% Output:1.2kW"),
    ("wind_forecast", "Wind: Now:12km/hNE Gusts:25km/h Forecast:15km/hNW"),
    ("rain_prediction", "Rain: Probability:75%% Start:14:00 Duration:3h Amount:12mm"),
    ("humidity_level", "Humidity: Indoor:45%% Outdoor:65%% Dew point:17C"),
    ("barometric_pressure", "Pressure: 1013.25hPa Steady Trend:rising slightly"),
    ("fog_detection", "Fog: Visibility:200m Type:Radiation Duration:until 9AM"),
    ("storm_track", "Storm: TD-15 Category:TS Speed:25km/h NW Path:36h"),
]
f += "\n/* ===== Batch 139: Weather + Environment ===== */\n"
for c, det in details139:
    f += "static void " + c + "_139(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# === BATCH 140: Social + Communication ===
cmds140 = ["email_send","email_recv","sms_send","calendar_event",
            "contact_add","social_post","social_feed","chat_group",
            "notification_push","status_update","file_share","meeting_schedule"]

d += "\n/* Batch 140: Social + Communication */\n"
for c in cmds140:
    d += f"static void {c}_140(int argc, char args[][CMD_MAX_LEN]);\n"

t += '    /* Batch 140: Social + Communication */\n'
for c in cmds140:
    t += '    {"' + c.replace("_","-") + '", ' + c + '_140}, '
t += '\n'

details140 = [
    ("email_send", "Email: To:user@host Subject:Report Sent OK Message-ID:abc123"),
    ("email_recv", "Inbox: 12 unread 3 flagged Latest:Meeting notes 10:23"),
    ("sms_send", "SMS: To:+1234567890 Sent Delivered 14:23 Cost:$0.01"),
    ("calendar_event", "Event: Team Standup Recurring:Daily Time:09:00 Duration:15min"),
    ("contact_add", "Contact: John Doe Added Email:john@co Phone:+1234567890"),
    ("social_post", "Posted: Hello world! Likes:0 Comments:0 Time:14:23"),
    ("social_feed", "Feed: 47 new posts 12 photos 3 videos Trending:#tech"),
    ("chat_group", "Group: Dev Team Members:12 Messages today:89"),
    ("notification_push", "Push: 5 unread 2 urgent Latest:Deployment complete"),
    ("status_update", "Status: Online Status text:Working on BYO-OS"),
    ("file_share", "Shared: report.pdf Size:2.3MB Recipients:3 Expiry:7d"),
    ("meeting_schedule", "Meeting: Sprint Review Tomorrow 14:00 Duration:1h Attendees:8"),
]
f += "\n/* ===== Batch 140: Social + Communication ===== */\n"
for c, det in details140:
    f += "static void " + c + "_140(int argc, char args[][CMD_MAX_LEN]) {\n"
    f += "    (void)argc; (void)args;\n"
    f += '    vga_puts("' + det + '\\n");\n'
    f += "}\n"

# INJECT
m = "static void audio_fft_137(int argc, char args[][CMD_MAX_LEN]);"
i = content.find(m)
if i >= 0:
    content = content[:i+len(m)] + d + content[i+len(m):]
    print("Decls OK")
else: print("ERROR decl!")

m = '{"audio-fft", audio_fft_137},'
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
print("DONE - Batch 138-140 injected!")
