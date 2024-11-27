#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
#include "Plateau.h"
#include "Joueurs.h"
#include "Barriere.h"
#include "Score.h"
#include "Sauvegarde.h"

// Fonction pour vérifier s'il y a une barrière entre deux positions
int barriereEntre(int x1, int y1, int x2, int y2,
                  char plateau[SIZE][SIZE][4]) {
    int midX = (x1 + x2) / 2;
    int midY = (y1 + y2) / 2;
    if (strcmp(plateau[midX][midY], "B") == 0) {
        return 1;
    }
    return 0;
}

// Fonction pour déplacer une barrière (changement de position lors de la sélection)
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
    if (*x < 1) *x = 1; // Garder x et y dans les limites du plateau
    if (*x > SIZE - 3) *x = SIZE - 3; // Ajusté pour barrière de taille 4
    if (*y < 1) *y = 1;
    if (*y > SIZE - 3) *y = SIZE - 3; // Ajusté pour barrière de taille 4
}

void placerBarriere(char plateau[SIZE][SIZE][4], int x, int y, char orientation, GameState *state, int joueur) {
    int *nb_barrieres_joueur;
    switch (joueur) { // Sélection du compteur de barrières en fonction du joueur
        case 1: nb_barrieres_joueur = &state->nb_barrieres[0]; break;
        case 2: nb_barrieres_joueur = &state->nb_barrieres[1]; break;
        case 3: nb_barrieres_joueur = &state->nb_barrieres[2]; break;
        case 4: nb_barrieres_joueur = &state->nb_barrieres[3]; break;
        default: return;
    }
    if (*nb_barrieres_joueur <= 0) {
        printf("Vous n'avez plus de barrières à placer !\n");
        return;
    }
    if (orientation == 'V') {
        if (x > 0 && x < SIZE - 3) {
            strcpy(plateau[x - 1][y], "B");
            strcpy(plateau[x][y], "B");
            strcpy(plateau[x + 1][y], "B");
            strcpy(plateau[x + 2][y], "B");
            (*nb_barrieres_joueur)--;
        }
    } else if (orientation == 'H') {
        if (y > 0 && y < SIZE - 3) {
            strcpy(plateau[x][y - 1], "B");
            strcpy(plateau[x][y], "B");
            strcpy(plateau[x][y + 1], "B");
            strcpy(plateau[x][y + 2], "B");
            (*nb_barrieres_joueur)--;
        }
    }
}


// Fonction pour vérifier si un chemin est valide pour un joueur
int estCheminValide(char plateau[SIZE][SIZE][4], int startX, int startY, int targetRow) {
    return 1; // Désactivation de la vérification du chemin
}

// Fonction pour vérifier si une barrière peut être placée (désactivée)
int peutPlacerBarriere(char plateau[SIZE][SIZE][4], int x, int y, char orientation,
                       int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GameMode) {
    // Autoriser toujours le placement de la barrière
    return 1;
}

