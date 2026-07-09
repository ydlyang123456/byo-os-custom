@echo off
chcp 65001 >nul
echo ============================================
echo    BYO-OS Build (via WSL)
echo ============================================
echo.
wsl -e bash -c "cd /mnt/e/aisystem/byo-os && chmod +x build.sh && bash build.sh"
echo.
echo Build complete! ISO: byo-os.iso
pause
