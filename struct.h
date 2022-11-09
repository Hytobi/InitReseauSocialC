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

/*
Définissez les types et les variables nécessaires pour représenter les éléments
suivants : -un tableau villes de chaînes de caractères une matrice
-distance_villes qui contient des entiers
-une structure Personne qui contient :
--un champ nom de type chaîne de caractères
--un champ ville de type chaîne de caractères
--un champ abonnements de type liste chaînée de Personne
-un tableau tab_personnes de pointeurs sur des Personne
*/

typedef struct _Personne Personne;
typedef struct _ListeChainePersonne {
    Personne *personne;
    struct _ListeChainePersonne *suivant;
} Liste;

typedef struct _Personne {
    char nom[MAX_CHAR];
    char ville[MAX_CHAR];
    Liste *abonnements;
} Personne;

typedef struct _tab_personnes {
    Personne **personne;
    int length;
} tab_personnes;

#endif