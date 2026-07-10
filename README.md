# BYO-OS - Build Your Own Operating System v2.7

> ?? 从零构建的 x86_64 操作系统，Debian 12 兼容，支持宝塔面板
> 纯手写 C/ASM，无任何现有操作系统代码

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)]()
[![Arch](https://img.shields.io/badge/arch-x86__64-blue)]()
[![Debian Compat](https://img.shields.io/badge/Debian-12_bookworm-orange)]()
[![License](https://img.shields.io/badge/license-MIT-green)]()

## ? 核心特性

| 特性 | 说明 |
|------|------|
| ??? **从零构建** | 纯手写 x86_64 内核，无 Linux/Windows 代码 |
| ?? **Debian 12 兼容** | 识别为 Debian bookworm，兼容包管理器 |
| ??? **宝塔面板支持** | 完整兼容 BT Panel 安装脚本 |
| ?? **Web 管理面板** | 宝塔式 GUI，手机/电脑浏览器管理 |
| ?? **Shell 环境** | 50000+ 行模拟命令的完整 Shell |
| ?? **ProcFS** | 动态 /proc 文件系统 (cpuinfo, meminfo, stat...) |
| ?? **SMP 多核** | xAPIC 多核启动支持 |
| ?? **开机音乐** | PC 喇叭演奏开机旋律 |
| ?? **Termux 运行** | Android 手机一键安装运行 |
| ?? **128GB 内存** | 64位 PMM 支持最大 128GB |

## ?? Termux 一键安装（Android 手机）

```bash
pkg install git -y
git clone https://github.com/ydlyang123456/byo-os-custom.git ~/byo-os
bash ~/byo-os/install_termux.sh
```

### 安装后命令

```bash
byo start      # 启动 QEMU + Web 面板
byo stop       # 停止
byo status     # 查看状态
byo update     # 更新
byo logs       # 查看日志
byo build      # 从源码编译
byo uninstall  # 卸载
bs             # = byo start (快捷)
bss            # = byo stop
```

## ?? Windows 快速开始

### 构建 ISO

```bash
# WSL 中
cd /mnt/e/aisystem/byo-os
bash build.sh
```

### 运行

```bash
# 终端1: 启动 QEMU
qemu-system-x86_64 -cdrom byo-os.iso -m 256 -serial tcp::4321,server,nowait -display sdl

# 终端2: 启动 Web 面板
python gateway.py
# → 浏览器打开 http://localhost:7777
```

## ??? 内核架构

```
┌─────────────────────────────────────────────┐
│                BYO-OS Kernel                │
├─────────────────┬───────────────────────────┤
│  x86_64 Arch    │  Memory Subsystem         │
│  ├─ GDT (64bit) │  ├─ PMM (128GB 位图)      │
│  ├─ IDT/ISR     │  ├─ VMM (4级页表)         │
│  ├─ IRQ/PIC     │  ├─ Heap (kmalloc/kfree)  │
│  └─ Syscall     │  └─ ProcFS (/proc)        │
├─────────────────┼───────────────────────────┤
│  File System    │  Network Stack            │
│  ├─ RAMFS       │  ├─ NE2000 Driver         │
│  ├─ ProcFS      │  ├─ ARP/IP/ICMP/TCP/UDP  │
│  ├─ Initramfs   │  └─ HTTP Server           │
│  └─ FAT32       │                           │
├─────────────────┼───────────────────────────┤
│  Drivers        │  Services                 │
│  ├─ PS/2 Kbd    │  ├─ Shell (50000+ cmd)   │
│  ├─ PS/2 Mouse  │  ├─ Process Scheduler     │
│  ├─ ATA PIO     │  ├─ User System           │
│  ├─ PCI Scan    │  ├─ BT Panel Compat       │
│  ├─ RTC/CMOS    │  ├─ Desktop (VBE)         │
│  ├─ USB (UHCI)  │  └─ Journal System        │
│  └─ PC Speaker  │                           │
└─────────────────┴───────────────────────────┘
```

## ?? 组件状态

| 组件 | 状态 | 说明 |
|------|------|------|
| 64位引导 | ? | Multiboot2 + GRUB |
| GDT/IDT/IRQ | ? | 64位长模式 |
| PMM (128GB) | ? | 位图页面分配器 |
| VMM | ? | 4级页表映射 |
| Heap | ? | kmalloc/kfree |
| Syscall (Linux ABI) | ? | int 0x80 |
| FAT32 | ? | ATA 磁盘读取 |
| TCP/IP Stack | ? | ARP/IP/ICMP/UDP/TCP |
| PCI/ATA/RTC | ? | 设备驱动 |
| USB | ? | UHCI/OHCI/EHCI 检测 |
| VBE Graphics | ? | 640x480~1024x768 |
| Sound | ? | PC 喇叭 + 旋律 |
| Desktop | ? | 窗口/按钮/图标 |
| ProcFS | ? | 动态 /proc 文件系统 |
| SMP | ? | xAPIC 多核支持 |
| Initramfs | ? | Debian 12 伪装 |
| Web Panel | ? | 宝塔式管理界面 |
| Shell | ? | 50000+ 模拟命令 |
| BT Panel | ? | 完整兼容层 |

## ?? Web 管理面板

- **Dashboard** - 实时 CPU/内存/磁盘监控
- **Terminal** - Web 终端执行 OS 命令
- **File Manager** - 文件浏览/编辑/删除
- **BT Panel** - 宝塔面板状态管理
- **Network** - 网络配置和统计
- **Users** - 用户管理

## ?? 项目结构

```
byo-os/
├── boot/
│   ├── boot.asm              # 16位引导
│   ├── boot_entry_64.asm     # 64位入口
│   ├── gdt64.asm             # 64位 GDT
│   └── smp_trampoline.asm    # AP 启动
├── kernel/
│   ├── main.c                # 内核入口
│   ├── shell.c               # Shell (50000+行)
│   ├── tcpip.c               # TCP/IP 协议栈
│   ├── smp.c                 # 多核支持
│   ├── procfs.c              # /proc 文件系统
│   ├── initramfs.c           # Debian 伪装
│   ├── memory64.c            # 64位 PMM
│   ├── heap64.c              # 64位堆
│   ├── vmm.c                 # 虚拟内存
│   ├── syscall.c             # Linux ABI
│   ├── gfx_enhanced.c        # 图形增强
│   ├── vbe.c                 # VBE 模式
│   ├── desktop.c             # 桌面环境
│   └── ... (40+ 文件)
├── include/
│   ├── kernel.h              # 主头文件
│   ├── procfs.h              # ProcFS API
│   └── syscall.h             # Syscall 号
├── gateway.py                # Web 管理面板
├── panel.html                # 前端页面
├── build.sh                  # 构建脚本
├── install_termux.sh         # Termux 安装
└── README.md                 # 本文件
```

## ??? 技术栈

- **语言**: C99, NASM x86_64, Python 3
- **构建**: GCC cross-compiler, ld, grub-mkrescue
- **运行**: QEMU (系统模拟)
- **管理**: Python HTTP Server + HTML5 SPA
- **协议**: 串口 TCP 隧道
- **兼容**: Debian 12 bookworm ABI

## ?? 许可证

MIT License

## ?? 贡献

欢迎 Issue 和 PR！
