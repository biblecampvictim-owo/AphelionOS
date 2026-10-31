//Made on Oct 28. 2026 5:34 PM
//also with these dates i mean "when i created this file" not when i last updated it
#include "audio.h"
#include <stdint.h>
#include <unistd.h>
#include "delay.h"

extern int printf(const char* format, ...);

static void play_sound(uint32_t frequency) {
    uint32_t div;
    uint8_t tmp;

    if (frequency == 0) return;

    div = 1193180 / frequency;
    outb(0x43, 0xB6);
    outb(0x42, (uint8_t)(div));
    outb(0x42, (uint8_t)(div >> 8));

    tmp = inb(0x61);
    if (tmp != (tmp | 3)) {
        outb(0x61, tmp | 3);
    }
}
//You know one day someone is going to find this source code and think:
//Damn, What was going on in this guys head while making these comments???
//To that i say: lAlllaALlalaLLAllaLAlalaLlLALAAAAA

void play_beep(void) {
    printf("Playing beep 1..\n");
    play_sound(440);
    delay(1);
    printf("Playing beep 2..\n");
    play_sound(840);
    delay(1);
    printf("Playing beep 3..\n");
    play_sound(140); //A4 o algo
    delay(1);
    nosound();
    
    printf("Beep complete!\n");
}

//Notes
void play_g(void) {
    play_sound(240);
    delay(1);
    nosound(); 
}
void play_f(void) {
    play_sound(340);
    delay(1);
    nosound(); 
}
void play_e(void) {
    play_sound(440);
    delay(1);
    nosound(); 
}
void play_d(void) {
    play_sound(540);
    delay(1);
    nosound(); 
}
void play_c(void) {
    play_sound(640);
    delay(1);
    nosound(); 
}
void play_b(void) {
    play_sound(740);
    delay(1);
    nosound(); 
}
void play_a(void) {
    play_sound(840);
    delay(1);
    nosound(); 
}