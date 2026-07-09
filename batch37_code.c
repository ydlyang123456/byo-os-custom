/* === Batch 37: Dev Tools + Multimedia + Editors + Security === */

/* gdb - GNU debugger */
static void cmd_gdb(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("GNU gdb (GDB) 13.2\n");
        vga_puts("Usage: gdb [program] [-batch -ex run]\n");
        return;
    }
    vga_puts("GNU gdb (GDB) 13.2\n");
    vga_puts("Reading symbols from ");
    vga_puts(args[1]);
    vga_puts("...\n");
    vga_puts("(gdb) run\n");
    vga_puts("Starting program: /tmp/");
    vga_puts(args[1]);
    vga_puts("\n[Inferior 1 (process 1234) exited normally]\n");
}

/* valgrind - memory debugger */
static void cmd_valgrind(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("valgrind-3.21.0\n");
        vga_puts("Usage: valgrind [--tool=memcheck] <program>\n");
        return;
    }
    vga_puts("==1234== Memcheck, a memory error detector\n");
    vga_puts("==1234== Command: ");
    vga_puts(args[1]);
    vga_puts("\n==1234== \n");
    vga_puts("==1234== HEAP SUMMARY:\n");
    vga_puts("==1234==     in use at exit: 0 bytes in 0 blocks\n");
    vga_puts("==1234==   total heap usage: 10 allocs, 10 frees, 1,024 bytes allocated\n");
    vga_puts("==1234== \n");
    vga_puts("==1234== All heap blocks were freed -- no leaks are possible\n");
    vga_puts("==1234== \n");
    vga_puts("==1234== ERROR SUMMARY: 0 errors from 0 contexts\n");
}

/* lldb - LLVM debugger */
static void cmd_lldb(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("LLDB 17.0.0\n");
        vga_puts("Usage: lldb <program>\n");
        return;
    }
    vga_puts("(lldb) target create \""); vga_puts(args[1]); vga_puts("\"\n");
    vga_puts("Current executable set to '"); vga_puts(args[1]); vga_puts("' (x86_64).\n");
    vga_puts("(lldb) run\n");
    vga_puts("Process 1234 launched\n");
    vga_puts("Process 1234 exited with status = 0\n");
}

/* perf - performance analysis */
static void cmd_perf(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: perf [record|report|stat|top]\n");
        return;
    }
    if (strcmp(args[1], "stat") == 0) {
        vga_puts(" Performance counter stats for '");
        if (argc > 2) vga_puts(args[2]);
        vga_puts("':\n\n");
        vga_puts("         1,234,567      cycles\n");
        vga_puts("           456,789      instructions\n");
        vga_puts("            12,345      cache-misses\n");
        vga_puts("\n       0.001234567 seconds time elapsed\n");
    } else if (strcmp(args[1], "report") == 0) {
        vga_puts("Overhead  Command\n");
        vga_puts("  45.23%  "); vga_puts(args[2] ? args[2] : "app"); vga_puts("\n");
        vga_puts("  23.12%  libc.so.6\n");
        vga_puts("  12.45%  libpthread.so.0\n");
    } else {
        vga_puts("perf: '"); vga_puts(args[1]); vga_puts("' is not a perf command.\n");
    }
}

/* strace - system call trace (enhanced) */
static void cmd_strace_v2(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: strace <command>\n"); return; }
    vga_puts("execve(\""); vga_puts(args[1]); vga_puts("\", [\""); vga_puts(args[1]); vga_puts("\"], 0x7ffd) = 0\n");
    vga_puts("brk(NULL)                               = 0x5600\n");
    vga_puts("openat(AT_FDCWD, \"/lib/libc.so.6\", O_RDONLY) = 3\n");
    vga_puts("read(3, \"\\x7fELF\", 16)                 = 16\n");
    vga_puts("mmap(NULL, 123456, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f00\n");
    vga_puts("close(3)                                = 0\n");
    vga_puts("openat(AT_FDCWD, \"/etc/ld.so.cache\", O_RDONLY) = 3\n");
    vga_puts("access(\"/etc/ld.so.preload\", R_OK)      = -1 ENOENT\n");
    vga_puts("openat(AT_FDCWD, \"/lib/libm.so.6\", O_RDONLY) = 3\n");
    vga_puts("write(1, \"Hello\\n\", 6)                  = 6\n");
    vga_puts("exit_group(0)                           = ?\n");
    vga_puts("+++ exited with 0 +++\n");
}

