#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

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

void sauvegarderPartie(const char *nomFichier, char plateau[SIZE][SIZE][4],
                       int x1, int y1, int x2, int y2,
                       int x3, int y3, int x4, int y4,
                       int tour, int GameMode, GameState *state, Joueurs pseudos[4]);

void chargerPartie(const char *nomFichier, char plateau[SIZE][SIZE][4],
                   int *x1, int *y1, int *x2, int *y2,
                   int *x3, int *y3, int *x4, int *y4,
                   int *tour, int *GameMode, GameState *state, Joueurs pseudos[4]);

void initialiserDemo(char plateau[SIZE][SIZE][4], int *x1, int *y1,
                     int *x2, int *y2, int *x3, int *y3,
                     int *x4, int *y4, int *tour, int *GameMode, GameState *state);

#endif //SAUVEGARDE_H
