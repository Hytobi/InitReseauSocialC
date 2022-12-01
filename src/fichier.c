#include "fichier.h"

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

void frees(tab_personnes *tab_p, char *ch, char *villes[MAX_VILLE],
           int taille) {
    for (int i = 0; i < tab_p->length; i++) {
        free(tab_p->personne[i]->abonnements);
        free(tab_p->personne[i]->suivi_par);
        free(tab_p->personne[i]);
    }
    free(tab_p->personne);
    free(tab_p);
    for (int i = 0; i < taille; i++) {
        free(villes[i]);
    }
}
