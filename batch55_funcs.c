/* ===== Batch 55: Multimedia + Creative Tools (40 commands) ===== */

static void cmd_blender55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: blender <version|render|scene|addons|script>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Blender v4.1.0\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Cycles: 4.1, EEVEE Next\n");
vga_puts("Python API: 3.11\n");
vga_puts("License: GPL v2+\n");
}
else if(strcmp(args[1],"render")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Rendering scene default.blend...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Engine: Cycles (GPU, CUDA)\n");
vga_puts("Resolution: 1920x1080 @ 128 samples\n");
vga_puts("Denoising: OpenImageDenoise\n");
vga_puts("Render time: 42.7s\n");
vga_puts("Saved: output_0001.png\n");
}
else if(strcmp(args[1],"scene")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Scene objects:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Cube (Mesh)  verts:8 faces:6\n");
vga_puts("  Camera        type:PERSP  fov:50\n");
vga_puts("  Light         type:POINT  energy:1000W\n");
vga_puts("  Armature      bones:24  animation:walk\n");
}
else if(strcmp(args[1],"addons")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Enabled addons:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  node_wrangler, loop_tools\n");
vga_puts("  auto_lighting, rigify\n");
vga_puts("  3d-view-port-info\n");
vga_puts("Installed: 12  Enabled: 6\n");
}
else if(strcmp(args[1],"script")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Python script execution:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  import bpy; bpy.ops.mesh.primitive_uv_sphere_add()\n");
vga_puts("  Created: Sphere (32 seg, 16 ring)\n");
vga_puts("  Applied subdivision (level 2)\n");
vga_puts("Script completed in 0.023s\n");
}
else{vga_puts("Usage: blender <version|render|scene|addons|script>\n");}
}

static void cmd_gimp55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: gimp <version|image|filter|script|batch>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("GIMP v2.10.36\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("GEGL: 0.4.48  Babl: 0.1.108\n");
vga_puts("GEGL filters: 312\n");
vga_puts("License: GPL v3+\n");
}
else if(strcmp(args[1],"image")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("New image created:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Size: 3840x2160 (4K)\n");
vga_puts("  Color: RGB 8-bit\n");
vga_puts("  Layers: 1 (Background)\n");
vga_puts("  Resolution: 300 PPI\n");
vga_puts("  Memory: 23.6 MB\n");
}
else if(strcmp(args[1],"filter")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Applying Gaussian Blur...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Radius X: 5.0  Y: 5.0\n");
vga_puts("  Filter time: 1.23s\n");
vga_puts("Available: blur, sharpen, distort\n");
vga_puts("  enhance, artistic, light-shadow\n");
}
else if(strcmp(args[1],"script")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Script-Fu console ready\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  > (car (gimp-image-list))\n");
vga_puts("  1  ; #<Image 3840x2160 RGB>\n");
vga_puts("Script: batch_resize.scm loaded\n");
}
else if(strcmp(args[1],"batch")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Batch processing:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input: 48 images (RAW + JPEG)\n");
vga_puts("  Script: batch_export_web.scm\n");
vga_puts("  Output: /output/web/*.webp\n");
vga_puts("  Processed: 48/48  Time: 127.4s\n");
}
else{vga_puts("Usage: gimp <version|image|filter|script|batch>\n");}
}

static void cmd_inkscape55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: inkscape <version|draw|export|path|svg>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Inkscape v1.3.2\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("GTK: 3.24.38  Cairo: 1.18.0\n");
vga_puts("Lib2geom: 2.0\n");
vga_puts("License: GPL v2+\n");
}
else if(strcmp(args[1],"draw")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("SVG canvas ready\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Viewport: 0,0  1920x1080\n");
vga_puts("  Grid: Cartesian 10px\n");
vga_puts("  Snapping: enabled (nodes, paths)\n");
vga_puts("  Layers: 3 (bg, main, overlay)\n");
}
else if(strcmp(args[1],"export")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Exporting SVG...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Format: PDF (vector)\n");
vga_puts("  DPI: 300  Area: page\n");
vga_puts("  Text: convert to outlines\n");
vga_puts("  Saved: design_export.pdf\n");
}
else if(strcmp(args[1],"path")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Path operations:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  union, difference, intersection\n");
vga_puts("  exclusion, division, cut\n");
vga_puts("  nodes: 1247  handles: 892\n");
vga_puts("  Smoothness: 0.25 tolerance\n");
}
else if(strcmp(args[1],"svg")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("SVG Document Info:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Width: 800px  Height: 600px\n");
vga_puts("  Elements: 342  Paths: 187\n");
vga_puts("  Embedded fonts: 3 (Open Sans)\n");
vga_puts("  File size: 487 KB\n");
}
else{vga_puts("Usage: inkscape <version|draw|export|path|svg>\n");}
}

static void cmd_krita55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: krita <version|canvas|brush|layer|animation>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Krita v5.2.2\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Qt: 6.6.1  KDE Frameworks: 5.115\n");
vga_puts("Color: 16-bit float, CMYK\n");
vga_puts("License: GPL v3+\n");
}
else if(strcmp(args[1],"canvas")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("New canvas:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Size: 4000x3000 px (300 DPI)\n");
vga_puts("  Color: RGB 16-bit\n");
vga_puts("  Profile: sRGB IEC61966-2.1\n");
vga_puts("  Memory: 68.6 MB\n");
}
else if(strcmp(args[1],"brush")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Brush engines loaded:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Pixel, Paint, Sketch, Hatching\n");
vga_puts("  Filter, Chalk, Deform, Color\n");
vga_puts("  Default: Bristle Oil (size 15)\n");
vga_puts("  Presets: 187 active\n");
}
else if(strcmp(args[1],"layer")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Layer stack:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  [visible] Details    (paint)\n");
vga_puts("  [visible] Character  (paint)\n");
vga_puts("  [locked]  Background (paint)\n");
vga_puts("  Blending: normal  Opacity: 100%\n");
}
else if(strcmp(args[1],"animation")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Animation timeline:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  FPS: 24  Duration: 3s (72 frames)\n");
vga_puts("  Onion skin: enabled (2 prev, 2 next)\n");
vga_puts("  Keyframes: 12  Drawn: 48/72\n");
vga_puts("  Playback: stopped at frame 0\n");
}
else{vga_puts("Usage: krita <version|canvas|brush|layer|animation>\n");}
}

static void cmd_darktable55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: darktable <version|import|develop|export|lens>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("darktable v4.6.1\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("OpenCL: enabled  GPU: NVIDIA RTX\n");
vga_puts("Color management: LCMS2\n");
vga_puts("License: GPL v3+\n");
}
else if(strcmp(args[1],"import")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Importing photos...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Source: /sdcard/DCIM/100CANON/\n");
vga_puts("  Files: 247 CR2 images\n");
vga_puts("  Catalog: darktable.db (24,891)\n");
vga_puts("  XMP sidecar: enabled\n");
}
else if(strcmp(args[1],"develop")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Processing pipeline:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  1. rawprepare  2. lenscorrection\n");
vga_puts("  3. colorbalance  4. tonecurve\n");
vga_puts("  5. vibrance  6. sharpen\n");
vga_puts("  7. vignetting  8. grain\n");
vga_puts("  Modules active: 12/28\n");
}
else if(strcmp(args[1],"export")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Exporting 247 images:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Format: JPEG Q92  sRGB\n");
vga_puts("  Resize: fit 3000px  No crop\n");
vga_puts("  Progress: 247/247 (100%)\n");
vga_puts("  Output: /exports/wedding/\n");
}
else if(strcmp(args[1],"lens")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Lens correction applied:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Lens: Canon EF 24-70mm f/2.8L\n");
vga_puts("  Focal: 50mm  Aperture: f/2.8\n");
vga_puts("  Distortion: -1.2%  Vignetting: 12%\n");
vga_puts("  TCA: corrected (0.002px)\n");
}
else{vga_puts("Usage: darktable <version|import|develop|export|lens>\n");}
}

