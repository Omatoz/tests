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
        int choix;
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
        scanf("%d", &choix);
        return choix;
}