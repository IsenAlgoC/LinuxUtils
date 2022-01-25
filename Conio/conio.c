/**
 * @file conio.c
 * @author Audran TOURNEUR (audran.tourneur@student.junia.com)
 * Rémi VAN BOXEM (remi.van-boxem@student.junia.com)
 * @brief Fonctions de gestion de la console (c)
 * @version 0.1
 * @date 2022-01-23
 *
 */

// Includes
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

/* reads from keypress, doesn't echo */
int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

// int _getch() {
//     return getch();
// }

/* reads from keypress, echoes */
int getche(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
