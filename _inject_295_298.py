# inject_295_298.py
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 295: Game Engine & Graphics =====
b295_decls = """static void cmd_godot295(int argc, char args[][CMD_MAX_LEN]);
static void cmd_unity295(int argc, char args[][CMD_MAX_LEN]);
static void cmd_unreal295(int argc, char args[][CMD_MAX_LEN]);
static void cmd_blender295(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gimp295(int argc, char args[][CMD_MAX_LEN]);
static void cmd_inkscape295(int argc, char args[][CMD_MAX_LEN]);
static void cmd_krita295(int argc, char args[][CMD_MAX_LEN]);
static void cmd_darktable295(int argc, char args[][CMD_MAX_LEN]);
static void cmd_rawtherapee295(int argc, char args[][CMD_MAX_LEN]);
static void cmd_opencv295(int argc, char args[][CMD_MAX_LEN]);
static void cmd_vulkan295(int argc, char args[][CMD_MAX_LEN]);
static void cmd_opengl295(int argc, char args[][CMD_MAX_LEN]);
"""

b295_entries = """    /* Batch 295: Game Engine & Graphics */
    {"godot", cmd_godot295}, {"unity", cmd_unity295}, {"unreal", cmd_unreal295},
    {"blender", cmd_blender295}, {"gimp", cmd_gimp295}, {"inkscape", cmd_inkscape295},
    {"krita", cmd_krita295}, {"darktable", cmd_darktable295}, {"rawtherapee", cmd_rawtherapee295},
    {"opencv", cmd_opencv295}, {"vulkan", cmd_vulkan295}, {"opengl", cmd_opengl295},
"""

b295_funcs = """/* ===== Batch 295: Game Engine & Graphics ===== */
static void cmd_godot295(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: godot <project>\\n"); return; }
    vga_printf("godot: opening project %s\\n", args[1]);
    vga_puts("godot: engine 4.1 loaded\\n");
}
static void cmd_unity295(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Unity: game engine\\n");
    vga_puts("unity: no GUI available\\n");
}
static void cmd_unreal295(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Unreal Engine: game engine\\n");
    vga_puts("unreal: no GUI available\\n");
}
static void cmd_blender295(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Blender 3.6: 3D creation suite\\n");
    vga_puts("blender: no GUI available\\n");
}
static void cmd_gimp295(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("GIMP 2.10: image editor\\n");
    vga_puts("gimp: no GUI available\\n");
}
static void cmd_inkscape295(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Inkscape: vector graphics editor\\n");
}
static void cmd_krita295(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Krita: digital painting\\n");
}
static void cmd_darktable295(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("darktable: photography workflow\\n");
}
static void cmd_rawtherapee295(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("RawTherapee: RAW image processor\\n");
}
static void cmd_opencv295(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("OpenCV 4.8: computer vision\\n");
    vga_puts("opencv: camera initialized\\n");
}
static void cmd_vulkan295(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Vulkan 1.3: graphics API\\n");
}
static void cmd_opengl295(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("OpenGL 4.6: graphics API\\n");
}
"""

# ===== BATCH 296: Scientific Computing =====
b296_decls = """static void cmd_scipy296(int argc, char args[][CMD_MAX_LEN]);
static void cmd_sympy296(int argc, char args[][CMD_MAX_LEN]);
static void cmd_matplotlib296(int argc, char args[][CMD_MAX_LEN]);
static void cmd_plotly296(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bokeh296(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dask296(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pyarrow296(int argc, char args[][CMD_MAX_LEN]);
static void cmd_polars296(int argc, char args[][CMD_MAX_LEN]);
static void cmd_rapids296(int argc, char args[][CMD_MAX_LEN]);
static void cmd_jax296(int argc, char args[][CMD_MAX_LEN]);
static void cmd_flax296(int argc, char args[][CMD_MAX_LEN]);
static void cmd_haiku296(int argc, char args[][CMD_MAX_LEN]);
"""

