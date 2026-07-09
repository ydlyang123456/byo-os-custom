with open('E:/aisystem/byo-os/kernel/fs.c', 'r', encoding='utf-8') as f:
    content = f.read()

# Fix fs_read_file - add memcpy before return 0
old = '''            memset(buf, 0, max_len);
            return 0;'''
new = '''            memset(buf, 0, max_len);
            if (copy_len > 0)
                memcpy(buf, fs_entries[i].data, copy_len);
            return copy_len;'''
content = content.replace(old, new)

with open('E:/aisystem/byo-os/kernel/fs.c', 'w', encoding='utf-8', newline='\n') as f:
    f.write(content)
print('Fixed fs_read_file')