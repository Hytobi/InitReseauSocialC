#ifndef CONNEXE_H
#define CONNEXE_H

#include "reseau.h"
#include "struct.h"

/* qui calcule une composante connexe sur les noeuds
qui ne sont pas déjà rattachés et leur attribue num_compo
comme numéro de composante.
*/
void calcule_une_composante_connexe(Personne *p, int num_compo);

/*qui calcule toutes les composantes connexes du graphe.
Le tableau tab_composantes doit être initialisé à -1.
*/
int *calcule_les_composantes_connexes(tab_personnes *tab_p, int nb);

/*qui affiche tous les noeuds de la composante numéro num_compo.
Pour chaque personne, on veut connaître son nom, sa ville, les noms des
personnes à qui elle est abonnée et les noms des personnes qui la suivent.
*/
void affiche_une_composante(tab_personnes *tab_p, int num_compo);

/*qui affiche toutes les composantes. */
void affiche_les_composantes(tab_personnes *tab_p, int *tab, int taille);

#endif