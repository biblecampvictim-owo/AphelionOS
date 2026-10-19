#include "idt.h"
#include <stdint.h>
#include "stdio.h"
struct IDTEntry g_idt[256];
struct IDTPtr   g_idtp;

extern void isr_0(void);
extern void isr_1(void);
//gates
void idt_set_gate(uint8_t vector, void* base, uint16_t selector, uint8_t flags) {
    g_idt[vector].offset_low    = (uint32_t)base & 0xFFFF;
    g_idt[vector].selector      = selector;
    g_idt[vector].zero          = 0;
    g_idt[vector].type_attr     = flags;
    g_idt[vector].offset_high   = ((uint32_t)base >> 16) & 0xFFFF;
}
//here under is for the interrupts. like print("Interrupt received!\n");
void isr_handler(void* frame) {
    printf("An interrupt was received.\n");
    for (;;); //stop so it doesnt loop forever
}
//job
void idt_init(void) {
    g_idtp.limit = sizeof(struct IDTEntry) * 256 - 1;
    g_idtp.base  = (uint32_t)&g_idt[0];

    idt_set_gate(0, isr_0, 0x08, 0x8E);

    __asm__ volatile("lidt (%0)" : : "r"(&g_idtp));
}