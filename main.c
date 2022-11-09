#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "reseau.h"
#include "struct.h"

tab_personnes *init_tab_personnes() {
    tab_personnes *tab_p = malloc(sizeof(tab_personnes));
    tab_p->personne = malloc(sizeof(Personne) * MAX_TAB);
    for (int i = 0; i < MAX_TAB; i++) {
        tab_p->personne[i] = malloc(sizeof(Personne));
    }
    tab_p->length = 0;
    return tab_p;
}

char *lire_chaine(FILE *f) {
    char *chaine = malloc(sizeof(char) * MAX_CHAR * 5);
    int i = 0;
    char c;
    while ((c = fgetc(f)) != EOF && c != ';') {
        chaine[i++] = c;
    }
    chaine[i] = '\0';
    if (c == EOF) return NULL;
    return chaine;
}

void afficher_tab_personnes(tab_personnes *tab_p) {
    for (int i = 0; i < tab_p->length; i++) {
        printf("------- Personne %d --\n", i);
        print_personne(tab_p->personne[i]);
    }
}

void afficherMatrice(int matrice[MAX_VILLE][MAX_VILLE], int taille) {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}

void initMatrice(int matrice[MAX_VILLE][MAX_VILLE], int taille) {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            matrice[i][j] = 0;
        }
    }
}

int main() {
    char *villes[MAX_VILLE];
    int distance_villes[MAX_VILLE][MAX_VILLE];
    char *chaine;
    int phase = 0, nb_pers = 0, nb_villes = 0;

    tab_personnes *tab_p = init_tab_personnes();
    FILE *f = fopen("data/reseau1.txt", "r");
    if (f == NULL) RAGE_QUIT("Impossible d'ouvrir le fichier");

    while ((chaine = lire_chaine(f)) != NULL) {
        if (phase == 0) {
            nb_pers = parsePersonnesInfos(chaine, tab_p);
            phase++;
        } else if (phase == 1) {
            nb_villes = parseVillesInfos(chaine, villes);
            initMatrice(distance_villes, nb_villes);
            phase++;
        } else if (phase == 2 && nb_pers--) {
            parsePersonne(chaine, tab_p);
            if (nb_pers == 0) phase++;
        } else {
            // afficher_tab_personnes(tab_p);
            parseVille(chaine, villes, distance_villes);
        }
    }
    afficherMatrice(distance_villes, nb_villes);
    printf("\nla fin\n");
    return EXIT_SUCCESS;
}