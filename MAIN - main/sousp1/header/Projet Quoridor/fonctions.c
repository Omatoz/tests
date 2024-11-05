#include <stdio.h>
#include "header.h"

// Définition des variables globales
int modePlacement1 = 0;
int modePlacement2 = 0;
int modePlacement3 = 0;
int modePlacement4 = 0;
int barrierX, barrierY;
char orientation = 'V'; // Orientation par défaut de la barrière

void initialiserPlateau(char plateau[SIZE][SIZE][4]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            plateau[i][j][0] = '\0';

            if (i == 0 && j == 0) {
                strcpy(plateau[i][j], TOP_LEFT_CORNER);
            } else if (i == 0 && j == SIZE - 1) {
                strcpy(plateau[i][j], TOP_RIGHT_CORNER);
            } else if (i == SIZE - 1 && j == 0) {
                strcpy(plateau[i][j], BOTTOM_LEFT_CORNER);
            } else if (i == SIZE - 1 && j == SIZE - 1) {
                strcpy(plateau[i][j], BOTTOM_RIGHT_CORNER);
            } else if (i == 0 || i == SIZE - 1) {
                strcpy(plateau[i][j], HORIZONTAL_LINE);
            } else if (j == 0 || j == SIZE - 1) {
                strcpy(plateau[i][j], VERTICAL_LINE);
            }
                // Intérieur du plateau
            else if (i % 2 == 0 && j % 2 == 0) {
                strcpy(plateau[i][j], INTERSECTION);
            } else if (i % 2 == 0) {
                strcpy(plateau[i][j], HORIZONTAL_LINE);
            } else if (j % 2 == 0) {
                strcpy(plateau[i][j], VERTICAL_LINE);
            } else {
                strcpy(plateau[i][j], " ");
            }
        }
    }
}

