#!/data/data/com.termux/files/usr/bin/bash
# BYO-OS Termux 卸载
pkill -f "qemu-system-i386.*byo-os" 2>/dev/null
pkill -f "gateway.py" 2>/dev/null
sleep 1
rm -rf "$HOME/byo-os"
echo "卸载完成"