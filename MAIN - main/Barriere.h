#ifndef BARRIERE_H
#define BARRIERE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Menu.h"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

// Déclarations des fonctions
int barriereEntre(int x1, int y1, int x2, int y2, char plateau[SIZE][SIZE][4]);

void deplacerBarriere(int *x, int *y, int direction, char joueur, GameState *state);

void placerBarriere(char plateau[SIZE][SIZE][4], int x, int y, char orientation, GameState *state, int joueur);

int estCheminValide(char plateau[SIZE][SIZE][4], int startX, int startY, int targetRow);

int peutPlacerBarriere(char plateau[SIZE][SIZE][4], int x, int y, char orientation,
                       int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GameMode);
#endif //BARRIERE_H
