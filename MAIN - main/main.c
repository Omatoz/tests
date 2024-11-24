#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Ajouté pour utiliser strcpy
#include "header.h"

int main() {
    char plateau[SIZE][SIZE][4];
    int x1, y1, x2, y2, x3, y3, x4, y4;
    int tour;
    int GameMode;
    GameState state; // Utilisation correcte de la structure state
    Pseudos pseudos[4];

    srand(time(NULL));
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    SetConsoleOutputCP(CP_UTF8);
#endif

    int choix;

    do {
        // Affichage du menu
        printf("                              *******      **     **     *******     *******     **   *******       *******     *******  \n");
        printf("                             **/////**    /**    /**    **/////**   /**////**   /**  /**////**     **/////**   /**////** \n");
        printf("                            **     //**   /**    /**   **     //**  /**   /**   /**  /**    /**   **     //**  /**   /** \n");
        printf("                           /**      /**   /**    /**  /**      /**  /*******    /**  /**    /**  /**      /**  /*******  \n");
        printf("                           /**    **/**   /**    /**  /**      /**  /**///**    /**  /**    /**  /**      /**  /**///**  \n");
        printf("                           //**  // **    /**    /**  //**     **   /**  //**   /**  /**    **   //**     **   /**  //** \n");
        printf("                            //******* **  //*******    //*******    /**   //**  /**  /*******     //*******    /**   //**\n");
        printf("                             /////// //    ///////      ///////     //     //   //   ///////       ///////     //     // \n");
        printf("\n");
        printf("\n");
        printf("                                                        Choisissez une option :\n");
        printf("\n");
        printf("                                                        0. COMMENCER UNE NOUVELLE PARTIE\n");
        printf("                                                        1. CHARGER UNE PARTIE SAUVEGARDEE\n");
        printf("                                                        2. CHARGER LA PARTIE DE DEMONSTRATION\n");
        printf("                                                        3. AFFICHER L'AIDE\n");
        printf("                                                        4. AFFICHER LES SCORES\n");
        printf("                                                        5. QUITTER\n");
        printf("\n");
        printf("                                                                  Votre choix : ");
        scanf("%d", &choix);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        // Gestion des choix
        switch (choix) {
            case 0:
                // Initialisation des variables pour une nouvelle partie
                x1 = 1; y1 = SIZE / 2;
                x2 = SIZE - 2; y2 = SIZE / 2;
                x3 = SIZE / 2; y3 = 1;
                x4 = SIZE / 2; y4 = SIZE - 2;
                GameMode = 0;
                state = (GameState){0, 0, 0, 0, 0, 0, 'V', 0}; // Initialisation de state

                // Demander le mode de jeu
                do {
                    printf("\n");
                    printf("                                                        Choisissez le mode de jeu (2 ou 4) :\n");
                    printf("\n");
                    printf("                                                        Mode 2 - 2 Joueurs\n");
                    printf("                                                        Mode 4 - 4 Joueurs\n");
                    printf("\n");
                    printf("                                                                  Votre choix : ");
                    scanf("%d", &GameMode);
                    if (GameMode != 2 && GameMode != 4) {
                        printf("Erreur ! Veuillez choisir un mode de jeu valide.\n\n");
                    } else if (GameMode == 2 || GameMode == 4) {
                        Pseudo(pseudos, GameMode, &GameMode); // Passage correct de &GameMode
                    }
                } while (GameMode != 2 && GameMode != 4);

                // Consommer le caractère '\n' restant dans le tampon
                while ((c = getchar()) != '\n' && c != EOF);

                // Initialisation du plateau
                initialiserPlateau(plateau);
                strcpy(plateau[x1][y1], "1");
                strcpy(plateau[x2][y2], "2");

                if (GameMode == 4) {
                    strcpy(plateau[x3][y3], "3");
                    strcpy(plateau[x4][y4], "4");
                }
                break;

            case 1:
                chargerPartie("sauvegarde.dat", plateau, &x1, &y1, &x2, &y2,
                              &x3, &y3, &x4, &y4, &tour, &GameMode, &state); // Passage correct de &state
                break;

            case 2:
                initialiserDemo(plateau, &x1, &y1, &x2, &y2,
                                &x3, &y3, &x4, &y4, &tour, &GameMode, &state); // Passage correct de &state
                break;

            case 3:
                clearConsole(); // Effacer la console
                printf("\n QUORIDOR\n");
                printf("\n1. BUT DU JEU\n");
                printf("\nLe jeu du Quoridor est un jeu de réflexion où le but est d'atteindre la ligne opposée en premier.\nLes joueurs jouent chacun leur tour et ont la possibilité d'effectuer une des deux actions possibles : Avancer leur pion ou poser une barrière.\n");
                printf("\n2. REGLES DU JEU\n");
                printf("Les règles complètes sont affichées ici...\n");
                break;

            case 4:
                // Implémentation de l'affichage des scores (non fournie)
                printf("Fonction d'affichage des scores non encore implémentée.\n");
                break;

            case 5:
                exit(0);
                break;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }

        if (choix == 0 || choix == 1 || choix == 2) {
            tour = (rand() % GameMode) + 1;

            // Boucle principale du jeu
            while (1) {
                clearConsole(); // Effacer la console
                afficherPlateau(plateau, &state); // Passage correct de &state
                int input;
                printf("C'est au joueur %d de jouer.\n", tour);

                input = lireTouche();
                if (input == 'T') {
                    sauvegarderPartie("sauvegarde.dat", plateau, x1, y1, x2, y2,
                                      x3, y3, x4, y4, tour, GameMode, &state); // Passage correct de &state
                    printf("Partie sauvegardée ! Appuyez sur Entrée pour continuer...");
                    getchar();
                    continue;
                }

                // Gestion des actions selon le joueur courant
                if (tour == 1) {
                    if (state.modePlacement1 == 0 && input == 'a') {
                        state.modePlacement1 = 1;
                        // Initialiser barrierX et barrierY adjacents au joueur 1
                        if (x1 + 1 < SIZE - 1) { // Assurer qu'on reste dans les limites
                            state.barrierX = x1 + 1;
                            state.barrierY = y1;
                        } else {
                            state.barrierX = x1;
                            state.barrierY = y1;
                        }
                        state.orientation = 'V';
                    } else if (state.modePlacement1 == 1) {
                        if (input == '\n' || input == '\r') { // Touche Entrée
                            // Placer la barrière sans vérification
                            placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation, &state);
                            state.modePlacement1 = 0;
                            tour = 2;
                        } else if (input == 'o' || input == 'O') {
                            state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                        } else {
                            deplacerBarriere(plateau, &state.barrierX, &state.barrierY, input, PLAYER1, &state);
                        }
                    } else {
                        deplacerPion(plateau, &x1, &y1, input, PLAYER1);

                        if (x1 == SIZE - 2) {
                            clearConsole();
                            afficherPlateau(plateau, &state);
                            afficherEcranVictoire(1, pseudos);

                            printf("Appuyez sur Entrée pour quitter...");
                            getchar();
                            getchar();
                            break;
                        }

                        tour = 2;
                    }
                } else if (tour == 2) {
                    if (state.modePlacement2 == 0 && input == 'a') {
                        state.modePlacement2 = 1;
                        // Initialiser barrierX et barrierY adjacents au joueur 2
                        if (x2 - 1 > 0) { // Assurer qu'on reste dans les limites
                            state.barrierX = x2 - 1;
                            state.barrierY = y2;
                        } else {
                            state.barrierX = x2;
                            state.barrierY = y2;
                        }
                        state.orientation = 'V';
                    } else if (state.modePlacement2 == 1) {
                        if (input == '\n' || input == '\r') { // Touche Entrée
                            // Placer la barrière sans vérification
                            placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation, &state);
                            state.modePlacement2 = 0;
                            if (GameMode == 2) {
                                tour = 1;
                            } else if (GameMode == 4) {
                                tour = 3;
                            }
                        } else if (input == 'o' || input == 'O') {
                            state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                        } else {
                            deplacerBarriere(plateau, &state.barrierX, &state.barrierY, input, PLAYER2, &state);
                        }
                    } else {
                        deplacerPion(plateau, &x2, &y2, input, PLAYER2);

                        if (x2 == 1) {
                            clearConsole();
                            afficherPlateau(plateau, &state);
                            afficherEcranVictoire(2, pseudos);

                            printf("Appuyez sur Entrée pour quitter...");
                            getchar();
                            getchar();
                            break;
                        }

                        if (GameMode == 2) {
                            tour = 1;
                        } else if (GameMode == 4) {
                            tour = 3;
                        }
                    }
                } else if (tour == 3) {
                    if (state.modePlacement3 == 0 && input == 'a') {
                        state.modePlacement3 = 1;
                        // Initialiser barrierX et barrierY adjacents au joueur 3
                        if (x3 + 1 < SIZE - 1) { // Assurer qu'on reste dans les limites
                            state.barrierX = x3 + 1;
                            state.barrierY = y3;
                        } else {
                            state.barrierX = x3;
                            state.barrierY = y3;
                        }
                        state.orientation = 'V';
                    } else if (state.modePlacement3 == 1) {
                        if (input == '\n' || input == '\r') { // Touche Entrée
                            // Placer la barrière sans vérification
                            placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation, &state);
                            state.modePlacement3 = 0;
                            tour = 4;
                        } else if (input == 'o' || input == 'O') {
                            state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                        } else {
                            deplacerBarriere(plateau, &state.barrierX, &state.barrierY, input, PLAYER3, &state);
                        }
                    } else {
                        deplacerPion(plateau, &x3, &y3, input, PLAYER3);

                        if (y3 == SIZE - 2) {
                            clearConsole();
                            afficherPlateau(plateau, &state);
                            afficherEcranVictoire(3, pseudos);

                            printf("Appuyez sur Entrée pour quitter...");
                            getchar();
                            getchar();
                            break;
                        }

                        tour = 4;
                    }
                } else if (tour == 4) {
                    if (state.modePlacement4 == 0 && input == 'a') {
                        state.modePlacement4 = 1;
                        // Initialiser barrierX et barrierY adjacents au joueur 4
                        if (x4 - 1 > 0) { // Assurer qu'on reste dans les limites
                            state.barrierX = x4 - 1;
                            state.barrierY = y4;
                        } else {
                            state.barrierX = x4;
                            state.barrierY = y4;
                        }
                        state.orientation = 'V';
                    } else if (state.modePlacement4 == 1) {
                        if (input == '\n' || input == '\r') { // Touche Entrée
                            // Placer la barrière sans vérification
                            placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation, &state);
                            state.modePlacement4 = 0;
                            tour = 1;
                        } else if (input == 'o' || input == 'O') {
                            state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                        } else {
                            deplacerBarriere(plateau, &state.barrierX, &state.barrierY, input, PLAYER4, &state);
                        }
                    } else {
                        deplacerPion(plateau, &x4, &y4, input, PLAYER4);

                        if (y4 == 1) {
                            clearConsole();
                            afficherPlateau(plateau, &state);
                            afficherEcranVictoire(4, pseudos);

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
