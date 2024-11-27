
#ifndef PLATEAU_H
#define PLATEAU_H

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
void initialiserPlateau(char plateau[SIZE][SIZE][4]);

void afficherPlateau(char plateau[SIZE][SIZE][4], int Gamemode, GameState *state, Joueurs pseudos[]);

void clearConsole();

#endif //PLATEAU_H
