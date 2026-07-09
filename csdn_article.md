# BYO-OS：从零打造一个完整的x86操作系统

## 项目简介

BYO-OS是一个完全自主开发的x86操作系统，不依赖Linux、Windows或任何其他现有操作系统内核。它从最底层的引导程序开始，逐步构建了完整的操作系统功能，包括：

- **自定义x86内核**（232KB）— 从零编写，无任何外部依赖
- **750+ Shell命令** — 覆盖25+类别，功能媲美Debian
- **Web管理面板** — 18个页面的现代化管理界面
- **QEMU虚拟机运行** — 支持串口桥接和网络访问

## 技术架构

```
┌─────────────────────────────────────────────────┐
│                   Web Browser                    │
│              http://localhost:7777               │
└──────────────────────┬──────────────────────────┘
                       │
┌──────────────────────▼──────────────────────────┐
│              Python Gateway                      │
│              (gateway.py)                        │
└──────────────────────┬──────────────────────────┘
                       │ TCP:4321
┌──────────────────────▼──────────────────────────┐
│              QEMU Virtual Machine                │
│  ┌────────────────────────────────────────────┐  │
│  │           BYO-OS Kernel (232KB)            │  │
│  │  ┌──────┐ ┌──────┐ ┌──────┐ ┌──────────┐  │  │
│  │  │ Shell │ │  FS  │ │ Net  │ │Scheduler │  │  │
│  │  │750+  │ │      │ │TCP/IP│ │          │  │  │
│  │  └──────┘ └──────┘ └──────┘ └──────────┘  │  │
│  └────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────┘
```

## 核心模块

### 1. 引导程序（Boot Loader）

```asm
; boot/boot.asm - 16位实模式引导
[BITS 16]
[ORG 0x7C00]

start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    
    ; 加载内核到内存
    mov ah, 0x02
    mov al, 20      ; 扇区数
    mov ch, 0        ; 柱面
    mov cl, 2        ; 扇区
    mov dh, 0        ; 磁头
    mov bx, 0x1000   ; 目标地址
    int 0x13
    
    ; 切换到保护模式
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode
```

### 2. 内核主程序

```c
// kernel/main.c
#include "kernel.h"

void kernel_main(void) {
    // 初始化所有子系统
    gdt_init();      // 全局描述符表
    idt_init();      // 中断描述符表
    irq_init();      // 硬件中断
    pmm_init();      // 物理内存管理
    heap_init();     // 堆内存分配
    timer_init();    // 定时器
    keyboard_init(); // PS/2键盘
    serial_init();   // 串口通信
    net_init();      // 网络协议栈
    fs_init();       // 文件系统
    
    // 启动Shell
    shell_init();
    shell_run();
}
```

### 3. Shell系统 — 750+命令

BYO-OS的Shell系统支持25+类别的750+命令：

| 类别 | 代表命令 | 数量 |
|------|----------|------|
| 系统管理 | ps, top, kill, systemctl | 50+ |
| 文件操作 | ls, cat, cp, mv, rm, find | 40+ |
| 网络工具 | ping, curl, wget, ssh, nmap | 80+ |
| 安全工具 | iptables, nmap, hydra, trivy | 60+ |
| 数据库 | mysql, psql, redis, mongo | 30+ |
| 容器 | docker, podman, kubectl | 40+ |
| 开发工具 | gcc, make, git, python, vim | 50+ |
| Web服务 | nginx, apache, caddy | 20+ |
| 云服务 | aws, azure, gcloud, terraform | 30+ |
| AI/ML | tensorflow, pytorch, ollama | 20+ |
| 监控 | prometheus, grafana, zabbix | 30+ |
| 游戏 | steam, wine, proton | 10+ |
| 办公 | libreoffice, pandoc | 15+ |
| 通信 | element, signal, discord | 20+ |

### 4. 网络协议栈

```c
// kernel/net.c - NE2000网卡驱动
void net_init(void) {
    // 初始化NE2000兼容网卡
    ne2000_init();
    
    // 初始化TCP/IP协议栈
    tcp_init();
    udp_init();
    ip_init();
    arp_init();
    icmp_init();
    
    // 启动DHCP客户端
    dhcp_init();
}
```

### 5. 文件系统

```c
// kernel/fs.c - 简单文件系统
typedef struct {
    char name[32];
    uint32_t size;
    uint32_t data_block;
    uint8_t is_directory;
} fs_entry;

// 支持的操作
int fs_create(const char *name);
int fs_read(const char *name, char *buf, int size);
int fs_write(const char *name, const char *data, int size);
int fs_delete(const char *name);
int fs_list(char *buf, int bufsize);
```

### 6. 进程调度器

```c
// kernel/scheduler.c
typedef struct {
    int pid;
    char name[32];
    int priority;
    int state;  // RUNNING, WAITING, STOPPED
    void (*entry)(void);
} process;

void scheduler_tick(void) {
    // 时间片轮转调度
    current_process = find_next_ready();
    if (current_process) {
        context_switch(&current_process->context);
    }
}
```

### 7. Web管理面板

Web管理面板基于Python构建，提供18个管理页面：

- **Dashboard** — 系统概览
- **Terminal** — 在线终端
- **Processes** — 进程管理
- **Monitor** — 资源监控
- **File Manager** — 文件管理
- **Network** — 网络配置
- **Security** — 安全工具
- **Dev Tools** — 开发工具
- **Containers** — 容器管理
- **Multimedia** — 多媒体工具

## 如何运行

### 1. 编译内核

```bash
# 在WSL中编译
cd /mnt/e/aisystem/byo-os
bash build.sh
```

### 2. 启动QEMU

```powershell
# 在Windows中启动
D:\qemu\qemu-system-i386.exe `
    -cdrom E:\aisystem\byo-os\byo-os.iso `
    -m 128 `
    -serial tcp::4321,server,nowait `
    -display sdl
```

### 3. 启动Web面板

```powershell
python E:\aisystem\byo-os\gateway.py
# 访问 http://localhost:7777
```

## 项目统计

| 指标 | 数值 |
|------|------|
| 内核大小 | 232KB |
| ISO大小 | 5.3MB |
| Shell代码行数 | 5,063行 |
| 唯一命令数 | 750+ |
| Git提交数 | 8个 |
| 支持类别 | 25+ |

## 未来计划

1. **GUI桌面环境** — 实现图形用户界面
2. **网络浏览器** — 内置文本/图形浏览器
3. **包管理器** — 完整的软件包管理系统
4. **多用户支持** — 完整的用户权限管理
5. **SMP支持** — 多处理器支持

## GitHub

项目已开源：https://github.com/ydlyang123456/byo-os-custom

## 总结

BYO-OS证明了一个完全自主开发的操作系统可以具备与主流Linux发行版相媲美的功能。通过从零开始构建每个组件，我们深入理解了操作系统的底层原理，包括：

- 引导加载和实模式/保护模式切换
- 内存管理和进程调度
- 文件系统设计和实现
- 网络协议栈和驱动程序
- Shell解析和命令执行
- Web服务和远程管理

这个项目不仅是一个技术挑战，更是一次深入理解计算机系统本质的学习之旅。
