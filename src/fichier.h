#ifndef FICHIER_H
#define FICHIER_H

#include <stdio.h>

#include "reseau.h"

// Initialise le tableau de personne
tab_personnes *init_tab_personnes();

// Lit une chaine de caractère jusqu'à un ';'
char *lire_chaine(FILE *f);

// Affiche une matrice
void afficherMatrice(int matrice[MAX_VILLE][MAX_VILLE], int taille);

// Initialise une matrice à 0
void initMatrice(int matrice[MAX_VILLE][MAX_VILLE], int taille);

// Libère la mémoire
void frees(tab_personnes *tab_p, char *ch, char *villes[MAX_VILLE], int taille);

#endif