static void cmd_rawtherapee55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: rawtherapee <version|process|batch|profile|queue>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("RawTherapee v5.10\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Engine: RT-engine (multi-threaded)\n");
vga_puts("Demosaic: AMaZE + VNG4\n");
vga_puts("License: GPL v3+\n");
}
else if(strcmp(args[1],"process")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Processing RAW file...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input: DSC_0451.NEF (24.2 MP)\n");
vga_puts("  Demosaic: AMaZE  White balance: auto\n");
vga_puts("  Exposure: +0.3EV  Highlights: -40\n");
vga_puts("  Output: DSC_0451.tiff (48-bit)\n");
}
else if(strcmp(args[1],"batch")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Batch queue:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Pending: 156 images\n");
vga_puts("  Processing: 2 threads active\n");
vga_puts("  Completed: 89/156  ETA: 14min\n");
vga_puts("  Profile: Landscape RT\n");
}
else if(strcmp(args[1],"profile")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Processing profile:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Name: Landscape Enhanced\n");
vga_puts("  Tone curve: S-curve (gentle)\n");
vga_puts("  Color: ProPhoto  Bit depth: 16\n");
vga_puts("  Noise reduction: bilateral 30\n");
}
else if(strcmp(args[1],"queue")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Export queue status:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Format: TIFF 16-bit  sRGB\n");
vga_puts("  Resize: 4000px wide  No JPEG\n");
vga_puts("  Output dir: /exports/processed/\n");
vga_puts("  Speed: 8.2 images/min\n");
}
else{vga_puts("Usage: rawtherapee <version|process|batch|profile|queue>\n");}
}

static void cmd_hugin55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: hugin <version|stitch|optimise|calibrate|blend>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Hugin v2023.0.0\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Panorama tools: 2023.0\n");
vga_puts("Enblend: 4.2  Panotools: 2.9\n");
vga_puts("License: GPL v2+\n");
}
else if(strcmp(args[1],"stitch")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Stitching panorama...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input: 24 images (RAW, 24MP)\n");
vga_puts("  Projection: cylindrical\n");
vga_puts("  Output: 12000x4500 (360-deg)\n");
vga_puts("  Blending: multiblend  Time: 3m42s\n");
}
else if(strcmp(args[1],"optimise")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Optimising lens parameters:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Focal length: 17.5mm (est)\n");
vga_puts("  Distortion (a): 0.00234\n");
vga_puts("  Vignetting (Vb): -0.123\n");
vga_puts("  RMS error: 0.42px (good)\n");
}
else if(strcmp(args[1],"calibrate")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Lens calibration:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Lens: Nikon 14-24mm f/2.8G\n");
vga_puts("  Calibrated: distortion, CA, vignetting\n");
vga_puts("  Saved: nikon1424.xml\n");
}
else if(strcmp(args[1],"blend")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Enblend output:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Feather: 70px  Compression: LZW\n");
vga_puts("  Seams: graph-cut optimised\n");
vga_puts("  Output: panorama.tif (187 MB)\n");
}
else{vga_puts("Usage: hugin <version|stitch|optimise|calibrate|blend>\n");}
}

static void cmd_synfig55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: synfig <version|render|layers|animate|export>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Synfig Studio v1.5.1\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Renderer: Synfig Animation 1\n");
vga_puts("Formats: SIF, SIFZ, GIF, AVI, MP4\n");
vga_puts("License: GPL v2+\n");
}
else if(strcmp(args[1],"render")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Rendering animation...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Canvas: 1920x1080 @ 24fps\n");
vga_puts("  Frames: 0-479 (20s)\n");
vga_puts("  Rendered: 234/480 (48.8%)\n");
vga_puts("  ETA: 12 minutes\n");
}
else if(strcmp(args[1],"layers")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Layer types available:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Region, Circle, Rectangle, Star\n");
vga_puts("  Polygon, Spline, Text, Group\n");
vga_puts("  Gradient, Noise, Blur, Transform\n");
vga_puts("  Active layers: 18 in timeline\n");
}
else if(strcmp(args[1],"animate")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Animation workspace:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Waypoints: 47 keyframes\n");
vga_puts("  Duration: 20s @ 24fps = 480 frames\n");
vga_puts("  Interpolation: TCBezier (default)\n");
vga_puts("  Playhead: frame 0  Playing: no\n");
}
else if(strcmp(args[1],"export")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Export options:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Video: MP4 (H.264, 8Mbps)\n");
vga_puts("  GIF: 256 colors, 50fps, dither\n");
vga_puts("  Image sequence: PNG 32-bit\n");
vga_puts("  Saved: animation_output.mp4\n");
}
else{vga_puts("Usage: synfig <version|render|layers|animate|export>\n");}
}

static void cmd_opentoonz55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: opentoonz <version|scene|palette|xsheet|scan>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("OpenToonz v1.7.1\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Framework: Qt 6.5  Plugin: SDK 1.0\n");
vga_puts("Toonz raster: 7.0\n");
vga_puts("License: BSD\n");
}
else if(strcmp(args[1],"scene")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Current scene:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Name: character_walk\n");
vga_puts("  FPS: 24  Duration: 5s (120 frames)\n");
vga_puts("  Col1: character (vector)\n");
vga_puts("  Col2: background (raster)\n");
vga_puts("  Col3: effects (fx);\n");
}
else if(strcmp(args[1],"palette")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Style palette:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Styles: 256 (GTS format)\n");
vga_puts("  Main: skin=#F5CBA7 outline=#2C3E50\n");
vga_puts("  Fill: white=#FFFFFF shadow=#34495E\n");
vga_puts("  Styles linked to Toonz levels\n");
}
else if(strcmp(args[1],"xsheet")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Xsheet columns:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Col1: 120 frames (exposure sheet)\n");
vga_puts("  Col2: 120 frames (static BG)\n");
vga_puts("  Col3: 120 frames (motion blur fx)\n");
vga_puts("  Current: frame 1\n");
}
else if(strcmp(args[1],"scan")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Scan module:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input: 300 DPI b/w lineart\n");
vga_puts("  Cleanup: remove noise, threshold\n");
vga_puts("  Pages scanned: 24/48\n");
vga_puts("  Output: scan_001.tlv\n");
}
else{vga_puts("Usage: opentoonz <version|scene|palette|xsheet|scan>\n");}
}

static void cmd_kdenlive55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: kdenlive <version|timeline|render|effects|proxy>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Kdenlive v23.08.4\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("MLT: 7.22.0  Framework: Qt 6.5\n");
vga_puts("GPU: OpenGL, VDPAU\n");
vga_puts("License: GPL v2+\n");
}
else if(strcmp(args[1],"timeline")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Timeline status:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Resolution: 3840x2160 @ 30fps\n");
vga_puts("  Duration: 00:15:42\n");
vga_puts("  Tracks: V1(black) V2(b-roll) A1(narr) A2(music)\n");
vga_puts("  Clips: 47  Transitions: 12\n");
}
else if(strcmp(args[1],"render")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Rendering project...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Format: MP4 (H.264/ACC)\n");
vga_puts("  Bitrate: 20 Mbps  CRF: 18\n");
vga_puts("  Progress: 67% (10:31/15:42)\n");
vga_puts("  ETA: 4 minutes 30 seconds\n");
}
else if(strcmp(args[1],"effects")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Applied effects on V1:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  1. transform (zoom 120%)\n");
vga_puts("  2. colorcorrection (sat +15)\n");
vga_puts("  3. denoiser (hqdn3d)\n");
vga_puts("Available: 287 effects in 14 categories\n");
}
else if(strcmp(args[1],"proxy")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Proxy manager:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Proxy clips: 32/47 generated\n");
vga_puts("  Profile: 720p  Codec: MPEG-2\n");
vga_puts("  Storage: 2.4 GB in /proxies/\n");
vga_puts("  Status: generating (15 remaining)\n");
}
else{vga_puts("Usage: kdenlive <version|timeline|render|effects|proxy>\n");}
}

