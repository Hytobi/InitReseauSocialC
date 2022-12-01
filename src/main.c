#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "connexe.h"
#include "fichier.h"
#include "navigation.h"
#include "parser.h"
#include "reseau.h"
#include "struct.h"

int main() {
    char *villes[MAX_VILLE];
    int distance_villes[MAX_VILLE][MAX_VILLE];
    char *chaine;
    int phase = 0, nb_pers = 0, nb_villes = 0, copy;
    int *tab_composante, *tab_composante_fc;

    tab_personnes *tab_p = init_tab_personnes();
    FILE *f = fopen("data/reseau2.txt", "r");
    if (f == NULL) RAGE_QUIT("Impossible d'ouvrir le fichier");

    while ((chaine = lire_chaine(f)) != NULL) {
        if (phase == 0) {
            nb_pers = parsePersonnesInfos(chaine, tab_p);
            copy = nb_pers;
            phase++;
        } else if (phase == 1) {
            nb_villes = parseVillesInfos(chaine, villes);
            initMatrice(distance_villes, nb_villes);
            phase++;
        } else if (phase == 2 && copy--) {
            parsePersonne(chaine, tab_p);
            if (copy == 0) phase++;
        } else {
            parseVille(chaine, villes, distance_villes);
        }
    }
    fclose(f);  // On ferme le fichier

    // Les print qui vont bien
    int print = 1;
    if (print) {
        symetriser(tab_p);
        afficher_tab_personnes(tab_p);
        afficherMatrice(distance_villes, nb_villes);
        printf("\nTeste de la fonction distance\n");
        printf(
            "-------%d-------\n",
            distance_personne(tab_p->personne[0], tab_p->personne[1], tab_p));
        printf("\n");
        print_distances(distance_general(tab_p), tab_p);
        printf("\n");

        tab_composante = calcule_les_composantes_connexes(tab_p, nb_pers);
        affiche_les_composantes(tab_p, tab_composante, nb_pers);

        // On remet a zero le num_compo pour la suite
        for (int i = 0; i < nb_pers; i++) {
            tab_p->personne[i]->num_compo = 0;
        }

        tab_composante_fc =
            calcule_les_composantes_fortement_connexes(tab_p, nb_pers);
        affiche_les_cfc(tab_p, tab_composante_fc, nb_pers);
    }

    free(tab_composante);
    frees(tab_p, chaine, villes, nb_villes);

    return EXIT_SUCCESS;
}