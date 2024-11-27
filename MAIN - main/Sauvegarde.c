#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
#include "Plateau.h"
#include "Joueurs.h"
#include "Barriere.h"
#include "Score.h"
#include "Sauvegarde.h"

// Fonction pour sauvegarder la partie
void sauvegarderPartie(const char *nomFichier,
                       char plateau[SIZE][SIZE][4], int x1, int y1, int x2, int y2,
                       int x3, int y3, int x4, int y4, int tour, int GameMode,
                       GameState *state, Joueurs pseudos[4]) {

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
    fwrite(pseudos, sizeof(Joueurs), 4, f);

    fclose(f);
    printf("Partie sauvegardée dans le fichier '%s'.\n", nomFichier);
}

// Fonction pour charger une partie
void chargerPartie(const char *nomFichier,
                   char plateau[SIZE][SIZE][4], int *x1, int *y1, int *x2, int *y2,
                   int *x3, int *y3, int *x4, int *y4, int *tour, int *GameMode,
                   GameState *state, Joueurs pseudos[4]) {

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
    fread(pseudos, sizeof(Joueurs), 4, f);

    fclose(f);
    printf("Partie chargée depuis le fichier '%s'.\n", nomFichier);
}

// Fonction pour initialiser une partie de démonstration
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

    // Initialiser l'état du jeu
    *tour = 1; // C'est au tour du joueur 1 de jouer
    *state = (GameState){0, 0, 0, 0, 0, 0, 'V', 5, 5, 5, 5};

    // Placer des barrières pour simuler une partie avancée
    placerBarriere(plateau, 6, 9, 'H', state, 1);
    placerBarriere(plateau, 8, 7, 'V', state, 2);
    placerBarriere(plateau, 10, 9, 'H', state, 1);
    placerBarriere(plateau, 12, 11, 'V', state, 2);
}
