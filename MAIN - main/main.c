#include "Menu.h"
#include "Plateau.h"
#include "Joueurs.h"
#include "Barriere.h"
#include "Score.h"
#include "Sauvegarde.h"

int main() {
    char plateau[SIZE][SIZE][4];
    int x1, y1, x2, y2, x3, y3, x4, y4;
    int tour;
    int GameMode;
    GameState state;
    Joueurs pseudos[4];
    Joueurs scores[100]; // Tableau pour stocker jusqu'à 100 joueurs
    int nbScores = 0;    // Nombre actuel de joueurs dans les scores

    srand(time(NULL));

#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    SetConsoleOutputCP(CP_UTF8);
#endif

    int choix, c;
    do {
        afficherMenu();
        scanf("%d", &choix);
        while ((c = getchar()) != '\n' && c != EOF);

        // Gestion des choix
        switch (choix) {
            case 0:
                nouvellePartie(plateau, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4, &state, pseudos, scores, &nbScores, &GameMode);
                break;

            case 1:
                // Charger les scores depuis le fichier
                chargerScores("scores.dat", scores, &nbScores);
                chargerPartie("sauvegarde.dat", plateau, &x1, &y1, &x2, &y2,
                              &x3, &y3, &x4, &y4, &tour, &GameMode, &state, pseudos);
                break;

            case 2:
                // Charger les scores depuis le fichier
                chargerScores("scores.dat", scores, &nbScores);
                initialiserDemo(plateau, &x1, &y1, &x2, &y2,
                                &x3, &y3, &x4, &y4, &tour, &GameMode, &state);
                break;

            case 3:
                afficherAide();
                break;

            case 4:
                // Charger les scores depuis le fichier
                chargerScores("scores.dat", scores, &nbScores);
                // Afficher les scores
                afficherScores(scores, nbScores);
                printf("Appuyez sur Entrée pour revenir au menu principal...");
                getchar();
                getchar(); // Attendre que l'utilisateur appuie sur Entrée
                break;

            case 5:
                exit(0);

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }

        if (choix == 0 || choix == 1 || choix == 2) {
            tour = (rand() % GameMode) + 1;

            // Boucle principale du jeu
            while (1) {
                clearConsole(); // Effacer la console

                afficherPlateau(plateau, GameMode, &state, pseudos);

                int input;
                printf("C'est à %s de jouer.\n", pseudos[tour-1].pseudos);

                // Afficher les actions possibles selon le joueur et le mode placement
                if (tour == 1) {
                    if (state.modePlacement[0] == 0) {
                        printf("\nActions possibles :\n");
                        printf("- Déplacez votre pion avec : z/q/s/d.\n");
                        printf("- Appuyez sur 'a' pour placer une barrière.\n");
                        printf("- Appuyez sur Espace pour passer votre tour.\n");
                        printf("- Appuyez sur 'T' pour sauvegarder.\n");
                        printf("- Appuyez sur Q pour quitter...");
                    } else {
                        printf("\nPlacement barrières :\n");
                        printf("- Déplacez la barrière avec z/q/s/d.\n");
                        printf("- Changez l'orientation avec 'o'.\n");
                        printf("- Appuyez sur Entrée pour la placer.\n");
                        printf("- Le nombre de barrières restantes pour %s est de : %d barrières.\n", pseudos[tour-1].pseudos, state.nb_barrieres[0]);
                    }
                } else if (tour == 2) {
                    if (state.modePlacement[1] == 0) {
                        printf("\nActions possibles :\n");
                        printf("- Déplacez votre pion avec les flèches du clavier.\n");
                        printf("- Appuyez sur 'a' pour placer une barrière.\n");
                        printf("- Appuyez sur Espace pour passer votre tour.\n");
                        printf("- Appuyez sur 'T' pour sauvegarder.\n");
                        printf("- Appuyez sur Q pour quitter...");
                    } else {
                        printf("\nPlacement barrières :\n");
                        printf("- Déplacez la barrière avec les flèches du clavier.\n");
                        printf("- Changez l'orientation avec 'o'.\n");
                        printf("- Appuyez sur Entrée pour la placer.\n");
                        printf("- Le nombre de barrières restantes pour %s est de : %d barrières.\n", pseudos[tour-1].pseudos, state.nb_barrieres[1]);
                    }
                } else if (tour == 3) {
                    if (state.modePlacement[2] == 0) {
                        printf("\nActions possibles :\n");
                        printf("- Déplacez votre pion avec : t/f/g/h.\n");
                        printf("- Appuyez sur 'a' pour placer une barrière.\n");
                        printf("- Appuyez sur Espace pour passer votre tour.\n");
                        printf("- Appuyez sur 'T' pour sauvegarder.\n");
                        printf("- Appuyez sur Q pour quitter...");
                    } else {
                        printf("\nPlacement barrières :\n");
                        printf("- Déplacez la barrière avec t/f/g/h.\n");
                        printf("- Changez l'orientation avec 'o'.\n");
                        printf("- Appuyez sur Entrée pour la placer.\n");
                        printf("- Le nombre de barrières restantes pour %s est de : %d barrières.\n", pseudos[tour-1].pseudos, state.nb_barrieres[2]);
                    }
                } else if (tour == 4) {
                    if (state.modePlacement[3] == 0) {
                        printf("\nActions possibles :\n");
                        printf("- Déplacez votre pion avec : i/j/k/l.\n");
                        printf("- Appuyez sur 'a' pour placer une barrière.\n");
                        printf("- Appuyez sur Espace pour passer votre tour.\n");
                        printf("- Appuyez sur 'T' pour sauvegarder.\n");
                        printf("- Appuyez sur Q pour quitter...");
                    } else {
                        printf("\nPlacement barrières :\n");
                        printf("- Déplacez la barrière avec i/j/k/l.\n");
                        printf("- Changez l'orientation avec 'o'.\n");
                        printf("- Appuyez sur Entrée pour la placer.\n");
                        printf("- Le nombre de barrières restantes pour %s est de : %d barrières.\n", pseudos[tour-1].pseudos, state.nb_barrieres[3]);
                    }
                }

                input = lireTouche();

                if (input == 'T') {
                    sauvegarderPartie("sauvegarde.dat", plateau, x1, y1, x2, y2,
                                      x3, y3, x4, y4, tour, GameMode, &state, pseudos);
                    printf("Partie sauvegardée ! Appuyez sur Entrée pour continuer...");
                    getchar(); // Consommer le '\n' restant
                    getchar(); // Attendre que l'utilisateur appuie sur Entrée
                    continue;
                }

                if (input == 'Q') {
                    sauvegarderPartie("sauvegarde.dat", plateau, x1, y1, x2, y2,
                                      x3, y3, x4, y4, tour, GameMode, &state, pseudos);
                    break;
                }
                // Gestion des actions selon le joueur courant
                if (tour == 1) {
                    if (state.modePlacement[0] == 0 && input == 'a') {
                        if (state.nb_barrieres[0] > 0) {
                            state.modePlacement[0] = 1;
                            state.barrierX = x1;
                            state.barrierY = y1;
                            state.orientation = 'V';
                        } else {
                            printf("Vous n'avez plus de barrières à placer !\n");
                            printf("Appuyez sur Entrée pour continuer...");
                            getchar();
                        }
                    } else if (state.modePlacement[0] == 1) {
                        if (input == '\n' || input == '\r') { // Touche Entrée
                            // Placer la barrière sans vérifier
                            placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation, &state, 1);
                            state.modePlacement[0] = 0;
                            tour = 2;
                        } else if (input == 'o' || input == 'O') {
                            state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                        } else {
                            deplacerBarriere(&state.barrierX, &state.barrierY, input, PLAYER1, &state);
                        }
                    } else {
                        deplacerPion(plateau, &x1, &y1, (char)input, PLAYER1,
                                     x1, y1, x2, y2, x3, y3, x4, y4, GameMode);

                        if (x1 == SIZE - 2) {
                            clearConsole();
                            afficherPlateau(plateau, GameMode, &state, pseudos);
                            afficherEcranVictoire(1, pseudos);

                            // Mettre à jour le score du joueur gagnant
                            mettreAJourScore(scores, nbScores, pseudos[0].pseudos);
                            // Sauvegarder les scores mis à jour
                            sauvegarderScores("scores.dat", scores, nbScores);

                            printf("Appuyez sur Entrée pour quitter...");
                            getchar();
                            getchar();
                            break;
                        }

                        tour = 2;
                    }
                } else if (tour == 2) {
                    if (state.modePlacement[1] == 0 && input == 'a') {
                        if (state.nb_barrieres[1] > 0) {
                            state.modePlacement[1] = 1;
                            state.barrierX = x2;
                            state.barrierY = y2;
                            state.orientation = 'V';
                        } else {
                            printf("Vous n'avez plus de barrières à placer !\n");
                            printf("Appuyez sur Entrée pour continuer...");
                            getchar();
                        }
                    } else if (state.modePlacement[1] == 1) {
                        if (input == '\n' || input == '\r') { // Touche Entrée
                            // Placer la barrière sans vérifier
                            placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation, &state, 2);
                            state.modePlacement[1] = 0;
                            tour = (GameMode == 2) ? 1 : 3;
                        } else if (input == 'o' || input == 'O') {
                            state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                        } else {
                            deplacerBarriere(&state.barrierX, &state.barrierY, input, PLAYER2, &state);
                        }
                    } else {
                        deplacerPion(plateau, &x2, &y2, (char)input, PLAYER2,
                                     x1, y1, x2, y2, x3, y3, x4, y4, GameMode);

                        if (x2 == 1) {
                            clearConsole();
                            afficherPlateau(plateau, GameMode, &state, pseudos);
                            afficherEcranVictoire(2, pseudos);

                            // Mettre à jour le score du joueur gagnant
                            mettreAJourScore(scores, nbScores, pseudos[1].pseudos);
                            // Sauvegarder les scores mis à jour
                            sauvegarderScores("scores.dat", scores, nbScores);

                            printf("Appuyez sur Entrée pour quitter...");
                            getchar();
                            getchar();
                            break;
                        }

                        tour = (GameMode == 2) ? 1 : 3;
                    }
                } else if (tour == 3) {
                    if (state.modePlacement[2] == 0 && input == 'a') {
                        if (state.nb_barrieres[2] > 0) {
                            state.modePlacement[2] = 1;
                            state.barrierX = x3;
                            state.barrierY = y3;
                            state.orientation = 'V';
                        } else {
                            printf("Vous n'avez plus de barrières à placer !\n");
                            printf("Appuyez sur Entrée pour continuer...");
                            getchar();
                        }
                    } else if (state.modePlacement[2] == 1) {
                        if (input == '\n' || input == '\r') { // Touche Entrée
                            // Placer la barrière sans vérifier
                            placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation, &state, 3);
                            state.modePlacement[2] = 0;
                            tour = 4;
                        } else if (input == 'o' || input == 'O') {
                            state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                        } else {
                            deplacerBarriere(&state.barrierX, &state.barrierY, input, PLAYER3, &state);
                        }
                    } else {
                        deplacerPion(plateau, &x3, &y3, (char)input, PLAYER3,
                                     x1, y1, x2, y2, x3, y3, x4, y4, GameMode);

                        if (y3 == SIZE - 2) {
                            clearConsole();
                            afficherPlateau(plateau, GameMode, &state, pseudos);
                            afficherEcranVictoire(3, pseudos);

                            // Mettre à jour le score du joueur gagnant
                            mettreAJourScore(scores, nbScores, pseudos[2].pseudos);
                            // Sauvegarder les scores mis à jour
                            sauvegarderScores("scores.dat", scores, nbScores);

                            printf("Appuyez sur Entrée pour quitter...");
                            getchar();
                            getchar();
                            break;
                        }

                        tour = 4;
                    }
                } else if (tour == 4) {
                    if (state.modePlacement[3] == 0 && input == 'a') {
                        if (state.nb_barrieres[3] > 0) {
                            state.modePlacement[3] = 1;
                            state.barrierX = x4;
                            state.barrierY = y4;
                            state.orientation = 'V';
                        } else {
                            printf("Vous n'avez plus de barrières à placer !\n");
                            printf("Appuyez sur Entrée pour continuer...");
                            getchar();
                        }
                    } else if (state.modePlacement[3] == 1) {
                        if (input == '\n' || input == '\r') { // Touche Entrée
                            // Placer la barrière sans vérifier
                            placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation, &state, 4);
                            state.modePlacement[3] = 0;
                            tour = 1;
                        } else if (input == 'o' || input == 'O') {
                            state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                        } else {
                            deplacerBarriere(&state.barrierX, &state.barrierY, input, PLAYER4, &state);
                        }
                    } else {
                        deplacerPion(plateau, &x4, &y4, (char)input, PLAYER4,
                                     x1, y1, x2, y2, x3, y3, x4, y4, GameMode);

                        if (y4 == 1) {
                            clearConsole();
                            afficherPlateau(plateau, GameMode, &state, pseudos);
                            afficherEcranVictoire(4, pseudos);

                            // Mettre à jour le score du joueur gagnant
                            mettreAJourScore(scores, nbScores, pseudos[3].pseudos);
                            // Sauvegarder les scores mis à jour
                            sauvegarderScores("scores.dat", scores, nbScores);

                            printf("Appuyez sur Entrée pour quitter...");
                            getchar();
                            getchar();
                            break;
                        }

                        tour = 1;
                    }
                }
            }
        }
        clearConsole();
    } while (choix != 5); // Quitte lorsque l'utilisateur choisit l'option 5.

    return 0;
}


