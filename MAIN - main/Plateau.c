#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
#include "Plateau.h"
#include "Joueurs.h"
#include "Barriere.h"
#include "Score.h"
#include "Sauvegarde.h"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// Fonction pour initialiser le plateau
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
            } else if (i % 2 == 0 && j % 2 == 0) {
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

// Fonction pour afficher le plateau
void afficherPlateau(char plateau[SIZE][SIZE][4], int GameMode, GameState *state, Joueurs pseudos[]) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    printf("  ");
    for (int i = 0; i < SIZE / 2; i++) {
        printf("%2d  ", i);
    }
    printf("             INFORMATIONS JOUEURS\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            char *c = plateau[i][j];
            int isBarrierTemp = 0; // Vérifier si une barrière est en cours de placement
            if ((state->modePlacement[0] || state->modePlacement[1] ||
                 state->modePlacement[2] || state->modePlacement[3])) {
                if (state->orientation == 'V') {
                    if ((i == state->barrierX - 1 || i == state->barrierX ||
                         i == state->barrierX + 1 || i == state->barrierX + 2) &&
                        j == state->barrierY) {
                        isBarrierTemp = 1;
                    }
                } else if (state->orientation == 'H') {
                    if (i == state->barrierX &&
                        (j == state->barrierY - 1 || j == state->barrierY ||
                         j == state->barrierY + 1 || j == state->barrierY + 2)) {
                        isBarrierTemp = 1;
                    }
                }
            }

            // Afficher les éléments du plateau avec des couleurs
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
            } else if (strcmp(c, "B") == 0) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("%s ", c);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[32m%s\033[0m ", c);
#endif
            } else if (isBarrierTemp) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("B ");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[32;1mB\033[0m ");
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

        // Affichage des informations sur les joueurs et barrières
        if (i == 1) {
            printf("   Joueur 1 : %s (Pion BLEU)", pseudos[0].pseudos);
        } else if (i == 2) {
            printf("   Barrières restantes: %d", state->nb_barrieres[0]);
        } else if (i == 5) {
            printf("   Joueur 2 : %s (Pion ROUGE)", pseudos[1].pseudos);
        } else if (i == 6) {
            printf("   Barrières restantes: %d", state->nb_barrieres[1]);
        } else if (i == 9 && GameMode == 4) {
            printf("   Joueur 3 : %s (Pion VERT)", pseudos[2].pseudos);
        } else if (i == 10 && GameMode == 4) {
            printf("   Barrières restantes: %d", state->nb_barrieres[2]);
        } else if (i == 13 && GameMode == 4) {
            printf("   Joueur 4 : %s (Pion JAUNE)", pseudos[3].pseudos);
        } else if (i == 14 && GameMode == 4) {
            printf("   Barrières restantes: %d", state->nb_barrieres[3]);
        }
        printf("\n");
    }
}

// Fonction pour effacer la console
void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}
