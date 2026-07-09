const fs = require('fs');
const p = 'E:/aisystem/byo-os/kernel/shell.c';
let c = fs.readFileSync(p, 'utf8');

// Remove duplicate function definitions from batch 17
// These were already defined in batch 14/15/16
const dups = [
    'cmd_grafana_agent', 'cmd_vector', 'cmd_fluentd', 'cmd_fluentbit',
    'cmd_filebeat', 'cmd_logstash', 'cmd_kibana', 'cmd_telegraf',
    'cmd_containerruntime', 'cmd_crio', 'cmd_runc', 'cmd_crictl',
    'cmd_buildah', 'cmd_skopeo', 'cmd_mqtt_sub', 'cmd_mqtt_pub',
    'cmd_nsq', 'cmd_pulsar', 'cmd_kafka_connect', 'cmd_kcat'
];

let removed = 0;
for (const fn of dups) {
    // Remove function definition blocks
    const regex = new RegExp('\\nstatic void ' + fn + '\\(int argc, char args\\[\\]\\[CMD_MAX_LEN\\]\\) \\{[^}]*\\}\\n', 'g');
    const before = c.length;
    c = c.replace(regex, '');
    if (c.length < before) removed++;
}

// Also remove duplicate table entries
for (const fn of dups) {
    const regex2 = new RegExp('\\{[^}]*' + fn + '[^}]*\\},?\\s*', 'g');
    c = c.replace(regex2, '');
}

fs.writeFileSync(p, c, 'utf8');
console.log('Removed', removed, 'duplicate functions');
console.log('Lines:', c.split('\n').length);