/* vim - text editor */
static void cmd_vim(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("VIM - Vi IMproved 9.0\n");
        vga_puts("Usage: vim [file]\n");
        return;
    }
    vga_puts("~                     \n");
    vga_puts("~                     \n");
    vga_puts("\""); vga_puts(args[1]); vga_puts("\" 0L, 0C\n");
    vga_puts("Press ENTER or type command to continue\n");
}

/* nano - text editor */
static void cmd_nano(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("GNU nano 7.2\n");
        vga_puts("Usage: nano [file]\n");
        return;
    }
    vga_puts("  GNU nano 7.2             ");
    vga_puts(args[1]);
    vga_puts("\n");
    vga_puts("[ New File ]\n");
    vga_puts("^G Help    ^O Write   ^R Read    ^K Cut     ^J Justify\n");
    vga_puts("^X Exit    ^\\ Replace ^I Insert  ^U Paste   ^T To Spell\n");
}

/* emacs - text editor */
static void cmd_emacs(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("GNU Emacs 28.2\n");
        vga_puts("Usage: emacs [file]\n");
        return;
    }
    vga_puts("Loading /etc/emacs/emacs-startup.el (source)...\n");
    vga_puts("GNU Emacs 28.2\n");
    vga_puts("Buffer: "); vga_puts(args[1]); vga_puts("\n");
}

/* code - VS Code */
static void cmd_code(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Visual Studio Code 1.85.0\n");
        vga_puts("Usage: code [file|folder]\n");
        return;
    }
    vga_puts("Visual Studio Code 1.85.0\n");
    vga_puts("Opening "); vga_puts(args[1]); vga_puts("...\n");
}

/* subl - Sublime Text */
static void cmd_subl(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Sublime Text Build 4169\n");
        vga_puts("Usage: subl [file]\n");
        return;
    }
    vga_puts("Sublime Text Build 4169\n");
    vga_puts("Opening "); vga_puts(args[1]); vga_puts("...\n");
}

/* notepad++ - text editor */
static void cmd_notepadqq(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Notepadqq 2.0.0\n");
        vga_puts("Usage: notepadqq [file]\n");
        return;
    }
    vga_puts("Notepadqq 2.0.0\n");
    vga_puts("Opening "); vga_puts(args[1]); vga_puts("...\n");
}

/* svn - Subversion */
static void cmd_svn(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("svn, version 1.14.3\n");
        vga_puts("Usage: svn [checkout|update|commit|status|log|diff]\n");
        return;
    }
    if (strcmp(args[1], "checkout") == 0) {
        vga_puts("A    src/main.c\n");
        vga_puts("A    src/Makefile\n");
        vga_puts("Checked out revision 100.\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_puts("M       src/main.c\n");
        vga_puts("M       src/Makefile\n");
    } else if (strcmp(args[1], "commit") == 0) {
        vga_puts("Sending        src/main.c\n");
        vga_puts("Transmitting file data .\n");
        vga_puts("Committed revision 101.\n");
    } else if (strcmp(args[1], "log") == 0) {
        vga_puts("------------------------------------------------------------------------\n");
        vga_puts("r101 | admin | 2026-07-09 | 1 line\n\n");
        vga_puts("Updated main.c\n");
        vga_puts("------------------------------------------------------------------------\n");
    } else {
        vga_puts("svn: '"); vga_puts(args[1]); vga_puts("' is not a subcommand.\n");
    }
}

