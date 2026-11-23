#include "bgcolor.h"
#include "customisation.h"
#include "stdio.h"

extern void clrscr(void);
extern char keyboard_getchar(void);

// IDEA: Graphical pluto while this text plays.

void select_theme_on_boot(void) {
    while (1) {
        set_black_background();
        clrscr();
        printf("       ____________________________________________________________________\n");
        printf("      |    Welcome! If you are seeing this the shell has initialized.      |\n");
        printf("      |____________________________________________________________________|\n\n\n");
        printf("            Type in the number to select the shell theme (Default = 2)\n\n\n");
        printf("                       1) White background, blue text\n");
        printf("                       2) Black background, white text\n");
        printf("                       3) Black background, green text\n");
        printf("                       4) Black background, red text\n");

        char c = keyboard_getchar();
        if (c == '1') {
            vga_disable_blink();
            clrscr();
            set_white_blue_background();
            break;
        } else if (c == '2') {
            vga_disable_blink();
            clrscr();
            set_black_background();
            break;
        } else if (c == '3') {
            vga_disable_blink();
            clrscr();
            set_black_green_background();
            break;
        }
        else if (c == '4') {
            vga_disable_blink();
            clrscr();
            set_black_red_background();
            break;
        }
    }
}