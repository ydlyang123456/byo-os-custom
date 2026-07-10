#!/data/data/com.termux/files/usr/bin/bash
# ============================================================
#   BYO-OS - Termux 一键安装脚本
#   用法: bash install_termux.sh
# ============================================================
set -e

INSTALL_DIR="$HOME/byo-os"
REPO="ydlyang123456/byo-os-custom"
API="https://api.github.com/repos/$REPO/releases/latest"

R='\033[1;31m' G='\033[1;32m' Y='\033[1;33m' B='\033[1;34m' C='\033[1;36m' N='\033[0m'

banner() {
    echo -e "${C}"
    echo "  ╔══════════════════════════════════════════════╗"
    echo "  ║       BYO-OS Termux Installer v2.0          ║"
    echo "  ║     纯手写 x86 操作系统 - 一键安装          ║"
    echo "  ╚══════════════════════════════════════════════╝"
    echo -e "${N}"
}

check_termux() {
    if [ -d "/data/data/com.termux" ]; then
        echo -e "${G}[✓]${N} 检测到 Termux 环境"
    else
        echo -e "${Y}[!]${N} 未检测到 Termux，此脚本专为 Termux 设计"
        echo -e "${Y}[!]${N} 其他系统请使用 build.sh"
        exit 1
    fi
}

install_deps() {
    echo -e "${B}[1/5]${N} 更新包管理器..."
    pkg update -y 2>/dev/null || apt update -y

    echo -e "${B}[2/5]${N} 安装依赖包..."
    pkg install -y qemu-system-x86 2>/dev/null || apt install -y qemu-system-x86
    pkg install -y python 2>/dev/null || apt install -y python
    pkg install -y git 2>/dev/null || apt install -y git
    pkg install -y curl 2>/dev/null || apt install -y curl
    echo -e "${G}[✓]${N} 依赖安装完成"
}

clone_repo() {
    echo -e "${B}[3/5]${N} 获取 BYO-OS 文件..."
    if [ -d "$INSTALL_DIR" ]; then
        echo -e "${Y}[~]${N} 目录已存在，更新中..."
        cd "$INSTALL_DIR"
        git pull --quiet 2>/dev/null || true
    else
        echo -e "${Y}[~]${N} 克隆仓库..."
        git clone "https://github.com/$REPO.git" "$INSTALL_DIR"
        cd "$INSTALL_DIR"
    fi
    echo -e "${G}[✓]${N} 文件已就绪: $INSTALL_DIR"
}

download_iso() {
    echo -e "${B}[4/5]${N} 检查 ISO 镜像..."
    if [ -f "$INSTALL_DIR/byo-os.iso" ]; then
        ISO_SIZE=$(stat -c%s "$INSTALL_DIR/byo-os.iso" 2>/dev/null || stat -f%z "$INSTALL_DIR/byo-os.iso" 2>/dev/null || echo 0)
        echo -e "${G}[✓]${N} ISO 已存在: $(( ISO_SIZE / 1024 / 1024 ))MB"
    else
        echo -e "${Y}[~]${N} 从 GitHub Releases 下载 ISO..."
        ISO_URL=$(curl -s "$API" | grep -o '"browser_download_url": *"[^"]*byo-os\.iso"' | head -1 | sed 's/.*"browser_download_url": *"//;s/"//')
        if [ -n "$ISO_URL" ]; then
            curl -L -o "$INSTALL_DIR/byo-os.iso" "$ISO_URL"
            echo -e "${G}[✓]${N} ISO 下载完成"
        else
            echo -e "${R}[✗]${N} 无法获取 ISO，请手动编译"
        fi
    fi
}

create_scripts() {
    echo -e "${B}[5/5]${N} 创建启动脚本..."
    
    # start_termux.sh
    cat > "$INSTALL_DIR/start_termux.sh" << 'STARTEOF'
#!/data/data/com.termux/files/usr/bin/bash
set -e
DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$DIR"
G='\033[1;32m' Y='\033[1;33m' B='\033[1;34m' C='\033[1;36m' N='\033[0m'
echo -e "${C}  BYO-OS 启动器 v2.0${N}"
if [ ! -f "$DIR/byo-os.iso" ]; then
    echo -e "${Y}[!] byo-os.iso 不存在，请先运行 install_termux.sh${N}"
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
STARTEOF
    chmod +x "$INSTALL_DIR/start_termux.sh"
    
    # stop_termux.sh
    cat > "$INSTALL_DIR/stop_termux.sh" << 'STOPEOF'
#!/data/data/com.termux/files/usr/bin/bash
pkill -f "qemu-system-i386.*byo-os" 2>/dev/null
pkill -f "gateway.py" 2>/dev/null
echo "BYO-OS 已停止"
STOPEOF
    chmod +x "$INSTALL_DIR/stop_termux.sh"
    
    # uninstall_termux.sh
    cat > "$INSTALL_DIR/uninstall_termux.sh" << 'UNINSTALLEOF'
#!/data/data/com.termux/files/usr/bin/bash
pkill -f "qemu-system-i386.*byo-os" 2>/dev/null
pkill -f "gateway.py" 2>/dev/null
sleep 1
rm -rf "$HOME/byo-os"
echo "卸载完成"
UNINSTALLEOF
    chmod +x "$INSTALL_DIR/uninstall_termux.sh"
    
    # 添加快捷命令
    PROFILE="$HOME/.bashrc"
    if ! grep -q "byo-start" "$PROFILE" 2>/dev/null; then
        echo "" >> "$PROFILE"
        echo "# BYO-OS" >> "$PROFILE"
        echo "alias byo-start='bash $INSTALL_DIR/start_termux.sh'" >> "$PROFILE"
        echo "alias byo-stop='bash $INSTALL_DIR/stop_termux.sh'" >> "$PROFILE"
    fi
    echo -e "${G}[✓]${N} 启动脚本已创建"
}

print_usage() {
    echo ""
    echo -e "${C}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${N}"
    echo -e "${G}  ✅ 安装完成!${N}"
    echo ""
    echo -e "  ${B}快速启动:${N}"
    echo -e "    bash $INSTALL_DIR/start_termux.sh"
    echo ""
    echo -e "  ${B}或使用快捷命令 (重启 Termux 后生效):${N}"
    echo -e "    byo-start    启动"
    echo -e "    byo-stop     停止"
    echo ""
    echo -e "  ${B}Web 面板: http://localhost:7777${N}"
    echo -e "${C}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${N}"
}

main() {
    banner
    check_termux
    install_deps
    clone_repo
    download_iso
    create_scripts
    print_usage
}
main "$@"