static void cmd_resolve55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: resolve <version|project|color|fairlight|fusion>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("DaVinci Resolve Studio v18.6.4\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("GPU: NVIDIA RTX 4090 (16GB)\n");
vga_puts("License: Proprietary ($295)\n");
}
else if(strcmp(args[1],"project")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Current project:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Name: commercial_final_v7\n");
vga_puts("  Timeline: 00:02:15  @ 23.976fps\n");
vga_puts("  Clips: 89  Timeline: 4 tracks\n");
vga_puts("  Media pool: 347 clips (2.4TB)\n");
}
else if(strcmp(args[1],"color")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Color grading workspace:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Nodes: 8 (serial + parallel)\n");
vga_puts("  LUTs: FilmConvert, custom_cube\n");
vga_puts("  Scopes: Waveform, Vectorscope\n");
vga_puts("  Qualifier: HSL key active\n");
}
else if(strcmp(args[1],"fairlight")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Fairlight audio:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Sample rate: 48kHz / 24-bit\n");
vga_puts("  Tracks: 16 (8 dialogue, 4 SFX, 4 music)\n");
vga_puts("  Bus: Stereo Master, 5.1 Surround\n");
vga_puts("  Plugins: FairlightFX 42 active\n");
}
else if(strcmp(args[1],"fusion")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Fusion compositing:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Nodes: 34 in node graph\n");
vga_puts("  Effects: planar tracker, keyer\n");
vga_puts("  Particles: fire, smoke (GPU)\n");
vga_puts("  Render: 1280x720 preview @ 24fps\n");
}
else{vga_puts("Usage: resolve <version|project|color|fairlight|fusion>\n");}
}

static void cmd_obs55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: obs <version|scenes|sources|stream|record>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("OBS Studio v30.1.2\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("FFmpeg: 6.1.1  Qt: 6.5.2\n");
vga_puts("Encoder: NVENC (NVIDIA)\n");
vga_puts("License: GPL v2+\n");
}
else if(strcmp(args[1],"scenes")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Scene collection (5 scenes):\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  1. Gaming (active)  - 4 sources\n");
vga_puts("  2. Just Chatting     - 3 sources\n");
vga_puts("  3. BRB Screen        - 2 sources\n");
vga_puts("  4. Starting Soon     - 3 sources\n");
vga_puts("  5. Ending            - 2 sources\n");
}
else if(strcmp(args[1],"sources")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Active sources (Gaming):\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Game Capture: D3D11 (1080p60)\n");
vga_puts("  Webcam: C920 (1080p30)\n");
vga_puts("  Mic: Blue Yeti (48kHz)\n");
vga_puts("  Overlay: browser source (local)\n");
}
else if(strcmp(args[1],"stream")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Stream status:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Platform: Twitch (RTMPS)\n");
vga_puts("  Bitrate: 6000 Kbps  FPS: 60\n");
vga_puts("  Dropped frames: 0 (0.00%)\n");
vga_puts("  Uptime: 02:34:18  Viewers: 127\n");
}
else if(strcmp(args[1],"record")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Recording:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Format: MKV (remux to MP4)\n");
vga_puts("  Encoder: NVENC H.264 CQP 18\n");
vga_puts("  Resolution: 2560x1440 @ 60fps\n");
vga_puts("  File size: 12.4 GB  Duration: 1:14:32\n");
}
else{vga_puts("Usage: obs <version|scenes|sources|stream|record>\n");}
}

static void cmd_audacity55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: audacity <version|track|effect|export|analyze>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Audacity v3.5.1\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("wxWidgets: 3.2.4  PortAudio: v19.7\n");
vga_puts("FFmpeg: libavformat 60.16\n");
vga_puts("License: GPL v2+\n");
}
else if(strcmp(args[1],"track")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Current project:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Sample rate: 48000 Hz\n");
vga_puts("  Bit depth: 32-bit float\n");
vga_puts("  Track 1: Voice (mono, 5:32)\n");
vga_puts("  Track 2: Music (stereo, 5:32)\n");
vga_puts("  Selection: 0:00 - 5:32\n");
}
else if(strcmp(args[1],"effect")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Apply effect:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Effect: Noise Reduction\n");
vga_puts("  Profile: -12 dB  Sensitivity: 6\n");
vga_puts("  Frequency smoothing: 3 bands\n");
vga_puts("  Applied to Track 1, 100% selected\n");
}
else if(strcmp(args[1],"export")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Exporting audio:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Format: WAV 16-bit PCM\n");
vga_puts("  Channels: Stereo  Rate: 48000\n");
vga_puts("  Saved: voiceover_final.wav\n");
vga_puts("  Size: 48.2 MB\n");
}
else if(strcmp(args[1],"analyze")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Audio analysis:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Peak: -3.2 dB  RMS: -18.4 dB\n");
vga_puts("  LUFS: -22.1  Dynamic range: 14.2\n");
vga_puts("  Clipping: 0 samples\n");
vga_puts("  DC offset: 0.0001\n");
}
else{vga_puts("Usage: audacity <version|track|effect|export|analyze>\n");}
}

static void cmd_lmms55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: lmms <version|project|instruments|effects|export>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("LMMS v1.2.2\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Audio: JACK/ALSA/SDL\n");
vga_puts("Plugins: LADSPA, LV2, VST2\n");
vga_puts("License: GPL v2+\n");
}
else if(strcmp(args[1],"project")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Project: synthwave_night.mmpz\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  BPM: 128  Time sig: 4/4\n");
vga_puts("  Duration: 3:42 (112 bars)\n");
vga_puts("  Tracks: 14 (6 beat, 3 bass, 5 mel)\n");
}
else if(strcmp(args[1],"instruments")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Loaded instruments:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Triple Oscillator (lead)\n");
vga_puts("  Organic (pad)  Mallets (arp)\n");
vga_puts("  AudioFileProcessor (kick, snare)\n");
vga_puts("  VeSTige: Diva (bass synth)\n");
}
else if(strcmp(args[1],"effects")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Effects chain:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Reverb: room size 0.7, wet 0.3\n");
vga_puts("  Delay: 1/8 dotted, feedback 40%\n");
vga_puts("  Equalizer: low-cut 80Hz, shelf +3dB\n");
vga_puts("  Compressor: ratio 4:1, attack 10ms\n");
}
else if(strcmp(args[1],"export")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Exporting project...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Format: OGG Vorbis Q8\n");
vga_puts("  Sample rate: 44100 Hz\n");
vga_puts("  Exported: synthwave_night.ogg\n");
vga_puts("  Size: 8.4 MB  Time: 45.2s\n");
}
else{vga_puts("Usage: lmms <version|project|instruments|effects|export>\n");}
}

static void cmd_ardour55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: ardour <version|session|tracks|mixer|export>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Ardour v8.4\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Audio: JACK/ALSA/PortAudio\n");
vga_puts("DSP: 64-bit float internal\n");
vga_puts("License: GPL v2+ / freeware build\n");
}
else if(strcmp(args[1],"session")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Session: studio_session.ardour\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Sample rate: 96000 Hz\n");
vga_puts("  Duration: 22:15  Tempo: 120 BPM\n");
vga_puts("  Tracks: 32  Buses: 8\n");
vga_puts("  Snapshots: 14\n");
}
else if(strcmp(args[1],"tracks")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Track list (32 tracks):\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  1-8:   Drums (8 mic inputs)\n");
vga_puts("  9-14:  Bass, Guitar L/R, Keys L/R\n");
vga_puts("  15-24: Vocals (lead + 4 harmonies)\n");
vga_puts("  25-32: Strings, brass, FX\n");
}
else if(strcmp(args[1],"mixer")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Mixer snapshot:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Master: -2.1 dBFS  Peak: -0.3\n");
vga_puts("  Kick: -8dB  Snare: -6dB\n");
vga_puts("  Vocal: -4dB  Bass: -5dB\n");
vga_puts("  Active plugins: 67\n");
}
else if(strcmp(args[1],"export")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Export session:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Format: FLAC 24-bit 96kHz\n");
vga_puts("  Tracks: 32 -> Stereo mixdown\n");
vga_puts("  Exported: studio_mix_24-96.flac\n");
vga_puts("  Size: 187 MB\n");
}
else{vga_puts("Usage: ardour <version|session|tracks|mixer|export>\n");}
}

