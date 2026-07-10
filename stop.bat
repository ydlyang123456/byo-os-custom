@echo off
echo ???? BYO-OS...
taskkill /F /IM qemu-system-i386.exe >nul 2>&1
taskkill /F /IM python.exe /FI "WINDOWTITLE eq BYO-OS*" >nul 2>&1
echo BYO-OS ???
timeout /t 2 >nul