const fs = require('fs');
const p = 'E:/aisystem/byo-os/kernel/shell.c';
let c = fs.readFileSync(p, 'utf8');

// Fix: cmd.telegram -> cmd_telegram (dots not allowed in C function names)
c = c.replace('static void cmd.telegram(', 'static void cmd_telegram(');
c = c.replace('cmd.telegram', 'cmd_telegram');

// Also fix cmdgrafana_on -> cmd_grafana_on
c = c.replace('static void cmdgrafana_on(', 'static void cmd_grafana_on(');

fs.writeFileSync(p, c, 'utf8');
console.log('Fixed cmd.telegram and cmdgrafana_on');
