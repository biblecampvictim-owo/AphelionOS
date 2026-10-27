#include "rps.h"
#include "random.h"
#include "bgcolor.h"
#include "restorescreen.h"

extern void clrscr(void);
extern int printf(const char* format, ...);
extern char keyboard_getchar(void);

void cmd_rps(void) {
    int p_score = 0;
    int c_score = 0;

    while(1){
        clrscr();
        set_grey_background();
        printf("==== ROCK PAPER SCISSORS ====\n\n");
        printf("Score - You: %d | AphelionOS: %d\n\n", p_score, c_score);
        printf("Choose between:\n");
        printf("[R] Rock\n");
        printf("[P] Paper\n");
        printf("[S] Scissors\n");
        printf("[Q] Quit\n\n");
        printf("Enter choice: ");

        char choice = keyboard_getchar();
        printf("%c\n\n", choice);

        if (choice == 'q' || choice == 'Q') {
            break;
        }
        if (choice != 'r' && choice != 'R' &&
            choice != 'p' && choice != 'P' &&
            choice != 's' && choice != 'S') {
            printf("Invalid choice! Press any key to try again.\n");
            keyboard_getchar();
            continue;
        }

        int p_val = 0;
        if (choice == 'r' || choice == 'R') p_val = 0;
        else if (choice == 'p' || choice == 'P') p_val = 1;
        else if (choice == 's' || choice == 'S') p_val = 2;

        int c_val = rand() % 3;

        const char* choices_str[] = {"Rock", "Paper", "Scissors"};

        printf("You chose: %s\n", choices_str[p_val]);
        printf("AphelionOS chose: %s\n\n", choices_str[c_val]);

        if (p_val == c_val) {
            printf("Its a tie!\n");
        } else if ((p_val == 0 && c_val == 2) ||
                   (p_val == 1 && c_val == 0) ||
                   (p_val == 2 && c_val == 1)) {
            printf("You win this round!\n");
            p_score++;
        } else {
            printf("AphelionOS wins this round!\n");
            c_score++;
        }
        printf("\nPress any key to continue...");
        keyboard_getchar();
    }
    restore_screen();
    clrscr();
    printf("\nExited Rock Paper Scissors.\n");
}