static void cmd_musescore55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: musescore <version|score|playback|export|midi>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("MuseScore v4.2.1\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Sound: MuseSounds Library\n");
vga_puts("Audio: JACK/ALSA/PulseAudio\n");
vga_puts("License: GPL v3+\n");
}
else if(strcmp(args[1],"score")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Current score:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Title: Symphony No. 5 in C minor\n");
vga_puts("  Instruments: 85 (full orchestra)\n");
vga_puts("  Measures: 348  Pages: 72\n");
vga_puts("  Key: C minor  Time: 3/4\n");
}
else if(strcmp(args[1],"playback")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Playback:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Soundfont: MuseScore Orchestra\n");
vga_puts("  Tempo: 108 BPM  Dynamic: mf\n");
vga_puts("  Position: mm.47 beat 2\n");
vga_puts("  Active voices: 12\n");
}
else if(strcmp(args[1],"export")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Export options:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  PDF: 72 pages (engraved)\n");
vga_puts("  MIDI: symphony5.mid (348 measures)\n");
vga_puts("  Audio: FLAC 24-bit (MuseSounds)\n");
vga_puts("  MusicXML: symphony5.musicxml\n");
}
else if(strcmp(args[1],"midi")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("MIDI info:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Tracks: 85  Channels: 16\n");
vga_puts("  Total notes: 12,847\n");
vga_puts("  Duration: 28:14\n");
vga_puts("  Key events: 4 key changes\n");
}
else{vga_puts("Usage: musescore <version|score|playback|export|midi>\n");}
}

static void cmd_sox_full55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: sox_full <version|convert|effect|info|combine>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("SoX v14.4.2\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Sound eXchange - Swiss army knife of audio\n");
vga_puts("Codecs: WAV, MP3, FLAC, OGG, AAC\n");
vga_puts("License: LGPL v2+\n");
}
else if(strcmp(args[1],"convert")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Converting audio...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  recording.wav (48kHz/24bit)\n");
vga_puts("  Output: recording.flac (lossless)\n");
vga_puts("  Size: 142MB -> 89MB (38% savings)\n");
vga_puts("  Conversion complete in 2.3s\n");
}
else if(strcmp(args[1],"effect")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Apply effects chain:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  highpass 80 lowpass 8000\n");
vga_puts("  compand 0.3,1 6:-70,-60,-20\n");
vga_puts("  gain -3 rate 44100\n");
vga_puts("Effects applied successfully\n");
}
else if(strcmp(args[1],"info")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Audio file info:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: sample.wav\n");
vga_puts("  48000Hz  2 channels  16-bit PCM\n");
vga_puts("  Duration: 3:24  Size: 30.6 MB\n");
}
else if(strcmp(args[1],"combine")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Combining audio files:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  sox track1.wav track2.wav mix.wav\n");
vga_puts("  sox track1.wav track2.wav concat.wav\n");
vga_puts("  Mixed: 2 tracks  Output: mix.wav\n");
}
else{vga_puts("Usage: sox_full <version|convert|effect|info|combine>\n");}
}

static void cmd_lame55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: lame <version|encode|decode|info|quality>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("LAME v3.100.1\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("MP3 encoder/decoder\n");
vga_puts("VBR/ABR/CBR modes\n");
vga_puts("License: LGPL v2+\n");
}
else if(strcmp(args[1],"encode")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Encoding to MP3...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  song.wav (44.1kHz stereo)\n");
vga_puts("  Output: song.mp3  VBR V2 (~192kbps)\n");
vga_puts("  Psycho-acoustic model: v2\n");
vga_puts("  Size: 42MB -> 6.2MB (85% reduction)\n");
vga_puts("  Encoding time: 12.4s\n");
}
else if(strcmp(args[1],"decode")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Decoding MP3 to WAV...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  podcast.mp3 (128kbps CBR)\n");
vga_puts("  Output: podcast.wav (16-bit PCM)\n");
vga_puts("  Duration: 45:22  Size: 152MB\n");
}
else if(strcmp(args[1],"info")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("MP3 file info:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: track01.mp3\n");
vga_puts("  192kbps CBR  44100Hz  Stereo\n");
vga_puts("  Duration: 4:12  Size: 5.9 MB\n");
vga_puts("  Encoder: LAME 3.100  VBR: off\n");
}
else if(strcmp(args[1],"quality")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Quality presets:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  V0: ~245kbps (best VBR)\n");
vga_puts("  V2: ~190kbps (good quality)\n");
vga_puts("  192: CBR (compatibility)\n");
vga_puts("  320: CBR (maximum quality)\n");
}
else{vga_puts("Usage: lame <version|encode|decode|info|quality>\n");}
}

static void cmd_opus55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: opus <version|encode|decode|info|compare>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Opus v1.5.1 (libopus)\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Codec: SILK + CELT hybrid\n");
vga_puts("Bandwidth: 8kHz - 48kHz\n");
vga_puts("License: BSD\n");
}
else if(strcmp(args[1],"encode")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Encoding to Opus...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  speech.wav (16kHz mono)\n");
vga_puts("  Output: speech.opus  64kbps\n");
vga_puts("  VBR: enabled  Complexity: 10\n");
vga_puts("  Size: 12MB -> 2.1MB (83% savings)\n");
}
else if(strcmp(args[1],"decode")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Decoding Opus...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  stream.opus (48kHz stereo)\n");
vga_puts("  Output: decoded.wav (16-bit PCM)\n");
vga_puts("  Duration: 3:48  Size: 39.2MB\n");
}
else if(strcmp(args[1],"info")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Opus file info:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: voice_chat.opus\n");
vga_puts("  64kbps VBR  48000Hz  Stereo\n");
vga_puts("  Duration: 12:45  Size: 5.8 MB\n");
vga_puts("  Application: VOIP  Delay: 20ms\n");
}
else if(strcmp(args[1],"compare")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Codec comparison (same source):\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Opus 64kbps:  VMAF=97.2  2.1MB\n");
vga_puts("  AAC 128kbps:  VMAF=96.8  4.2MB\n");
vga_puts("  MP3 192kbps:  VMAF=95.1  5.9MB\n");
vga_puts("  Opus wins at lower bitrate\n");
}
else{vga_puts("Usage: opus <version|encode|decode|info|compare>\n");}
}

static void cmd_fdk_aac55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: fdk_aac <version|encode|decode|profile|info>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("fdk-aac v2.0.3\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Fraunhofer FDK AAC Codec Library\n");
vga_puts("HE-AAC v2, HE-AAC v1, AAC-LC\n");
vga_puts("License: Apache 2.0\n");
}
else if(strcmp(args[1],"encode")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Encoding to AAC...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  music.wav (44.1kHz stereo)\n");
vga_puts("  Output: music.m4a  HE-AAC v2 96kbps\n");
vga_puts("  SBR: enabled  PS: enabled\n");
vga_puts("  Size: 42MB -> 3.4MB (92% reduction)\n");
}
else if(strcmp(args[1],"decode")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Decoding AAC to PCM...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  podcast.m4a (AAC-LC 128kbps)\n");
vga_puts("  Output: podcast.wav (16-bit PCM)\n");
vga_puts("  Duration: 1:02:33  Size: 418MB\n");
}
else if(strcmp(args[1],"profile")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("AAC profiles:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  AAC-LC:   96-320kbps (standard)\n");
vga_puts("  HE-AAC v1: 32-96kbps (SBR)\n");
vga_puts("  HE-AAC v2: 16-48kbps (SBR+PS)\n");
vga_puts("  LD:        32-64kbps (low delay)\n");
}
else if(strcmp(args[1],"info")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("AAC file info:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: album_track.m4a\n");
vga_puts("  Profile: AAC-LC  192kbps VBR\n");
vga_puts("  44100Hz  Stereo  Duration: 5:18\n");
vga_puts("  Encoder: fdk-aac 2.0.3\n");
}
else{vga_puts("Usage: fdk_aac <version|encode|decode|profile|info>\n");}
}

