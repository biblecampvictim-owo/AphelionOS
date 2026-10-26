#include "stdint.h"
#include "stdio.h"
#include "disk.h"
#include "fat.h"
#include "x86.h"

#define MK_FP(seg, off) ((void far*)(((uint32_t)(seg) << 16) | (uint16_t)(off)))

static uint8_t g_ReadBuffer[512];

void __cdecl cstart_(uint16_t bootDrive)
{
    printf("Stage 2 started (Drive 0x%x)\r\n", bootDrive);

    DISK disk;
    if (!DISK_Initialize(&disk, (uint8_t)bootDrive))
    {
        printf("Disk init error!\r\n");
        goto end;
    }
    printf("Disk init OK\r\n");

    if (!FAT_Initialize(&disk))
    {
        printf("FAT init error!\r\n");
        goto end;
    }
    printf("FAT init OK\r\n");

    printf("Opening KERNEL.BIN...\r\n");
    FAT_File far* fd = FAT_Open(&disk, "KERNEL.BIN");
    if (fd == NULL)
    {
        printf("Kernel file not found!\r\n");
        goto end;
    }

    printf("Kernel found! Reading...\r\n");
    uint32_t read;
    uint16_t kernelSeg = 0x3000;
    uint16_t kernelOff = 0x0000;

    while ((read = FAT_Read(&disk, fd, sizeof(g_ReadBuffer), g_ReadBuffer)))
    {
        uint8_t far* dst = (uint8_t far*)MK_FP(kernelSeg, kernelOff);
        for (uint16_t i = 0; i < (uint16_t)read; i++)
        {
            dst[i] = g_ReadBuffer[i];
        }

        kernelOff += (uint16_t)read;
        kernelSeg += (kernelOff >> 4);
        kernelOff &= 0x0F;

        printf(".");
    }
    FAT_Close(fd);

    printf("\r\nKernel loaded! Entering 32-bit mode...\r\n");

    x86_EnableA20();
    x86_EnterProtectedMode();

end:
    for (;;);
}