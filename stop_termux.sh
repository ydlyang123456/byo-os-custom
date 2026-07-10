#!/data/data/com.termux/files/usr/bin/bash
# BYO-OS Termux 停止
pkill -f "qemu-system-i386.*byo-os" 2>/dev/null
pkill -f "gateway.py" 2>/dev/null
echo "BYO-OS 已停止"