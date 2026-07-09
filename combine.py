import sys
# Read parts and combine
parts = []
for i in range(1, 20):
    try:
        with open(f'E:/aisystem/byo-os/p{i}.c', 'r') as f:
            parts.append(f.read())
    except:
        break
with open('E:/aisystem/byo-os/kernel/shell.c', 'w', encoding='utf-8', newline='\n') as f:
    f.write('\n'.join(parts))
print(f'Combined {len(parts)} parts into shell.c')