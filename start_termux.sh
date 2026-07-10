#!/data/data/com.termux/files/usr/bin/bash
# BYO-OS 启动器 v3.0
# 如果安装了 byo 命令，直接委托
if command -v byo &>/dev/null; then
    byo start "$@"
    exit $?
fi

DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$DIR"

RED='\033[1;31m' GRN='\033[1;32m' YLW='\033[1;33m' BLU='\033[1;34m' CYN='\033[1;36m' BLD='\033[1m' RST='\033[0m'

echo -e "${CYN}  BYO-OS 启动器 v3.0${RST}"

# Pre-flight checks
for cmd in qemu-system-i386 python3; do
    if ! command -v "$cmd" &>/dev/null; then
        echo -e "${RED}缺少 $cmd，请先运行 install_termux.sh${RST}"
        exit 1
    fi
done

if [ ! -f "$DIR/byo-os.iso" ]; then
    echo -e "${RED}byo-os.iso 不存在!${RST}"
    exit 1
fi

# Stop existing instances
pkill -f "qemu-system-i386.*byo-os" 2>/dev/null || true
pkill -f "gateway.py" 2>/dev/null || true
sleep 1

# Start QEMU (headless in Termux, SDL if display available)
echo -e "${GRN}[1/2] 启动 QEMU 虚拟机...${RST}"
DISPLAY_FLAG="-display none"
if [ -n "${DISPLAY:-}" ] && [ "$DISPLAY" != ":0" ] 2>/dev/null; then
    DISPLAY_FLAG="-display sdl"
fi

qemu-system-i386 \
    -cdrom "$DIR/byo-os.iso" \
    -m 128 \
    -serial tcp::4321,server,nowait \
    $DISPLAY_FLAG \
    -accel tcg \
    -vga std \
    -name "BYO-OS" &
QEMU_PID=$!
echo "$QEMU_PID" > "$DIR/qemu.pid"
sleep 2

if ! kill -0 "$QEMU_PID" 2>/dev/null; then
    echo -e "${RED}QEMU 启动失败!${RST}"
    exit 1
fi
echo -e "${GRN}  QEMU 已启动 (PID: $QEMU_PID)${RST}"

# Start Web Gateway
echo -e "${GRN}[2/2] 启动 Web 面板...${RST}"
python3 "$DIR/gateway.py" &
GW_PID=$!
echo "$GW_PID" > "$DIR/gateway.pid"
sleep 1

echo "$QEMU_PID $GW_PID" > "$DIR/byo-os.pid"

echo ""
echo -e "${GRN}╔═══════════════════════════════════════╗${RST}"
echo -e "${GRN}║  BYO-OS 已启动!                      ║${RST}"
echo -e "${GRN}║  Web 面板: ${BLU}http://localhost:7777${GRN}    ║${RST}"
echo -e "${GRN}║  停止: ${YLW}Ctrl+C${RST}${GRN} 或运行 byo stop      ║${RST}"
echo -e "${GRN}╚═══════════════════════════════════════╝${RST}"

cleanup() {
    echo -e "\n${YLW}停止 BYO-OS...${RST}"
    kill $QEMU_PID 2>/dev/null
    kill $GW_PID 2>/dev/null
    pkill -f "qemu-system-i386.*byo-os" 2>/dev/null
    pkill -f "gateway.py" 2>/dev/null
    rm -f "$DIR/byo-os.pid" "$DIR/qemu.pid" "$DIR/gateway.pid"
    echo -e "${GRN}已停止${RST}"
    exit 0
}
trap cleanup INT TERM

wait