#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reseau.h"
#include "struct.h"

int estSeparateur(char c) {
    return c == '[' || c == ']' || c == ',' || c == ' ' || c == '{' ||
           c == '}' || c == '(' || c == ')' || c == '\n' || c == '\0';
}

/*
    écrire une fonction parsePersonnesInfos qui prend la liste de personnes
    (exemple : [kevin,karim,alice,paul,charlotte,gabriel,dalila],)
    et créé puis commence à remplir le tableau personneTab.
*/
int parsePersonnesInfos(char *personnes, tab_personnes *tab_p) {
    int i = 0, j = 0;
    int nb_pers = 0;

    while (personnes[i] != '\0') {
        if (!estSeparateur(personnes[i])) {
            char *nom = malloc(sizeof(char) * MAX_CHAR);
            while (!estSeparateur(personnes[i])) {
                nom[j] = personnes[i];
                i++;
                j++;
            }
            nom[j] = '\0';
            if (tab_p->length == MAX_TAB) RAGE_QUIT("Trop de personnes");
            strcpy(tab_p->personne[tab_p->length]->nom, nom);
            tab_p->personne[tab_p->length]->num_compo = 0;
            tab_p->length++, nb_pers++, j = 0;
            free(nom);
        }
        i++;
    }

    return nb_pers;
}

/*
    écrire une fonction parseVillesInfos qui prend la liste de villes
    (exemple : [lille,lens,arras,douai,carvin,seclin],)
    et crée puis rempli le tableau villes.
*/
int parseVillesInfos(char *listeVilles, char *villes[MAX_VILLE]) {
    int i = 0, j = 0, k = 0, nb_v = 0;
    char *ville = malloc(sizeof(char) * MAX_CHAR);

    while (listeVilles[i] != '\0') {
        if (estSeparateur(listeVilles[i]))
            i++;
        else {
            while (!estSeparateur(listeVilles[i])) {
                ville[j] = listeVilles[i];
                i++;
                j++;
            }
            ville[j] = '\0';
            i++;
            if (k >= MAX_VILLE) RAGE_QUIT("Trop de villes");
            villes[k] = malloc(sizeof(char) * j);
            strcpy(villes[k], ville);
            k++, j = 0;
            nb_v++;
        }
    }
    free(ville);
    return nb_v;
}

/*
    écrire une fonction parsePersonne qui prend une chaîne en entrée
    (de type : kevin:{[gabriel,dalila],lille},)
    et qui ajoute les infos de la personne ainsi que ses abonnements.
*/
void parsePersonne(char *personneInfo, tab_personnes *tab_p) {
    int i = 0, j = 0;
    char *nom = malloc(sizeof(char) * MAX_CHAR);
    char *ville = malloc(sizeof(char) * MAX_CHAR);

    while (estSeparateur(personneInfo[i])) i++;

    // On récupère le nom
    while (personneInfo[i] != ':') {
        nom[j] = personneInfo[i];
        i++;
        j++;
    }
    nom[j] = '\0';
    // On rentre dans la liste d'abonnés
    while (personneInfo[i] != '[') i++;
    i++;  // On saute le crochet ouvrant

    // On recupère la personne dans le tableau
    Personne *p = get_personne(nom, tab_p);
    if (p == NULL) RAGE_QUIT("Personne inconnue");

    // On récupère les abonnés
    while (personneInfo[i] != ']') {
        j = 0;  // On réinitialise le compteur de caractères
        char *nomAbonne = malloc(sizeof(char) * MAX_CHAR);
        while (!estSeparateur(personneInfo[i])) {
            nomAbonne[j] = personneInfo[i];
            i++;
            j++;
        }
        nomAbonne[j] = '\0';
        // personneInfo[i] est soit un crochet fermant, soit une virgule

        // On recupère la personne abonné dans le tableau
        Personne *abonne = get_personne(nomAbonne, tab_p);
        if (abonne == NULL) RAGE_QUIT("Personne inconnue");

        // On ajoute l'abonné à la liste
        ajoute_abo(p, abonne);

        // si on s'est arrété sur le crochet fermant, on sort de la boucle
        if (personneInfo[i] == ']') break;
        i++;  // sinon on saute la virgule

        free(nomAbonne);
    }
    i += 2;  // On saute le crochet fermant et la virgule
    j = 0;   // On réinitialise le compteur de caractères

    // On avance (au cas ou il y aurait des espaces)
    while (estSeparateur(personneInfo[i])) i++;

    // On récupère la ville
    while (personneInfo[i] != '}') {
        ville[j] = personneInfo[i];
        i++;
        j++;
    }
    ville[j] = '\0';
    strcpy(p->ville, ville);

    // On libère la mémoire
    free(nom);
    free(ville);
}

/*
    écrire une fonction parseVille qui prend une chaîne en entrée
    (de type : (lille,22,lens),) qui met à jour la matrice distancesVilles.
*/
int chercheIndVille(char *ville, char *villes[MAX_VILLE]) {
    int i = 0;
    while (strcmp(ville, villes[i]) != 0 && i < MAX_VILLE) i++;
    if (i >= MAX_VILLE) RAGE_QUIT("Ville inconnue");
    return i;
}

void parseVille(char *distVilleInfo, char *villes[MAX_VILLE],
                int distVilles[MAX_VILLE][MAX_VILLE]) {
    // La premiere est la ville de depart, la deuxieme est la ville d'arrivee
    int i = 0, j = 0, nb = 0, ligne = 0, colonne = 0;
    char *mot1 = malloc(sizeof(char) * MAX_CHAR);
    char *mot2 = malloc(sizeof(char) * MAX_CHAR);
    char *mot3 = malloc(sizeof(char) * MAX_CHAR);

    while (estSeparateur(distVilleInfo[i])) i++;
    // On récupère la ville de départ
    while (distVilleInfo[i] != ',') {
        mot1[j] = distVilleInfo[i];
        i++;
        j++;
    }
    mot1[j] = '\0';

    ligne = chercheIndVille(mot1, villes);
    i++;    // On saute la virgule
    j = 0;  // On réinitialise le compteur de caractères
    // On recupère la distance
    while (distVilleInfo[i] != ',') {
        mot2[j] = distVilleInfo[i];
        i++;
        j++;
    }
    mot2[j] = '\0';
    nb = atoi(mot2);
    i++;    // On saute la virgule
    j = 0;  // On réinitialise le compteur de caractères
    while (distVilleInfo[i] != ')') {
        mot3[j] = distVilleInfo[i];
        i++;
        j++;
    }
    mot3[j] = '\0';
    colonne = chercheIndVille(mot3, villes);

    distVilles[ligne][colonne] = nb;
    distVilles[colonne][ligne] = nb;  // pour le fun
}

void ajoute_Suivi(Personne *p1, Personne *p2) {
    Liste *l = malloc(sizeof(Liste));
    l->personne = p2;
    l->suivant = p1->suivi_par;
    p1->suivi_par = l;
}

void symetriser(tab_personnes *tab_p) {
    for (int i = 0; i < tab_p->length; i++) {
        Personne *p = tab_p->personne[i];
        for (int j = 0; j < tab_p->length; j++) {
            Personne *p2 = tab_p->personne[j];
            Liste *parse = p2->abonnements;
            while (parse != NULL) {
                if (p == parse->personne) {
                    ajoute_Suivi(p, p2);
                }
                parse = parse->suivant;
            }
        }
    }
}
