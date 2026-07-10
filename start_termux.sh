#!/data/data/com.termux/files/usr/bin/bash
# BYO-OS Termux 启动器
set -e
DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$DIR"
G='\033[1;32m' Y='\033[1;33m' B='\033[1;34m' C='\033[1;36m' N='\033[0m'
echo -e "${C}  BYO-OS 启动器 v2.0${N}"
if [ ! -f "$DIR/byo-os.iso" ]; then
    echo -e "${Y}[!] byo-os.iso 不存在，请先运行 install_termux.sh${N}"
    exit 1
fi
if ! command -v qemu-system-i386 &>/dev/null; then
    echo -e "${Y}[!] 请先运行: pkg install qemu-system-x86${N}"
    exit 1
fi
if ! command -v python3 &>/dev/null; then
    echo -e "${Y}[!] 请先运行: pkg install python${N}"
    exit 1
fi
pkill -f "qemu-system-i386.*byo-os" 2>/dev/null || true
pkill -f "gateway.py" 2>/dev/null || true
sleep 1
echo -e "${G}[1/3] 启动 QEMU...${N}"
qemu-system-i386 -cdrom "$DIR/byo-os.iso" -m 128 -serial tcp::4321,server,nowait -display sdl -accel tcg -vga std -name "BYO-OS" &
QEMU_PID=$!
sleep 2
echo -e "${G}[2/3] 启动 Web 面板...${N}"
python3 "$DIR/gateway.py" &
GW_PID=$!
sleep 1
echo -e "${G}[3/3] 启动完成!${N}"
echo -e "  ${B}Web 面板: http://localhost:7777${N}"
echo -e "  ${B}QEMU 虚拟机: 独立窗口${N}"
echo -e "  ${B}Ctrl+C 停止${N}"
cleanup() {
    echo -e "${Y}正在停止...${N}"
    kill $QEMU_PID 2>/dev/null; kill $GW_PID 2>/dev/null
    pkill -f "qemu-system-i386.*byo-os" 2>/dev/null
    pkill -f "gateway.py" 2>/dev/null
    exit 0
}
trap cleanup INT TERM
wait