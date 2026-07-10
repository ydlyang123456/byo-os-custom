#!/usr/bin/env python3
"""Translate panel.html to Chinese"""
import re

with open("panel.html", "r", encoding="utf-8") as f:
    html = f.read()

# Sidebar navigation
replacements = [
    # Title
    ("Management Panel v13", "管理面板 v13"),
    ("BYO-OS Management Panel", "BYO-OS 管理面板"),
    
    # Sidebar sections
    (">Main<", ">主要<"),
    (">Management<", ">管理<"),
    (">Tools<", ">工具<"),
    
    # Sidebar links
    ("Dashboard", "仪表盘"),
    ("Terminal", "终端"),
    ("System Info", "系统信息"),
    ("Processes", "进程管理"),
    ("Network", "网络"),
    ("Files", "文件管理"),
    ("Users", "用户管理"),
    ("Services", "服务管理"),
    ("Packages", "软件包"),
    ("Commands", "命令参考"),
    ("Logs", "日志"),
    ("Settings", "设置"),
    
    # Dashboard cards
    ("<h3>System</h3>", "<h3>系统</h3>"),
    ("<h3>Memory</h3>", "<h3>内存</h3>"),
    ("<h3>Tasks</h3>", "<h3>任务</h3>"),
    ("<h3>Network</h3>", "<h3>网络</h3>"),
    ("<h3>Serial</h3>", "<h3>串口</h3>"),
    
    # Labels
    (">Platform<", ">平台<"),
    (">Arch<", ">架构<"),
    (">User<", ">用户<"),
    (">Total<", ">总计<"),
    (">Free<", ">空闲<"),
    (">Heap<", ">堆内存<"),
    (">Load<", ">负载<"),
    (">Uptime<", ">运行时间<"),
    (">IP<", ">IP 地址<"),
    (">Port<", ">端口<"),
    (">Serial Status<", ">串口状态<"),
    (">Gateway<", ">网关<"),
    (">Connection<", ">连接<"),
    
    # Status
    (">Up<", ">运行<"),
    (">Down<", ">停止<"),
    
    # Buttons
    (">Refresh<", ">刷新<"),
    (">Reconnect<", ">重连<"),
    (">Ping Gateway<", ">Ping 网关<"),
    (">Clear<", ">清屏<"),
    (">Show All<", ">显示全部<"),
    (">Show Debug Info<", ">显示调试信息<"),
    (">Debug<", ">调试<"),
    
    # Terminal
    ("BYO-OS> ", "BYO-OS> "),
    
    # Loading/Status messages
    ("Loading...", "加载中..."),
    ("Connection Error", "连接错误"),
    ("Gateway Offline", "网关离线"),
    ("Checking...", "检查中..."),
    ("Connected", "已连接"),
    ("Offline", "离线"),
    ("Reconnecting...", "重连中..."),
    ("Connected!", "已连接!"),
    ("Failed", "失败"),
    ("Reconnect failed", "重连失败"),
    
    # System info labels
    ("Platform", "平台"),
    ("Architecture", "架构"),
    
    # Process page
    ("processes", "进程列表"),
    
    # File manager
    ("files", "文件列表"),
    
    # Network
    ("net status", "网络状态"),
    
    # Other
    ("Auto-refresh: OFF", "自动刷新: 关闭"),
    ("Auto-refresh: ON", "自动刷新: 开启"),
    ("No commands match: ", "没有匹配的命令: "),
    ("Click a button or type to search...", "点击按钮或输入搜索..."),
    ("Click a button to load data...", "点击按钮加载数据..."),
    ("Loading debug info...", "加载调试信息..."),
    ("Searching...", "搜索中..."),
    ("Running: ", "执行中: "),
    ("Network error: ", "网络错误: "),
]

for old, new in replacements:
    html = html.replace(old, new)

# Fix the title
html = html.replace("<title>BYO-OS Management Panel</title>", "<title>BYO-OS 管理面板</title>")

with open("panel.html", "w", encoding="utf-8", newline="\n") as f:
    f.write(html)

print("panel.html translated to Chinese!")
print(f"File size: {len(html)} bytes")