#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"

tab_personnes *init_tab_personnes() {
    tab_personnes *tab_p = malloc(sizeof(tab_personnes));
    tab_p->personne = malloc(sizeof(Personne) * MAX_TAB);
    tab_p->length = 0;
    return tab_p;
}

int main() {
    char *villes[MAX_VILLE];
    int distance_villes[MAX_VILLE][MAX_VILLE];
    tab_personnes *tab_p = init_tab_personnes();
    return EXIT_SUCCESS;
}