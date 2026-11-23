#ifndef DELAY_H
#define DELAY_H
//This variable was made an independent header file on The 29th of Oct. 2026 at ~11:10 PM.
//This variable originally belonged to audio.c as audio_delay.  

//woof
static void delay(int number_of_seconds) {

    long total_iterations = (long)number_of_seconds * 100000000;
    
    for (volatile long i = 0; i < total_iterations; i++) {
        __asm__ __volatile__("nop");
    }
}

#endif