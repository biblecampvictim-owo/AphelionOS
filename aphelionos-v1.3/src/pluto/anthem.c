//Created on Oct 31 2026 7:28 PM
#include "bgcolor.h"
#include "anthem.h"
#include "anthem_music.h"
#include "restorescreen.h"
#include "audio.h"
#include "textcolor.h"
#include "delay.h"

extern void clrscr(void);
extern int printf(const char* format, ...);
extern char keyboard_getchar(void);

void finish_anthem(void){
    clrscr();
    while(1){
        clrscr();
        printf("------------------------------- AphelionOS Anthem ------------------------------");
        printf("  *          *  *           *         *      *         *       *      *       \n");
        printf("       *  *        *  *         *        *       *           *          *    *\n");
        printf(" *           *           *         AphelionOS      *           *          *   \n");
        printf("  *  *    *     *           *         *             *     *__________________ \n");
        printf("         *       *              *    oooooo              *|                  |\n");
        printf(" *     *    *           *         o          o  *       * |  Press 'b' to    |\n");
        printf("      __________________     *  o              o      *   |  play again.     |\n");
        printf("   * |   Thanks for     |      o                o         |                  |\n");
        printf("     |    Listening!    |      o                o     *   |__________________|\n");
        printf("     |__________________|      o                o    *            *       \n");
        printf("                  *             o              o         *          *     *\n");
        printf("   *         *              *     o          o    *            *           \n");
        printf("         *           *               oooooo            *             *     \n");
        printf("                               *                  *          *     *      *\n");
        printf("     *         *          *           *       *                 *     *     \n");
        printf("  *         *        *        ___________________________       *       *    \n");
        printf(" *      *     *         *    |                           |  *      *      *  \n");
        printf("     *    *          *       |  Press 'q' twice to quit. |   *    *          \n");
        printf(" *           *               |___________________________|             *     \n");
        printf("   *        *          *             *                *        *         *   \n");
        printf("         *          *     *     *            *        *          *           \n");
        printf("    *          *            *     *            *                  *          \n*");
        printf("     *   *     *           *        *       *      *     *    *      *   *   \n");
        printf("  *           *           *                *            *      *            *");

        //LOUD WARNING IF U ARE READING THIS FROM THE LIVE
        char choice = keyboard_getchar();
        void anthem_duration();
        if (choice == 'q' || choice == 'Q'){
            break;
        }
        if (choice == 'b' || choice == 'B'){
            anthem_duration();
        }
    }
    restore_screen();
    clrscr();
    printf("\nExited Anthem.\n");
    
}


void anthem_duration(void){
    clrscr();
    printf("------------------------------- AphelionOS Anthem ------------------------------");
    printf("  *          *  *           *         *      *        *         *      \n");
    printf("       *  *        *  *         *        *        *       *        *    *    *\n");
    printf("                                * AphelionOS        *                 *      *\n");
    printf("     *         *           *                  *                       *    \n");
    printf("  *         *          *            ooooooo                *         *    *\n");
    printf(" *           *                  o        o    o     *                       *\n");
    printf("  *  *                  *    o  o        o       o     *     *     *    *    \n");
    printf("         *        *        o    o         o        o           *              \n");
    printf(" *     *   *             o     o            ooooo    o                 *   *  \n");
    printf("        *  *        *   o   o                         o      *       *      * \n");
    printf("   *     *       *     o o       oooo                  o         *            \n");
    printf("            *          o       o      o                o       *        *      \n");
    printf("     *         *       o       o      o                o    *           *     \n");
    printf("                   *   o o       oooo                  o          *           \n");
    printf(" *            *         o  o                          o            *        *  \n");
    printf("   *          *          o   o              ooooo    o     *             *    \n");
    printf("         *                o  o            o       o o                   *      \n");
    printf(" *      *      *     *      o           o         o            *      *      * \n");
    printf("     *     *         *         o       o       o           *    *              \n");
    printf("   *         *           *          ooooooo                *        *        * \n");
    printf("         *          *     *                  *        *          *            \n");
    printf("    *          *            *     *            *                  *          \n");
    printf("     *   *     *     *     *        *       *      *     *    *      *   *   *\n");
    printf("  *           *           *      *          *    *       *      *            *");
    init_anthem();
    finish_anthem();
}

void cmd_anthem(void){
    clrscr();
    while(1){
        clrscr();
        printf("------------------------------- AphelionOS Anthem ------------------------------");
        printf("  *          *  *           *         *      *         *       *      *        \n");
        printf("       *  *        *  *         *        *       *           *          *    * \n");
        printf(" *           *           *         AphelionOS      *           *          *    \n");
        printf("  *  *    *     *           *         *             *     * __________________ \n");
        printf("         *       *              *    oooooo              * |                  |\n");
        printf(" *     *    *           *         o          o  *       *  |  Press 'b' to    |\n");
        printf("        *  *                 *  o              o      *    |  start. you wont |\n");
        printf("   *     *          *          o                o          |  be able to quit |\n");
        printf("            *            *     o                o       *  |   Until it is    |\n");
        printf("     *        *       *     *  o                o    *     |    finished.     |\n");
        printf("                  *             o              o         * | (VOLUME WARNING) |\n");
        printf("   *         *              *     o          o    *        |__________________|\n");
        printf("         *           *               oooooo            *                    \n");
        printf("                               *                  *          *     *         *\n");
        printf("     *         *          *           *       *                 *     *  \n");
        printf("  *         *       *      __________________________       *         *\n");
        printf(" *      *                 |                          |  *      *    *    \n");
        printf("     *    *         *     |  Press 'q' once to quit. |   *    *          *\n");
        printf(" *           *            |__________________________|           *     *  \n");
        printf("   *        *          *             *                *        *        *   \n");
        printf("         *          *     *     *            *        *          *            *\n");
        printf("    *          *            *     *            *                  *          \n*");
        printf("     *   *     *           *        *       *      *     *    *      *   *   *\n");
        printf("  *           *           *                *            *      *            *");

        //LOUD WARNING IF U ARE READING THIS FROM THE LIVE
        char choice = keyboard_getchar();
        if (choice == 'q' || choice == 'Q'){
            break;
        }
        if (choice == 'b' || choice == 'B'){
            anthem_duration();
        }
    }
    restore_screen();
    clrscr();
    printf("\nExited Anthem.\n");
    
}
