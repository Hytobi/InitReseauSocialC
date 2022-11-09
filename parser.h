#ifndef PARSER_H
#define PARSER_H

#include "struct.h"

/*
    écrire une fonction parsePersonnesInfos qui prend la liste de personnes
    (exemple : [kevin,karim,alice,paul,charlotte,gabriel,dalila],)
    et créé puis commence à remplir le tableau personneTab.
*/
int parsePersonnesInfos(char *personnes, tab_personnes *tab_p);

/*
    écrire une fonction parseVillesInfos qui prend la liste de villes
    (exemple : [lille,lens,arras,douai,carvin,seclin],)
    et crée puis rempli le tableau villes.
*/
int parseVillesInfos(char *listeVilles, char *villes[MAX_VILLE]);

/*
    écrire une fonction parsePersonne qui prend une chaîne en entrée
    (de type : kevin:{[gabriel,dalila],lille},)
    et qui ajoute les infos de la personne ainsi que ses abonnements.
*/
void parsePersonne(char *personneInfo, tab_personnes *tab_p);

/*
    écrire une fonction parseVille qui prend une chaîne en entrée
    (de type : (lille,22,lens),) qui met à jour la matrice distancesVilles.
*/
void parseVille(char *distVilleInfo, char *villes[MAX_VILLE],
                int distancesVilles[MAX_VILLE][MAX_VILLE]);

#endif