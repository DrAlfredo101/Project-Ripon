#!/usr/bin/env bash
set -euo pipefail

IMG="drive.img"
MOUNT_DIR=$(mktemp -d)

# Ensure loop device and mount point are always cleaned up on exit
cleanup() {
    umount "$MOUNT_DIR" 2>/dev/null || true
    rmdir "$MOUNT_DIR" 2>/dev/null || true
    if [[ -n "${LOOPDEV:-}" ]]; then
        losetup -d "$LOOPDEV" 2>/dev/null || true
    fi
}
trap cleanup EXIT

# 1. Attach image and capture the assigned loop device (e.g., /dev/loop0)
LOOPDEV=$(losetup --find --show --partscan "$IMG")

# 2. Format partition 3 as FAT32
mkfs.vfat -F 32 "${LOOPDEV}p2"
mkfs.vfat -F 32 "${LOOPDEV}p3"