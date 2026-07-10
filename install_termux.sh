#!/data/data/com.termux/files/usr/bin/bash
# ============================================================
#   BYO-OS 一键安装器 v3.0
#   智能检测 · 架构适配 · 断点续传 · 自动编译
#   用法: curl -sL https://raw.githubusercontent.com/.../install.sh | bash
# ============================================================
set -euo pipefail

INSTALL_DIR="$HOME/byo-os"
REPO="ydlyang123456/byo-os-custom"
RAW="https://raw.githubusercontent.com/$REPO/main"
API="https://api.github.com/repos/$REPO/releases/latest"

RED='\033[1;31m' GREEN='\033[1;32m' YELLOW='\033[1;33m'
BLUE='\033[1;34m' CYAN='\033[1;36m' BOLD='\033[1m' DIM='\033[2m' RESET='\033[0m'

ok()   { echo -e "  ${GREEN}✓${RESET} $1"; }
warn() { echo -e "  ${YELLOW}!${RESET} $1"; }
fail() { echo -e "  ${RED}✗${RESET} $1"; exit 1; }
info() { echo -e "  ${BLUE}→${RESET} $1"; }

# --- Banner ---
echo -e "${CYAN}"
echo "  ╔═══════════════════════════════════════════════════╗"
echo "  ║                                                   ║"
echo "  ║     ╦  ╦╦╔═╗╔═╗╦═╗╔╦╗╔═╗╔═╗╔╦╗                  ║"
echo "  ║     ╚╗╔╝║╠╣ ╠╦╝╠╦╝ ║ ║╣ ╠═╣║                    ║"
echo "  ║      ╚╝ ╚╚═╝╩╚═╩╚═ ╩ ╚═╝╩ ╩╩                    ║"
echo "  ║         Build Your Own OS  v3.0                   ║"
echo "  ║     纯手写 x86 操作系统 · Termux 一键安装        ║"
echo "  ║                                                   ║"
echo "  ╚═══════════════════════════════════════════════════╝"
echo -e "${RESET}"

# --- Step 1: Environment Check ---
echo -e "${BOLD}[1/7] 环境检测${RESET}"

if [ -d "/data/data/com.termux" ]; then
    ok "Termux 环境"
else
    warn "非 Termux 环境，继续安装（部分功能可能受限）"
fi

ARCH=$(uname -m)
case "$ARCH" in
    aarch64|arm64) ok "架构: $ARCH (ARM64)" ;;
    armv7*|armhf)  warn "架构: $ARCH (ARM32) - 性能可能较差" ;;
    x86_64)        ok "架构: $ARCH (x86_64)" ;;
    *)             warn "架构: $ARCH (未知)" ;;
esac

MEM_FREE=$(free -m 2>/dev/null | awk '/^Mem:/{print $7}' || echo "?")
ok "可用内存: ${MEM_FREE}MB"

# --- Step 2: Package Manager ---
echo ""
echo -e "${BOLD}[2/7] 包管理器${RESET}"

if command -v pkg &>/dev/null; then
    PM="pkg"
elif command -v apt &>/dev/null; then
    PM="apt"
elif command -v pacman &>/dev/null; then
    PM="pacman"
else
    fail "未找到包管理器（pkg/apt/pacman）"
fi
ok "使用: $PM"

# --- Step 3: Dependencies ---
echo ""
echo -e "${BOLD}[3/7] 安装依赖${RESET}"

DEPS_NEEDED=()

check_dep() {
    local name="$1" pkg_name="${2:-$1}"
    if command -v "$name" &>/dev/null; then
        ok "$name 已安装"
    else
        warn "$name 缺少，将安装"
        DEPS_NEEDED+=("$pkg_name")
    fi
}

check_dep "git"
check_dep "curl"
check_dep "python3" "python"
check_dep "qemu-system-i386" "qemu-system-x86"
check_dep "nasm" "nasm"
check_dep "gcc" "clang"
check_dep "make"
check_dep "jq"

