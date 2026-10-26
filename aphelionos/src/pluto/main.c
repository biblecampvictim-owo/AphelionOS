#include <stdint.h>
#include "stdio.h"
#include "arch/i686/idt.h"
#include "keyboard.h"
#include "shell.h"

void kernel_main()
{
    clrscr();
    printf("The kernel has been Initialized.\n");

    idt_init();
    keyboard_init();

    __asm__ volatile("sti");
    //test the interrupter!
    //int a = 3;
    //int b = 0;
    //int c = a / c;
    shell_run();

    for (;;);
}