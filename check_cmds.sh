#!/bin/bash
for cmd in fuser killall mtr base64 md5sum sha256sum cksum macchanger expand unexpand seq basename dirname realpath od xxd hexdump strings file split paste column fmt fold ssh scp wget dig nslookup arp traceroute tcpdump iptables netstat ss route ifconfig lsof ulimit nice renice timeout watch time killall pstree pgrep pkill pidof ldd xargs getent getconf logrotate mkswap swapon swapoff sync; do
    if grep -q ""$cmd"" /mnt/e/aisystem/byo-os/kernel/shell.c; then
        echo "EXISTS: $cmd"
    else
        echo "MISSING: $cmd"
    fi
done
