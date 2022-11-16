#ifndef RESEAU_H
#define RESEAU_H

#include "struct.h"

// Cette fonction créée une nouvelle personne (sans abonnements) et l'ajoute à
// tab_personnes.
void ajoute_personne(char *nom, char *ville, tab_personnes *tab_p);

// Cette fonction donne les informations d'une personne depuis son nom, null
// sinon
Personne *get_personne(char *nom, tab_personnes *tab_p);

// ajoute p2 aux abonnements de p1.
void ajoute_abo(Personne *p1, Personne *p2);
// enlève p2 aux abonnements de p1.
void enleve_abo(Personne *p1, Personne *p2);

// afficher une personne : son nom, sa ville, le nom des personnes qu'il suit.
void afficher_tab_personnes(tab_personnes *tab_p);

#endif