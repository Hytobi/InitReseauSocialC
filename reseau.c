#include "reseau.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cette fonction créée une nouvelle personne (sans abonnements) et l'ajoute à
// tab_personnes.
void ajoute_personne(char *nom, char *ville, tab_personnes *tab_p) {
    // On la crée
    Personne *p = malloc(sizeof(Personne));
    strcpy(p->nom, nom);
    strcpy(p->ville, ville);
    p->abonnements = NULL;
    // On l'ajoute au tableau
    tab_p->personne[tab_p->length] = p;
    tab_p->length++;
}

// Cette fonction donne les informations d'une personne depuis son nom, null
// sinon
Personne *get_personne(char *nom, tab_personnes *tab_p) {
    int i;
    for (i = 0; i < tab_p->length; i++) {
        if (strcmp(tab_p->personne[i]->nom, nom) == 0) {
            return tab_p->personne[i];
        }
    }
    return NULL;
}

// ajoute p2 aux abonnements de p1.
void ajoute_abo(Personne *p1, Personne *p2) {
    if (p1 == NULL || p2 == NULL) {
        printf("Erreur : une des personnes n'existe pas\n");
        return;
    }
    Liste *l = malloc(sizeof(Liste));
    l->personne = p2;
    l->suivant = p1->abonnements;
    p1->abonnements = l;
}

/*
écrire une fonction enleve_abo qui prend deux personnes p1 et p2 en
paramètres et enlève p2 aux abonnements de p1.
*/
void enleve_abo(Personne *p1, Personne *p2) {
    if (p1 == NULL || p2 == NULL) {
        printf("Erreur : une des personnes n'existe pas\n");
        return;
    }
    Liste *l = p1->abonnements;
    Liste *l_prec = NULL;
    while (l != NULL) {
        if (l->personne == p2) {
            if (l_prec == NULL) {
                p1->abonnements = l->suivant;
            } else {
                l_prec->suivant = l->suivant;
            }
            free(l);
            return;
        }
        l_prec = l;
        l = l->suivant;
    }
}

// d'afficher une personne : son nom, sa ville, le nom des personnes qu'il suit.

void printListe(Liste *liste) {
    if (liste == NULL) return;
    printf("%s ", liste->personne->nom);
    printListe(liste->suivant);
}

void print_personne(Personne *p) {
    printf("nom : %s\n", p->nom);
    printf("ville : %s\n", p->ville);
    printf("abonnements : ");
    printListe(p->abonnements);
    printf("\n");
}
