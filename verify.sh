#!/bin/bash
for cmd in fuser killall mtr base64 md5sum sha256sum cksum macchanger expand unexpand traceroute ifconfig getent getconf mkswap; do
    if grep -q "\"$cmd\"" /mnt/e/aisystem/byo-os/kernel/shell.c; then
        echo "OK: $cmd"
    else
        echo "MISSING: $cmd"
    fi
done