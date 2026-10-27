#include "help.h"
#include "bgcolor.h"
#include "restorescreen.h"

extern void clrscr(void);
extern int printf(const char* format, ...);
extern char keyboard_getchar(void);

static const char* help_pages[] = {
    "========= HELP =========\n\n"
    "GENERAL COMMANDS\n\n"
    "help - Prints this help menu\n"
    "clear - Clears the screen\n"
    "echo (...) - Echos whatever you put after Echo \n"
    "sysinfo - Shows system related information\n"
    "contact - Contact me!\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "========= HELP =========\n\n"
    "BOOK RELATED COMMANDS\n\n"
    "communism - Read Chapter one of the communist manifesto.\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "========= HELP =========\n\n"
    "GAME RELATED COMMANDS\n\n"
    "pong - Opens a two player pong game\n"
    "rps - Rock Paper Scissors!!\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "========= HELP =========\n\n"
    "JOKE/TEST COMMANDS\n\n"
    "fuck\n"
    "fuckyou\n"
    "die - Cause a critical system interrupt on purpose\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",
};
//fuck that was, not a lot
#define TOTAL_PAGES 4

void cmd_help(void) {
    int current_page = 0;
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
    clrscr();
    printf("\nReturned to shell.\n");
}