#ifndef RESEAU_H
#define RESEAU_H

#include "struct.h"

/*
écrire une fonction ajoute_abo qui prend deux personnes p1 et p2 en paramètres
et écrire une fonction enleve_abo qui prend deux personnes p1 et p2 en
paramètres et enlève p2 aux abonnements de p1. écrire une fonction qui permet
d'afficher une personne : son nom, sa ville, le nom des personnes qu'il suit.
*/

// Cette fonction créée une nouvelle personne (sans abonnements) et l'ajoute à
// tab_personnes.
void ajoute_personne(char *nom, char *ville, tab_personnes *tab_p);

// Cette fonction donne les informations d'une personne depuis son nom, null
// sinon
Personne *get_personne(char *nom, tab_personnes *tab_p);

// ajoute p2 aux abonnements de p1.
void ajoute_abo(Personne *p1, Personne *p2);

void enleve_abo(Personne *p1, Personne *p2);

// afficher une personne : son nom, sa ville, le nom des personnes qu'il suit.
void print_personne(Personne *p);

#endif