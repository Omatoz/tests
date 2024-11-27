//
// Created by cazau on 11/26/2024.
//

#ifndef JOUEURS_H
#define JOUEURS_H

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
void jeu(int *tour, int GameMode, char plateau[SIZE][SIZE][4], GameState *state, Joueurs pseudos[4]);

void deplacerPion(char plateau[SIZE][SIZE][4], int *x, int *y, char direction, char joueur,
                  int x1, int y1, int x2, int y2,
                  int x3, int y3, int x4, int y4, int GameMode);

int lireTouche();

void Pseudo(Joueurs pseudosPartie[4], int *GameMode, Joueurs scores[], int *nbScores);

void afficherEcranVictoire(int joueur, Joueurs pseudos[4]);

#endif //JOUEURS_H
