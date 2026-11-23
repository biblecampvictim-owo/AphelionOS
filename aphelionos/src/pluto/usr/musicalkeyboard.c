//Created on Oct 28 2026 9:36 PM
#include "bgcolor.h"
#include "musicalkeyboard.h"
#include "restorescreen.h"
#include "audio.h"
#include "stdio.h"

extern char keyboard_getchar(void);

void cmd_keyboard(void) {
    unsigned char prev_color = g_vga_color;
    char choice = ' ';
    while(1){
        clrscr();
        set_cyan_background();
        //it took me some time to get this right
        printf("------------------------------- Musical Keyboard -------------------------------\n\n\n\n");
        printf("                       Current Key: %c \n\n\n\n\n\n", choice);
        printf("                        A    B    C    D    E    F    G     \n\n\n\n\n\n");
        
        printf("                               Press q to quit.\n");
        choice = keyboard_getchar();
        if (choice == 'q' || choice == 'Q') {
            break;
        }
        //here come the notes...
        if (choice == 'a' || choice == 'A') {
            play_a();
        }
        if (choice == 'b' || choice == 'B') {
            play_b();
        }
        if (choice == 'c' || choice == 'C') {
            play_c();
        }
        if (choice == 'd' || choice == 'D') {
            play_d();
        }
        if (choice == 'e' || choice == 'E') {
            play_e();
        }
        if (choice == 'f' || choice == 'F') {
            play_f();
        }             
        if (choice == 'g' || choice == 'G') {
            play_g();
        }                             

    }
    restore_screen();
    apply_vga_attr(prev_color);
    clrscr();
    printf("\nExited Musical Keyboard.\n");
}
//im going make such good songs with this, like.. Idk