static void cmd_exiftool55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: exiftool <version|read|write|batch|gps>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("ExifTool v12.76\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Perl-based metadata reader/writer\n");
vga_puts("Supported: 400+ file types\n");
vga_puts("License: GPL v1+ / freeware\n");
}
else if(strcmp(args[1],"read")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Reading EXIF from photo.jpg:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Camera: Canon EOS R5\n");
vga_puts("  Lens: RF 50mm f/1.2L USM\n");
vga_puts("  ISO: 400  f/2.8  1/500s\n");
vga_puts("  Date: 2024-01-15 14:32:07\n");
vga_puts("  GPS: 35.6762N 139.6503E (Tokyo)\n");
}
else if(strcmp(args[1],"write")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Writing metadata...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  -Artist=John Doe\n");
vga_puts("  -Copyright=2024\n");
vga_puts("  -Description=Sunset at Shibuya\n");
vga_puts("  1 file updated\n");
}
else if(strcmp(args[1],"batch")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Batch processing:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  exiftool -r -all= ./photos/\n");
vga_puts("  Files scanned: 1,247\n");
vga_puts("  Stripped: 1,189 metadata blocks\n");
vga_puts("  Errors: 0  Warnings: 3\n");
}
else if(strcmp(args[1],"gps")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("GPS extraction:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  12 photos with GPS data found\n");
vga_puts("  Locations: Tokyo(4), Kyoto(3), Osaka(5)\n");
vga_puts("  KML export: track.kml (12 points)\n");
}
else{vga_puts("Usage: exiftool <version|read|write|batch|gps>\n");}
}

static void cmd_imagemagick55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: imagemagick <version|convert|identify|montage|compare>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("ImageMagick v7.1.1-28\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Delegates: JPEG PNG TIFF WebP\n");
vga_puts("Quantum: Q16 HDRI  Formats: 237\n");
vga_puts("License: Apache 2.0\n");
}
else if(strcmp(args[1],"convert")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Converting image...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  photo.tiff (24MP)\n");
vga_puts("  Resize: 800x600  Crop: center\n");
vga_puts("  Output: photo_thumb.webp\n");
vga_puts("  Size: 42MB -> 124KB (99.7% savings)\n");
}
else if(strcmp(args[1],"identify")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Image identification:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: banner.png\n");
vga_puts("  3840x1080 PNG RGBA 8-bit\n");
vga_puts("  Gamma: 2.2  Colorspace: sRGB\n");
vga_puts("  Size: 2.4 MB  Depth: 32-bit\n");
}
else if(strcmp(args[1],"montage")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Creating montage:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Layout: 4x3 grid  Tile: 200x200\n");
vga_puts("  Border: 10px white  Shadow: yes\n");
vga_puts("  Output: montage.jpg (Q95)\n");
vga_puts("  Total: 12 images in 1 montage\n");
}
else if(strcmp(args[1],"compare")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Image comparison:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  SSIM: 0.9847 (very similar)\n");
vga_puts("  PSNR: 38.2 dB\n");
vga_puts("  MAE: 2.3 per pixel\n");
vga_puts("  Diff map: diff_output.png\n");
}
else{vga_puts("Usage: imagemagick <version|convert|identify|montage|compare>\n");}
}

static void cmd_graphicsmagick55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: graphicsmagick <version|convert|identify|composite|tile>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("GraphicsMagick v1.3.43\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Image processing toolkit\n");
vga_puts("Formats: 98  Delegates: JPEG PNG\n");
vga_puts("License: MIT\n");
}
else if(strcmp(args[1],"convert")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Converting image:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  photo.ppm (6MP)\n");
vga_puts("  Resize: 1200x800  Rotate: 90\n");
vga_puts("  Sharpen: 0x1.0  Quality: 92\n");
vga_puts("  Output: photo_out.jpg  (287KB)\n");
}
else if(strcmp(args[1],"identify")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Image details:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: scan.tiff\n");
vga_puts("  4896x3672 TIFF 8-bit RGB\n");
vga_puts("  Resolution: 300x300 DPI\n");
vga_puts("  Compression: LZW  Size: 28.7MB\n");
}
else if(strcmp(args[1],"composite")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Compositing images:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Base: background.png\n");
vga_puts("  Overlay: logo.png (gravity center)\n");
vga_puts("  Opacity: 80%  Blend: over\n");
vga_puts("  Output: composed.png\n");
}
else if(strcmp(args[1],"tile")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Creating tile sheet:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input: 24 sprite frames\n");
vga_puts("  Layout: 8x3 grid  Frame: 128x128\n");
vga_puts("  Output: spritesheet.png (1024x384)\n");
vga_puts("  Transparent background: yes\n");
}
else{vga_puts("Usage: graphicsmagick <version|convert|identify|composite|tile>\n");}
}

static void cmd_webp55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: webp <version|encode|decode|info|anim>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("libwebp v1.3.2\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("WebP codec (lossy + lossless)\n");
vga_puts("Anim: WebP animation support\n");
vga_puts("License: BSD\n");
}
else if(strcmp(args[1],"encode")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Encoding to WebP...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  photo.jpg (3840x2160)\n");
vga_puts("  Output: photo.webp  Quality: 85\n");
vga_puts("  Method: 4  Size: 4.2MB -> 892KB\n");
vga_puts("  Savings: 78.8% vs JPEG\n");
}
else if(strcmp(args[1],"decode")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Decoding WebP...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  image.webp (lossy)\n");
vga_puts("  Output: image.png (RGBA)\n");
vga_puts("  Size: 124KB -> 2.8MB (lossless)\n");
}
else if(strcmp(args[1],"info")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("WebP file info:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: hero_banner.webp\n");
vga_puts("  2560x1440 lossy VP8  Q:80\n");
vga_puts("  ICC profile: sRGB embedded\n");
vga_puts("  Animation: 12 frames  Loop: yes\n");
}
else if(strcmp(args[1],"anim")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Animated WebP:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Frames: 24  Duration: 800ms\n");
vga_puts("  Frame size: 300x200\n");
vga_puts("  Lossy per-frame Q: 80\n");
vga_puts("  Total: 342KB  Rate: 30fps\n");
}
else{vga_puts("Usage: webp <version|encode|decode|info|anim>\n");}
}

static void cmd_avif55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: avif <version|encode|decode|info|compare>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("libavif v1.0.4 (AV1)\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Codec: libaom / rav1e / SVT-AV1\n");
vga_puts("HDR: Dolby Vision, HDR10+\n");
vga_puts("License: BSD\n");
}
else if(strcmp(args[1],"encode")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Encoding to AVIF...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  photo.tiff (48MP)\n");
vga_puts("  Output: photo.avif  Q:30  Speed:4\n");
vga_puts("  Codec: libaom  10-bit HDR\n");
vga_puts("  Size: 92MB -> 1.8MB (98% savings)\n");
}
else if(strcmp(args[1],"decode")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Decoding AVIF...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  photo.avif (10-bit)\n");
vga_puts("  Output: photo.png (16-bit RGBA)\n");
vga_puts("  Resolution: 6000x4000\n");
}
else if(strcmp(args[1],"info")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("AVIF file info:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: product_photo.avif\n");
vga_puts("  3000x2000 AV1  10-bit YUV420\n");
vga_puts("  Color: BT.2020 PQ (HDR10)\n");
vga_puts("  Size: 892KB  Anim: single frame\n");
}
else if(strcmp(args[1],"compare")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Format comparison (same source):\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  AVIF Q30:  SSIM=0.98  1.8MB\n");
vga_puts("  WebP Q80:  SSIM=0.97  3.2MB\n");
vga_puts("  JPEG Q90:  SSIM=0.96  5.1MB\n");
vga_puts("  AVIF has best quality/size ratio\n");
}
else{vga_puts("Usage: avif <version|encode|decode|info|compare>\n");}
}

static void cmd_heif55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: heif <version|encode|decode|info|thumbnail>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("libheif v1.17.6\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Codec: libde265 (HEVC/H.265)\n");
vga_puts("Multi-image: yes  Thumbnail: yes\n");
vga_puts("License: LGPL v3+\n");
}
else if(strcmp(args[1],"encode")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Encoding to HEIF...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  photo.png (30MP RGBA)\n");
vga_puts("  Output: photo.heif  Q:85 8-bit\n");
vga_puts("  Encoder: x265  Tiling: 4x2\n");
vga_puts("  Size: 42MB -> 2.1MB (95% savings)\n");
}
else if(strcmp(args[1],"decode")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Decoding HEIF...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  photo.heif (HEVC 10-bit)\n");
vga_puts("  Output: photo.tiff (16-bit)\n");
vga_puts("  Color: Display P3  Alpha: yes\n");
}
else if(strcmp(args[1],"info")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("HEIF file info:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: portrait.heif\n");
vga_puts("  3024x4032 HEVC Main Still 8-bit\n");
vga_puts("  Color: sRGB  Alpha: no\n");
vga_puts("  Thumbnail: 320x426  Grid: none\n");
}
else if(strcmp(args[1],"thumbnail")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Extracting thumbnails:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Thumbnails embedded: 3\n");
vga_puts("  Sizes: 160x213, 320x427, 640x853\n");
vga_puts("  Extracted: thumb_320.jpg (12KB)\n");
}
else{vga_puts("Usage: heif <version|encode|decode|info|thumbnail>\n");}
}

