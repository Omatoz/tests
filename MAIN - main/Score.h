//
// Created by cazau on 11/26/2024.
//

#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Menu.h"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

// Déclarations des fonctions pour la gestion des scores
void chargerScores(const char *nomFichier, Joueurs scores[], int *nbScores);

void sauvegarderScores(const char *nomFichier, Joueurs scores[], int nbScores);

void mettreAJourScore(Joueurs scores[], int nbScores, const char *pseudo);

void afficherScores(Joueurs scores[], int nbScores);

#endif //SCORE_H
