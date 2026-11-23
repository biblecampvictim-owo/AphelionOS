//Made on nov 17th 2026

#include <stdint.h>
#include "bgcolor.h"
#include "textcolor.h"
#include "stdio.h"
#include "restorescreen.h"
#include "chess.h"

extern void clrscr(void);
extern char keyboard_getchar(void);

void init_chess(void){
    char board[8][8][3] = {
        //I constantly think that its 9/11 squares for some reason
        {"r2", "h2", "b2", "q2", "k2", "b2", "h2", "r2"},
        {"p2", "p2", "p2", "p2", "p2", "p2", "p2", "p2"},
        {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
        {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
        {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
        {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
        {"p1", "p1", "p1", "p1", "p1", "p1", "p1", "p1"},
        {"r1", "h1", "b1", "q1", "k1", "b1", "h1", "r1"}
    };

    int cur_r = 4;
    int cur_c = 4;
    char hold[3] = "  ";
    int hold_r = -1;
    int hold_c = -1;

    clrscr();
    while(1){
        clrscr();

        char square[8][8][4];
        for(int r = 0; r < 8; r++){
            for(int c = 0; c < 8; c++){
                if(r == cur_r && c == cur_c){
                    if(hold[0] != ' '){
                        //you know how theres a youtuber that says "i am a never nester"? well,
                        //i am a ALWAYS nester!
                        //slot machines!
                        square[r][c][0] = 'x';
                        square[r][c][1] = '*';
                        square[r][c][2] = '\0';
                    } else {
                        square[r][c][0] = ' ';
                        square[r][c][1] = 'x';
                        square[r][c][2] = '\0';
                    }
                } else {
                    square[r][c][0] = board[r][c][0];
                    square[r][c][1] = board[r][c][1];
                    square[r][c][2] = '\0';
                }
            }
        }
        printf("-----------------------------------  Chess!  -----------------------------------");
        printf(" ________________                                                _____________ \n");
        printf("|p = pawn        |                                              | q = quit    |\n");
        printf("|b = bishop      |    _______________________________________   | a = move x  |\n");
        printf("|h = horse       | 8 | %s | %s | %s | %s | %s | %s | %s | %s |  | left        |\n", square[0][0], square[0][1], square[0][2], square[0][3], square[0][4], square[0][5], square[0][6], square[0][7]);
        printf("|k = king        |   |____|____|____|____|____|____|____|____|  | w = move x  |\n");                                    //PARTY
        printf("|q = queen       | 7 | %s | %s | %s | %s | %s | %s | %s | %s |  | up          |\n", square[1][0], square[1][1], square[1][2], square[1][3], square[1][4], square[1][5], square[1][6], square[1][7]);
        printf("|r = rook        |   |____|____|____|____|____|____|____|____|  | s = move x  |\n");
        printf("|1 = white       | 6 | %s | %s | %s | %s | %s | %s | %s | %s |  | down        |\n", square[2][0], square[2][1], square[2][2], square[2][3], square[2][4], square[2][5], square[2][6], square[2][7]);
        printf("|2 = black       |   |____|____|____|____|____|____|____|____|  | d = move x  |\n");
        printf("|x = current     | 5 | %s | %s | %s | %s | %s | %s | %s | %s |  | right       |\n", square[3][0], square[3][1], square[3][2], square[3][3], square[3][4], square[3][5], square[3][6], square[3][7]);
        printf("|selected square |   |____|____|____|____|____|____|____|____|  | p = hold    |\n");
        printf("|x* = current    | 4 | %s | %s | %s | %s | %s | %s | %s | %s |  | selected    |\n", square[4][0], square[4][1], square[4][2], square[4][3], square[4][4], square[4][5], square[4][6], square[4][7]);
        printf("|selected square |   |____|____|____|____|____|____|____|____|  | piece       |\n");
        printf("|and you are     | 3 | %s | %s | %s | %s | %s | %s | %s | %s |  | m = place in|\n", square[5][0], square[5][1], square[5][2], square[5][3], square[5][4], square[5][5], square[5][6], square[5][7]);
        printf("|holding a piece |   |____|____|____|____|____|____|____|____|  | selected    |\n");
        printf("|________________| 2 | %s | %s | %s | %s | %s | %s | %s | %s |  | square      |\n", square[6][0], square[6][1], square[6][2], square[6][3], square[6][4], square[6][5], square[6][6], square[6][7]);
        printf("                     |____|____|____|____|____|____|____|____|  |_____________|\n");
        printf("                   1 | %s | %s | %s | %s | %s | %s | %s | %s |                 \n", square[7][0], square[7][1], square[7][2], square[7][3], square[7][4], square[7][5], square[7][6], square[7][7]);
        printf("                     |____|____|____|____|____|____|____|____|                 \n");
        printf("                         a    b    c    d    e    f    g   h                    \n\n\n");
        //this is a huge milestone. i can work towards a diddy blud calc
        char choice = keyboard_getchar();
        if (choice == 'q' || choice == 'Q'){
            break;
        } else if ((choice == 'w' || choice == 'W') && cur_r > 0){
            cur_r--;
        } else if ((choice == 's' || choice == 'S') && cur_r < 7){
            cur_r++;
        } else if ((choice == 'a' || choice == 'A') && cur_c > 0){
            cur_c--;
        } else if ((choice == 'd' || choice == 'D') && cur_c < 7){
            cur_c++;
        } else if ((choice == 'p' || choice == 'P') && hold[0] == ' ' && board[cur_r][cur_c][0] != ' '){
            hold[0] = board[cur_r][cur_c][0];
            hold[1] = board[cur_r][cur_c][1];
            hold_r = cur_r;
            hold_c = cur_c;
        } else if ((choice == 'm' || choice == 'M') && hold[0] != ' '){
            //yall dont know how long i spent on this
            board[hold_r][hold_c][0] = ' ';
            board[hold_r][hold_c][1] = ' ';
            board[cur_r][cur_c][0] = hold[0];
            board[cur_r][cur_c][1] = hold[1];
            hold[0] = ' ';
            hold[1] = ' ';
            hold_r = -1;
            hold_c = -1;
        }
    }
    restore_screen();
    clrscr();
    printf("\nExited chess.\n");
}