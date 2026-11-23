#include "help.h"
#include "bgcolor.h"
#include "restorescreen.h"
#include "stdio.h"

extern char keyboard_getchar(void);

static const char* help_pages[] = {
    "========= HELP =========\n\n"
    "GENERAL COMMANDS\n\n"
    "help - Prints this help menu\n"
    "clear - Clears the screen\n"
    "echo (...) - Echos whatever you put after Echo \n"
    "sysinfo - Shows system related information\n"
    "reboot - Reboot the system\n"
    "contact - Contact me!\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "========= HELP =========\n\n"
    "BOOK RELATED COMMANDS\n\n"
    "communism - Read Chapter one of the communist manifesto.\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "========= HELP =========\n\n"
    "SONG RELATED COMMANDS\n\n"
    "anthem - Play the official AphelionOS Anthem!\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "========= HELP =========\n\n"
    "GAME RELATED COMMANDS\n\n"
    "pong - Opens a two player pong game\n"
    "chess - Play two player chess!\n"
    "rps - Rock Paper Scissors!!\n"
    "musicalkeyboard - (VOLUME WARNING) Opens a musical keyboard!\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "========= HELP =========\n\n"
    "GRAPHICS RELATED COMMANDS\n\n"
    "graphics - Enter graphics mode and see the logo! Press 'ESC' to reboot.\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "========= HELP =========\n\n"
    "JOKE/TEST COMMANDS\n\n"
    "fuck\n"
    "fuckyou\n"
    "die - (VOLUME WARNING) Cause a critical system interrupt on purpose\n"
    "beep - (VOLUME WARNING) Play three beeps\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",
};
//fuck that was, not a lot
#define TOTAL_PAGES 6

void cmd_help(void) {
    int current_page = 0;
    unsigned char prev_color = g_vga_color;
    while (1) {
        clrscr();
        printf("%s\n", help_pages[current_page]);
        set_purple_background_helpc();

        char key = keyboard_getchar();
        if (key == 'a' || key == 'A') {
            if (current_page > 0) {
                current_page--;
            }
        }
        else if (key == 'd' || key == 'D') {
            if (current_page < TOTAL_PAGES - 1) {
                current_page++;
            }
        }
        else if (key == 'q' || key == 'Q') {
            break; 
        }
    }

    restore_screen();
    apply_vga_attr(prev_color);
    clrscr();
    printf("\nReturned to shell.\n");
}