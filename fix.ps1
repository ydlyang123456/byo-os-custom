#!/bin/bash
cd /mnt/e/aisystem/byo-os
find . -name "*.c" -o -name "*.h" | xargs sed -i 's/\r$//' 2>/dev/null
python3 -c "
import re
with open('kernel/net.c','r') as f: c = f.read()
c = c.replace('ne2000_init();', 'int ne_st = ne2000_init();')
c = c.replace('arp_request(net_gw);', 'if (ne_st == 0) arp_request(net_gw);')
with open('kernel/net.c','w') as f: f.write(c)
print('net.c patched')
"
