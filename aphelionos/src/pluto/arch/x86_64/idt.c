#include "idt.h"
#include <stdint.h> //uhhh
#include "stdio.h"
#include "red_error.h"
#include "bgcolor.h"
#include "audio.h"
//I am going to polish this idt in the future.
//That time is NOW!

struct IDTEntry g_idt[256];
struct IDTPtr   g_idtp;

extern void isr_0(void);
extern void isr_1(void);
extern void isr_2(void);
extern void isr_3(void);
extern void isr_4(void);
extern void isr_5(void);
extern void isr_6(void);
extern void isr_7(void);
extern void isr_8(void);
extern void isr_9(void);
extern void isr_10(void);
extern void isr_11(void);
extern void isr_12(void);
extern void isr_13(void);
extern void isr_14(void);
extern void isr_15(void);
extern void isr_16(void);
extern void isr_17(void);
extern void isr_18(void);
extern void isr_19(void);
extern void isr_20(void);
extern void isr_21(void);
extern void isr_22(void);
extern void isr_23(void);
extern void isr_24(void);
extern void isr_25(void);
extern void isr_26(void);
extern void isr_27(void);
extern void isr_28(void);
extern void isr_29(void);
extern void isr_30(void);
extern void isr_31(void);

extern void clrscr(void);

//gates
void idt_set_gate(uint8_t vector, void* base, uint16_t selector, uint8_t flags) {
    uint64_t ui_base = (uint64_t)base;

    g_idt[vector].offset_low  = ui_base & 0xFFFF;
    g_idt[vector].selector    = selector;
    g_idt[vector].ist         = 0;
    g_idt[vector].type_attr   = flags;
    g_idt[vector].offset_mid  = (ui_base >> 16) & 0xFFFF;
    g_idt[vector].offset_high = (ui_base >> 32) & 0xFFFFFFFF;
    g_idt[vector].reserved    = 0;
}

//You do not want to get this lol,
//I mean, Obviously? What am i saying?

void isr_handler(struct InterruptFrame* frame) {
    set_vga_color(0x4F);
    clrscr();
    set_red_background();
    printf("ERROR: A critical system interrupt was received.\n");
    printf("Interrupt Vector: %llu\n", (unsigned long long)frame->interrupt_number);
    printf("Error Code: 0x%llx\n", (unsigned long long)frame->error_code);
    printf("Faulting Instruction: 0x%llx\n", (unsigned long long)frame->rip);
    red_error();

    printf("If this is not intentional (Like you did the die command or u divided by zero anywhere), Please post this as an issue on the official github page:\n");
    printf("https://github.com/biblecampvictim-owo/AphelionOS\n");
    printf("It is recommended you reboot.\n");
    //cant forget em tunes
    while(1){
        play_b();
        audio_delay_error();
        nosound();
        play_c();
    }
}

//job
void idt_init(void) {
    g_idtp.limit = sizeof(struct IDTEntry) * 256 - 1;
    g_idtp.base  = (uint64_t)&g_idt[0];

    idt_set_gate(0, isr_0, 0x08, 0x8E);
    idt_set_gate(1, isr_1, 0x08, 0x8E);
    idt_set_gate(2, isr_2, 0x08, 0x8E);
    idt_set_gate(3, isr_3, 0x08, 0x8E);
    idt_set_gate(4, isr_4, 0x08, 0x8E);
    idt_set_gate(5, isr_5, 0x08, 0x8E);
    idt_set_gate(6, isr_6, 0x08, 0x8E);
    idt_set_gate(7, isr_7, 0x08, 0x8E);
    idt_set_gate(8, isr_8, 0x08, 0x8E);
    idt_set_gate(9, isr_9, 0x08, 0x8E);
    idt_set_gate(10, isr_10, 0x08, 0x8E);
    idt_set_gate(11, isr_11, 0x08, 0x8E);
    idt_set_gate(12, isr_12, 0x08, 0x8E);
    idt_set_gate(13, isr_13, 0x08, 0x8E);
    idt_set_gate(14, isr_14, 0x08, 0x8E);
    idt_set_gate(15, isr_15, 0x08, 0x8E);
    idt_set_gate(16, isr_16, 0x08, 0x8E);
    idt_set_gate(17, isr_17, 0x08, 0x8E);
    idt_set_gate(18, isr_18, 0x08, 0x8E);
    idt_set_gate(19, isr_19, 0x08, 0x8E);
    idt_set_gate(20, isr_20, 0x08, 0x8E);
    idt_set_gate(21, isr_21, 0x08, 0x8E);
    idt_set_gate(22, isr_22, 0x08, 0x8E);
    idt_set_gate(23, isr_23, 0x08, 0x8E);
    idt_set_gate(24, isr_24, 0x08, 0x8E);
    idt_set_gate(25, isr_25, 0x08, 0x8E);
    idt_set_gate(26, isr_26, 0x08, 0x8E);
    idt_set_gate(27, isr_27, 0x08, 0x8E);
    idt_set_gate(28, isr_28, 0x08, 0x8E);
    idt_set_gate(29, isr_29, 0x08, 0x8E);
    idt_set_gate(30, isr_30, 0x08, 0x8E);
    idt_set_gate(31, isr_31, 0x08, 0x8E);


    __asm__ volatile("lidt %0" : : "m"(g_idtp));
}