#ifndef FICHIER_H
#define FICHIER_H

#include <stdio.h>

#include "reseau.h"

tab_personnes *init_tab_personnes();

char *lire_chaine(FILE *f);

void afficherMatrice(int matrice[MAX_VILLE][MAX_VILLE], int taille);

void initMatrice(int matrice[MAX_VILLE][MAX_VILLE], int taille);

void frees(tab_personnes *tab_p, char *ch, char *villes[MAX_VILLE], int taille);

#endif