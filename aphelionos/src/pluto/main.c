#include <stdint.h>
#include "stdio.h"
#include "arch/x86_64/idt.h"
#include "keyboard.h"
#include "shell.h"

void kmain()
{

    idt_init();
    keyboard_init();

    clrscr();
    printf("The kernel has been Initialized.\n");
    if (sizeof(void*) == 8) {
        printf("Architecture: x86_64 (64-bit Long Mode Active)\n");
        printf("if you see this AphelionOS initialized succesfully!\n");
    }
    else if (sizeof(void*) == 4) {
        printf("The architecture is 32 bits, Which is not supposed to be! Expect bugs!");
    }
    else if (sizeof(void*) == 2) {
        printf("The architecture is 16 bits, Which is not supposed to be! Expect bugs!");
    }

    __asm__ volatile("sti" ::: "memory");
    //int a = 3;
    //int b = 0;    test the interrupter!
    //int c = a / c;
    shell_run();

    for (;;){
    __asm__ volatile("hlt");
    }
}