/* hg - Mercurial */
static void cmd_hg(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Mercurial Distributed SCM (version 6.5.2)\n");
        vga_puts("Usage: hg [init|clone|commit|push|pull|update|log|status]\n");
        return;
    }
    if (strcmp(args[1], "init") == 0) {
        vga_puts("updating the branch cache\n");
        vga_puts("initializing branch cache\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_puts("M src/main.c\n");
        vga_puts("M src/Makefile\n");
    } else if (strcmp(args[1], "log") == 0) {
        vga_puts("changeset:   100:abc123456789\n");
        vga_puts("user:        admin\n");
        vga_puts("date:        Thu Jul 09 00:00:00 2026 +0000\n");
        vga_puts("summary:     Updated main.c\n");
    } else {
        vga_puts("hg: '"); vga_puts(args[1]); vga_puts("' is not a Mercurial command.\n");
    }
}

/* p4 - Perforce */
static void cmd_p4(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Perforce - The Fast Software Configuration Management System\n");
        vga_puts("Usage: p4 [change|edit|submit|sync|where|files]\n");
        return;
    }
    if (strcmp(args[1], "where") == 0) {
        vga_puts("//depot/... //client/...\n");
    } else if (strcmp(args[1], "files") == 0) {
        vga_puts("//depot/src/main.c #123,125\n");
        vga_puts("//depot/src/Makefile #45,46\n");
    } else {
        vga_puts("p4: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* ffmpeg - multimedia framework (enhanced) */
static void cmd_ffmpeg(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("ffmpeg version 6.0\n");
        vga_puts("Usage: ffmpeg [-i input] [-c:v codec] [-c:a codec] output\n");
        return;
    }
    if (strcmp(args[1], "-version") == 0) {
        vga_puts("ffmpeg version 6.0-0ubuntu1\n");
        vga_puts("built with gcc 12.3.0\n");
        vga_puts("configuration: --enable-gpl --enable-libx264\n");
    } else if (strcmp(args[1], "-i") == 0 && argc > 2) {
        vga_puts("Input #0, ");
        vga_puts(args[2]);
        vga_puts(", from file '");
        if (argc > 3) vga_puts(args[3]);
        vga_puts("':\n");
        vga_puts("  Duration: 00:02:30.00, start: 0.000000\n");
        vga_puts("  Stream #0:0: Video: h264, yuv420p, 1920x1080\n");
        vga_puts("  Stream #0:1: Audio: aac, 44100 Hz, stereo\n");
    } else {
        vga_puts("ffmpeg: '"); vga_puts(args[1]); vga_puts("' is not an ffmpeg option.\n");
    }
}

/* ffprobe - multimedia analyzer */
static void cmd_ffprobe(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("ffprobe version 6.0\n");
        vga_puts("Usage: ffprobe [input]\n");
        return;
    }
    vga_puts("Input #0, from '"); vga_puts(args[1]); vga_puts("':\n");
    vga_puts("  Duration: 00:02:30.00\n");
    vga_puts("  Stream #0:0: Video: h264, yuv420p, 1920x1080, 30 fps\n");
    vga_puts("  Stream #0:1: Audio: aac, 44100 Hz, stereo, 128 kb/s\n");
}

/* ffplay - media player */
static void cmd_ffplay(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("ffplay version 6.0\n");
        vga_puts("Usage: ffplay [input]\n");
        return;
    }
    vga_puts("Playing: "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("Video: 1920x1080, Audio: 44100 Hz stereo\n");
    vga_puts("(Press q to quit)\n");
}

/* lame - MP3 encoder */
static void cmd_lame(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) {
        vga_puts("LAME 3.100\n");
        vga_puts("Usage: lame [options] <input.wav> <output.mp3>\n");
        return;
    }
    vga_puts("LAME 3.100 64-bit\n");
    vga_puts("Encoding "); vga_puts(args[1]); vga_puts(" to "); vga_puts(args[2]); vga_puts("\n");
    vga_puts("Encoding as 44.1 kHz, 128 kbps, joint-stereo\n");
    vga_puts("Done.\n");
}

