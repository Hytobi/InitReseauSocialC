#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "struct.h"

// Distance entre p1 et p2
int distance_personne(Personne *p1, Personne *p2);
int *distance_general(tab_personnes *tab_p);

void print_distances(int *distances, tab_personnes *tab_p);

#endif
