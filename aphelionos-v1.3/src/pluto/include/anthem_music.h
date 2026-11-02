#ifndef ANTHEM_MUSIC_H
#define ANTHEM_MUSIC_H
//Made on Nov 1 2026 ~5:00 PM
#include "audio.h"
#include "delay.h"
#include "anthem.h"
#include "textcolor.h"
//theres probably a better way to do this but whatever

extern char keyboard_getchar(void);
extern void clrscr(void);

void init_anthem(void){
    while(1){
        //1
        red_text();
        play_e_long();
        orange_text();
        play_c_medium();
        yellow_text();
        play_a_medium();
        green_text();
        play_b_short();
        //2
        cyan_text();  
        play_b_long();
        blue_text();
        play_c_medium();
        purple_text();  //good order
        play_a_medium();
        red_text();
        play_b_medium();
        orange_text();
        play_c_medium();
        yellow_text();
        play_d_medium();
        green_text();
        play_c_medium();
        cyan_text();
        play_a_short();
        delay(0.5);
        blue_text();
        play_b_medium();
        purple_text(); //good order 2
        play_d_medium();
        red_text();
        play_c_short();
        orange_text();
        play_b_medium();
        yellow_text();
        //loop 1
        play_a_medium();
        green_text();
        play_b_medium();
        cyan_text();
        play_c_medium();
        blue_text();
        play_d_short();
        purple_text(); //good order 3
        play_c_medium();
        red_text();
        play_d_medium();
        orange_text();
        play_b_long(); //1
        yellow_text();
        play_a_medium();
        green_text();
        play_b_medium();
        cyan_text();
        play_c_medium();
        blue_text();
        play_d_short();
        purple_text(); //good order 4
        play_c_medium();
        red_text();
        play_d_medium();
        orange_text();
        play_b_long();
        yellow_text();
        play_c_medium();
        green_text();
        play_b_medium();
        cyan_text();
        play_d_long();
        blue_text();
        play_c_long();
        purple_text(); //good order 5
        play_d_medium();
        red_text();
        play_b_long();
        orange_text();
        play_c_medium();
        yellow_text();
        play_a_short();
        green_text();
        play_b_medium();
        cyan_text();
        play_d_short();
        blue_text();
        play_b_medium();
        purple_text(); //good order 6
        play_a_long();
        red_text();
        //end
        play_f_medium();
        delay(2);
        orange_text();
        play_f_medium();
        yellow_text();
        play_e_long();
        green_text();

        break;
    }
}

#endif