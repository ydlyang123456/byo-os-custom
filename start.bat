@echo off
chcp 65001 >nul
title BYO-OS Launch v9
echo ============================================
echo    BYO-OS - One-Click Launch v9
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

echo [1/3] Starting QEMU...
echo        ISO: %~dp0byo-os.iso
echo        Display: SDL
echo        Serial: TCP 4321 (for web panel)
echo        Network: NE2000 + port forward 8888-^>80
echo.
start "" "D:\qemu\qemu-system-i386.exe" ^
    -cdrom "%~dp0byo-os.iso" ^
    -m 128 ^
    -serial tcp::4321,server,nowait ^
    -display sdl ^
    -netdev user,id=net0,hostfwd=tcp::8888-:80 ^
    -device ne2k_pci,netdev=net0

echo [2/3] Waiting for QEMU to initialize (8 seconds)...
timeout /t 8 /nobreak >nul

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
echo    QEMU Window:  SDL display (use this to type)
echo    Web Panel:    http://localhost:7777
echo    HTTP Port:    8888 (mapped to OS port 80)
echo.
echo    TIP: Click inside QEMU window, then type.
echo         Enter key should work with SDL display.
echo         Web panel connects via TCP serial port 4321.
echo ============================================
echo.

python "%~dp0gateway.py"

pause
