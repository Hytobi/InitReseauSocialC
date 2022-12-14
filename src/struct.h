#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR 200
#define MAX_TAB 10
#define MAX_VILLE 10
#define RAGE_QUIT(msg)                \
    {                                 \
        fprintf(stderr, "%s\n", msg); \
        exit(EXIT_FAILURE);           \
    }

typedef struct _Personne Personne;
typedef struct _ListeChainePersonne {
    Personne *personne;
    struct _ListeChainePersonne *suivant;
} Liste;

typedef struct _Personne {
    char nom[MAX_CHAR];
    char ville[MAX_CHAR];
    Liste *abonnements;
    Liste *suivi_par;
    int num_compo;
} Personne;

typedef struct _tab_personnes {
    Personne **personne;
    int length;
} tab_personnes;

#endif