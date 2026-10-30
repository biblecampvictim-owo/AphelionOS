#include <stdint.h>
#include "stdio.h"
#include "arch/x86_64/idt.h"
#include "keyboard.h"
#include "shell.h"

void kmain()
{

    clrscr();
    printf("The kernel has been Initialized.\n");
    if (sizeof(void*) == 8) {
    printf("Architecture: x86_64 (64-bit Long Mode Active)\n");
    } else {
    printf("Architecture: 32-bit Protected Mode\n");
    }

    idt_init();
    keyboard_init();

    __asm__ volatile("sti");
    //int a = 3;
    //int b = 0;    //test the interrupter!
    //int c = a / c;
    shell_run();

    for (;;);
}