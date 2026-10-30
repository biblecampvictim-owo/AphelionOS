#include "idt.h"
#include <stdint.h> //uhhh
#include "stdio.h"
#include "red_error.h"
#include "bgcolor.h"
#include "audio.h"

struct IDTEntry g_idt[256];
struct IDTPtr   g_idtp;

extern void isr_0(void);
extern void isr_1(void);
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

//You do not want to get this lol
void isr_handler(void* frame) {
    clrscr();
    set_red_background();
    printf("ERROR: A critical system interrupt was received. Did you divide by zero?\n");
    red_error();
    printf("If not, Please post this as an issue on the official github page:\n");
    printf("https://github.com/biblecampvictim-owo/AphelionOS\n");
    printf("It is recommended you reboot.\n");
    //error music
    while(1){
        play_b();
        audio_delay_error();
        nosound();
        play_c();
    }

    for (;;); //stop so it doesnt loop forever, Please never remove this
}

//job
void idt_init(void) {
    g_idtp.limit = sizeof(struct IDTEntry) * 256 - 1;
    g_idtp.base  = (uint64_t)&g_idt[0];

    idt_set_gate(0, isr_0, 0x08, 0x8E);

    __asm__ volatile("lidt %0" : : "m"(g_idtp));
}