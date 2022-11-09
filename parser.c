#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"

int estSeparateur(char c) {
    return c == '[' || c == ']' || c == ',' || c == ' ' || c == '{' || c == '}';
}

/*
    écrire une fonction parsePersonnesInfos qui prend la liste de personnes
    (exemple : [kevin,karim,alice,paul,charlotte,gabriel,dalila],)
    et créé puis commence à remplir le tableau personneTab.
*/
void parsePersonnesInfos(char *personnes, tab_personnes *tab_p) {
    int i = 0, j = 0, k = 0;
    char *nom = malloc(sizeof(char) * MAX_CHAR);
    while (personnes[i] != '\0') {
        if (estSeparateur(personnes[i]))
            i++;
        else {
            while (personnes[i] != ',') {
                nom[j] = personnes[i];
                i++;
                j++;
            }
            i++;  // On saute la virgule
            if (tab_p->length == MAX_TAB) RAGE_QUIT("Trop de personnes");
            strcpy(tab_p->personne[tab_p->length]->nom, nom);
            tab_p->length++;
            j = 0;  // On réinitialise le compteur de caractères
        }
    }
    free(nom);
}

/*
    écrire une fonction parseVillesInfos qui prend la liste de villes
    (exemple : [lille,lens,arras,douai,carvin,seclin],)
    et crée puis rempli le tableau villes.
*/
void parseVillesInfos(char *listeVilles, char *villes[MAX_VILLE]) {
    int i = 0, j = 0, k = 0;
    char *ville = malloc(sizeof(char) * MAX_CHAR);

    while (listeVilles[i] != '\0') {
        if (estSeparateur(listeVilles[i]))
            i++;
        else {
            while (listeVilles[i] != ',') {
                ville[j] = listeVilles[i];
                i++;
                j++;
            }
            i++;
            if (k >= MAX_VILLE) RAGE_QUIT("Trop de villes");
            strcpy(villes[k], ville);
            k++;
            j = 0;
        }
    }
    free(ville);
}

/*
    écrire une fonction parsePersonne qui prend une chaîne en entrée
    (de type : kevin:{[gabriel,dalila],lille},)
    et qui ajoute les infos de la personne ainsi que ses abonnements.
*/
void parsePersonne(char *personneInfo, tab_personnes *tab_p) {
    int i = 0, j = 0, k = 0;
    char *nom = malloc(sizeof(char) * MAX_CHAR);
    char *ville = malloc(sizeof(char) * MAX_CHAR);
    char *abonne = malloc(sizeof(char) * MAX_CHAR);

    while (personneInfo[i] != '\0') {
        if (estSeparateur(personneInfo[i]))
            i++;
        else {
            // On récupère le nom
            while (personneInfo[i] != ':') {
                nom[j] = personneInfo[i];
                i++;
                j++;
            }
            j = 0;  // On réinitialise le compteur de caractères

            // On rentre dans la liste d'abonnés
            while (personneInfo[i] != '[') i++;
            i++;  // On saute le crochet ouvrant

            // On recupère la place de la personne dans le tableau
            while (strcmp(tab_p->personne[k]->nom, nom) != 0 &&
                   k < tab_p->length)
                k++;
            if (k >= tab_p->length) RAGE_QUIT("Personne inconnue");

            // On récupère les abonnés
            while (personneInfo[i] != ']') {
                while (personneInfo[i] != ',') {
                    abonne[j] = personneInfo[i];
                    i++;
                    j++;
                }
                j = 0;
                // On recupère la place de la personne abonné dans le tableau
                while (strcmp(tab_p->personne[j]->nom, abonne) != 0 &&
                       j < tab_p->length)
                    j++;
                if (j >= tab_p->length) RAGE_QUIT("Personne inconnue");

                // On ajoute l'abonné à la liste
                Liste *tmp = malloc(sizeof(Liste));
                tmp->personne = tab_p->personne[j];
                tmp->suivant = tab_p->personne[k]->abonnements;
                tab_p->personne[k]->abonnements = tmp;

                // On fait le ménage
                free(tmp);
                j = 0;
                i++;  // On saute la virgule
            }
            i++;  // On saute le crochet fermant et la
            // j est deja a 0

            // On avance
            while (estSeparateur(personneInfo[i])) i++;

            // On récupère la ville
            while (personneInfo[i] != '}') {
                ville[j] = personneInfo[i];
                i++;
                j++;
            }
            strcmp(tab_p->personne[k]->ville, ville);
            i++;
            j = 0;
        }
    }
    free(nom);
    free(ville);
    free(abonne);
}

/*
    écrire une fonction parseVille qui prend une chaîne en entrée
    (de type : (lille,22,lens),) qui met à jour la matrice distancesVilles.
*/
void parseVille(char *distanceVilleInfo,
                int distancesVilles[MAX_VILLE][MAX_VILLE]);