#include <stdint.h>
#include "stdio.h"
#include "arch/i686/idt.h"
#include "keyboard.h"
#include "shell.h"

void kernel_main()
{
    clrscr();
    printf("The kernel has been successfully initialized. Welcome!\n");

    idt_init();
    keyboard_init();

    __asm__ volatile("sti");

    shell_run();

    for (;;);
}
