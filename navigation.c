#include "navigation.h"

#include <stdio.h>
#include <stdlib.h>

Liste *initListe() {
    Liste *l = malloc(sizeof(Liste));

    l->personne = NULL;
    l->suivant = NULL;
    return l;
}
void print_Liste(Liste *l) {
    if (l == NULL) {
        printf("Liste vide\n");
        return;
    }
    while (l != NULL) {
        printf("%s ", l->personne->nom);
        l = l->suivant;
    }
    printf("\n");
}

// Distance entre p1 et p2
int distance_personne(Personne *p1, Personne *p2, tab_personnes *tab_p) {
    if (p1 == NULL || p2 == NULL)
        RAGE_QUIT("Erreur : une des personnes n'existe pas");
    if (p1 == p2) return 0;

    Liste *navig;
    Liste *tabListe[MAX_TAB * 10];
    tabListe[0] = p1->abonnements;
    int sizeTab = 1, found = 0;
    int distance = 1, i = 0, ajout = 1, ajoutTmp = 0;

    while (!found) {
        navig = tabListe[i];
        while (navig != NULL) {
            // On s'arrete si on a trouvé p2
            if (navig->personne == p2) {
                found = 1;
                break;
            }
            // On ajoute les abonnements de la personne à la liste
            tabListe[sizeTab++] = navig->personne->abonnements;
            // Si on est dans une autre composante connexe on tourne en rond
            // si le tableau est plein c'est qu'il n'y a pas de chemin
            if (sizeTab == MAX_TAB * 10) return 0;
            // On passe à la personne suivante
            ajoutTmp++;
            navig = navig->suivant;
        }
        i++;
        // Si j'ai parcouru tout ceux que j'avais ajouté je passe au niveau
        // suivant
        if (!found && i == ajout) {
            ajout += ajoutTmp;
            distance++;
            ajoutTmp = 0;
        }
    }
    return distance;
}

int *distance_general(tab_personnes *tab_p) {
    int *distances = malloc(sizeof(int) * tab_p->length * tab_p->length);
    int i, j;
    for (i = 0; i < tab_p->length; i++) {
        for (j = 0; j < tab_p->length; j++) {
            distances[i * tab_p->length + j] = distance_personne(
                tab_p->personne[i], tab_p->personne[j], tab_p);
        }
    }
    return distances;
}

void print_distances(int *distances, tab_personnes *tab_p) {
    int i, j;
    printf("distance generale :\n");
    printf("\t\t");
    for (i = 0; i < tab_p->length; i++) {
        printf("%s\t\t", tab_p->personne[i]->nom);
    }
    printf("\n");
    for (i = 0; i < tab_p->length; i++) {
        printf("%s    \t ", tab_p->personne[i]->nom);
        for (j = 0; j < tab_p->length; j++) {
            printf("  %d\t\t", distances[i * tab_p->length + j]);
        }
        printf("\n");
    }
}