/* sox - Swiss Army knife of audio */
static void cmd_sox(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("SoX 14.4.2\n");
        vga_puts("Usage: sox [input] [output] [effects]\n");
        return;
    }
    vga_puts("SoX 14.4.2: ");
    if (argc > 2) {
        vga_puts(args[1]); vga_puts(" -> "); vga_puts(args[2]); vga_puts("\n");
    } else {
        vga_puts(args[1]); vga_puts("\n");
    }
    vga_puts("Input File     : "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("Sample Rate    : 44100\n");
    vga_puts("Channels       : 2\n");
    vga_puts("Duration       : 00:03:25.00\n");
}

/* mediainfo - media file info */
static void cmd_mediainfo(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("MediaInfo 23.10\n");
        vga_puts("Usage: mediainfo <file>\n");
        return;
    }
    vga_puts("General\n");
    vga_puts("Complete name : "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("Format        : MPEG-4\n");
    vga_puts("File size     : 45.2 MiB\n");
    vga_puts("Duration      : 2 min 30 s\n");
    vga_puts("\nVideo\n");
    vga_puts("Format        : AVC (H.264)\n");
    vga_puts("Width         : 1920 pixels\n");
    vga_puts("Height        : 1080 pixels\n");
    vga_puts("Frame rate    : 30.000 FPS\n");
    vga_puts("\nAudio\n");
    vga_puts("Format        : AAC\n");
    vga_puts("Sample rate   : 44100 Hz\n");
    vga_puts("Channels      : 2\n");
}

/* exiftool - metadata reader */
static void cmd_exiftool(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("ExifTool version 12.60\n");
        vga_puts("Usage: exiftool [file]\n");
        return;
    }
    vga_puts("[File]          FileName                        : "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("[File]          FileSize                        : 4.5 MB\n");
    vga_puts("[File]          FileType                        : JPEG\n");
    vga_puts("[EXIF]          Make                            : Canon\n");
    vga_puts("[EXIF]          Model                           : EOS R5\n");
    vga_puts("[EXIF]          DateTimeOriginal                : 2026:07:09 12:00:00\n");
    vga_puts("[EXIF]          ExposureTime                    : 1/250\n");
    vga_puts("[EXIF]          FNumber                         : 2.8\n");
    vga_puts("[EXIF]          ISOSpeedRatings                 : 400\n");
}

/* imagemagick - image processing */
static void cmd_convert(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) {
        vga_puts("ImageMagick 7.1.1\n");
        vga_puts("Usage: convert [input] [output]\n");
        return;
    }
    vga_puts("ImageMagick 7.1.1 Q16 HDRI\n");
    vga_puts("Converting "); vga_puts(args[1]); vga_puts(" -> "); vga_puts(args[2]); vga_puts("\n");
    vga_puts("Done.\n");
}

/* gimp - image editor */
static void cmd_gimp(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("GIMP 2.10.36\n");
        vga_puts("Usage: gimp [file]\n");
        return;
    }
    vga_puts("GIMP 2.10.36\n");
    vga_puts("Opening "); vga_puts(args[1]); vga_puts("...\n");
}

/* inkscape - vector graphics editor */
static void cmd_inkscape(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Inkscape 1.3.2\n");
        vga_puts("Usage: inkscape [file]\n");
        return;
    }
    vga_puts("Inkscape 1.3.2\n");
    vga_puts("Opening "); vga_puts(args[1]); vga_puts("...\n");
}

/* audacity - audio editor */
static void cmd_audacity(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Audacity 3.4.2\n");
    vga_puts("Opening Audacity...\n");
}

/* blender - 3D creation suite */
static void cmd_blender(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Blender 4.0.2\n");
    vga_puts("Read blend: /tmp/untitled.blend\n");
}

