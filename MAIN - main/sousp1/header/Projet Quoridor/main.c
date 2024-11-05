#include <stdio.h>
#include "header.h"

int main() {
    char plateau[SIZE][SIZE][4];
    int x1 = 1, y1 = 9; // Position de départ du joueur 1 (colonne centrale)
    int x2 = SIZE - 2, y2 = 9; // Position de départ du joueur 2 (colonne centrale)
    int x3 = 9, y3 = 1; // Position de départ du joueur 3 (colonne gauche)
    int x4 = 9, y4 = SIZE - 2; // Position de départ du joueur 4 (colonne droite)
    int tour = 1;
    char nomJoueur1[50], nomJoueur2[50], nomJoueur3[50], nomJoueur4[50];

#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    SetConsoleOutputCP(CP_UTF8);
#endif

    nom(nomJoueur1, 1);
    nom(nomJoueur2, 2);
    nom(nomJoueur3, 3);
    nom(nomJoueur4, 4);

    initialiserPlateau(plateau);
    strcpy(plateau[x1][y1], "1");
    strcpy(plateau[x2][y2], "2");
    strcpy(plateau[x3][y3], "3");
    strcpy(plateau[x4][y4], "4");

    while (1) {
        system("cls"); // Pour Windows
        // system("clear"); // Pour Unix/Linux

        afficherPlateau(plateau, barrierX, barrierY, modePlacement1, modePlacement2, modePlacement3, modePlacement4, orientation);

        int input;
        printf("C'est au joueur %d de jouer.\n", tour);

        if (tour == 1) {
            if (modePlacement1 == 0) {
                printf("Appuyez sur 'a' pour placer une barrière ou déplacez votre pion avec z/q/s/d.\n");
            } else {
                printf("Déplacez la barrière avec z/q/s/d, changez l'orientation avec 'o' et appuyez sur Entrée pour la placer.\n");
            }
        } else if (tour == 2) {
            if (modePlacement2 == 0) {
                printf("Appuyez sur 'p' pour placer une barrière ou déplacez votre pion avec les flèches.\n");
            } else {
                printf("Déplacez la barrière avec les flèches, changez l'orientation avec 'O' et appuyez sur Entrée pour la placer.\n");
            }
        } else if (tour == 3) {
            if (modePlacement3 == 0) {
                printf("Appuyez sur 'w' pour placer une barrière ou déplacez votre pion avec t/f/g/h.\n");
            } else {
                printf("Déplacez la barrière avec t/f/g/h, changez l'orientation avec 'm' et appuyez sur Entrée pour la placer.\n");
            }
        } else if (tour == 4) {
            if (modePlacement4 == 0) {
                printf("Appuyez sur 'n' pour placer une barrière ou déplacez votre pion avec i/j/k/l.\n");
            } else {
                printf("Déplacez la barrière avec i/j/k/l, changez l'orientation avec 'M' et appuyez sur Entrée pour la placer.\n");
            }
        }

        input = lireTouche();
        // printf("Input: %d\n", input); // Décommentez pour le débogage

        if (tour == 1) {
            if (input == 'a' && modePlacement1 == 0) {
                modePlacement1 = 1;
                barrierX = x1;
                barrierY = y1;
                orientation = 'V';
            } else if (modePlacement1 == 1) {
                if (input == 13 || input == '\n') { // Touche Entrée
                    placerBarriere(plateau, barrierX, barrierY, orientation);
                    modePlacement1 = 0;
                    tour = 2;
                } else if (input == 'o') {
                    orientation = (orientation == 'V') ? 'H' : 'V';
                } else {
                    deplacerBarriere(&barrierX, &barrierY, input, PLAYER1);
                }
            } else {
                deplacerPion(plateau, &x1, &y1, input, PLAYER1);

                // Vérifier la condition de victoire pour le joueur 1
                if (x1 == SIZE - 2) {
                    system("cls"); // Pour Windows
                    // system("clear"); // Pour Unix/Linux
                    afficherPlateau(plateau, barrierX, barrierY, modePlacement1, modePlacement2, modePlacement3, modePlacement4, orientation);
                    printf("Le joueur 1 a gagné !\n");
                    break;
                }

                tour = 2;
            }
        } else if (tour == 2) {
            if (input == 'p' && modePlacement2 == 0) {
                modePlacement2 = 1;
                barrierX = x2;
                barrierY = y2;
                orientation = 'V';
            } else if (modePlacement2 == 1) {
                if (input == 13 || input == '\n') { // Touche Entrée
                    placerBarriere(plateau, barrierX, barrierY, orientation);
                    modePlacement2 = 0;
                    tour = 3;
                } else if (input == 'O') {
                    orientation = (orientation == 'V') ? 'H' : 'V';
                } else {
                    deplacerBarriere(&barrierX, &barrierY, input, PLAYER2);
                }
            } else {
                deplacerPion(plateau, &x2, &y2, input, PLAYER2);

                // Vérifier la condition de victoire pour le joueur 2
                if (x2 == 1) {
                    system("cls"); // Pour Windows
                    // system("clear"); // Pour Unix/Linux
                    afficherPlateau(plateau, barrierX, barrierY, modePlacement1, modePlacement2, modePlacement3, modePlacement4,orientation);
                    printf("Le joueur 2 a gagné !\n");
                    break;
                }
                tour = 3;
            }
        } else if (tour == 3) {
            if (input == 'w' && modePlacement3 == 0) {
                modePlacement3 = 1;
                barrierX = x3;
                barrierY = y3;
                orientation = 'V';
            } else if (modePlacement3 == 1) {
                if (input == 13 || input == '\n') { // Touche Entrée
                    placerBarriere(plateau, barrierX, barrierY, orientation);
                    modePlacement3 = 0;
                    tour = 4;
                } else if (input == 'm') {
                    orientation = (orientation == 'V') ? 'H' : 'V';
                } else {
                    deplacerBarriere(&barrierX, &barrierY, input, PLAYER3);
                }
            } else {
                deplacerPion(plateau, &x3, &y3, input, PLAYER3);

                // Vérifier la condition de victoire pour le joueur 3
                if (y3 == SIZE - 2) {
                    system("cls"); // Pour Windows
                    // system("clear"); // Pour Unix/Linux
                    afficherPlateau(plateau, barrierX, barrierY, modePlacement1, modePlacement2, modePlacement3, modePlacement4,orientation);
                    printf("Le joueur 3 a gagné !\n");
                    break;
                }
                tour = 4;
            }
        } else if (tour == 4) {
            if (input == 'n' && modePlacement4 == 0) {
                modePlacement4 = 1;
                barrierX = x4;
                barrierY = y4;
                orientation = 'V';
            } else if (modePlacement4 == 1) {
                if (input == 13 || input == '\n') { // Touche Entrée
                    placerBarriere(plateau, barrierX, barrierY, orientation);
                    modePlacement4 = 0;
                    tour = 1;
                } else if (input == 'M') {
                    orientation = (orientation == 'V') ? 'H' : 'V';
                } else {
                    deplacerBarriere(&barrierX, &barrierY, input, PLAYER4);
                }
            } else {
                deplacerPion(plateau, &x4, &y4, input, PLAYER4);

                // Vérifier la condition de victoire pour le joueur 4
                if (y4 == 1) {
                    system("cls"); // Pour Windows
                    // system("clear"); // Pour Unix/Linux
                    afficherPlateau(plateau, barrierX, barrierY, modePlacement1, modePlacement2, modePlacement3, modePlacement4,orientation);
                    printf("Le joueur 4 a gagné !\n");
                    break;
                }
                tour = 1;
            }
        }
    }

    return 0;
}
