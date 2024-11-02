#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#else
#include <termios.h>
#include <unistd.h>
#endif

#define SIZE 19
#define PLAYER1 '1'
#define PLAYER2 '2'
#define PLAYER3 '3'
#define PLAYER4 '4'

// Caractères de dessin de boîte
#define VERTICAL_LINE   "║"
#define HORIZONTAL_LINE "═"
#define TOP_LEFT_CORNER     "╔"
#define TOP_RIGHT_CORNER    "╗"
#define BOTTOM_LEFT_CORNER  "╚"
#define BOTTOM_RIGHT_CORNER "╝"
#define INTERSECTION    "╬"

// Variables globales pour le placement des barrières
extern int modePlacement1;
extern int modePlacement2;
extern int modePlacement3;
extern int modePlacement4;
extern int barrierX;
extern int barrierY;
extern char orientation;

// Déclarations des fonctions
void initialiserPlateau(char plateau[SIZE][SIZE][4]);
void afficherPlateau(char plateau[SIZE][SIZE][4], int barrierX, int barrierY, int modePlacement1, int modePlacement2, int modePlacement3, int modePlacement4,char orientation);
int lireTouche();
int barriereEntre(int x1, int y1, int x2, int y2, char plateau[SIZE][SIZE][4]);
void deplacerPion(char plateau[SIZE][SIZE][4], int *x, int *y, int direction, char joueur);
void deplacerBarriere(int *x, int *y, int direction, char joueur);
void placerBarriere(char plateau[SIZE][SIZE][4], int x, int y, char orientation);
void nom(char* nomJoueur, int numeroJoueur);
#endif //HEADER_H