/* gpg - encryption */
static void cmd_gpg(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("gpg (GnuPG) 2.4.3\n");
        vga_puts("Usage: gpg [--encrypt|--decrypt|--sign|--verify|--gen-key]\n");
        return;
    }
    if (strcmp(args[1], "--version") == 0) {
        vga_puts("gpg (GnuPG) 2.4.3\n");
        vga_puts("libgcrypt 1.10.3\n");
    } else if (strcmp(args[1], "--encrypt") == 0) {
        vga_puts("gpg: encryption with 'admin@byo-os' completed\n");
    } else if (strcmp(args[1], "--decrypt") == 0) {
        vga_puts("gpg: decrypted message\n");
    } else if (strcmp(args[1], "--sign") == 0) {
        vga_puts("gpg: signature created\n");
    } else if (strcmp(args[1], "--verify") == 0) {
        vga_puts("gpg: Good signature from \"admin <admin@byo-os>\"\n");
    } else if (strcmp(args[1], "--gen-key") == 0) {
        vga_puts("gpg: key generation complete\n");
    } else {
        vga_puts("gpg: '"); vga_puts(args[1]); vga_puts("' is not a valid option.\n");
    }
}

/* ssh-keygen - SSH key generation */
static void cmd_ssh_keygen(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("ssh-keygen: generating a new SSH key pair.\n");
        vga_puts("Enter file in which to save: /root/.ssh/id_rsa\n");
        vga_puts("Enter passphrase: [empty]\n");
        vga_puts("Your identification has been saved.\n");
        vga_puts("Your public key has been saved.\n");
        return;
    }
    vga_puts("ssh-keygen: generating new key pair.\n");
    vga_puts("Your public key has been saved in /root/.ssh/id_rsa.pub\n");
}

/* ssh-agent - SSH agent */
static void cmd_ssh_agent(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("SSH_AUTH_SOCK=/tmp/ssh-XXXX/agent.1234; export SSH_AUTH_SOCK;\n");
    vga_puts("SSH_AGENT_PID=1234; export SSH_AGENT_PID;\n");
    vga_puts("Agent pid 1234\n");
}

/* ssh-add - SSH key manager */
static void cmd_ssh_add(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Identity added: /root/.ssh/id_rsa (admin@byo-os)\n");
        return;
    }
    vga_puts("Identity added: "); vga_puts(args[1]); vga_puts(" (admin@byo-os)\n");
}

