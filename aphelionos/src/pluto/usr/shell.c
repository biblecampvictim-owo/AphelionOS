#include "string.h"
#include "stdio.h"
#include "keyboard.h"
#include "communism.h"
#include "help.h"
#include "pong.h"
#include "rps.h"
#include "bgcolor.h"
#include "die.h"
#include "audio.h"
#include "musicalkeyboard.h"
#include "anthem.h"
#include "initgraphics.h"
#include "drawing.h"
#include "sysreboot.h"
#include "chess.h"
#include "customisation.h"

char keyboard_getchar(void);

//special defininition
int strncmp(const char* s1, const char* s2, size_t n) {
    while (n && *s1 && (*s1 == *s2)) {
        s1++;
        s2++;
        n--;
    }
    if (n == 0) {
        return 0;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

void shell_getline(char* buffer, int max_size) {
    int current_index = 0;
    buffer[0] = '\0';
    while (1) {
        char c = keyboard_getchar();

        if (c == '\n' || c == '\r') {
            putc('\n');
            buffer[current_index] = '\0';
            return;
        } 
        else if (c == '\b') {
            if (current_index > 0) {
                current_index--;
                buffer[current_index] = '\0';
                putc('\b');
                putc(' ');
                putc('\b');
            }
        } 
        
        else if (current_index < max_size - 1 && c >= 32 && c <= 126) {
            buffer[current_index++] = c;
            buffer[current_index] = '\0';
            putc(c);
        }
    }
}

void shell_run(void) {
    char input_buffer[128];
    select_theme_on_boot();

    printf("\nAphelionOS v1.4\n");
    printf("Type 'help' for a list of commands.\n\n");

    while (1) {
        printf("aphelion> ");
        shell_getline(input_buffer, sizeof(input_buffer));
        //BEHOLD. THE GREAT WALL OF IFS.
        if (strlen(input_buffer) == 0) {
            continue;
        }

        if (strcmp(input_buffer, "help") == 0) {
            cmd_help();
        } //else if i have aids
        else if (strcmp(input_buffer, "fuck") == 0) {
            printf("Oui shit!\n");
        }
        else if (strcmp(input_buffer, "fuckyou") == 0) {
            printf("fuck you too i guess?? why we being rude dude why you bulleh meh\n");
        }
        else if (strcmp(input_buffer, "clear") == 0) {
            clrscr();
        }
        else if (strncmp(input_buffer, "echo ", 5) == 0) {
            printf("%s\n", input_buffer + 5);
        }
        else if (strcmp(input_buffer, "sysinfo") == 0) {
            printf(" \n");
            printf("Kernel: Pluto\n");
            printf("Kernel version: v1.1 \n");
            printf("BITS: 64\n");
            printf(" \n");
            printf("OS name: AphelionOS \n");
            printf("Mainly programmed in C and 16/32/64 bit Assembly.\n");
            printf(" \n");
            printf("Latest addition: More customisation\n");
            printf("Latest user addition: More customisation\n");
            printf("Developed by: <nvme0n1> /AKA/ <biblecampvictim-owo> OR <luccavis32>\n");
            printf(" \n");
        }
        else if (strcmp(input_buffer, "contact") == 0) {
            printf("PUBLIC CONTACT INFORMATION:\n");
            printf("YOUTUBE: Squidy_fish\n");
            printf("GITHUB: biblecampvictim-owo\n");
            printf("official repo: https://github.com/biblecampvictim-owo/AphelionOS\n");
            printf("DISCORD: luccavis32\n");
        }
        //game zone
        else if (strcmp(input_buffer, "pong") == 0) {
            cmd_pong();
        }
        else if (strcmp(input_buffer, "rps") == 0) {
            cmd_rps();
        }
        else if (strcmp(input_buffer, "musicalkeyboard") == 0) {
            cmd_keyboard();
        }
        else if (strcmp(input_buffer, "chess") == 0) {
            init_chess();
        }
        //not game zone
        else if (strcmp(input_buffer, "die") == 0) {
            cmd_die();
        }
        else if (strcmp(input_buffer, "communism") == 0) {
            cmd_communism();
        }
        else if (strcmp(input_buffer, "beep") == 0) {
            play_beep();
        }
        else if (strcmp(input_buffer, "anthem") == 0) {
            cmd_anthem();
        }

        else if (strcmp(input_buffer, "reboot") == 0) {
            sys_reboot();
        }

        //graphics
        else if (strcmp(input_buffer, "graphics") == 0) {
            g_init();
            //drawing
            g_largewhitecircle();
            g_circleoutline();
            g_circleoutline1();
            g_circleoutline2();
            g_circleoutline3();
            g_circleoutline4();
            g_circleoutline5();
            char choice = keyboard_getchar();
            if (choice == 'q' || choice == 'Q') {
                g_init(); 
            }
            //wait for esc
            while (1) {
                char c = keyboard_getchar();
                if (c == 27) {
                    break;
                }
            }
            sys_reboot(); //reboot when ESC is pressed
        }
        else {
            printf("Unknown command: %s\n", input_buffer);
        }
    }
}