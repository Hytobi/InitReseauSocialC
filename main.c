#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fichier.h"
#include "navigation.h"
#include "parser.h"
#include "reseau.h"
#include "struct.h"

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
            parseVille(chaine, villes, distance_villes);
        }
    }
    fclose(f);  // On ferme le fichier

    printf("pas de prob avant distance\n");
    int k;
    if (!(k = distance_personne(tab_p->personne[0], tab_p->personne[5]))) {
        RAGE_QUIT("Erreur lors du calcul de la distance générale\n");
        return EXIT_FAILURE;
    }
    printf("-------%d-------\n", k);
    printf("diste entre 2 personnes fait \n");
    /*
    printf("distance generale :\n");
    int *dist;
    if (!(dist = distance_general(tab_p))) {
        RAGE_QUIT("Erreur lors du calcul de la distance générale\n");
        return EXIT_FAILURE;
    }
    printf("diste entre generale fait \n");


    print_distances(dist, tab_p);

    printf("diste print fait \n");
    free(dist);
    */
    frees(tab_p, chaine, villes, nb_villes);

    // Les print qui vont bien
    // afficher_tab_personnes(tab_p);
    // afficherMatrice(distance_villes, nb_villes);
    return EXIT_SUCCESS;
}