#!/data/data/com.termux/files/usr/bin/bash
# BYO-OS 停止 v3.0
if command -v byo &>/dev/null; then
    byo stop "$@"
    exit $?
fi

echo "停止 BYO-OS..."
pkill -f "qemu-system-i386.*byo-os" 2>/dev/null
pkill -f "gateway.py" 2>/dev/null
rm -f "$HOME/byo-os/byo-os.pid" "$HOME/byo-os/qemu.pid" "$HOME/byo-os/gateway.pid" 2>/dev/null
echo "已停止"