static void cmd_libreoffice_calc55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: libreoffice_calc <version|open|formula|chart|macro>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("LibreOffice Calc v24.2.3\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Calc engine: 8.2.3.2\n");
vga_puts("Max rows: 1,048,576  Cols: 1,024\n");
vga_puts("License: MPL v2\n");
}
else if(strcmp(args[1],"open")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Opening spreadsheet:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: budget_2024.xlsx\n");
vga_puts("  Sheets: 4 (Q1-Q4 + Summary)\n");
vga_puts("  Data range: A1:Z500\n");
vga_puts("  Charts: 3 embedded  Pivot: 1\n");
}
else if(strcmp(args[1],"formula")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Formula engine:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  =SUM(B2:B100)     -> 45,832\n");
vga_puts("  =AVERAGE(C2:C100) -> 1,234.56\n");
vga_puts("  =VLOOKUP(A2,Sheet2,3,0) -> OK\n");
vga_puts("  Functions: 510 available\n");
}
else if(strcmp(args[1],"chart")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Chart types:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Column, Bar, Line, Area, Scatter\n");
vga_puts("  Pie, Doughnut, Stock, Bubble\n");
vga_puts("  Radar, Net, Polar\n");
vga_puts("  Active chart: Revenue bar (Q1-Q4)\n");
}
else if(strcmp(args[1],"macro")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Macro support:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Languages: Basic, Python, JavaScript\n");
vga_puts("  Macros: 5 recorded\n");
vga_puts("  Module: BudgetModule (12 functions)\n");
vga_puts("  Security: Medium (prompt on run)\n");
}
else{vga_puts("Usage: libreoffice_calc <version|open|formula|chart|macro>\n");}
}

static void cmd_libreoffice_writer55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: libreoffice_writer <version|open|format|spell|pdf>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("LibreOffice Writer v24.2.3\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Writer engine: 24.2.3.2\n");
vga_puts("Formats: DOCX, ODT, RTF, PDF\n");
vga_puts("License: MPL v2\n");
}
else if(strcmp(args[1],"open")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Opening document:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: report_2024.docx\n");
vga_puts("  Pages: 47  Words: 12,847\n");
vga_puts("  Images: 14  Tables: 6\n");
vga_puts("  Styles: 23 custom styles\n");
}
else if(strcmp(args[1],"format")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Formatting options:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Styles: 145 (78 custom)\n");
vga_puts("  Fonts: 42 available (12 embedded)\n");
vga_puts("  Headers/Footers: custom page nums\n");
vga_puts("  Page layout: A4, 2.5cm margins\n");
}
else if(strcmp(args[1],"spell")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Spell check:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Language: English (US)\n");
vga_puts("  Dictionary: en_US (2024.02)\n");
vga_puts("  Errors found: 3  Warnings: 7\n");
vga_puts("  Grammar: LanguageTool (premium)\n");
}
else if(strcmp(args[1],"pdf")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Exporting to PDF:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Quality: PDF/A-1b (archival)\n");
vga_puts("  Encryption: AES-256\n");
vga_puts("  Bookmarks: yes  TOC: hyperlinked\n");
vga_puts("  Saved: report_2024.pdf (2.8MB)\n");
}
else{vga_puts("Usage: libreoffice_writer <version|open|format|spell|pdf>\n");}
}

static void cmd_libreoffice_impress55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: libreoffice_impress <version|open|slide|theme|export>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("LibreOffice Impress v24.2.3\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Presentation: Impress 24.2.3.2\n");
vga_puts("Export: PDF, PPTX, ODP, SVG\n");
vga_puts("License: MPL v2\n");
}
else if(strcmp(args[1],"open")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Opening presentation:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: product_launch.pptx\n");
vga_puts("  Slides: 32  Layout: widescreen\n");
vga_puts("  Animations: 47 (entrance + exit)\n");
vga_puts("  Transitions: 12 (fade, zoom)\n");
}
else if(strcmp(args[1],"slide")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Slide master:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Layouts: 11 standard\n");
vga_puts("  Title slide: centered, bold\n");
vga_puts("  Content: bullet list, 24pt\n");
vga_puts("  Custom: product, comparison, timeline\n");
}
else if(strcmp(args[1],"theme")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Theme designer:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Colors: primary=#2E86AB accent=#E84855\n");
vga_puts("  Fonts: Heading=Montserrat Body=Open Sans\n");
vga_puts("  Background: gradient (navy to charcoal)\n");
vga_puts("  Effects: drop shadow on images\n");
}
else if(strcmp(args[1],"export")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Exporting presentation:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  PDF: all slides with notes\n");
vga_puts("  PPTX: full compatibility mode\n");
vga_puts("  Images: PNG per slide (1920x1080)\n");
vga_puts("  Saved: product_launch.pdf (18.4MB)\n");
}
else{vga_puts("Usage: libreoffice_impress <version|open|slide|theme|export>\n");}
}

static void cmd_gnucash55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: gnucash <version|accounts|report|budget|import>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("GnuCash v5.6\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Engine: Double-entry accounting\n");
vga_puts("Formats: GnuCash XML, SQLite\n");
vga_puts("License: GPL v2+\n");
}
else if(strcmp(args[1],"accounts")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Account tree:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Assets\n");
vga_puts("    Checking: $12,456.78\n");
vga_puts("    Savings:  $45,230.12\n");
vga_puts("    Investments: $89,123.45\n");
vga_puts("  Liabilities  Credit Card: -$1,234.56\n");
}
else if(strcmp(args[1],"report")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Financial reports:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Income:  $8,500.00 (Jan)\n");
vga_puts("  Expenses: $6,234.89 (Jan)\n");
vga_puts("  Net:      $2,265.11\n");
vga_puts("  Net Worth: $145,575.79\n");
}
else if(strcmp(args[1],"budget")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Budget summary (Jan 2024):\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Housing:   $1500/$1500 (100%)\n");
vga_puts("  Food:      $620/$800  (77.5%)\n");
vga_puts("  Transport: $280/$300  (93.3%)\n");
vga_puts("  Savings:   $800/$800  (100%)\n");
}
else if(strcmp(args[1],"import")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Import transactions:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Source: bank_OFX_download.qfx\n");
vga_puts("  Transactions: 47\n");
vga_puts("  Matched: 42  New: 5\n");
vga_puts("  Imported: Checking account\n");
}
else{vga_puts("Usage: gnucash <version|accounts|report|budget|import>\n");}
}

static void cmd_blender_cli55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: blender_cli <version|render|script|convert|batch>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Blender CLI v4.1.0 (headless)\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Mode: background (no display)\n");
vga_puts("Python: 3.11  Cycles: GPU enabled\n");
}
else if(strcmp(args[1],"render")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Headless render:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  blender -b scene.blend -o //out_ -f 1\n");
vga_puts("  Engine: Cycles  Samples: 256\n");
vga_puts("  Resolution: 3840x2160\n");
vga_puts("  Render time: 38.2s (GPU)\n");
vga_puts("  Output: out_0001.png\n");
}
else if(strcmp(args[1],"script")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Python script execution:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  blender -b -P my_script.py\n");
vga_puts("  Script processed 1,200 objects\n");
vga_puts("  Exported: output.fbx (12.4MB)\n");
vga_puts("  Exit code: 0  Time: 4.7s\n");
}
else if(strcmp(args[1],"convert")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("3D format conversion:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  model.blend (50MB)\n");
vga_puts("  Output: model.gltf (glTF 2.0)\n");
vga_puts("  Embedded textures: 4 (PBR)\n");
vga_puts("  Output size: 18.3MB\n");
}
else if(strcmp(args[1],"batch")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Batch render:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Files: 12 .blend files\n");
vga_puts("  All: Cycles 256spp 1080p\n");
vga_puts("  Completed: 12/12 (100%)\n");
vga_puts("  Total time: 8m42s  Output: /renders/\n");
}
else{vga_puts("Usage: blender_cli <version|render|script|convert|batch>\n");}
}

