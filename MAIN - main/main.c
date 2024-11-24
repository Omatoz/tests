#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
    char plateau[SIZE][SIZE][4];
    int x1, y1, x2, y2, x3, y3, x4, y4;
    int tour;
    int GameMode;
    GameState state;
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
        printf("              *******      **     **     *******     *******     **   *******       *******     *******  \n");
        printf("             **/////**    /**    /**    **/////**   /**////**   /**  /**////**     **/////**   /**////** \n");
        printf("            **     //**   /**    /**   **     //**  /**   /**   /**  /**    /**   **     //**  /**   /** \n");
        printf("           /**      /**   /**    /**  /**      /**  /*******    /**  /**    /**  /**      /**  /*******  \n");
        printf("           /**    **/**   /**    /**  /**      /**  /**///**    /**  /**    /**  /**      /**  /**///**  \n");
        printf("           //**  // **    /**    /**  //**     **   /**  //**   /**  /**    **   //**     **   /**  //** \n");
        printf("            //******* **  //*******    //*******    /**   //**  /**  /*******     //*******    /**   //**\n");
        printf("             /////// //    ///////      ///////     //     //   //   ///////       ///////     //     // \n");
        printf("\n");
        printf("\n");
        printf("Choisissez une option :\n");
        printf("0. COMMENCER UNE NOUVELLE PARTIE\n");
        printf("1. CHARGER UNE PARTIE SAUVEGARDEE\n");
        printf("2. CHARGER LA PARTIE DE DEMONSTRATION\n");
        printf("3. AFFICHER L'AIDE\n");
        printf("4. AFFICHER LES SCORES\n");
        printf("5. QUITTER\n");
        printf("Votre choix : ");
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
                state = (GameState){0, 0, 0, 0, 0, 0, 'V'};

                // Demander le mode de jeu
                do {
                    printf("Choisissez le mode de jeu (2 ou 4) :\n");
                    printf("Mode 2 - 2 Joueurs\n");
                    printf("Mode 4 - 4 Joueurs\n");
                    printf("Votre choix : ");
                    scanf("%d", &GameMode);
                    if (GameMode != 2 && GameMode != 4) {
                        printf("Erreur ! Veuillez choisir un mode de jeu valide.\n\n");
                    } else if (GameMode == 2 || GameMode == 4){
                        Pseudo(pseudos, GameMode, &GameMode);
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
                                  &x3, &y3, &x4, &y4, &tour, &GameMode, &state);
            break;
            case 2:
                initialiserDemo(plateau, &x1, &y1, &x2, &y2,
                            &x3, &y3, &x4, &y4, &tour, &GameMode, &state);
            break;
            case 3:
                clearConsole(); // Effacer la console
                printf("\n QUORIDOR\n");
                printf("\n1. BUT DU JEU\n");
                printf("\nLe jeu du Quoridor est un jeu de réflexion où le but est d'atteindre le premier la ligne opposé.\nLes joueurs jouent chacun leur tour et ont la possibilité d'effectuer une des deux actions possibles : Avancer son pion ou poser une barrière.\n");
                printf("\n2. REGLES DU JEU\n");
                printf("A. REGLE POUR 2 JOUEURS\nEn début de partie, les barrières sont remisées dans leur zone de stockage : 10 barrières par joueur.\nChaque joueur pose son pion au centre de sa ligne de départ.\nUn tirage au sort détermine qui commence.");
                printf("B. REGLE POUR 4 JOUEURS\nEn début de partie, les 4 pions sont disposés au centre de chacun des 4 cotés du plateau et chaque joueur dispose de 5 barrières.\nLes règles sont strictement identiques, mais on ne peut sauter plus d’un pion à la fois");
                printf("3. DEROULEMENT DE LA PARTIE\nA tour de rôle, chaque joueur choisit de déplacer son pion ou de poser une de ses barrières.\nLorsqu’il n’a plus de barrières, un joueur est obligé de déplacer son pion.\n");
                printf("\n1. Déplacement des pions:\nLes pions se déplacent d’une case, horizontalement ou verticalement, en avant ou en arrière, les barrières doivent être contournées.\n");
                printf("\n2. Pose des barrières:\nUne barrière doit être posée exactement entre 2 blocs de 2 cases.\nLa pose des barrières a pour but de se créer son propre chemin ou de ralentir.\nl’adversaire, mais il est interdit de lui fermer totalement l’accès à sa ligne de but: il faut toujours lui laisser une solution.\n");
                printf("\n3. Face à face:\nQuand les 2 pions se retrouvent en vis-à-vis sur 2 cases voisines non séparées par une barrière, le joueur dont c’est le tour peut sauter son adversaire et se placer derrière lui.\nSi une barrière est située derrière le pion, le joueur peut choisir de bifurquer à droite ou à gauche.\n");
                printf("\nFIN DE PARTIE\nLe premier joueur qui atteint une des 9 cases de la ligne opposée à sa ligne de départ gagne la partie.\n");
                printf("\nDUREE DE PARTIE\nLe jeu dure de 10 à 20 minutes.\n");
                do {
                    printf("\nAPPUYEZ SUR M POUR RETOURNER AU MENU\n");
                    scanf(" %c", &choix);
                    if (choix == 'm' || choix == 'M') {
                            break;
                    }
                } while (choix != 'm' || choix != 'M');
            case 4:
                // SCORES
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

                afficherPlateau(plateau, &state);

                int input;
                printf("C'est à %s de jouer.\n", pseudos[tour-1].pseudos);

                // Afficher les actions possibles selon le joueur et le mode placement
                if (tour == 1) {
                    if (state.modePlacement1 == 0) {
                        printf("\nActions possibles :\n");
                        printf("Déplacez votre pion avec : z/q/s/d.\n");
                        printf("Appuyez sur 'a' pour placer une barrière.\n");
                        printf("Appuyez sur la barre espace pour passer votre tour.\n");
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
                        printf("Appuyez sur la barre espace pour passer votre tour.\n");
                        printf("Appuyez sur 'T' pour sauvegarder.\n");
                    } else {
                        printf("\nPlacement barrières :\n");
                        printf("Déplacez la barrière avec les flèches du clavier.\n");
                        printf("Changez l'orientation avec 'o'.\n");
                        printf("Appuyez sur Entrée pour la placer.\n");
                    }
                } else if (tour == 3) {
                    if (state.modePlacement3 == 0) {
                        printf("\nActions possibles :\n");
                        printf("Déplacez votre pion avec : t/f/g/h.\n");
                        printf("Appuyez sur 'a' pour placer une barrière.\n");
                        printf("Appuyez sur la barre espace pour passer votre tour.\n");
                        printf("Appuyez sur 'T' pour sauvegarder.\n");
                    } else {
                        printf("\nPlacement barrières :\n");
                        printf("Déplacez la barrière avec t/f/g/h.\n");
                        printf("Changez l'orientation avec 'o'.\n");
                        printf("Appuyez sur Entrée pour la placer.\n");
                    }
                } else if (tour == 4) {
                    if (state.modePlacement4 == 0) {
                        printf("\nActions possibles :\n");
                        printf("Déplacez votre pion avec : i/j/k/l.\n");
                        printf("Appuyez sur 'a' pour placer une barrière.\n");
                        printf("Appuyez sur la barre espace pour passer votre tour.\n");
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

                // Gestion des actions selon le joueur courant
                if (tour == 1) {
                    if (state.modePlacement1 == 0 && input == 'a') {
                        state.modePlacement1 = 1;
                        state.barrierX = x1;
                        state.barrierY = y1;
                        state.orientation = 'V';
                    } else if (state.modePlacement1 == 1) {
                        if (input == '\n' || input == '\r') { // Touche Entrée
                            // Vérifier si la barrière peut être placée
                            if (peutPlacerBarriere(plateau, state.barrierX, state.barrierY, state.orientation,
                                                   x1, y1, x2, y2, x3, y3, x4, y4, GameMode)) {
                                placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation);
                                state.modePlacement1 = 0;
                                tour = 2;
                                                   } else {
                                                       printf("Impossible de placer la barrière ici.\n");
                                                       printf("Appuyez sur Entrée pour continuer...");
                                                       getchar(); // Consommer le '\n' restant
                                                       getchar(); // Attendre que l'utilisateur appuie sur Entrée
                                                       state.modePlacement1 = 0; // Sortir du mode placement
                                                   }
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
                        state.barrierX = x2;
                        state.barrierY = y2;
                        state.orientation = 'V';
                    } else if (state.modePlacement2 == 1) {
                        if (input == '\n' || input == '\r') { // Touche Entrée
                            // Vérifier si la barrière peut être placée
                            if (peutPlacerBarriere(plateau, state.barrierX, state.barrierY, state.orientation,
                                                   x1, y1, x2, y2, x3, y3, x4, y4, GameMode)) {
                                placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation);
                                state.modePlacement2 = 0;
                                if (GameMode == 2) {
                                    tour = 1;
                                } else if (GameMode == 4) {
                                    tour = 3;
                                }
                                                   } else {
                                                       printf("Impossible de placer la barrière ici.\n");
                                                       printf("Appuyez sur Entrée pour continuer...");
                                                       getchar(); // Consommer le '\n' restant
                                                       getchar(); // Attendre que l'utilisateur appuie sur Entrée
                                                       state.modePlacement2 = 0; // Sortir du mode placement
                                                   }
                        } else if (input == 'o' || input == 'O') {
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
                    if (state.modePlacement3 == 0 && input == 'a') {
                        state.modePlacement3 = 1;
                        state.barrierX = x3;
                        state.barrierY = y3;
                        state.orientation = 'V';
                    } else if (state.modePlacement3 == 1) {
                        if (input == '\n' || input == '\r') { // Touche Entrée
                            // Vérifier si la barrière peut être placée
                            if (peutPlacerBarriere(plateau, state.barrierX, state.barrierY, state.orientation,
                                                   x1, y1, x2, y2, x3, y3, x4, y4, GameMode)) {
                                placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation);
                                state.modePlacement3 = 0;
                                tour = 4;
                                                   } else {
                                                       printf("Impossible de placer la barrière ici.\n");
                                                       printf("Appuyez sur Entrée pour continuer...");
                                                       getchar(); // Consommer le '\n' restant
                                                       getchar(); // Attendre que l'utilisateur appuie sur Entrée
                                                       state.modePlacement3 = 0; // Sortir du mode placement
                                                   }
                        } else if (input == 'o' || input == 'O') {
                            state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                        } else {
                            deplacerBarriere(&state.barrierX, &state.barrierY, input, PLAYER3, &state);
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
                        state.barrierX = x4;
                        state.barrierY = y4;
                        state.orientation = 'V';
                    } else if (state.modePlacement4 == 1) {
                        if (input == '\n' || input == '\r') { // Touche Entrée
                            // Vérifier si la barrière peut être placée
                            if (peutPlacerBarriere(plateau, state.barrierX, state.barrierY, state.orientation,
                                                   x1, y1, x2, y2, x3, y3, x4, y4, GameMode)) {
                                placerBarriere(plateau, state.barrierX, state.barrierY, state.orientation);
                                state.modePlacement4 = 0;
                                tour = 1;
                                                   } else {
                                                       printf("Impossible de placer la barrière ici.\n");
                                                       printf("Appuyez sur Entrée pour continuer...");
                                                       getchar(); // Consommer le '\n' restant
                                                       getchar(); // Attendre que l'utilisateur appuie sur Entrée
                                                       state.modePlacement4 = 0; // Sortir du mode placement
                                                   }
                        } else if (input == 'o' || input == 'O') {
                            state.orientation = (state.orientation == 'V') ? 'H' : 'V';
                        } else {
                            deplacerBarriere(&state.barrierX, &state.barrierY, input, PLAYER4, &state);
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
    } while (choix != 5); // Quitte lorsque l'utilisateur choisit l'option 5.
}


