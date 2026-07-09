const fs = require('fs');
const p = 'E:/aisystem/byo-os/kernel/shell.c';
let c = fs.readFileSync(p, 'utf8');

// Fix cmd_dust missing closing brace
c = c.replace(
    'static void cmd_dust(int argc, char args[][CMD_MAX_LEN]) {\n    vga_puts("dust: disk usage\\n");\n\nstatic void cmd_duuf',
    'static void cmd_dust(int argc, char args[][CMD_MAX_LEN]) {\n    vga_puts("dust: disk usage\\n");\n}\n\nstatic void cmd_duuf'
);

// Fix cmdborg -> cmd_borg (if exists as cmdborg)
c = c.replace('static void cmdborg(', 'static void cmd_borg_adv(');

fs.writeFileSync(p, c, 'utf8');
console.log('Fixed cmd_dust');