if [ ${#DEPS_NEEDED[@]} -gt 0 ]; then
    info "安装 ${#DEPS_NEEDED[@]} 个依赖..."
    $PM update -y 2>/dev/null
    for dep in "${DEPS_NEEDED[@]}"; do
        info "  安装 $dep..."
        $PM install -y "$dep" 2>/dev/null || warn "$dep 安装失败，跳过"
    done
else
    ok "所有依赖已就绪"
fi

# Verify critical deps
for cmd in qemu-system-i386 python3 git curl; do
    command -v "$cmd" &>/dev/null || fail "关键依赖 $cmd 安装失败"
done

# --- Step 4: Clone / Update Repo ---
echo ""
echo -e "${BOLD}[4/7] 获取 BYO-OS 源码${RESET}"

if [ -d "$INSTALL_DIR/.git" ]; then
    info "仓库已存在，拉取最新..."
    cd "$INSTALL_DIR"
    git pull --quiet 2>/dev/null && ok "源码已更新" || warn "更新失败，使用现有版本"
else
    info "克隆仓库..."
    git clone --depth 1 "https://github.com/$REPO.git" "$INSTALL_DIR"
    cd "$INSTALL_DIR"
    ok "源码获取完成"
fi

# --- Step 5: Download ISO ---
echo ""
echo -e "${BOLD}[5/7] ISO 镜像${RESET}"

ISO_PATH="$INSTALL_DIR/byo-os.iso"

if [ -f "$ISO_PATH" ]; then
    ISO_SIZE=$(stat -c%s "$ISO_PATH" 2>/dev/null || stat -f%z "$ISO_PATH" 2>/dev/null || echo 0)
    if [ "$ISO_SIZE" -gt 1000000 ]; then
        ok "ISO 已存在: $(( ISO_SIZE / 1024 / 1024 ))MB"
    else
        warn "ISO 文件异常，重新下载..."
        rm -f "$ISO_PATH"
    fi
fi

if [ ! -f "$ISO_PATH" ]; then
    info "从 GitHub Releases 下载 ISO..."
    # Try latest release
    ISO_URL=$(curl -s "$API" | python3 -c "
import sys,json
try:
    d=json.load(sys.stdin)
    for a in d.get('assets',[]):
        if 'byo-os' in a['name'] and a['name'].endswith('.iso'):
            print(a['browser_download_url']); break
except: pass
" 2>/dev/null)

    if [ -n "$ISO_URL" ]; then
        info "下载: $ISO_URL"
        curl -L --progress-bar -o "$ISO_PATH" "$ISO_URL" 2>&1
        if [ -f "$ISO_PATH" ] && [ "$(stat -c%s "$ISO_PATH" 2>/dev/null || stat -f%z "$ISO_PATH" 2>/dev/null || echo 0)" -gt 1000000 ]; then
            ok "ISO 下载完成"
        else
            warn "ISO 下载失败或文件不完整"
        fi
    else
        warn "未找到 Release ISO，将从源码构建..."
    fi
fi

# --- Step 6: Build (if no ISO) ---
echo ""
echo -e "${BOLD}[6/7] 编译检查${RESET}"

if [ ! -f "$ISO_PATH" ]; then
    if command -v nasm &>/dev/null && command -v gcc &>/dev/null; then
        info "从源码编译..."
        cd "$INSTALL_DIR"
        bash build.sh 2>&1 | tail -5
        if [ -f "$ISO_PATH" ]; then
            ok "编译成功"
        else
            fail "编译失败"
        fi
    else
        fail "无法编译: 缺少 nasm/gcc"
    fi
else
    ok "ISO 就绪，跳过编译"
fi

# --- Step 7: Install Management Script ---
echo ""
echo -e "${BOLD}[7/7] 安装管理命令${RESET}"

# Create unified 'byo' command
cat > "$INSTALL_DIR/byo" << 'BYOCMD'
#!/data/data/com.termux/files/usr/bin/bash
# BYO-OS unified management command
DIR="$(cd "$(dirname "$(readlink -f "$0" 2>/dev/null || realpath "$0" 2>/dev/null || echo "$0")")" && pwd)"
cd "$DIR" 2>/dev/null || cd "$HOME/byo-os"

RED='\033[1;31m' GRN='\033[1;32m' YLW='\033[1;33m' BLU='\033[1;34m' CYN='\033[1;36m' BLD='\033[1m' RST='\033[0m'

byo_start() {
    if [ -f "$HOME/byo-os/byo-os.pid" ]; then
        local pid=$(cat "$HOME/byo-os/byo-os.pid")
        if kill -0 "$pid" 2>/dev/null; then
            echo -e "${YLW}BYO-OS 已在运行中 (PID: $pid)${RST}"
            echo -e "${BLU}Web 面板: http://localhost:7777${RST}"
            return 0
        fi
        rm -f "$HOME/byo-os/byo-os.pid"
    fi

    echo -e "${CYN}启动 BYO-OS...${RST}"

    # Kill stale processes
    pkill -f "qemu-system-i386.*byo-os" 2>/dev/null || true
    pkill -f "gateway.py" 2>/dev/null || true
    sleep 1

    # Check ISO
    if [ ! -f "$HOME/byo-os/byo-os.iso" ]; then
        echo -e "${RED}byo-os.iso 不存在!${RST}"
        echo -e "${YLW}运行: byo update${RST}"
        return 1
    fi

    # Check/display mode
    DISPLAY_ARG="-display none"
    if command -v termux-open-url &>/dev/null || [ -d "/data/data/com.termux" ]; then
        DISPLAY_ARG="-display none"
    fi

    # Start QEMU
    echo -e "${GRN}[1/2] 启动 QEMU 虚拟机...${RST}"
    qemu-system-i386 \
        -cdrom "$HOME/byo-os/byo-os.iso" \
        -m 128 \
        -serial tcp::4321,server,nowait \
        $DISPLAY_ARG \
        -accel tcg \
        -vga std \
        -name "BYO-OS" &
    QEMU_PID=$!
    echo "$QEMU_PID" > "$HOME/byo-os/qemu.pid"
    sleep 2

    # Check QEMU started
    if ! kill -0 "$QEMU_PID" 2>/dev/null; then
        echo -e "${RED}QEMU 启动失败!${RST}"
        return 1
    fi
    echo -e "${GRN}  QEMU 已启动 (PID: $QEMU_PID)${RST}"

    # Start Web Gateway
    echo -e "${GRN}[2/2] 启动 Web 面板...${RST}"
    python3 "$HOME/byo-os/gateway.py" &
    GW_PID=$!
    echo "$GW_PID" > "$HOME/byo-os/gateway.pid"
    sleep 1

    echo "$QEMU_PID $GW_PID" > "$HOME/byo-os/byo-os.pid"

    echo ""
    echo -e "${GRN}╔═══════════════════════════════════════╗${RST}"
    echo -e "${GRN}║  BYO-OS 已启动!                      ║${RST}"
    echo -e "${GRN}║                                       ║${RST}"
    echo -e "${GRN}║  Web 面板: ${BLU}http://localhost:7777${GRN}    ║${RST}"
    echo -e "${GRN}║  QEMU PID: ${QEMU_PID}${GRN}                      ║${RST}"
    echo -e "${GRN}║  Gateway PID: ${GW_PID}${GRN}                   ║${RST}"
    echo -e "${GRN}║                                       ║${RST}"
    echo -e "${GRN}║  停止: ${YLW}byo stop${GRN}                     ║${RST}"
    echo -e "${GRN}╚═══════════════════════════════════════╝${RST}"

    # Wait for gateway
    wait $GW_PID 2>/dev/null
}

byo_stop() {
    echo -e "${YLW}停止 BYO-OS...${RST}"
    if [ -f "$HOME/byo-os/gateway.pid" ]; then
        kill "$(cat "$HOME/byo-os/gateway.pid")" 2>/dev/null
        rm -f "$HOME/byo-os/gateway.pid"
    fi
    if [ -f "$HOME/byo-os/qemu.pid" ]; then
        kill "$(cat "$HOME/byo-os/qemu.pid")" 2>/dev/null
        rm -f "$HOME/byo-os/qemu.pid"
    fi
    rm -f "$HOME/byo-os/byo-os.pid"
    pkill -f "qemu-system-i386.*byo-os" 2>/dev/null
    pkill -f "gateway.py" 2>/dev/null
    echo -e "${GRN}已停止${RST}"
}

byo_status() {
    echo -e "${CYN}BYO-OS 状态:${RST}"
    if [ -f "$HOME/byo-os/byo-os.pid" ]; then
        local pids=$(cat "$HOME/byo-os/byo-os.pid")
        local qemu_pid=$(echo $pids | awk '{print $1}')
        local gw_pid=$(echo $pids | awk '{print $2}')
        if kill -0 "$qemu_pid" 2>/dev/null; then
            echo -e "  QEMU:     ${GRN}运行中${RST} (PID: $qemu_pid)"
        else
            echo -e "  QEMU:     ${RED}已停止${RST}"
        fi
        if kill -0 "$gw_pid" 2>/dev/null; then
            echo -e "  Gateway:  ${GRN}运行中${RST} (PID: $gw_pid)"
        else
            echo -e "  Gateway:  ${RED}已停止${RST}"
        fi
    else
        echo -e "  进程:     ${RED}未运行${RST}"
    fi
    if [ -f "$HOME/byo-os/byo-os.iso" ]; then
        local sz=$(stat -c%s "$HOME/byo-os/byo-os.iso" 2>/dev/null || stat -f%z "$HOME/byo-os/byo-os.iso" 2>/dev/null || echo 0)
        echo -e "  ISO:      ${GRN}$(( sz / 1024 / 1024 ))MB${RST}"
    else
        echo -e "  ISO:      ${RED}不存在${RST}"
    fi
    local ver=$(git describe --tags --always 2>/dev/null || echo "unknown")
    echo -e "  版本:     $ver"
}

byo_update() {
    echo -e "${CYN}更新 BYO-OS...${RST}"
    cd "$HOME/byo-os"
    git pull --quiet 2>/dev/null
    # Re-download ISO
    rm -f byo-os.iso
    local api="https://api.github.com/repos/ydlyang123456/byo-os-custom/releases/latest"
    local url=$(curl -s "$api" | python3 -c "
import sys,json
try:
    d=json.load(sys.stdin)
    for a in d.get('assets',[]):
        if 'byo-os' in a['name'] and a['name'].endswith('.iso'):
            print(a['browser_download_url']); break
except: pass
" 2>/dev/null)
    if [ -n "$url" ]; then
        curl -L --progress-bar -o byo-os.iso "$url"
        echo -e "${GRN}更新完成${RST}"
    else
        echo -e "${YLW}未找到新 ISO${RST}"
    fi
}

byo_logs() {
    if [ -f "$HOME/byo-os/gateway.pid" ]; then
        echo -e "${CYN}Web Gateway 日志:${RST}"
        # gateway.py prints to stdout, we can check if it's running
        local gw_pid=$(cat "$HOME/byo-os/gateway.pid")
        if kill -0 "$gw_pid" 2>/dev/null; then
            echo -e "${GRN}Gateway 正在运行 (PID: $gw_pid)${RST}"
        fi
    fi
    echo -e "${CYN}QEMU 串口日志:${RST}"
    echo -e "  ${BLU}http://localhost:7777/terminal${RST} 查看实时输出"
}

byo_help() {
    echo -e "${CYN}BYO-OS 管理命令 v3.0${RST}"
    echo ""
    echo "  ${BLU}byo start${RST}    启动 BYO-OS (QEMU + Web 面板)"
    echo "  ${BLU}byo stop${RST}     停止所有进程"
    echo "  ${BLU}byo restart${RST}  重启"
    echo "  ${BLU}byo status${RST}   查看运行状态"
    echo "  ${BLU}byo update${RST}   更新源码和 ISO"
    echo "  ${BLU}byo logs${RST}     查看日志"
    echo "  ${BLU}byo panel${RST}    在浏览器中打开 Web 面板"
    echo "  ${BLU}byo build${RST}    从源码编译"
    echo "  ${BLU}byo uninstall${RST} 卸载 BYO-OS"
    echo ""
}

case "${1:-help}" in
    start)    byo_start ;;
    stop)     byo_stop ;;
    restart)  byo_stop; sleep 1; byo_start ;;
    status)   byo_status ;;
    update)   byo_update ;;
    logs)     byo_logs ;;
    panel)
        echo -e "${BLU}打开 Web 面板: http://localhost:7777${RST}"
        if command -v termux-open-url &>/dev/null; then
            termux-open-url "http://localhost:7777"
        fi
        ;;
    build)
        cd "$HOME/byo-os" && bash build.sh
        ;;
    uninstall)
        read -p "确定卸载 BYO-OS? [y/N] " confirm
        if [ "$confirm" = "y" ] || [ "$confirm" = "Y" ]; then
            byo_stop
            rm -rf "$HOME/byo-os"
            echo -e "${GRN}卸载完成${RST}"
        fi
        ;;
    help|-h|--help) byo_help ;;
    *)
        echo -e "${RED}未知命令: $1${RST}"
        byo_help
        ;;
