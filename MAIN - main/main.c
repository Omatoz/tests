// main.c
#include "header.h"

int main() {
    char plateau[SIZE][SIZE][4];
    int x1, y1, x2, y2, x3, y3, x4, y4;
    int tour;
    int GameMode;
    GameState state;
    char pseudos[4];

    srand(time(NULL));
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    SetConsoleOutputCP(CP_UTF8);
#endif

    int choix = 0;
    printf("   *******      **     **     *******     *******     **   *******       *******     *******  \n");
    printf("  **/////**    /**    /**    **/////**   /**////**   /**  /**////**     **/////**   /**////** \n");
    printf(" **     //**   /**    /**   **     //**  /**   /**   /**  /**    /**   **     //**  /**   /** \n");
    printf("/**      /**   /**    /**  /**      /**  /*******    /**  /**    /**  /**      /**  /*******  \n");
    printf("/**    **/**   /**    /**  /**      /**  /**///**    /**  /**    /**  /**      /**  /**///**  \n");
    printf("//**  // **    /**    /**  //**     **   /**  //**   /**  /**    **   //**     **   /**  //** \n");
    printf(" //******* **  //*******    //*******    /**   //**  /**  /*******     //*******    /**   //**\n");
    printf("  /////// //    ///////      ///////     //     //   //   ///////       ///////     //     // \n");
    printf("\n");
    printf("\n");
    printf("Choisissez une option :\n");
    printf("0: Commencer une nouvelle partie\n");
    printf("1: Charger une partie sauvegardée\n");
    printf("2: Charger la partie de démonstration\n");
    printf("3: Afficher l’aide\n");
    printf("4: Afficher les scores des joueurs\n");
    printf("5: Quitter\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    // Consommer le caractère '\n' restant dans le tampon
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (choix == 1) {
        chargerPartie("sauvegarde.dat", plateau, &x1, &y1, &x2, &y2,
                      &x3, &y3, &x4, &y4, &tour, &GameMode, &state);
    } else if (choix == 2) {
        initialiserDemo(plateau, &x1, &y1, &x2, &y2,
                        &x3, &y3, &x4, &y4, &tour, &GameMode, &state);
    } else if (choix == 3) {
        exit(0);
    } else if (choix == 0) {
        {
            // Initialisation des variables pour une nouvelle partie
            x1 = 1; y1 = SIZE / 2;
            x2 = SIZE - 2; y2 = SIZE / 2;
            x3 = SIZE / 2; y3 = 1;
            x4 = SIZE / 2; y4 = SIZE - 2;
            GameMode = 0;
            state = (GameState){0, 0, 0, 0, 0, 0, 'V'};

            // Demander le mode de jeu
            do {
                printf("Choisissez le mode de jeu (2 ou 4) :\n");
                printf("Mode 2 -> 2 Joueurs\n");
                printf("Mode 4 -> 4 Joueurs\n");
                printf("Votre choix : ");
                scanf("%d", &GameMode);
                if (GameMode != 2 && GameMode != 4) {
                    printf("Erreur ! Veuillez choisir un mode de jeu valide.\n\n");
                }
                Pseudo(pseudos,GameMode,&GameMode);
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
        }

        tour = (rand() % GameMode) + 1;

        // Boucle principale du jeu
        while (1) {
            clearConsole(); // Effacer la console

            afficherPlateau(plateau, &state);

            int input;

            printf("\nC'est au joueur %d de jouer.\n", tour);

            if (tour == 1) {
                if (state.modePlacement1 == 0) {
                    printf("\nActions possibles :\n");
                    printf("Déplacez votre pion avec : z/q/s/d.\n");
                    printf("Appuyez sur 'a' pour placer une barrière.\n");
                    printf("Appuyez sur 'T' pour sauvegarder.\n");
                } else {
                    printf("\nPlacement barrières :\n");
                    printf("Déplacez la barrière avec z/q/s/d.\n");
                    printf("Changez l'orientation avec 'o'.\n");
                    printf("Appuyez sur Entrée pour la placer.\n");
                }
            } else if (tour == 2) {
                if (state.modePlacement2 == 0) {
                    printf("\nActions possibles :\n");
                    printf("Déplacez votre pion avec les flèches du clavier.\n");
                    printf("Appuyez sur 'a' pour placer une barrière.\n");
                    printf("Appuyez sur 'T' pour sauvegarder.\n");
                } else {
                    printf("\nPlacement barrières :\n");
                    printf("Déplacez la barrière avec les flèches du clavier.\n");
                    printf("Changez l'orientation avec 'o'.\n");
                    printf("Appuyez sur Entrée pour la placer.\n");                }
            } else if (tour == 3) {
                if (state.modePlacement3 == 0) {
                    printf("\nActions possibles :\n");
                    printf("Déplacez votre pion avec : t/f/g/h.\n");
                    printf("Appuyez sur 'a' pour placer une barrière.\n");
                    printf("Appuyez sur 'T' pour sauvegarder.\n");
                } else {
                    printf("\nPlacement barrières :\n");
                    printf("Déplacez la barrière avec t/f/g/h.\n");
                    printf("Changez l'orientation avec 'o'.\n");
                    printf("Appuyez sur Entrée pour la placer.\n");                }
            } else if (tour == 4) {
                if (state.modePlacement4 == 0) {
                    printf("\nActions possibles :\n");
                    printf("Déplacez votre pion avec : i/j/k/l.\n");
                    printf("Appuyez sur 'a' pour placer une barrière.\n");
                    printf("Appuyez sur 'T' pour sauvegarder.\n");
                } else {
                    printf("\nPlacement barrières :\n");
                    printf("Déplacez la barrière avec i/j/k/l.\n");
                    printf("Changez l'orientation avec 'o'.\n");
                    printf("Appuyez sur Entrée pour la placer.\n");
                }
            }

            input = lireTouche();

            if (input == 'T') {
                sauvegarderPartie("sauvegarde.dat", plateau, x1, y1, x2, y2,
                                  x3, y3, x4, y4, tour, GameMode, &state);
                printf("Partie sauvegardée ! Appuyez sur Entrée pour continuer...");
                getchar(); // Consommer le '\n' restant
                getchar(); // Attendre que l'utilisateur appuie sur Entrée
                continue;
            }

            if (tour == 1) {
                if (state.modePlacement1 == 0 && input == 'a') {
                    state.modePlacement1 = 1;
                    state.barrierX = x1;
                    state.barrierY = y1;
                    state.orientation = 'V';
                } else if (state.modePlacement1 == 1) {
                    if (input == '\n' || input == '\r') { // Touche Entrée
                        placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation);
                        state.modePlacement1 = 0;
                        tour = 2;
                    } else if (input == 'o' || input == 'O') {
                        state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                    } else {
                        deplacerBarriere(&state.barrierX, &state.barrierY, input, PLAYER1, &state);
                    }
                } else {
                    deplacerPion(plateau, &x1, &y1, input, PLAYER1);

                    if (x1 == SIZE - 2) {
                        clearConsole();
                        afficherPlateau(plateau, &state);
                        afficherEcranVictoire(1,pseudos);

                        printf("Appuyez sur Entrée pour quitter...");
                        getchar();
                        getchar();
                        break;
                    }

                    tour = 2;
                }
            } else if (tour == 2) {
                if (state.modePlacement2 == 0 && input == 'p') {
                    state.modePlacement2 = 1;
                    state.barrierX = x2;
                    state.barrierY = y2;
                    state.orientation = 'V';
                } else if (state.modePlacement2 == 1) {
                    if (input == '\n' || input == '\r') { // Touche Entrée
                        placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation);
                        state.modePlacement2 = 0;
                        if (GameMode == 2) {
                            tour = 1;
                        } else if (GameMode == 4) {
                            tour = 3;
                        }
                    } else if (input == 'o' || input == 'O')  {
                        state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                    } else {
                        deplacerBarriere(&state.barrierX, &state.barrierY, input, PLAYER2, &state);
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
                if (state.modePlacement3 == 0 && input == 'w') {
                    state.modePlacement3 = 1;
                    state.barrierX = x3;
                    state.barrierY = y3;
                    state.orientation = 'V';
                } else if (state.modePlacement3 == 1) {
                    if (input == '\n' || input == '\r') { // Touche Entrée
                        placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation);
                        state.modePlacement3 = 0;
                        tour = 4;
                    } else if (input == 'o' || input == 'O')  {
                        state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                    } else {
                        deplacerBarriere(&state.barrierX, &state.barrierY, input, PLAYER3, &state);
                    }
                } else {
                    deplacerPion(plateau, &x3, &y3, input, PLAYER3);

                    if (y3 == SIZE - 2) {
                        clearConsole();
                        afficherPlateau(plateau, &state);
                        afficherEcranVictoire(3,pseudos);

                        printf("Appuyez sur Entrée pour quitter...");
                        getchar();
                        getchar();
                        break;
                    }

                    tour = 4;
                }
            } else if (tour == 4) {
                if (state.modePlacement4 == 0 && input == 'n') {
                    state.modePlacement4 = 1;
                    state.barrierX = x4;
                    state.barrierY = y4;
                    state.orientation = 'V';
                } else if (state.modePlacement4 == 1) {
                    if (input == '\n' || input == '\r') { // Touche Entrée
                        placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation);
                        state.modePlacement4 = 0;
                        tour = 1;
                    } else if  (input == 'o' || input == 'O')  {
                        state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                    } else {
                        deplacerBarriere(&state.barrierX, &state.barrierY, input, PLAYER4, &state);
                    }
                } else {
                    deplacerPion(plateau, &x4, &y4, input, PLAYER4);

                    if (y4 == 1) {
                        clearConsole();
                        afficherPlateau(plateau, &state);
                        afficherEcranVictoire(4,pseudos);

                        printf("Appuyez sur Entrée pour quitter...");
                        getchar();
                        getchar();
                        break;
                    }

                    tour = 1;
                }
            }
        }
        return 0;
    }
}