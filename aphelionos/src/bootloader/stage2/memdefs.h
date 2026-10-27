#pragma once

// 0x00000000 - 0x000003FF - interrupt vector table
// 0x00000400 - 0x000004FF - BIOS data area

#pragma once

#define MEMORY_FAT_ADDR     ((void far*)0x00500000)
#define MEMORY_FAT_SIZE     0x00010000

#define MEMORY_KERNEL_ADDR  ((void far*)0x30000000)
#define MEMORY_KERNEL_SIZE  0x00050000

// 0x00020000 - 0x00030000 - stage2

// 0x00030000 - 0x00080000 - free

//I AINT TYPING ALLLATTT!!!!!!