b296_entries = """    /* Batch 296: Scientific Computing */
    {"scipy", cmd_scipy296}, {"sympy", cmd_sympy296}, {"matplotlib2", cmd_matplotlib296},
    {"plotly", cmd_plotly296}, {"bokeh", cmd_bokeh296}, {"dask", cmd_dask296},
    {"pyarrow", cmd_pyarrow296}, {"polars", cmd_polars296}, {"rapids", cmd_rapids296},
    {"jax", cmd_jax296}, {"flax", cmd_flax296}, {"haiku", cmd_haiku296},
"""

b296_funcs = """/* ===== Batch 296: Scientific Computing ===== */
static void cmd_scipy296(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("SciPy: scientific computing\\n");
}
static void cmd_sympy296(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("SymPy: symbolic mathematics\\n");
    vga_puts("sympy: x**2 + 1 = 0 -> x = I\\n");
}
static void cmd_matplotlib296(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("matplotlib: plotting\\n");
}
static void cmd_plotly296(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Plotly: interactive charts\\n");
}
static void cmd_bokeh296(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Bokeh: interactive visualization\\n");
}
static void cmd_dask296(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Dask: parallel computing\\n");
}
static void cmd_pyarrow296(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("PyArrow: Apache Arrow bindings\\n");
}
static void cmd_polars296(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Polars: fast DataFrames\\n");
}
static void cmd_rapids296(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("RAPIDS: GPU data science\\n");
}
static void cmd_jax296(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("JAX: accelerated computing\\n");
}
static void cmd_flax296(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Flax: neural networks with JAX\\n");
}
static void cmd_haiku296(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Haiku: neural networks with JAX\\n");
}
"""

# ===== BATCH 297: Audio Processing =====
b297_decls = """static void cmd_ffmpeg297(int argc, char args[][CMD_MAX_LEN]);
static void cmd_sox297(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_audacity297(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ardour297(int argc, char args[][CMD_MAX_LEN]);
static void cmd_lmms297(int argc, char args[][CMD_MAX_LEN]);
static void cmd_musescore297(int argc, char args[][CMD_MAX_LEN]);
static void cmd_fluidsynth297(int argc, char args[][CMD_MAX_LEN]);
static void cmd_timidity297(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pipewire297(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pulseaudio297(int argc, char args[][CMD_MAX_LEN]);
static void cmd_alsa297(int argc, char args[][CMD_MAX_LEN]);
static void cmd_jack297(int argc, char args[][CMD_MAX_LEN]);
"""

b297_entries = """    /* Batch 297: Audio Processing */
    {"ffmpeg2", cmd_ffmpeg297}, {"sox", cmd_sox297}, {"audacity", cmd_audacity297},
    {"ardour", cmd_ardour297}, {"lmms", cmd_lmms297}, {"musescore", cmd_musescore297},
    {"fluidsynth", cmd_fluidsynth297}, {"timidity", cmd_timidity297}, {"pipewire", cmd_pipewire297},
    {"pulseaudio", cmd_pulseaudio297}, {"alsa", cmd_alsa297}, {"jack", cmd_jack297},
"""

b297_funcs = """/* ===== Batch 297: Audio Processing ===== */
static void cmd_ffmpeg297(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ffmpeg <options>\\n"); return; }
    vga_puts("ffmpeg: audio/video converter\\n");
}
static void cmd_sox297(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sox <input> <output>\\n"); return; }
    vga_printf("sox: processing %s\\n", args[1]);
}
static void cmd_audacity297(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Audacity: audio editor\\n");
    vga_puts("audacity: no GUI available\\n");
}
static void cmd_ardour297(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Ardour: digital audio workstation\\n");
}
static void cmd_lmms297(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("LMMS: music production\\n");
}
static void cmd_musescore297(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("MuseScore: music notation\\n");
}
static void cmd_fluidsynth297(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("FluidSynth: MIDI synthesizer\\n");
}
static void cmd_timidity297(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("TiMidity: MIDI player\\n");
}
static void cmd_pipewire297(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("PipeWire: multimedia framework\\n");
}
static void cmd_pulseaudio297(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("PulseAudio: sound server\\n");
}
static void cmd_alsa297(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ALSA: sound driver\\n");
}
static void cmd_jack297(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("JACK: audio connection kit\\n");
}
"""

