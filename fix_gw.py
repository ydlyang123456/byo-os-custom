import re

path = 'E:/aisystem/byo-os/gateway.py'
with open(path, 'r', encoding='utf-8') as f:
    content = f.read()

# Increase default timeout from 3.0 to 8.0
content = content.replace('def send(self, cmd, timeout=3.0):', 'def send(self, cmd, timeout=8.0):')

with open(path, 'w', encoding='utf-8', newline='\n') as f:
    f.write(content)

print('Done: increased serial timeout to 8s')
