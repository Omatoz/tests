#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
#include "Plateau.h"
#include "Joueurs.h"
#include "Barriere.h"
#include "Score.h"
#include "Sauvegarde.h"

int afficherMenu() {
        // Affichage du menu
        printf("\n");
        printf("\n");
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
}

void nouvellePartie(char plateau[SIZE][SIZE][4], int *x1, int *y1, int *x2, int *y2,
                       int *x3, int *y3, int *x4, int *y4, GameState *state, Joueurs pseudos[],
                       Joueurs scores[], int *nbScores, int *GameMode) {
    // Initialisation des variables pour une nouvelle partie
    *x1 = 1; *y1 = SIZE / 2;
    *x2 = SIZE - 2; *y2 = SIZE / 2;
    *x3 = SIZE / 2; *y3 = 1;
    *x4 = SIZE / 2; *y4 = SIZE - 2;
    *GameMode = 0;
    *state = (GameState){0, 0, 0, 0, 0, 0, 'V', 10, 10, 0, 0};

    // Charger les scores depuis le fichier
    chargerScores("scores.dat", scores, nbScores);

    // Demander le mode de jeu
    do {
        printf("\n");
        printf("                                                        Choisissez le mode de jeu (2 ou 4) :\n");
        printf("\n");
        printf("                                                        Mode 2 - 2 Joueurs\n");
        printf("                                                        Mode 4 - 4 Joueurs\n");
        printf("\n");
        printf("                                                                  Votre choix : ");
        scanf("%d", GameMode);
        if (*GameMode != 2 && *GameMode != 4) {
            printf("Erreur ! Veuillez choisir un mode de jeu valide.\n\n");
        } else if (*GameMode == 2 || *GameMode == 4){
            Pseudo(pseudos, GameMode, scores, nbScores);
        }
    } while (*GameMode != 2 && *GameMode != 4);

    // Initialisation du plateau
    initialiserPlateau(plateau);
    strcpy(plateau[*x1][*y1], "1");
    strcpy(plateau[*x2][*y2], "2");

    if (*GameMode == 4) {
        strcpy(plateau[*x3][*y3], "3");
        strcpy(plateau[*x4][*y4], "4");
        *state = (GameState){0, 0, 0, 0, 0, 0, 'V', 5, 5, 5, 5};
    }
}

void afficherAide() {
        clearConsole(); // Effacer la console
        printf("\n QUORIDOR\n");
        printf("\n1. BUT DU JEU\n");
        printf("\nLe jeu du Quoridor est un jeu de réflexion où le but est d'atteindre le premier la ligne opposée.\nLes joueurs jouent chacun leur tour et ont la possibilité d'effectuer une des deux actions possibles : Avancer son pion ou poser une barrière.\n");
        printf("\n2. RÈGLES DU JEU\n");
        printf("\n");
        printf("A. RÈGLE POUR 2 JOUEURS\nEn début de partie, les barrières sont remisées dans leur zone de stockage : 10 barrières par joueur.\nChaque joueur pose son pion au centre de sa ligne de départ.\nUn tirage au sort détermine qui commence.\n");
        printf("\n");
        printf("B. RÈGLE POUR 4 JOUEURS\nEn début de partie, les 4 pions sont disposés au centre de chacun des 4 côtés du plateau et chaque joueur dispose de 5 barrières.\nLes règles sont strictement identiques, mais on ne peut sauter plus d’un pion à la fois.\n");
        printf("\n");
        printf("3. DÉROULEMENT DE LA PARTIE\nÀ tour de rôle, chaque joueur choisit de déplacer son pion ou de poser une de ses barrières.\nLorsqu’il n’a plus de barrières, un joueur est obligé de déplacer son pion.\n");
        printf("\n");
        printf("1. Déplacement des pions:\nLes pions se déplacent d’une case, horizontalement ou verticalement, en avant ou en arrière, les barrières doivent être contournées.\n");
        printf("\n2. Pose des barrières:\nUne barrière doit être posée exactement entre 2 blocs de 2 cases.\nLa pose des barrières a pour but de se créer son propre chemin ou de ralentir l’adversaire, mais il est interdit de lui fermer totalement l’accès à sa ligne de but: il faut toujours lui laisser une solution.\n");
        printf("\n3. Face à face:\nQuand les 2 pions se retrouvent en vis-à-vis sur 2 cases voisines non séparées par une barrière, le joueur dont c’est le tour peut sauter son adversaire et se placer derrière lui.\nSi une barrière est située derrière le pion, le joueur peut choisir de bifurquer à droite ou à gauche.\n");
        printf("\nFIN DE PARTIE\nLe premier joueur qui atteint une des 9 cases de la ligne opposée à sa ligne de départ gagne la partie.\n");
        printf("\nDURÉE DE PARTIE\nLe jeu dure de 10 à 20 minutes.\n");
        printf("\nAppuyez sur Entrée pour revenir au menu principal...");
        getchar();
        getchar(); // Attendre que l'utilisateur appuie sur Entrée
}