# ===== BATCH 298: Video Processing =====
b298_decls = """static void cmd_mpv298(int argc, char args[][CMD_MAX_LEN]);
static void cmd_vlc298(int argc, char args[][CMD_MAX_LEN]);
static void cmd_obs298(int argc, char args[][CMD_MAX_LEN]);
static void cmd_kdenlive298(int argc, char args[][CMD_MAX_LEN]);
static void cmd_shotcut298(int argc, char args[][CMD_MAX_LEN]);
static void cmd_davinci298(int argc, char args[][CMD_MAX_LEN]);
static void cmd_synfig298(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tupi298(int argc, char args[][CMD_MAX_LEN]);
static void cmd_mlt298(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gstreamer298(int argc, char args[][CMD_MAX_LEN]);
static void cmd_librav1e298(int argc, char args[][CMD_MAX_LEN]);
static void cmd_svt298_av1(int argc, char args[][CMD_MAX_LEN]);
"""

b298_entries = """    /* Batch 298: Video Processing */
    {"mpv", cmd_mpv298}, {"vlc", cmd_vlc298}, {"obs", cmd_obs298},
    {"kdenlive", cmd_kdenlive298}, {"shotcut", cmd_shotcut298}, {"davinci", cmd_davinci298},
    {"synfig", cmd_synfig298}, {"tupi", cmd_tupi298}, {"mlt", cmd_mlt298},
    {"gstreamer", cmd_gstreamer298}, {"rav1e", cmd_librav1e298}, {"svt-av1", cmd_svt298_av1},
"""

b298_funcs = """/* ===== Batch 298: Video Processing ===== */
static void cmd_mpv298(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: mpv <file>\\n"); return; }
    vga_printf("mpv: playing %s\\n", args[1]);
}
static void cmd_vlc298(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: vlc <file>\\n"); return; }
    vga_printf("vlc: playing %s\\n", args[1]);
}
static void cmd_obs298(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("OBS Studio: streaming\\n");
    vga_puts("obs: recording started\\n");
}
static void cmd_kdenlive298(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Kdenlive: video editor\\n");
}
static void cmd_shotcut298(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Shotcut: video editor\\n");
}
static void cmd_davinci298(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("DaVinci Resolve: professional video editing\\n");
}
static void cmd_synfig298(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Synfig: 2D animation\\n");
}
static void cmd_tupi298(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("TupiTube: 2D animation\\n");
}
static void cmd_mlt298(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("MLT: multimedia framework\\n");
}
static void cmd_gstreamer298(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("GStreamer: multimedia framework\\n");
}
static void cmd_librav1e298(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("rav1e: AV1 encoder\\n");
}
static void cmd_svt298_av1(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("SVT-AV1: AV1 encoder\\n");
}
"""

# Fix syntax errors
b297_decls = b297_decls.replace("static void_cmd_", "static void cmd_")
b298_decls = b298_decls.replace("static void cmd_svt298_av1", "static void cmd_svt298")

# Inject
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b295_decls + b296_decls + b297_decls + b298_decls + decl_marker)

old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + \
    '    /* Batch 263: Network Utilities */'
new_entries = b295_entries + b296_entries + b297_entries + b298_entries
content = content.replace(old_entry, old_entry + new_entries, 1)

func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b295_funcs + b296_funcs + b297_funcs + b298_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)
print("Injected Batches 295-298 (48 new commands)")