esac
BYOCMD
chmod +x "$INSTALL_DIR/byo"

# Symlink to PATH
if [ -d "$PREFIX/bin" ] || [ -d "/data/data/com.termux/files/usr/bin" ]; then
    BIN_DIR="${PREFIX:-/data/data/com.termux/files/usr}/bin"
    ln -sf "$INSTALL_DIR/byo" "$BIN_DIR/byo" 2>/dev/null && ok "命令 'byo' 已添加到 PATH" || {
        warn "无法添加到 PATH，请手动添加:"
        echo -e "    ${BLU}export PATH=\"\$HOME/byo-os:\$PATH\"${RST}"
    }
else
    warn "未找到 bin 目录，手动添加 PATH:"
    echo -e "    ${BLU}export PATH=\"\$HOME/byo-os:\$PATH\"${RST}"
fi

# Setup .bashrc aliases
PROFILE="$HOME/.bashrc"
MARKER="# BYO-OS-ALIASES"
if ! grep -q "$MARKER" "$PROFILE" 2>/dev/null; then
    cat >> "$PROFILE" << ALIASES

$MARKER
export PATH="\$HOME/byo-os:\$PATH"
alias bs='byo start'
alias bss='byo stop'
alias bst='byo status'
alias bu='byo update'
ALIASES
    ok ".bashrc 已更新"
