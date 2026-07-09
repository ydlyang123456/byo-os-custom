@echo off
chcp 65001 >nul
title BYO-OS Launch v8
echo ============================================
echo    BYO-OS - One-Click Launch v8
echo ============================================
echo.

if not exist "D:\qemu\qemu-system-i386.exe" (
    echo [ERROR] QEMU not found at D:\qemu\
    pause
    exit /b 1
)

if not exist "%~dp0byo-os.iso" (
    echo [ERROR] byo-os.iso not found!
    pause
    exit /b 1
)

python --version >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Python not found!
    pause
    exit /b 1
)

echo [0/3] Cleaning up ports...
for /f "tokens=5" %%a in ('netstat -ano ^| findstr ":7777 " ^| findstr "LISTENING" 2^>nul') do (
    taskkill /PID %%a /F >nul 2>&1
)
for /f "tokens=5" %%a in ('netstat -ano ^| findstr ":4321 " ^| findstr "LISTENING" 2^>nul') do (
    taskkill /PID %%a /F >nul 2>&1
)
timeout /t 2 /nobreak >nul

echo [1/3] Starting QEMU (GTK display for better keyboard)...
echo        ISO: %~dp0byo-os.iso
echo        Display: GTK (default, better keyboard)
echo        Serial: TCP 4321
echo.
start "" "D:\qemu\qemu-system-i386.exe" ^
    -cdrom "%~dp0byo-os.iso" ^
    -m 128 ^
    -serial tcp::4321,server,nowait ^
    -display gtk

echo [2/3] Waiting for QEMU to initialize (10 seconds)...
timeout /t 10 /nobreak >nul

netstat -ano | findstr ":4321" | findstr "LISTENING" >nul 2>&1
if %errorlevel% equ 0 (
    echo [OK] Port 4321 is listening
) else (
    echo [WARN] Port 4321 not yet listening, gateway will retry...
)

echo [3/3] Starting Web Management Panel...
echo.
echo ============================================
echo    BYO-OS is starting!
echo ============================================
echo.
echo    QEMU Display:  GTK window (OS visible)
echo    Web Panel:     http://localhost:7777
echo.
echo    IMPORTANT: Click inside QEMU window first,
echo    then type commands. Enter key should work
echo    with GTK display.
echo.
echo    Open browser: http://localhost:7777
echo ============================================
echo.

python "%~dp%gateway.py"

pause
