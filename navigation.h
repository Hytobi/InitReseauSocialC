#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "struct.h"

// Distance entre p1 et p2
int distance_personne(Personne *p1, Personne *p2, tab_personnes *tab_p);

// Crée une matriste de distance réseau
int *distance_general(tab_personnes *tab_p);

// Affiche la matrice de distance
void print_distances(int *distances, tab_personnes *tab_p);

#endif
