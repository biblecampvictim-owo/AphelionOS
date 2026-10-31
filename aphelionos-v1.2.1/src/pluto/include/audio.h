#ifndef AUDIO_H
#define AUDIO_H
//Created on oct 28 2026 around ~ 2 - 9 PM
#include <stdint.h>

void play_beep();
void play_a();
void play_b();
void play_c();
void play_d();
void play_e();
void play_f();
void play_g();

static void outb(unsigned short port, unsigned char val) {
    __asm__ __volatile__("outb %0, %1" : : "a"(val), "Nd"(port));
}

static unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static void nosound(void) {
    uint8_t tmp = inb(0x61) & 0xFC;
    outb(0x61, tmp);
}

static void audio_delay_error(void) {
    for (volatile int i = 0; i < 40000000; i++) {
        __asm__ __volatile__("nop");
    }
}

#endif