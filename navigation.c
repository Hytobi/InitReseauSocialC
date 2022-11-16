#include "navigation.h"

#include <stdio.h>
#include <stdlib.h>

// Distance entre p1 et p2
int distance_personne(Personne *p1, Personne *p2) {
    /* Idée : on fait une liste chainé avec une certaine taille et on precede
     * comme une file*/
    printf("rentrer dans le dist personne\n");

    if (p1 == NULL || p2 == NULL) {
        printf("Erreur : une des personnes n'existe pas\n");
        return -1;
    } else if (p1 == p2) {
        return 0;
    }
    Liste *navig = p1->abonnements;
    int found = 0;
    int distance = 1;

    printf("pas de probleme avant le while\n");

    while (!found) {
        Liste *navig_prec = navig;  // On garde le pointeur précédent
        printf("je rentre dans le 2eme while\n");
        while (navig) {
            // On regarde si on a trouvé p2
            printf(" personne %s\n", navig->personne->nom);
            if (navig->personne == p2) {
                found = 1;
                break;
            }
            navig = navig->suivant;  // On avance
            if (navig == NULL) printf("le navig est nul je dois sortir\n");
        }
        printf("j'avance d'un niveau\n");
        // Si on a pas trouvé, on avance d'un niveau
        if (!found) {
            navig = navig_prec;
            while (navig != NULL) {
                navig = navig->suivant;
                navig_prec->suivant = navig->personne->abonnements;
                navig_prec = navig_prec->suivant;
            }
            distance++;
        }
    }

    return distance;
}

int *distance_general(tab_personnes *tab_p) {
    int *distances = malloc(sizeof(int) * tab_p->length * tab_p->length);
    int i, j;
    for (i = 0; i < tab_p->length; i++) {
        for (j = 0; j < tab_p->length; j++) {
            distances[i * tab_p->length + j] =
                distance_personne(tab_p->personne[i], tab_p->personne[j]);
        }
    }
    return distances;
}

void print_distances(int *distances, tab_personnes *tab_p) {
    int i, j;
    for (i = 0; i < tab_p->length; i++) {
        for (j = 0; j < tab_p->length; j++) {
            printf("%d ", distances[i * tab_p->length + j]);
        }
        printf("\n");
    }
}
