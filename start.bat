@echo off
chcp 65001 >nul
title BYO-OS Launch
echo ============================================
echo    BYO-OS - One-Click Launch
echo ============================================
echo.

REM Check QEMU
if not exist "D:\qemu\qemu-system-i386.exe" (
    echo [ERROR] QEMU not found at D:\qemu\
    echo Please install QEMU or edit QEMU_PATH in this script
    pause
    exit /b 1
)

REM Check ISO
if not exist "%~dp0byo-os.iso" (
    echo [ERROR] byo-os.iso not found!
    echo Please run build.bat first to build the ISO
    pause
    exit /b 1
)

REM Check Python
python --version >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Python not found! Please install Python 3
    pause
    exit /b 1
)

REM Kill existing processes on ports
echo [0/3] Cleaning up ports...
for /f "tokens=5" %%a in ('netstat -ano ^| findstr ":7777 " ^| findstr "LISTENING" 2^>nul') do (
    taskkill /PID %%a /F >nul 2>&1
)
for /f "tokens=5" %%a in ('netstat -ano ^| findstr ":4321 " ^| findstr "LISTENING" 2^>nul') do (
    taskkill /PID %%a /F >nul 2>&1
)
timeout /t 1 /nobreak >nul

echo [1/3] Starting QEMU...
echo        ISO: %~dp0byo-os.iso
echo        Display: SDL
echo        Serial: TCP 4321 (for web panel bridge)
echo.
start "" "D:\qemu\qemu-system-i386.exe" ^
    -cdrom "%~dp0byo-os.iso" ^
    -m 128 ^
    -serial tcp::4321,server,nowait ^
    -display sdl

echo [2/3] Waiting for QEMU to initialize (5 seconds)...
timeout /t 5 /nobreak >nul

echo [3/3] Starting Web Management Panel...
echo.
echo ============================================
echo    BYO-OS is starting!
echo ============================================
echo.
echo    QEMU Display:  SDL window (OS visible)
echo    Serial Bridge: localhost:4321
echo    Web Panel:     http://localhost:7777
echo.
echo    Open browser and go to:
echo    ^> http://localhost:7777
echo.
echo    Press Ctrl+C in this window to stop
echo ============================================
echo.

python "%~dp0gateway.py"

pause
