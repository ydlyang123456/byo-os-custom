@echo off
chcp 65001 >nul
echo ============================================
echo    BYO-OS Web Panel (Standalone Mode)
echo ============================================
echo.
echo This starts only the web panel without QEMU.
echo The panel shows static data from the OS.
echo.

REM Kill existing
netstat -an | findstr ":7777 " | findstr "LISTENING" >nul 2>&1
if %errorlevel%==0 (
    for /f "tokens=5" %%a in ('netstat -ano ^| findstr ":7777 " ^| findstr "LISTENING"') do (
        taskkill /PID %%a /F >nul 2>&1
    )
    timeout /t 1 /nobreak >nul
)

echo Web Panel: http://localhost:7777
echo.
python "%~dp0gateway.py"
pause
