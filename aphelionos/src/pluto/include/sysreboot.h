#ifndef SYSREBOOT_H
#define SYSREBOOT_H

#include <stdint.h>

void sys_reboot(void) {
    uint8_t temp = 0x02;
    while (temp & 0x02) {
        temp = inb(0x64);
    }
    outb(0x64, 0xFE);
}

#endif