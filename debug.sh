#!/bin/bash
qemu-system-aarch64 \
    -machine virt,gic-version=3 \
    -cpu cortex-a57 \
    -kernel build/kernel.elf \
    -nographic \
    -s -S
