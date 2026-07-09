with open('E:/aisystem/byo-os/kernel/fs.c', 'r', encoding='utf-8') as f:
    content = f.read()

# Fix fs_create_file - store data at correct offset
old_create = '''    if (content && size > 0) {
        memcpy(fs_data_area, content, size);
    }'''
new_create = '''    if (content && size > 0) {
        memcpy(fs_data_area + block * FS_BLOCK_SIZE, content, size);
    }'''
content = content.replace(old_create, new_create)

# Fix fs_read_file - read from correct offset
old_read = '''            if (copy_len > 0)
                memcpy(buf, fs_data_area + fs_entries[i].data_block * FS_BLOCK_SIZE, copy_len);'''
new_read = '''            if (copy_len > 0)
                memcpy(buf, fs_data_area + fs_entries[i].data_block * FS_BLOCK_SIZE, copy_len);'''
# This is already correct from the previous fix

with open('E:/aisystem/byo-os/kernel/fs.c', 'w', encoding='utf-8', newline='\n') as f:
    f.write(content)
print('Fixed fs_create_file with correct offset')