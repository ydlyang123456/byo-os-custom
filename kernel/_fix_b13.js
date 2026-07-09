const fs = require('fs');
const p = 'E:/aisystem/byo-os/kernel/shell.c';
let c = fs.readFileSync(p, 'utf8');

// Fix: cmd_tunctl missing closing brace
c = c.replace(
    'static void cmd_tunctl(int argc, char args[][CMD_MAX_LEN]) {\n    vga_puts("tunctl: TUN/TAP configuration\\n");\n\n\nstatic void cmd_socat',
    'static void cmd_tunctl(int argc, char args[][CMD_MAX_LEN]) {\n    vga_puts("tunctl: TUN/TAP configuration\\n");\n}\n\nstatic void cmd_socat'
);

fs.writeFileSync(p, c, 'utf8');
console.log('Fixed cmd_tunctl. Verifying...');
console.log('Has correct brace:', c.includes('tunctl: TUN/TAP configuration\\n");\\n}'));
