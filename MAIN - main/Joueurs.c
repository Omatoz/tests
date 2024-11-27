#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
#include "Plateau.h"
#include "Joueurs.h"

#include <math.h>

#include "Barriere.h"
#include "Score.h"
#include "Sauvegarde.h"

// Fonction pour déplacer un pion avec gestion du saut
void deplacerPion(char plateau[SIZE][SIZE][4], int *x, int *y,
                  char direction, char joueur, int x1, int y1, int x2, int y2,
                  int x3, int y3, int x4, int y4, int GameMode) {
    int newX = *x, newY = *y;
    int opponentX = -1, opponentY = -1;
    int opponentFound = 0;
    int oppX[3], oppY[3]; // Variables pour les positions potentielles des adversaires
    int oppCount = 0;
    if (GameMode == 2) { // Remplir les positions des adversaires en fonction du joueur actuel
        if (joueur == PLAYER1) {
            oppX[0] = x2; oppY[0] = y2; oppCount = 1;
        } else if (joueur == PLAYER2) {
            oppX[0] = x1; oppY[0] = y1; oppCount = 1;
        }
    } else if (GameMode == 4) {
        int idx = 0;
        if (joueur != PLAYER1) { oppX[idx] = x1; oppY[idx++] = y1; }
        if (joueur != PLAYER2) { oppX[idx] = x2; oppY[idx++] = y2; }
        if (joueur != PLAYER3) { oppX[idx] = x3; oppY[idx++] = y3; }
        if (joueur != PLAYER4) { oppX[idx] = x4; oppY[idx++] = y4; }
        oppCount = idx;
    }
    // Calcul du déplacement souhaité
    if (joueur == PLAYER1) {
        if (direction == 'z' && *x > 1) {
            newX -= 2;
        } else if (direction == 's' && *x < SIZE - 2) {
            newX += 2;
        } else if (direction == 'q' && *y > 1) {
            newY -= 2;
        } else if (direction == 'd' && *y < SIZE - 2) {
            newY += 2;
        } else {
            return;
        }
    } else if (joueur == PLAYER2) {
        if (direction == 'U' && *x > 1) {
            newX -= 2;
        } else if (direction == 'D' && *x < SIZE - 2) {
            newX += 2;
        } else if (direction == 'L' && *y > 1) {
            newY -= 2;
        } else if (direction == 'R' && *y < SIZE - 2) {
            newY += 2;
        } else {
            return;
        }
    } else if (joueur == PLAYER3) {
        if (direction == 't' && *x > 1) {
            newX -= 2;
        } else if (direction == 'g' && *x < SIZE - 2) {
            newX += 2;
        } else if (direction == 'f' && *y > 1) {
            newY -= 2;
        } else if (direction == 'h' && *y < SIZE - 2) {
            newY += 2;
        } else {
            return;
        }
    } else if (joueur == PLAYER4) {
        if (direction == 'i' && *x > 1) {
            newX -= 2;
        } else if (direction == 'k' && *x < SIZE - 2) {
            newX += 2;
        } else if (direction == 'j' && *y > 1) {
            newY -= 2;
        } else if (direction == 'l' && *y < SIZE - 2) {
            newY += 2;
        } else {
            return;
        }
    }

    for (int i = 0; i < oppCount; i++) { // Vérifier s'il y a un pion adverse à la position cible
        if (newX == oppX[i] && newY == oppY[i]) {
            opponentX = oppX[i];
            opponentY = oppY[i];
            opponentFound = 1;
            break;
        }
    }
    if (opponentFound) { // Tentative de saut par-dessus l'adversaire
        int jumpX = opponentX + (opponentX - *x);
        int jumpY = opponentY + (opponentY - *y);
        // Vérifier les limites du plateau
        if (jumpX >= 1 && jumpX <= SIZE - 2 && jumpY >= 1 && jumpY <= SIZE - 2) {
            // Vérifier s'il n'y a pas de barrière entre l'adversaire et la case de saut
            if (!barriereEntre(opponentX, opponentY, jumpX, jumpY, plateau)) {
                // Vérifier si la case derrière l'adversaire est libre
                if (strcmp(plateau[jumpX][jumpY], " ") == 0) {
                    // Effectuer le saut
                    strcpy(plateau[*x][*y], " ");
                    *x = jumpX;
                    *y = jumpY;
                    char strJoueur[2] = {joueur, '\0'};
                    strcpy(plateau[*x][*y], strJoueur);
                    return;
                }
            }
        }

        // Si on ne peut pas sauter, vérifier les déplacements diagonaux
        int deltaX = opponentX - *x;
        int deltaY = opponentY - *y;

        int diagX1 = opponentX - deltaY; // Déterminer les mouvements diagonaux possibles
        int diagY1 = opponentY + deltaX;
        int diagX2 = opponentX + deltaY;
        int diagY2 = opponentY - deltaX;

        // Vérifier les deux diagonales possibles
        if (diagX1 >= 1 && diagX1 <= SIZE - 2 && diagY1 >= 1 && diagY1 <= SIZE - 2 &&
            strcmp(plateau[diagX1][diagY1], " ") == 0 &&
            !barriereEntre(*x, *y, diagX1, diagY1, plateau)) {
            // Déplacement en diagonale
            strcpy(plateau[*x][*y], " ");
            *x = diagX1;
            *y = diagY1;
            char strJoueur[2] = {joueur, '\0'};
            strcpy(plateau[*x][*y], strJoueur);
            return;
        }
        if (diagX2 >= 1 && diagX2 <= SIZE - 2 && diagY2 >= 1 && diagY2 <= SIZE - 2 &&
            strcmp(plateau[diagX2][diagY2], " ") == 0 &&
            !barriereEntre(*x, *y, diagX2, diagY2, plateau)) {
            // Déplacement en diagonale
            strcpy(plateau[*x][*y], " ");
            *x = diagX2;
            *y = diagY2;
            char strJoueur[2] = {joueur, '\0'};
            strcpy(plateau[*x][*y], strJoueur);
            return;
        } // Si aucun déplacement n'est possible, annuler le mouvement
        return;
    } // Vérifier s'il y a une barrière entre l'ancienne et la nouvelle position
    if (barriereEntre(*x, *y, newX, newY, plateau)) {
        return;
    }
    if (strcmp(plateau[newX][newY], " ") == 0) { // Vérifier si la nouvelle case est libre
        strcpy(plateau[*x][*y], " ");
        *x = newX;
        *y = newY;
        char strJoueur[2] = {joueur, '\0'};
        strcpy(plateau[*x][*y], strJoueur);
    }
}


