const fs = require('fs');
const c = fs.readFileSync('E:/aisystem/byo-os/kernel/shell.c', 'utf8');
const re = /"(\w+)"/g;
let m;
const cmds = new Set();
while (m = re.exec(c)) { if (c.includes('static void cmd_' + m[1])) cmds.add(m[1]); }
console.log('Total unique commands:', cmds.size);
console.log('File lines:', c.split('\n').length);
