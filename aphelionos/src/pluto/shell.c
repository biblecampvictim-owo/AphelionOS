#include "string.h"
#include "stdio.h"
#include "keyboard.h"
#include "communism.h"
#include "help.h"
#include "pong.h"
#include "rps.h"
#include "bgcolor.h"
#include "die.h"

//kanker
char keyboard_getchar(void);

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

    printf("\nAphelionOS v1.0.1\n");
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
            printf("Kernel version: v0.8.0 \n");
            printf("BITS: 32\n");
            printf(" \n");
            printf("OS name: AphelionOS \n");
            printf("Mainly programmed in C and 16 + 32 bit Assembly.\n");
            printf(" \n");
            printf("This Operating System is only to be run in QEMU.\n");
            printf("If you run it anywhere else, expect bugs.\n");
            printf("This OS has not been tested to be emulated on windows, please run it on Linux!\n");
            printf("PS if u didn't know; run it with ./run.sh\n");
            printf("Latest addition: ERROR messages have become red!\n");
            printf("Latest user addition: Pong\n");
            printf("Developed by: <nvme0n1> /AKA/ <biblecampvictim-owo>\n");
            printf(" \n");
        }
        else if (strcmp(input_buffer, "contact") == 0) {
            printf("PUBLIC CONTACT INFORMATION:\n");
            printf("GITHUB: biblecampvictim-owo\n");
            printf("official repo: https://github.com/biblecampvictim-owo/AphelionOS\n");
            printf("DISCORD: eevee540_tuff\n");
        }
        //game zone
        else if (strcmp(input_buffer, "pong") == 0) {
            cmd_pong();
        }
        else if (strcmp(input_buffer, "rps") == 0) {
            cmd_rps();
        }
        
        else if (strcmp(input_buffer, "die") == 0) {
            cmd_die();
        }
        else if (strcmp(input_buffer, "communism") == 0) {
            cmd_communism();
        }
        else {
            printf("Unknown command: %s\n", input_buffer);
        }
    }
}