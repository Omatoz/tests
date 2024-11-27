#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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


// Taille du Plateau 9x9
#define SIZE 19

#define PLAYER1 '1'
#define PLAYER2 '2'
#define PLAYER3 '3'
#define PLAYER4 '4'
#define PSEUDO 50

// Caractères de dessin de boîte
#define VERTICAL_LINE       "║"
#define HORIZONTAL_LINE     "═"
#define TOP_LEFT_CORNER     "╔"
#define TOP_RIGHT_CORNER    "╗"
#define BOTTOM_LEFT_CORNER  "╚"
#define BOTTOM_RIGHT_CORNER "╝"
#define INTERSECTION        "╬"

// Structure pour les pseudos et les scores des joueurs
typedef struct {
    char pseudos[PSEUDO];
    int score;
} Joueurs;

// Structure pour l'état de jeu
typedef struct {
    int modePlacement[4];
    int barrierX;
    int barrierY;
    char orientation;
    int nb_barrieres[4];
} GameState;

// Déclarations des fonctions
int afficherMenu();
void afficherAide();
void nouvellePartie (char plateau[SIZE][SIZE][4], int *x1, int *y1, int *x2, int *y2,
                       int *x3, int *y3, int *x4, int *y4, GameState *state, Joueurs pseudos[],
                       Joueurs scores[], int *nbScores, int *GameMode);

#endif // HEADER_H
