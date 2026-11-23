#ifndef RAINBOW_H
#define RAINBOW_H
#pragma once
//This file was created on Nov 2 2026 ~14:00
//red orange yellow green cyan blue purple
#include "textcolor.h"
#include "delay.h"
#include "bgcolor.h"
#include "restorescreen.h"
#include "anthem.h"

extern char keyboard_getchar(void);

void rainbowmode(void){
    while(1){
        red_text();
        delay(1);
        orange_text();
        delay(1);
        yellow_text();
        delay(1);
        green_text();
        delay(1);
        cyan_text();
        delay(1);
        blue_text();
        delay(1);
        purple_text();
    }
}

static void cmd_rainbowmode(void){
    red_text();
    delay(1);
    orange_text();
    delay(1);
    yellow_text();
    delay(1);
    green_text();
    delay(1);
    cyan_text();
    delay(1);
    blue_text();
    delay(1);
    purple_text();
}   
//ANTHEM.C it is a while loop,   if i try to quit with q it just loops back, meaning thats useless


#endif