/* auditd - audit daemon */
static void cmd_auditd(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: auditd [start|stop|status|auditctl]\n");
        return;
    }
    if (strcmp(args[1], "start") == 0) {
        vga_puts("auditd started\n");
    } else if (strcmp(args[1], "stop") == 0) {
        vga_puts("auditd stopped\n");
    } else if (strcmp(args[1], "status") == 0) {
        vga_puts("auditd is running (pid 1234)\n");
        vga_puts("Audit rules loaded: 15\n");
        vga_puts("Events logged today: 1234\n");
    } else {
        vga_puts("auditd: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* aide - file integrity checker */
static void cmd_aide(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: aide [--init|--check]\n");
        return;
    }
    if (strcmp(args[1], "--init") == 0) {
        vga_puts("AIDE 0.18.2\n");
        vga_puts("Initialising AIDE database...\n");
        vga_puts("AIDE database initialized.\n");
    } else if (strcmp(args[1], "--check") == 0) {
        vga_puts("AIDE found no differences between database and filesystem.\n");
    } else {
        vga_puts("aide: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* lynis - security auditing */
static void cmd_lynis(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: lynis [audit system|show groups]\n");
        return;
    }
    if (strcmp(args[1], "audit") == 0 && argc > 2 && strcmp(args[2], "system") == 0) {
        vga_puts("[+] Initializing...\n");
        vga_puts("[+] Reading plugins...\n");
        vga_puts("[+] Starting security scanning...\n");
        vga_puts("[+] Performing tests...\n");
        vga_puts("=================================================================\n");
        vga_puts("  Lynis audit result\n");
        vga_puts("  Hardening score : 72/100\n");
        vga_puts("=================================================================\n");
    } else if (strcmp(args[1], "show") == 0 && argc > 2 && strcmp(args[2], "groups") == 0) {
        vga_puts("Available audit groups:\n");
        vga_puts("  boot\n  filesystems\n  kernel\n  memory\n  networking\n");
    } else {
        vga_puts("lynis: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* clamav - antivirus */
static void cmd_clamscan(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: clamscan [file|directory]\n");
        return;
    }
    vga_puts("Scanning "); vga_puts(args[1]); vga_puts("...\n");
    vga_puts(args[1]); vga_puts(": OK\n\n");
    vga_puts("----------- SCAN SUMMARY -----------\n");
    vga_puts("Known viruses: 10000000\n");
    vga_puts("Engine version: 1.2.0\n");
    vga_puts("Scanned files: 1\n");
    vga_puts("Infected files: 0\n");
}

/* rkhunter - rootkit detection */
static void cmd_rkhunter(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: rkhunter [--check|--update]\n");
        return;
    }
    if (strcmp(args[1], "--check") == 0) {
        vga_puts("[ Rootkit Hunter version 1.4.6 ]\n");
        vga_puts("Checking system commands...\n");
        vga_puts("  [OK] /bin/ls\n");
        vga_puts("  [OK] /bin/ps\n");
        vga_puts("  [OK] /usr/bin/top\n");
        vga_puts("System checks: 100 passed, 0 warnings\n");
    } else if (strcmp(args[1], "--update") == 0) {
        vga_puts("Checking for updates...\n");
        vga_puts("rkhunter: database is up to date.\n");
    } else {
        vga_puts("rkhunter: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* chkrootkit - rootkit detection */
static void cmd_chkrootkit(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("chkrootkit 0.5.7b\n");
    vga_puts("Checking `amd`... not found\n");
    vga_puts("Checking `basename`... not found\n");
    vga_puts("Checking `chfn`... not found\n");
    vga_puts("Checking `ls`... not found\n");
    vga_puts("Checking `netstat`... not found\n");
    vga_puts("Nothing suspicious found.\n");
}

/* apt - Debian package manager */
static void cmd_apt(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("apt 2.6.1 (i386)\n");
        vga_puts("Usage: apt [install|remove|update|upgrade|search|show|list]\n");
        return;
    }
    if (strcmp(args[1], "update") == 0) {
        vga_puts("Hit:1 http://deb.debian.org/debian bookworm InRelease\n");
        vga_puts("Reading package lists... Done\n");
        vga_puts("All packages are up to date.\n");
    } else if (strcmp(args[1], "install") == 0 && argc > 2) {
        vga_puts("Reading package lists... Done\n");
        vga_puts("Building dependency tree... Done\n");
        vga_puts("The following NEW packages will be installed:\n");
        vga_puts("  "); vga_puts(args[2]); vga_puts("\n");
        vga_puts("0 upgraded, 1 newly installed, 0 to remove.\n");
        vga_puts("Need to get 123 kB of archives.\n");
        vga_puts("Unpacking "); vga_puts(args[2]); vga_puts("...\n");
        vga_puts("Setting up "); vga_puts(args[2]); vga_puts(" ...\n");
    } else if (strcmp(args[1], "list") == 0) {
        vga_puts("Listing...\n");
        vga_puts("apt/stable,now 2.6.1 i386 [installed]\n");
        vga_puts("base-files/stable,now 12.4 i386 [installed]\n");
        vga_puts("bash/stable,now 5.2.15-2 i386 [installed]\n");
    } else if (strcmp(args[1], "search") == 0 && argc > 2) {
        vga_puts("Sorting... Done\n");
        vga_puts("Full Text Search... Done\n");
        vga_puts(args[2]); vga_puts("/stable 1.0-1 i386\n");
        vga_puts("  "); vga_puts(args[2]); vga_puts(" - description\n");
    } else if (strcmp(args[1], "upgrade") == 0) {
        vga_puts("Reading package lists... Done\n");
        vga_puts("Building dependency tree... Done\n");
        vga_puts("0 upgraded, 0 newly installed, 0 to remove.\n");
    } else if (strcmp(args[1], "show") == 0 && argc > 2) {
        vga_puts("Package: "); vga_puts(args[2]); vga_puts("\n");
        vga_puts("Version: 1.0-1\n");
        vga_puts("Priority: optional\n");
        vga_puts("Section: utils\n");
        vga_puts("Maintainer: Admin <admin@byo-os>\n");
        vga_puts("Installed-Size: 123\n");
    } else if (strcmp(args[1], "remove") == 0 && argc > 2) {
        vga_puts("Reading package lists... Done\n");
        vga_puts("The following packages will be REMOVED:\n");
        vga_puts("  "); vga_puts(args[2]); vga_puts("\n");
        vga_puts("0 upgraded, 0 newly installed, 1 to remove.\n");
    } else {
        vga_puts("E: Invalid operation "); vga_puts(args[1]); vga_puts("\n");
    }
}

/* dpkg - Debian package manager */
static void cmd_dpkg(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("dpkg 1.21.21\n");
        vga_puts("Usage: dpkg [-i|-l|-r|-s|-L]\n");
        return;
    }
    if (strcmp(args[1], "-l") == 0) {
        vga_puts("Desired=Unknown/Install/Remove/Purge/Hold\n");
        vga_puts("| Status=Not/Inst/Conf-files/Unpacked/halF-conf/Half-inst/trig-aWait/Trig-pend\n");
        vga_puts("|/ Err?=(none)/Reinst-required (Status,Err: uppercase=bad)\n");
        vga_puts("||/ Name           Version      Architecture Description\n");
        vga_puts("+++-==============-============-============-\n");
        vga_puts("ii  base-files     12.4         i386         Debian base system miscellaneous files\n");
        vga_puts("ii  bash           5.2.15-2     i386         GNU Bourne Again SHell\n");
    } else if (strcmp(args[1], "-i") == 0 && argc > 2) {
        vga_puts("Selecting previously unselected package "); vga_puts(args[2]); vga_puts(".\n");
        vga_puts("Unpacking "); vga_puts(args[2]); vga_puts(" ...\n");
        vga_puts("Setting up "); vga_puts(args[2]); vga_puts(" ...\n");
    } else if (strcmp(args[1], "-s") == 0 && argc > 2) {
        vga_puts("Package: "); vga_puts(args[2]); vga_puts("\n");
        vga_puts("Status: install ok installed\n");
        vga_puts("Priority: optional\n");
    } else {
        vga_puts("dpkg: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* rpm - RPM package manager */
static void cmd_rpm(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("RPM version 4.18.2\n");
        vga_puts("Usage: rpm [-i|-q|-qa|-U|-e]\n");
        return;
    }
    if (strcmp(args[1], "-qa") == 0) {
        vga_puts("bash-5.2.15-2.i386\n");
        vga_puts("coreutils-9.1-1.i386\n");
        vga_puts("glibc-2.36-9.i386\n");
    } else if (strcmp(args[1], "-q") == 0 && argc > 2) {
        vga_puts(args[2]); vga_puts("-1.0-1.i386\n");
    } else if (strcmp(args[1], "-i") == 0 && argc > 2) {
        vga_puts("Installing "); vga_puts(args[2]); vga_puts("...\n");
    } else {
        vga_puts("rpm: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* yum - RHEL package manager */
static void cmd_yum(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Usage: yum [install|remove|update|search|list|info]\n");
        return;
    }
    if (strcmp(args[1], "install") == 0 && argc > 2) {
        vga_puts("Loaded plugins: fastestmirror\n");
        vga_puts("Loading mirror speeds\n");
        vga_puts("Resolving Dependencies\n");
        vga_puts("Installing:\n");
        vga_puts("  "); vga_puts(args[2]); vga_puts("    noarch    1.0-1\n");
        vga_puts("Complete!\n");
    } else if (strcmp(args[1], "list") == 0) {
        vga_puts("Installed Packages\n");
        vga_puts("bash.i686        5.2.15-2    @baseos\n");
        vga_puts("coreutils.i686   9.1-1       @baseos\n");
    } else {
        vga_puts("yum: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* dnf - DNF package manager */
static void cmd_dnf(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("DNF 4.14.0\n");
    vga_puts("Usage: dnf [install|remove|update|search|list|info]\n");
}

/* pacman - Arch package manager */
static void cmd_pacman(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("pacman 6.0.2\n");
        vga_puts("Usage: pacman [-S|-R|-Q|-U]\n");
        return;
    }
    if (strcmp(args[1], "-Ss") == 0 && argc > 2) {
        vga_puts(args[2]); vga_puts("/"); vga_puts(args[2]); vga_puts(" 1.0-1\n");
        vga_puts("    "); vga_puts(args[2]); vga_puts(" - description\n");
    } else if (strcmp(args[1], "-Q") == 0) {
        vga_puts("bash 5.2.15-1\n");
        vga_puts("coreutils 9.1-1\n");
        vga_puts("glibc 2.38-1\n");
    } else {
        vga_puts("pacman: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* snap - Snap package manager */
static void cmd_snap(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("snap 2.61.2\n");
        vga_puts("Usage: snap [install|remove|list|info|find|enable|disable]\n");
        return;
    }
    if (strcmp(args[1], "list") == 0) {
        vga_puts("Name    Version  Rev    Tracking       Publisher\n");
        vga_puts("core22  20231123 10333  latest/stable  canonical**\n");
        vga_puts("firefox 121.0    3785   latest/stable  mozilla**\n");
    } else if (strcmp(args[1], "install") == 0 && argc > 2) {
        vga_puts(args[2]); vga_puts(" 1.0 from Canonical installed\n");
    } else {
        vga_puts("snap: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* flatpak - Flatpak package manager */
static void cmd_flatpak(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Flatpak 1.14.4\n");
        vga_puts("Usage: flatpak [install|remove|list|update|search]\n");
        return;
    }
    if (strcmp(args[1], "list") == 0) {
        vga_puts("Name                     Application ID              Version\n");
        vga_puts("Firefox                  org.mozilla.firefox         121.0\n");
        vga_puts("VS Code                  com.visualstudio.code       1.85.0\n");
    } else if (strcmp(args[1], "install") == 0 && argc > 2) {
        vga_puts("Installing "); vga_puts(args[2]); vga_puts("...\n");
        vga_puts("Installation complete.\n");
    } else {
        vga_puts("flatpak: '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* npm_v2 - Node.js package manager (enhanced) */
static void cmd_npm_v2(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("npm 10.2.3\n");
        vga_puts("Usage: npm [install|init|start|test|run|update|ls|outdated|publish|version]\n");
        return;
    }
    if (strcmp(args[1], "install") == 0 && argc > 2) {
        vga_puts("added 1 package in 2s\n");
        vga_puts("\n1 package is looking for funding\n");
        vga_puts("  run `npm fund` for details\n");
    } else if (strcmp(args[1], "ls") == 0) {
        vga_puts("myproject@1.0.0\n");
        vga_puts("+-- express@4.18.2\n");
        vga_puts("+-- lodash@4.17.21\n");
        vga_puts("+-- axios@1.6.2\n");
        vga_puts("+-- react@18.2.0\n");
    } else if (strcmp(args[1], "outdated") == 0) {
        vga_puts("Package     Current  Wanted  Latest  Location\n");
        vga_puts("express      4.18.2   4.18.2   4.19.0  myproject\n");
        vga_puts("react       18.2.0   18.2.0   18.3.0  myproject\n");
    } else if (strcmp(args[1], "init") == 0) {
        vga_puts("Wrote to /package.json\n");
    } else if (strcmp(args[1], "start") == 0) {
        vga_puts("> myproject@1.0.0 start\n");
        vga_puts("> node index.js\n");
        vga_puts("Server running on port 3000\n");
    } else if (strcmp(args[1], "test") == 0) {
        vga_puts("> myproject@1.0.0 test\n");
        vga_puts("> jest\n");
        vga_puts("PASS  tests/app.test.js\n");
        vga_puts("Test Suites: 1 passed, 1 total\n");
    } else if (strcmp(args[1], "publish") == 0) {
        vga_puts("npm notice Publishing to https://registry.npmjs.org/\n");
        vga_puts("+ myproject@1.0.0\n");
    } else if (strcmp(args[1], "version") == 0) {
        vga_puts("npm 10.2.3\n");
        vga_puts("node v20.10.0\n");
    } else {
        vga_puts("npm ERR! Unknown command: "); vga_puts(args[1]); vga_puts("\n");
    }
}
