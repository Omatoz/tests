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

// Structure pour l'état de jeu
typedef struct {
    int modePlacement1;
    int modePlacement2;
    int modePlacement3;
    int modePlacement4;
    int barrierX;
    int barrierY;
    char orientation;
} GameState;

typedef struct {
    char pseudos[PSEUDO];
}Pseudos;



// Déclarations des fonctions
void initialiserPlateau(char plateau[SIZE][SIZE][4]);
void afficherPlateau(char plateau[SIZE][SIZE][4], GameState *state);
int lireTouche();
void clearConsole();
int barriereEntre(int x1, int y1, int x2, int y2,
                  char plateau[SIZE][SIZE][4]);
void deplacerPion(char plateau[SIZE][SIZE][4], int *x, int *y,
                  int direction, char joueur);
void deplacerBarriere(int *x, int *y, int direction, char joueur,
                      GameState *state);
void placerBarriere(char plateau[SIZE][SIZE][4], int x, int y,
                    char orientation);
void afficherEcranVictoire(int joueur, Pseudos pseudo[4]);
void sauvegarderPartie(const char *nomFichier,
                       char plateau[SIZE][SIZE][4], int x1, int y1, int x2, int y2,
                       int x3, int y3, int x4, int y4, int tour, int GameMode,
                       GameState *state);
void chargerPartie(const char *nomFichier,
                   char plateau[SIZE][SIZE][4], int *x1, int *y1, int *x2, int *y2,
                   int *x3, int *y3, int *x4, int *y4, int *tour, int *GameMode,
                   GameState *state);
void initialiserDemo(char plateau[SIZE][SIZE][4], int *x1, int *y1,
                     int *x2, int *y2, int *x3, int *y3, int *x4, int *y4,
                     int *tour, int *GameMode, GameState *state);
void Pseudo(Pseudos pseudo[4], int joueur, int *GameMode);

#endif // HEADER_H