void afficherPlateau(char plateau[SIZE][SIZE][4], int barrierX, int barrierY, int modePlacement1, int modePlacement2, int modePlacement3, int modePlacement4, char orientation) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            char *c = plateau[i][j];
            int isBarrierTemp = 0;

            // Afficher la barrière temporaire si le joueur est en mode placement
            if ((modePlacement1 || modePlacement2 || modePlacement3 || modePlacement4)) {
                if (orientation == 'V') {
                    if ((i == barrierX - 1 || i == barrierX || i == barrierX + 1 || i == barrierX + 2) && j == barrierY) {
                        isBarrierTemp = 1;
                    }
                } else if (orientation == 'H') {
                    if (i == barrierX && (j == barrierY - 1 || j == barrierY || j == barrierY + 1 || j == barrierY + 2)) {
                        isBarrierTemp = 1;
                    }
                }
            }

            if (strcmp(c, "1") == 0) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf("o ");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[34mo\033[0m ");
#endif
            } else if (strcmp(c, "2") == 0) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                printf("o ");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[31mo\033[0m ");
#endif
            } else if (strcmp(c, "|") == 0 || strcmp(c, "-") == 0) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("%s ", c);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[32m%s\033[0m ", c);
#endif
            } else if (strcmp(c, "3") == 0) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("o ");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[32mo\033[0m ");

#endif
            } else if (strcmp(c, "4") == 0) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("o ");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[33mo\033[0m ");
#endif
            } else if (isBarrierTemp) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("%s ", orientation == 'V' ? "|" : "-");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[32;1m%s\033[0m ", orientation == 'V' ? "|" : "-");
#endif
            } else if (i == 0 || i == SIZE - 1 || j == 0 || j == SIZE - 1) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                printf("%s ", c);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[0;33m%s\033[0m ", c);
#endif
            } else {
                printf("%s ", c);
            }
        }
        printf("\n");
    }
}

#ifdef _WIN32
int lireTouche() {
    int ch = getch();
    if (ch == 0 || ch == 224) {
        ch = getch();
        switch (ch) {
            case 72: return 'U'; // Flèche haut
            case 80: return 'D'; // Flèche bas
            case 75: return 'L'; // Flèche gauche
            case 77: return 'R'; // Flèche droite
            default: return 0;
        }
    } else {
        return ch; // Retourne le caractère tel quel pour les autres touches
    }
}
#else
void initialiserTermios(int echo) {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);
    newt.c_lflag &= ~ICANON; // Mode non canonique
    newt.c_lflag &= echo ? ECHO : ~ECHO; // Activer/désactiver l'écho
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void reinitialiserTermios() {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);
    newt.c_lflag |= ICANON;
    newt.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, &newt);
}

int lireTouche() {
    int ch = getchar();
    if (ch == '\033') { // Séquence d'échappement
        getchar(); // Sauter le '['
        switch(getchar()) {
            case 'A': return 'U'; // Flèche haut
            case 'B': return 'D'; // Flèche bas
            case 'C': return 'R'; // Flèche droite
            case 'D': return 'L'; // Flèche gauche
            default: return 0;
        }
    } else {
        return ch;
    }
}
#endif

int barriereEntre(int x1, int y1, int x2, int y2, char plateau[SIZE][SIZE][4]) {
    int midX = (x1 + x2) / 2;
    int midY = (y1 + y2) / 2;
    if (strcmp(plateau[midX][midY], "|") == 0 || strcmp(plateau[midX][midY], "-") == 0) {
        return 1;
    }
    return 0;
}

void deplacerPion(char plateau[SIZE][SIZE][4], int *x, int *y, int direction, char joueur) {
    int newX = *x, newY = *y;

    if (joueur == PLAYER1) {
        if (direction == 'z' && *x > 1) {
            newX -= 2;
        } else if (direction == 's' && *x < SIZE - 2) {
            newX += 2;
        } else if (direction == 'q' && *y > 1) {
            newY -= 2;
        } else if (direction == 'd' && *y < SIZE - 2) {
            newY += 2;
        } else {
            return;
        }
    } else if (joueur == PLAYER2) {
        if (direction == 'U' && *x > 1) {
            newX -= 2;
        } else if (direction == 'D' && *x < SIZE - 2) {
            newX += 2;
        } else if (direction == 'L' && *y > 1) {
            newY -= 2;
        } else if (direction == 'R' && *y < SIZE - 2) {
            newY += 2;
        } else {
            return;
        }
    } else if (joueur == PLAYER3) {
        if (direction == 't' && *x > 1) {
            newX -= 2;
        } else if (direction == 'g' && *x < SIZE - 2) {
            newX += 2;
        } else if (direction == 'f' && *y > 1) {
            newY -= 2;
        } else if (direction == 'h' && *y < SIZE - 2) {
            newY += 2;
        } else {
            return;
        }
    } else if (joueur == PLAYER4) {
        if (direction == 'i' && *x > 1) {
            newX -= 2;
        } else if (direction == 'k' && *x < SIZE - 2) {
            newX += 2;
        } else if (direction == 'j' && *y > 1) {
            newY -= 2;
        } else if (direction == 'l' && *y < SIZE - 2) {
            newY += 2;
        } else {
            return;
        }
    }

    if (barriereEntre(*x, *y, newX, newY, plateau)) {
        return;
    }

    if (strcmp(plateau[newX][newY], " ") == 0) {
        strcpy(plateau[*x][*y], " ");
        *x = newX;
        *y = newY;
        char strJoueur[2] = {joueur, '\0'};
        strcpy(plateau[*x][*y], strJoueur);
    }
}

void deplacerBarriere(int *x, int *y, int direction, char joueur) {
    int deltaX = 0, deltaY = 0;

    if (joueur == PLAYER1) {
        if (direction == 'z') {
            deltaX = -1;
        } else if (direction == 's') {
            deltaX = 1;
        } else if (direction == 'q') {
            deltaY = -1;
        } else if (direction == 'd') {
            deltaY = 1;
        }
    } else if (joueur == PLAYER2) {
        if (direction == 'U') {
            deltaX = -1;
        } else if (direction == 'D') {
            deltaX = 1;
        } else if (direction == 'L') {
            deltaY = -1;
        } else if (direction == 'R') {
            deltaY = 1;
        }
    } else if (joueur == PLAYER3) {
        if (direction == 't') {
            deltaX = -1;
        } else if (direction == 'g') {
            deltaX = 1;
        } else if (direction == 'f') {
            deltaY = -1;
        } else if (direction == 'h') {
            deltaY = 1;
        }
    } else if (joueur == PLAYER4) {
        if (direction == 'i') {
            deltaX = -1;
        } else if (direction == 'k') {
            deltaX = 1;
        } else if (direction == 'j') {
            deltaY = -1;
        } else if (direction == 'l') {
            deltaY = 1;
        }
    }

    *x += deltaX;
    *y += deltaY;

    // Garder x et y dans les limites du plateau
    if (*x < 1) *x = 1;
    if (*x > SIZE - 3) *x = SIZE - 3; // Ajusté pour barrière de taille 4
    if (*y < 1) *y = 1;
    if (*y > SIZE - 3) *y = SIZE - 3; // Ajusté pour barrière de taille 4
}

void placerBarriere(char plateau[SIZE][SIZE][4], int x, int y, char orientation) {
    if (orientation == 'V') {
        if (x > 0 && x < SIZE - 3) {
            // Placer une barrière verticale (sur quatre cases)
            strcpy(plateau[x - 1][y], "|");
            strcpy(plateau[x][y], "|");
            strcpy(plateau[x + 1][y], "|");
            strcpy(plateau[x + 2][y], "|");
        }
    } else if (orientation == 'H') {
        if (y > 0 && y < SIZE - 3) {
            // Placer une barrière horizontale (sur quatre cases)
            strcpy(plateau[x][y - 1], "-");
            strcpy(plateau[x][y], "-");
            strcpy(plateau[x][y + 1], "-");
            strcpy(plateau[x][y + 2], "-");
        }
    }
}
