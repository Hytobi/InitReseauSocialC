#include "connexe.h"

/* qui calcule une composante connexe sur les noeuds
qui ne sont pas déjà rattachés et leur attribue num_compo
comme numéro de composante.
*/
void calcule_une_composante_connexe(Personne *p, int num_compo) {
    Liste *liste = p->abonnements;
    Liste *liste2 = p->suivi_par;
    while (liste != NULL) {
        if (liste->personne->num_compo == 0) {
            liste->personne->num_compo = num_compo;
            calcule_une_composante_connexe(liste->personne, num_compo);
        }
        liste = liste->suivant;
    }
    while (liste2 != NULL) {
        if (liste2->personne->num_compo == 0) {
            liste2->personne->num_compo = num_compo;
            calcule_une_composante_connexe(liste2->personne, num_compo);
        }
        liste2 = liste2->suivant;
    }
}

/*qui calcule toutes les composantes connexes du graphe.
Le tableau tab_composantes doit être initialisé à -1.
*/
int *calcule_les_composantes_connexes(tab_personnes *tab_p, int nb) {
    int i;
    int *tab_composante = malloc(sizeof(int) * nb);
    for (i = 0; i < nb; i++) {
        tab_composante[i] = -1;
    }
    int num_compo = 1;
    for (i = 0; i < nb; i++) {
        if (tab_composante[i] == -1) {
            if (tab_p->personne[i]->num_compo != 0) {
                tab_composante[i] = tab_p->personne[i]->num_compo;
            } else {
                calcule_une_composante_connexe(tab_p->personne[i], num_compo);
                tab_composante[i] = num_compo;
                num_compo++;
            }
        }
    }
    return tab_composante;
}

/*qui affiche tous les noeuds de la composante numéro num_compo.
Pour chaque personne, on veut connaître son nom, sa ville, les noms des
personnes à qui elle est abonnée et les noms des personnes qui la suivent.
*/
void affiche_une_composante(tab_personnes *tab_p, int num_compo) {
    for (int j = 0; j < tab_p->length; j++) {
        if (tab_p->personne[j]->num_compo == num_compo) {
            print_personne(tab_p->personne[j]);
            printf("\n");
        }
    }
}

/*qui affiche toutes les composantes. */
int max(int *tab, int nb) {
    int max = 0;
    for (int i = 0; i < nb; i++) {
        if (tab[i] > max) {
            max = tab[i];
        }
    }
    return max;
}
void affiche_les_composantes(tab_personnes *tab_p, int *tab, int taille) {
    int i, len = max(tab, taille);
    printf("Il y a %d composantes connexes\n", len);
    for (i = 1; i < len + 1; i++) {
        printf("La composante numéro %d est composée de :\n", i);
        affiche_une_composante(tab_p, i);
        printf("\n");
    }
}
