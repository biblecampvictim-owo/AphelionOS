#include "pong.h"

#define BOARD_WIDTH 40
#define BOARD_HEIGHT 15

extern void clrscr(void);
extern int printf(const char* format, ...);
extern char keyboard_getchar(void);
//blue background for the fun of it
static void set_blue_background(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x1F << 8) | c;
    }
}
static void restore_screen(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x07 << 8) | c;
    }
}

void cmd_pong(void) {
    int p1_y = BOARD_HEIGHT / 2 - 1;
    int p2_y = BOARD_HEIGHT / 2 - 1;

    int ball_x = BOARD_WIDTH / 2;
    int ball_y = BOARD_HEIGHT / 2;
    int ball_dx = 1;
    int ball_dy = 1;

    int p1_score = 0;
    int p2_score = 0;

    while (1) {
        clrscr();
        set_blue_background(); //im blue dabedeee lalalaaaa

        printf("=== PONG (in alpha, expect bugs!) ===\n");
        printf("P1 (W/S): %d  |  P2 (I/K): %d  |  [Q] Exit\n\n", p1_score, p2_score);

        for (int y = 0; y < BOARD_HEIGHT; y++) {
            printf("|");
            for (int x = 0; x < BOARD_WIDTH; x++) {
                if (x == 0 && (y == p1_y || y == p1_y + 1)) {
                    printf("]");
                } else if (x == BOARD_WIDTH - 1 && (y == p2_y || y == p2_y + 1)) {
                    printf("[");
                } else if (x == ball_x && y == ball_y) {
                    printf("O");
                } else {
                    printf(" ");
                }
            }
            printf("|\n");
        }

        printf("Controls: W/S = Player 1 | I/K = Player 2 | Q = Quit\n");
        //my mind is about to fucking explode
        ball_x += ball_dx;
        ball_y += ball_dy;

        if (ball_y <= 0 || ball_y >= BOARD_HEIGHT - 1) {
            ball_dy = -ball_dy;
        }

        if (ball_x == 1 && (ball_y == p1_y || ball_y == p1_y + 1)) {
            ball_dx = -ball_dx;
        }

        if (ball_x == BOARD_WIDTH - 2 && (ball_y == p2_y || ball_y == p2_y + 1)) {
            ball_dx = -ball_dx;
        }

        if (ball_x < 0) {
            p2_score++;
            ball_x = BOARD_WIDTH / 2;
            ball_y = BOARD_HEIGHT / 2;
            ball_dx = 1;
        } else if (ball_x >= BOARD_WIDTH) {
            p1_score++;
            ball_x = BOARD_WIDTH / 2;
            ball_y = BOARD_HEIGHT / 2;
            ball_dx = -1;
        }

        char key = keyboard_getchar();

        if (key == 'q' || key == 'Q') {
            break;
        }

        if (key == 'w' || key == 'W') {
            if (p1_y > 0) p1_y--;
        } else if (key == 's' || key == 'S') {
            if (p1_y < BOARD_HEIGHT - 2) p1_y++;
        }
        if (key == 'i' || key == 'I') {
            if (p2_y > 0) p2_y--;
        } else if (key == 'k' || key == 'K') {
            if (p2_y < BOARD_HEIGHT - 2) p2_y++;
        }
        //very safe, Trust me!
        for (volatile int i = 0; i < 2000000; i++);
    }

    restore_screen();
    clrscr();
    printf("\nExited Pong.\n");
}