static void cmd_ffmpeg_full55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: ffmpeg_full <version|encode|decode|stream|filter>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("FFmpeg v6.1.1 (full build)\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Codecs: 312  Formats: 421\n");
vga_puts("HW accel: NVENC, VAAPI, QSV\n");
vga_puts("License: GPL v3+\n");
}
else if(strcmp(args[1],"encode")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Encoding video:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  raw_clip.mov (ProRes 4K)\n");
vga_puts("  Output: final.mp4  H.265 CRF 18\n");
vga_puts("  Speed: 45fps (NVENC)  Size: 2.1GB\n");
vga_puts("  Audio: AAC 256kbps stereo\n");
vga_puts("  Duration: 12:34\n");
}
else if(strcmp(args[1],"decode")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Decoding analysis:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Stream 0: H.264 3840x2160@60fps\n");
vga_puts("  Stream 1: AAC 48000Hz stereo\n");
vga_puts("  Stream 2: Subtitle (SRT)\n");
vga_puts("  Bitrate: 12.4 Mbps total\n");
}
else if(strcmp(args[1],"stream")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Streaming output:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  RTMP: rtmp://live.twitch.tv/app/...\n");
vga_puts("  Video: H.264 6000kbps 1080p60\n");
vga_puts("  Audio: AAC 160kbps\n");
vga_puts("  Dropped: 0  Uptime: 01:23:45\n");
}
else if(strcmp(args[1],"filter")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Filter graphs:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  scale=1920:1080,format=yuv420p\n");
vga_puts("  drawtext=text=Hello:fontsize=48\n");
vga_puts("  crop=1600:900:160:90\n");
vga_puts("  hflip, vflip, transpose, fade\n");
vga_puts("Available filters: 347\n");
}
else{vga_puts("Usage: ffmpeg_full <version|encode|decode|stream|filter>\n");}
}

static void cmd_vlc_full55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: vlc_full <version|play|convert|stream|subtitle>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("VLC Media Player v3.0.20\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("LibVLC: 3.0.20  Qt: 5.15\n");
vga_puts("Codecs: FFmpeg + native\n");
vga_puts("License: GPL v2+\n");
}
else if(strcmp(args[1],"play")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Playing media:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: movie_4k.mkv (68.2 GB)\n");
vga_puts("  Video: HEVC 3840x2160 HDR10\n");
vga_puts("  Audio: DTS-HD MA 7.1 (48kHz)\n");
vga_puts("  Subtitles: SRT (English)\n");
vga_puts("  Position: 01:23:45 / 02:15:30\n");
}
else if(strcmp(args[1],"convert")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("VLC conversion:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Input:  movie.mkv (BluRay)\n");
vga_puts("  Output: movie.mp4 (H.264 + AAC)\n");
vga_puts("  Profile: HD 1080p  Bitrate: 8Mbps\n");
vga_puts("  Progress: 67%  ETA: 12 min\n");
}
else if(strcmp(args[1],"stream")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Network stream:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  URL: rtp://@239.0.0.1:5004\n");
vga_puts("  Protocol: RTP/RTSP\n");
vga_puts("  Buffer: 300ms  Jitter: 12ms\n");
vga_puts("  Quality: auto-adapting bitrate\n");
}
else if(strcmp(args[1],"subtitle")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Subtitle support:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Formats: SRT, ASS/SSA, SUB, VTT\n");
vga_puts("  Encoding: UTF-8 auto-detect\n");
vga_puts("  Track: English (embedded)\n");
vga_puts("  Style: default (white, shadow)\n");
}
else{vga_puts("Usage: vlc_full <version|play|convert|stream|subtitle>\n");}
}

static void cmd_mpv_full55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: mpv_full <version|play|config|screenshot|shader>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("mpv v0.37.0\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Video: libmpv + ffmpeg\n");
vga_puts("GPU: OpenGL/Vulkan/D3D11\n");
vga_puts("License: GPL v2+\n");
}
else if(strcmp(args[1],"play")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Playing:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: anime_ep01.mkv (4.2 GB)\n");
vga_puts("  Video: AV1 1920x1080 24fps\n");
vga_puts("  Audio: FLAC 5.1 (96kHz)\n");
vga_puts("  VO: GPU (Vulkan)  AO: PulseAudio\n");
vga_puts("  FPS: 24.000  Drop: 0\n");
}
else if(strcmp(args[1],"config")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("mpv.conf settings:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  vo=gpu-next  hwdec=vulkan\n");
vga_puts("  profile=gpu-hq\n");
vga_puts("  scale=spline36  cscale=spline36\n");
vga_puts("  deband=yes  interpolation=yes\n");
}
else if(strcmp(args[1],"screenshot")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Screenshot:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Format: PNG (lossless)\n");
vga_puts("  Directory: ~/Pictures/mpv/\n");
vga_puts("  Naming: mpv-shot0001.png\n");
vga_puts("  Quality: full resolution\n");
}
else if(strcmp(args[1],"shader")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Custom shaders:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  FSRCNNX_x2_16-0-4-1.glsl\n");
vga_puts("  KrigBilateral.glsl (chroma)\n");
vga_puts("  AdaptiveSharpen.glsl\n");
vga_puts("  3 shaders active  GPU load: 12%\n");
}
else{vga_puts("Usage: mpv_full <version|play|config|screenshot|shader>\n");}
}

static void cmd_yt_dlp55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: yt_dlp <version|download|info|audio|format>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("yt-dlp v2024.03.10\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Extractors: 1200+ sites\n");
vga_puts("Python: 3.12  ffmpeg: 6.1\n");
vga_puts("License: Unlicense\n");
}
else if(strcmp(args[1],"download")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Downloading video...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  URL: https://youtube.com/watch?v=...\n");
vga_puts("  Title: Amazing Nature Documentary\n");
vga_puts("  Quality: 1080p60 (best)\n");
vga_puts("  Size: 847MB  ETA: 2m34s\n");
vga_puts("  Saved: Amazing_Nature_Documentary.mp4\n");
}
else if(strcmp(args[1],"info")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Video information:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Title: Tech Review 2024\n");
vga_puts("  Duration: 23:45  Views: 1.2M\n");
vga_puts("  Upload: 2024-03-08  Channel: TechGuy\n");
vga_puts("  Formats: 24 (3 audio, 21 video)\n");
}
else if(strcmp(args[1],"audio")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Audio extraction:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Format: FLAC (best quality)\n");
vga_puts("  Source: YouTube music video\n");
vga_puts("  Output: song.flac (42MB)\n");
vga_puts("  Sample rate: 48000Hz (native)\n");
}
else if(strcmp(args[1],"format")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Available formats:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  2160p60 VP9 (26MB/min)\n");
vga_puts("  1080p60 H.264 (8MB/min)\n");
vga_puts("  720p30  H.264 (3MB/min)\n");
vga_puts("  Audio: AAC 256kbps, Opus 160kbps\n");
}
else{vga_puts("Usage: yt_dlp <version|download|info|audio|format>\n");}
}

static void cmd_aria255(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: aria2 <version|download|metalink|rpc|global>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("aria2 v1.37.0\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Protocols: HTTP(S), FTP, SFTP, BitTorrent\n");
vga_puts("Metalink: yes  RPC: JSON-RPC\n");
vga_puts("License: GPL v2+\n");
}
else if(strcmp(args[1],"download")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Downloading:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: large_archive.tar.gz (12.4GB)\n");
vga_puts("  Connections: 16 (multi-segment)\n");
vga_puts("  Speed: 24.8 MB/s  Progress: 67%\n");
vga_puts("  ETA: 2m48s  Peers: 42 (BT)\n");
}
else if(strcmp(args[1],"metalink")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Metalink processing:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: linux_distro.metalink\n");
vga_puts("  Mirrors: 8  Hashes: SHA-256\n");
vga_puts("  Verified: 3 mirrors passed\n");
vga_puts("  Best mirror: cdn-fast.example.com\n");
}
else if(strcmp(args[1],"rpc")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("RPC server:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Port: 6800  Secret: ****\n");
vga_puts("  Active downloads: 4\n");
vga_puts("  Waiting: 12  Stopped: 3\n");
vga_puts("  Global speed: 48.2 MB/s\n");
}
else if(strcmp(args[1],"global")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Global config:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  max-connection-per-server=16\n");
vga_puts("  split=16  max-concurrent-downloads=5\n");
vga_puts("  continue=true  auto-file-renaming=true\n");
vga_puts("  dir=~/Downloads/aria2/\n");
}
else{vga_puts("Usage: aria2 <version|download|metalink|rpc|global>\n");}
}