// Fonction pour lire une touche sans attendre l'appui sur Entrée
int lireTouche() {
#ifdef _WIN32
    // Code spécifique à Windows
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
            case 72: return 'U'; // Flèche haut
            case 80: return 'D'; // Flèche bas
            case 75: return 'L'; // Flèche gauche
            case 77: return 'R'; // Flèche droite
            default: return 0;
        }
    } else {
        return ch;
    }
#else
    // Code spécifique à Unix/Linux
    struct termios oldt, newt;
    int ch;

    // Désactiver l'écho et la mise en tampon
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    if (ch == '\033') {
        getchar(); // Ignorer le caractère '['
        switch(getchar()) {
            case 'A': ch = 'U'; break; // Flèche haut
            case 'B': ch = 'D'; break; // Flèche bas
            case 'C': ch = 'R'; break; // Flèche droite
            case 'D': ch = 'L'; break; // Flèche gauche
            default: ch = 0;
        }
    }

    // Restaurer les paramètres du terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}


// Fonction pour saisir et afficher les pseudos des joueurs
void Pseudo(Joueurs pseudosPartie[4], int *GameMode, Joueurs scores[], int *nbScores) {
    for (int i = 0; i < *GameMode; i++) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {} // Consommer le caractère '\n' restant dans le tampon
        printf("\n");
        printf("\n");
        printf("                                            Saisir le pseudo du joueur %d (50 caractères maximum) :", i + 1);
        fgets(pseudosPartie[i].pseudos, PSEUDO, stdin); // Supprimer le caractère '\n' si présent
        size_t len = strlen(pseudosPartie[i].pseudos);
        if (len > 0 && pseudosPartie[i].pseudos[len - 1] == '\n') {
            pseudosPartie[i].pseudos[len - 1] = '\0';
        }

        int found = 0; // Vérifier si le pseudonyme existe déjà dans les scores
        for (int j = 0; j < *nbScores; j++) {
            if (strcmp(scores[j].pseudos, pseudosPartie[i].pseudos) == 0) { // Pseudonyme trouvé, récupérer le score
                pseudosPartie[i].score = scores[j].score;
                found = 1;
                break;
            }
        }
        if (!found) { // Nouveau joueur, l'ajouter à la liste des scores
            strcpy(scores[*nbScores].pseudos, pseudosPartie[i].pseudos);
            scores[*nbScores].score = 0;
            pseudosPartie[i].score = 0;
            (*nbScores)++;
        }
    }
    printf("\n");
    printf("\n                                                        Pseudos enregistrés :\n");  // Vérification pour savoir si les pseudos sont bien enregistrés
    for (int i = 0; i < *GameMode; i++) {
        printf("                                                        Joueur %d: %s\n", i + 1, pseudosPartie[i].pseudos);
    }
    printf("\n");
    printf("                                                        Appuyez sur entrer pour commencer à jouer.\n");
    getchar(); // Attendre que l'utilisateur appuie sur Entrée
}

// Fonction pour afficher l'écran de victoire
void afficherEcranVictoire(int joueur, Joueurs pseudos[4]) {
    printf("\n\n");
    printf("********************************\n");
    printf("*                              *\n");
    printf("*    Le joueur %s a gagné !    *\n", pseudos[joueur-1].pseudos);
    printf("*                              *\n");
    printf("********************************\n");
    printf("\n\n");
}
