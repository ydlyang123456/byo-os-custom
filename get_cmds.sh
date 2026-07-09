#!/bin/bash
sed -n '7025,7439p' /mnt/e/aisystem/byo-os/kernel/shell.c | grep -oE '"[a-z0-9._-]+"' | tr -d '"' | sort -u
