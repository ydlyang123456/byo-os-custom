#!/data/data/com.termux/files/usr/bin/bash
# BYO-OS 卸载 v3.0
echo "停止 BYO-OS..."
pkill -f "qemu-system-i386.*byo-os" 2>/dev/null
pkill -f "gateway.py" 2>/dev/null
sleep 1

echo "删除文件..."
rm -rf "$HOME/byo-os"

# Remove from PATH
rm -f "${PREFIX:-/data/data/com.termux/files/usr}/bin/byo" 2>/dev/null

# Remove aliases from .bashrc
sed -i '/# BYO-OS-ALIASES/,/^$/d' "$HOME/.bashrc" 2>/dev/null

echo "卸载完成"