static void cmd_rsync55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: rsync <version|sync|delta|snapshot|daemon>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("rsync v3.3.0\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Algorithm: rolling-checksum delta\n");
vga_puts("Transfer: SSH, rsync daemon\n");
vga_puts("License: GPL v3+\n");
}
else if(strcmp(args[1],"sync")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Syncing directories...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Source:  /data/project/\n");
vga_puts("  Dest:    remote:/backup/project/\n");
vga_puts("  Files: 12,847  Changed: 342\n");
vga_puts("  Transferred: 342 files (124MB)\n");
vga_puts("  Speed: 45.2 MB/s  Time: 2m48s\n");
}
else if(strcmp(args[1],"delta")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Delta transfer:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  File: database_backup.sql (2.4GB)\n");
vga_puts("  Changed blocks: 892 / 36,864\n");
vga_puts("  Transferred: 23MB (99% savings)\n");
vga_puts("  Checksum: xxh3  Speed: 156MB/s\n");
}
else if(strcmp(args[1],"snapshot")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Snapshot backup:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  --link-dest=/backup/latest\n");
vga_puts("  New snapshot: /backup/2024-03-10/\n");
vga_puts("  Hardlinked: 11,234 unchanged files\n");
vga_puts("  New/modified: 1,613 files (89MB)\n");
}
else if(strcmp(args[1],"daemon")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("rsync daemon:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Port: 873  PID: 4523\n");
vga_puts("  Modules: /data, /backup, /www\n");
vga_puts("  Auth: secrets file  Hosts: allow 192.168\n");
vga_puts("  Connections: 3 active  Transfers: 8\n");
}
else{vga_puts("Usage: rsync <version|sync|delta|snapshot|daemon>\n");}
}

static void cmd_rclone55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: rclone <version|sync|mount|copy|about>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("rclone v1.66.0\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Remotes: 70+ cloud providers\n");
vga_puts("Mount: FUSE 2 (rclone mount)\n");
vga_puts("License: MIT\n");
}
else if(strcmp(args[1],"sync")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Syncing to cloud...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Source:  /data/website/ (24.8GB)\n");
vga_puts("  Dest:    gdrive:backups/website/\n");
vga_puts("  Files: 8,432  Transferred: 1,247\n");
vga_puts("  Speed: 12.4 MB/s  ETA: 14min\n");
vga_puts("  Encryption: AES-256 (rclone crypt)\n");
}
else if(strcmp(args[1],"mount")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("FUSE mount:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Remote: gdrive:  Mount: /mnt/gdrive\n");
vga_puts("  Type: read-write  Cache: 512MB\n");
vga_puts("  VFS: full (max cache)\n");
vga_puts("  Space: 15.0 TB total, 12.3 TB free\n");
}
else if(strcmp(args[1],"copy")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Copy operation:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  s3:media-bucket/photos/ -> /backup/\n");
vga_puts("  Files: 24,567 (89.2 GB)\n");
vga_puts("  Checksum: md5 verified all\n");
vga_puts("  Completed in 45m12s\n");
}
else if(strcmp(args[1],"about")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Remote storage info:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  gdrive:  15.0 TB / 20.0 TB (75%)\n");
vga_puts("  s3:      2.4 TB  / 5.0 TB (48%)\n");
vga_puts("  backblaze: 1.2 TB / unlimited\n");
vga_puts("  Total:   18.6 TB across 3 remotes\n");
}
else{vga_puts("Usage: rclone <version|sync|mount|copy|about>\n");}
}

static void cmd_restic_full55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: restic_full <version|backup|restore|snapshots|check>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("restic v0.16.4\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Backend: local, S3, B2, SFTP\n");
vga_puts("Encryption: AES-256-CTR\n");
vga_puts("License: BSD\n");
}
else if(strcmp(args[1],"backup")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Running backup...\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Repo: s3:restic-backup\n");
vga_puts("  Source: /home/user/ (48.2 GB)\n");
vga_puts("  New files: 1,247  Changed: 89\n");
vga_puts("  Dedup: saved 34.7 GB (72%)\n");
vga_puts("  Snapshot: a1b2c3d4  Time: 3m24s\n");
}
else if(strcmp(args[1],"restore")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Restoring snapshot:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Snapshot: a1b2c3d4 (2024-03-10)\n");
vga_puts("  Target: /restore/home/\n");
vga_puts("  Files: 12,847  Size: 48.2 GB\n");
vga_puts("  Verified: SHA-256 checksums OK\n");
vga_puts("  Restore time: 8m42s\n");
}
else if(strcmp(args[1],"snapshots")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Snapshots (8 total):\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  a1b2c3d4  2024-03-10 14:30  48.2GB\n");
vga_puts("  e5f6g7h8  2024-03-09 14:30  47.8GB\n");
vga_puts("  i9j0k1l2  2024-03-08 14:30  47.1GB\n");
vga_puts("  Oldest: 2024-03-03  Total: 340GB\n");
}
else if(strcmp(args[1],"check")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Repository check:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Packs: 1,247  Blobs: 45,892\n");
vga_puts("  Checked: all packs (100%)\n");
vga_puts("  Errors: 0  Warnings: 0\n");
vga_puts("  Repository integrity: OK\n");
}
else{vga_puts("Usage: restic_full <version|backup|restore|snapshots|check>\n");}
}

static void cmd_borg_full55(int argc, char args[][CMD_MAX_LEN]) {
if(argc<2){vga_puts("Usage: borg_full <version|create|list|extract|compact>\n");return;}
if(strcmp(args[1],"version")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("BorgBackup v1.4.0\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("Deduplication: content-defined chunking\n");
vga_puts("Compression: lz4, zstd, zlib, lzma\n");
vga_puts("Encryption: AES-256-CTR + HMAC-SHA256\n");
vga_puts("License: BSD\n");
}
else if(strcmp(args[1],"create")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Creating archive:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Repo: /backup/borg-repo\n");
vga_puts("  Archive: home-2024-03-10\n");
vga_puts("  Source: /home/user/ (52.1 GB)\n");
vga_puts("  Dedup: saved 38.4 GB (73.7%)\n");
vga_puts("  Compressed: 8.2 GB  Time: 4m18s\n");
}
else if(strcmp(args[1],"list")==0){vga_set_color(VGA_LIGHT_GREEN,VGA_BLACK);vga_puts("Archives (12 total):\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  home-2024-03-10  52.1GB  8.2GB\n");
vga_puts("  home-2024-03-09  51.8GB  8.1GB\n");
vga_puts("  home-2024-03-08  50.2GB  7.9GB\n");
vga_puts("  Retention: 7 daily, 4 weekly, 6 monthly\n");
}
else if(strcmp(args[1],"extract")==0){vga_set_color(VGA_LIGHT_CYAN,VGA_BLACK);vga_puts("Extracting archive:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Archive: home-2024-03-10\n");
vga_puts("  Pattern: home/user/Documents/\n");
vga_puts("  Files: 2,341  Size: 4.2 GB\n");
vga_puts("  Extracted to: /restore/Documents/\n");
}
else if(strcmp(args[1],"compact")==0){vga_set_color(VGA_YELLOW,VGA_BLACK);vga_puts("Compacting repository:\n");vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
vga_puts("  Before: 8.2 GB (1,247 segments)\n");
vga_puts("  Freed: 1.4 GB (17%)\n");
vga_puts("  After: 6.8 GB (892 segments)\n");
vga_puts("  Compaction time: 1m12s\n");
}
else{vga_puts("Usage: borg_full <version|create|list|extract|compact>\n");}
}

