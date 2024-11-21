// sousp1.c
#include "header.h"

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

void afficherPlateau(char plateau[SIZE][SIZE][4], GameState *state) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            char *c = plateau[i][j];
            int isBarrierTemp = 0;

            if ((state->modePlacement1 || state->modePlacement2 ||
                 state->modePlacement3 || state->modePlacement4)) {
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

            if (strcmp(c, "1") == 0) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole,
                                        FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf("o ");
                SetConsoleTextAttribute(hConsole,
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[34mo\033[0m ");
#endif
            } else if (strcmp(c, "2") == 0) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                printf("o ");
                SetConsoleTextAttribute(hConsole,
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[31mo\033[0m ");
#endif
            } else if (strcmp(c, "3") == 0) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("o ");
                SetConsoleTextAttribute(hConsole,
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[32mo\033[0m ");
#endif
            } else if (strcmp(c, "4") == 0) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole,
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("o ");
                SetConsoleTextAttribute(hConsole,
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[33mo\033[0m ");
#endif
            } else if (strcmp(c, "B") == 0) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("%s ", c);
                SetConsoleTextAttribute(hConsole,
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[32m%s\033[0m ", c);
#endif
            } else if (isBarrierTemp) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole,
                                        FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printf("B ");
                SetConsoleTextAttribute(hConsole,
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
                printf("\033[32;1mB\033[0m ");
#endif
            } else if (i == 0 || i == SIZE - 1 || j == 0 || j == SIZE - 1) {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole,
                                        FOREGROUND_RED | FOREGROUND_GREEN);
                printf("%s ", c);
                SetConsoleTextAttribute(hConsole,
                                        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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

int lireTouche() {
#ifdef _WIN32
    // Code spécifique à Windows
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
            case 72: return 'U'; // Flèche haut
            case 80: return 'D'; // Flèche bas
            case 75: return 'L'; // Flèche gauche
            case 77: return 'R'; // Flèche droite
            default: return 0;
        }
    } else {
        return ch;
    }
#else
    // Code spécifique à Unix/Linux
    struct termios oldt, newt;
    int ch;

    // Désactiver l'écho et la mise en tampon
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    if (ch == '\033') {
        getchar(); // Ignorer le caractère '['
        switch(getchar()) {
            case 'A': ch = 'U'; break; // Flèche haut
            case 'B': ch = 'D'; break; // Flèche bas
            case 'C': ch = 'R'; break; // Flèche droite
            case 'D': ch = 'L'; break; // Flèche gauche
            default: ch = 0;
        }
    }

    // Restaurer les paramètres du terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}

int barriereEntre(int x1, int y1, int x2, int y2,
                  char plateau[SIZE][SIZE][4]) {
    int midX = (x1 + x2) / 2;
    int midY = (y1 + y2) / 2;
    if (strcmp(plateau[midX][midY], "B") == 0) {
        return 1;
    }
    return 0;
}

void deplacerPion(char plateau[SIZE][SIZE][4], int *x, int *y,
                  int direction, char joueur) {
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
    // Ajoutez le code pour les joueurs 3 et 4 si nécessaire

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

void deplacerBarriere(int *x, int *y, int direction, char joueur,
                      GameState *state) {
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
    }
    // Ajoutez le code pour les joueurs 3 et 4 si nécessaire

    *x += deltaX;
    *y += deltaY;

    // Garder x et y dans les limites du plateau
    if (*x < 1) *x = 1;
    if (*x > SIZE - 3) *x = SIZE - 3; // Ajusté pour barrière de taille 4
    if (*y < 1) *y = 1;
    if (*y > SIZE - 3) *y = SIZE - 3; // Ajusté pour barrière de taille 4
}

void placerBarriere(char plateau[SIZE][SIZE][4], int x, int y,
                    char orientation) {
    if (orientation == 'V') {
        if (x > 0 && x < SIZE - 3) {
            strcpy(plateau[x - 1][y], "B");
            strcpy(plateau[x][y], "B");
            strcpy(plateau[x + 1][y], "B");
            strcpy(plateau[x + 2][y], "B");
        }
    } else if (orientation == 'H') {
        if (y > 0 && y < SIZE - 3) {
            strcpy(plateau[x][y - 1], "B");
            strcpy(plateau[x][y], "B");
            strcpy(plateau[x][y + 1], "B");
            strcpy(plateau[x][y + 2], "B");
        }
    }
}

void afficherEcranVictoire(int joueur) {
    printf("\n\n");
    printf("********************************\n");
    printf("*                              *\n");
    printf("*    Le joueur %d a gagné !     *\n", joueur);
    printf("*                              *\n");
    printf("********************************\n");
    printf("\n\n");
}
void sauvegarderPartie(const char *nomFichier,
                       char plateau[SIZE][SIZE][4], int x1, int y1, int x2, int y2,
                       int x3, int y3, int x4, int y4, int tour, int GameMode,
                       GameState *state) {

    FILE *f = fopen(nomFichier, "wb");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
        return;
    }

    fwrite(plateau, sizeof(char), SIZE * SIZE * 4, f);
    fwrite(&x1, sizeof(int), 1, f);
    fwrite(&y1, sizeof(int), 1, f);
    fwrite(&x2, sizeof(int), 1, f);
    fwrite(&y2, sizeof(int), 1, f);
    fwrite(&x3, sizeof(int), 1, f);
    fwrite(&y3, sizeof(int), 1, f);
    fwrite(&x4, sizeof(int), 1, f);
    fwrite(&y4, sizeof(int), 1, f);
    fwrite(&tour, sizeof(int), 1, f);
    fwrite(&GameMode, sizeof(int), 1, f);
    fwrite(state, sizeof(GameState), 1, f);

    fclose(f);
    printf("Partie sauvegardée dans le fichier '%s'.\n", nomFichier);
}

void chargerPartie(const char *nomFichier,
                   char plateau[SIZE][SIZE][4], int *x1, int *y1, int *x2, int *y2,
                   int *x3, int *y3, int *x4, int *y4, int *tour, int *GameMode,
                   GameState *state) {

    FILE *f = fopen(nomFichier, "rb");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
        exit(EXIT_FAILURE);
    }

    fread(plateau, sizeof(char), SIZE * SIZE * 4, f);
    fread(x1, sizeof(int), 1, f);
    fread(y1, sizeof(int), 1, f);
    fread(x2, sizeof(int), 1, f);
    fread(y2, sizeof(int), 1, f);
    fread(x3, sizeof(int), 1, f);
    fread(y3, sizeof(int), 1, f);
    fread(x4, sizeof(int), 1, f);
    fread(y4, sizeof(int), 1, f);
    fread(tour, sizeof(int), 1, f);
    fread(GameMode, sizeof(int), 1, f);
    fread(state, sizeof(GameState), 1, f);

    fclose(f);
    printf("Partie chargée depuis le fichier '%s'.\n", nomFichier);
}

void initialiserDemo(char plateau[SIZE][SIZE][4], int *x1, int *y1,
                     int *x2, int *y2, int *x3, int *y3, int *x4, int *y4,
                     int *tour, int *GameMode, GameState *state) {

    // Initialiser le plateau
    initialiserPlateau(plateau);

    // Définir le mode de jeu à 2 joueurs
    *GameMode = 2;

    // Positions avancées des pions
    *x1 = 7;  *y1 = 9;   // Position avancée pour le joueur 1
    *x2 = 11; *y2 = 9;   // Position avancée pour le joueur 2

    // Placer les pions sur le plateau
    strcpy(plateau[*x1][*y1], "1");
    strcpy(plateau[*x2][*y2], "2");

    // Placer des barrières pour simuler une partie avancée
    placerBarriere(plateau, 6, 9, 'H');
    placerBarriere(plateau, 8, 7, 'V');
    placerBarriere(plateau, 10, 9, 'H');
    placerBarriere(plateau, 12, 11, 'V');

    // Initialiser l'état du jeu
    *tour = 1; // C'est au tour du joueur 1 de jouer
    *state = (GameState){0, 0, 0, 0, 0, 0, 'V'};
}

void Pseudo(char pseudo1[PSEUDO], char pseudo2[PSEUDO], char pseudo3[PSEUDO],char pseudo4[PSEUDO], int joueur, int *GameMode) {
    if (*GameMode == 2) {
        printf("Saisir le pseudo du premier joueur (50 caractères maximum) :");
        fgets(pseudo1,PSEUDO,stdin);
        printf("Saisir le pseudo du deuxième joueur (50 caractères maximum) :");
        fgets(pseudo2,PSEUDO,stdin);

        if (joueur == 1) {
            for ( int i = 0 ; i < PSEUDO ; i++) {
                printf("%c", pseudo1[i]);
            }
        } else if (joueur == 2) {
            for ( int j = 0 ; j < PSEUDO ; j++) {
                printf("%c", pseudo2[j]);
            }
        } else if (joueur == 3) {
            for ( int k = 0 ; k < PSEUDO ; k++) {
                printf("%c", pseudo3[k]);
            }
        } else if (joueur == 4) {
            for ( int l = 0 ; l < PSEUDO ; l++) {
                printf("%c", pseudo4[l]);
            }
        }
    }
    else if(*GameMode == 4) {
        printf("Saisir le pseudo du premier joueur (50 caractères maximum) :");
        fgets(pseudo1,PSEUDO,stdin);
        printf("Saisir le pseudo du deuxième joueur (50 caractères maximum) :");
        fgets(pseudo2,PSEUDO,stdin);
        printf("Saisir le pseudo du troisième joueur (50 caractères maximum) :");
        fgets(pseudo3,PSEUDO,stdin);
        printf("Saisir le pseudo du quatrième joueur (50 caractères maximum) :");
        fgets(pseudo4,PSEUDO,stdin);
    }
}

void Gagnant(int joueur) {

}
