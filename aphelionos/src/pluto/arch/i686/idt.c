#include "idt.h"
#include <stdint.h> //uhhh
#include "stdio.h"
#include "red_error.h"
#include "bgcolor.h"
struct IDTEntry g_idt[256];
struct IDTPtr   g_idtp;

extern void isr_0(void);
extern void isr_1(void);
extern void clrscr(void);

//gates
void idt_set_gate(uint8_t vector, void* base, uint16_t selector, uint8_t flags) {
    g_idt[vector].offset_low    = (uint32_t)base & 0xFFFF;
    g_idt[vector].selector      = selector;
    g_idt[vector].zero          = 0;
    g_idt[vector].type_attr     = flags;
    g_idt[vector].offset_high   = ((uint32_t)base >> 16) & 0xFFFF;
}

//You do not want to get this lol
void isr_handler(void* frame) {
    clrscr();
    set_red_background();
    printf("ERROR: A critical system interrupt was received. Did you divide by zero?\n");
    red_error();
    printf("If not, Please post this as an issue on the official github page:\n");
    printf("https://github.com/biblecampvictim-owo/AphelionOS\n");
    printf("It is recommended you reboot.\n");
    for (;;); //stop so it doesnt loop forever, Please never remove this
}

//job
void idt_init(void) {
    g_idtp.limit = sizeof(struct IDTEntry) * 256 - 1;
    g_idtp.base  = (uint32_t)&g_idt[0];

    idt_set_gate(0, isr_0, 0x08, 0x8E);

    __asm__ volatile("lidt (%0)" : : "r"(&g_idtp));
}