fi

echo ""
echo -e "${GREEN}╔═══════════════════════════════════════════════════╗${RESET}"
echo -e "${GREEN}║  ✅ BYO-OS 安装完成!                             ║${RESET}"
echo -e "${GREEN}║                                                   ║${RESET}"
echo -e "${GREEN}║  ${BOLD}快速命令:${RESET}${GREEN}                                     ║${RESET}"
echo -e "${GREEN}║                                                   ║${RESET}"
echo -e "${GREEN}║  ${BOLD}byo start${RESET}   启动 (QEMU + Web 面板)        ${GREEN}║${RESET}"
echo -e "${GREEN}║  ${BOLD}byo stop${RESET}    停止                           ${GREEN}║${RESET}"
echo -e "${GREEN}║  ${BOLD}byo status${RESET}  查看状态                       ${GREEN}║${RESET}"
echo -e "${GREEN}║  ${BOLD}byo update${RESET}  更新                           ${GREEN}║${RESET}"
echo -e "${GREEN}║  ${BOLD}byo help${RESET}    查看所有命令                   ${GREEN}║${RESET}"
echo -e "${GREEN}║                                                   ║${RESET}"
echo -e "${GREEN}║  ${BOLD}Web 面板: http://localhost:7777${RESET}             ${GREEN}║${RESET}"
echo -e "${GREEN}║                                                   ║${RESET}"
echo -e "${GREEN}║  ${BOLD}bs${RESET} = start  ${BOLD}bss${RESET} = stop  ${BOLD}bst${RESET} = status     ${GREEN}║${RESET}"
echo -e "${GREEN}║                                                   ║${RESET}"
echo -e "${GREEN}╚═══════════════════════════════════════════════════╝${RESET}"
echo ""
echo -e "${DIM}重启 Termux 后快捷命令生效${RESET}"