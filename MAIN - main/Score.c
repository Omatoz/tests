#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
#include "Plateau.h"
#include "Joueurs.h"
#include "Barriere.h"
#include "Score.h"
#include "Sauvegarde.h"

// Fonction pour charger les scores depuis le fichier
void chargerScores(const char *nomFichier, Joueurs scores[], int *nbScores) {
    FILE *f = fopen(nomFichier, "rb");
    if (f == NULL) {
        // Le fichier n'existe pas encore, initialiser nbScores à 0
        *nbScores = 0;
        return;
    }

    fread(nbScores, sizeof(int), 1, f);
    fread(scores, sizeof(Joueurs), *nbScores, f);

    fclose(f);
}

// Fonction pour sauvegarder les scores dans le fichier
void sauvegarderScores(const char *nomFichier, Joueurs scores[], int nbScores) {
    FILE *f = fopen(nomFichier, "wb");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier de scores");
        return;
    }

    fwrite(&nbScores, sizeof(int), 1, f);
    fwrite(scores, sizeof(Joueurs), nbScores, f);

    fclose(f);
}

// Fonction pour mettre à jour le score d'un joueur
void mettreAJourScore(Joueurs scores[], int nbScores, const char *pseudo) {
    for (int i = 0; i < nbScores; i++) {
        if (strcmp(scores[i].pseudos, pseudo) == 0) {
            scores[i].score += 1; // Incrémenter le score du joueur
            return;
        }
    }
    // Si le pseudo n'est pas trouvé, l'ajouter
    // (cela ne devrait pas arriver si nous gérons bien les pseudos)
}

// Fonction pour afficher les scores
void afficherScores(Joueurs scores[], int nbScores) {
    printf("\n\n=== Scores des joueurs ===\n");
    for (int i = 0; i < nbScores; i++) {
        printf("%s : %d point(s)\n", scores[i].pseudos, scores[i].score);
    }
    printf("==========================\n\n");
}

