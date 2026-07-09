# BYO-OS - Build Your Own Operating System

> 纯手写 x86 操作系统，无 Linux/Windows 依赖，可运行在 QEMU 虚拟机中

## ?? 快速开始

### 1. 构建 ISO
```bash
# 在 WSL 中运行
cd /mnt/e/aisystem/byo-os
chmod +x build.sh
bash build.sh
```
或在 Windows 中双击 `build.bat`

### 2. 启动系统 + Web管理面板
```
双击 start.bat
```
这会自动：
- 启动 QEMU 虚拟机（显示 OS 界面）
- 启动 Web 管理面板（http://localhost:7777）
- 通过串口桥接连接两者

### 3. 访问 Web 管理面板
浏览器打开 **http://localhost:7777**

## ?? 功能列表

### 内核特性
- ? GDT / IDT 中断管理
- ? IRQ / PIC 可编程中断控制器
- ? 100Hz 系统计时器
- ? PS/2 键盘驱动
- ? PS/2 鼠标驱动
- ? 物理内存管理器 (PMM)
- ? 内核堆分配器
- ? 多任务调度器
- ? RAMDISK 文件系统
- ? NE2000 网卡驱动（TX）
- ? TCP/IP 协议栈（ARP/IPv4/TCP）
- ? HTTP 服务器
- ? 用户权限系统
- ? 串口调试输出

### Web 管理面板（宝塔式）
- ?? **Dashboard** - 实时系统状态监控
- ?? **Web Terminal** - 通过浏览器执行 OS 命令
- ?? **File Manager** - 文件浏览、查看、创建、删除
- ?? **Network** - 网络配置和协议栈状态
- ?? **User Management** - 用户列表和权限
- ?? **Settings** - 系统配置、重启、关机

### Shell 命令
| 命令 | 说明 |
|------|------|
| `help` | 显示帮助 |
| `ls` | 列出文件 |
| `cat <file>` | 查看文件 |
| `write <file> <text>` | 写入文件 |
| `mem` | 内存信息 |
| `net` | 网络信息 |
| `ps` | 进程列表 |
| `whoami` | 当前用户 |
| `panel` | 文本管理面板 |
| `sysinfo` | 系统信息（JSON） |
| `halt` | 关机 |
| `reboot` | 重启 |

## ?? 架构

```
Browser ──→ http://localhost:7777 ──→ Python Gateway ──→ TCP:4321 ──→ QEMU Serial ──→ BYO-OS Shell
    ↑                                        │
    └────── Web Panel (Dashboard/Terminal/Files) ←──┘
```

- **OS** → 通过 COM1 串口输出/输入
- **QEMU** → 串口转发到 TCP 4321 端口
- **Python Gateway** → 连接串口，提供 Web 界面
- **浏览器** → 访问 http://localhost:7777

## ?? 项目结构

```
byo-os/
├── boot/boot.asm          # 引导程序
├── kernel/
│   ├── main.c             # 内核入口
│   ├── gdt.c / gdt_asm    # 全局描述符表
│   ├── idt.c / isr.asm    # 中断描述符表
│   ├── irq.c              # IRQ 处理
│   ├── keyboard.c         # PS/2 键盘
│   ├── mouse.c            # PS/2 鼠标
│   ├── timer.c            # 系统计时器
│   ├── memory.c           # 物理内存管理
│   ├── heap.c             # 内核堆
│   ├── serial.c           # 串口驱动（双向）
│   ├── fs.c               # RAMDISK 文件系统
│   ├── scheduler.c        # 多任务调度
│   ├── ne2000.c           # NE2000 网卡驱动
│   ├── net.c              # TCP/IP 协议栈
│   ├── user.c             # 用户权限
│   ├── shell.c            # 命令行界面
│   ├── panel.c            # 文本管理面板
│   ├── vga.c              # VGA 文本模式
│   ├── vga_modes.c        # VGA 模式切换
│   ├── string.c           # 字符串工具
│   ├── font.c             # 8x8 位图字体
│   └── linker.ld          # 链接脚本
├── include/kernel.h       # 主头文件
├── gateway.py             # Web 管理面板
├── build.sh               # 构建脚本（WSL）
├── build.bat              # 构建脚本（Windows）
├── start.bat              # 一键启动
├── start_web_only.bat     # 仅启动 Web 面板
└── byo-os.iso             # 构建输出
```

## ? 启动参数

### QEMU
```
qemu-system-i386.exe -cdrom byo-os.iso -m 128 -serial tcp::4321,server,nowait -display sdl
```

### Web 网关
```
python gateway.py
# → http://localhost:7777
```

## ?? 已知限制

1. **NE2000 RX**: QEMU SLiRP 不向 NE2000 回送数据包，仅 TX 可用
2. **串口替代网络**: Web 面板通过串口与 OS 通信，非真实网络
3. **内存限制**: 128MB，tmpfs 文件系统

## ?? 重新构建

```bash
# WSL
cd /mnt/e/aisystem/byo-os && bash build.sh

# Windows
build.bat
```
