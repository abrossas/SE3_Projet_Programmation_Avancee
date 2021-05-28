#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/requetes.h"

//---------- PREMIERE REQUETE ----------//

int airport_already_in_list(Liste_IATA l_iata, char iata[IATA_AIRPORT_MAX]) {
// Cette fonction renvoie 1 si une compagnie (identifié par son code IATA) est déjà présent dans une liste chainée de codes IATA et 0 sinon
	if (l_iata == NULL)
		return 0;
	while (l_iata != NULL) // on parcourt la liste chainée, si on trouve un élément similaire à iata, on renvoie 1 et on renvoie 0 si on a parcouru toute la liste sans jamais trouver
	{
		if (strcmp(iata,l_iata->airport)==0)
			return 1;
		l_iata = l_iata->p_next;
	}
    return 0;	
}	

void add_head(Liste_IATA *pl_iata, char iata[IATA_AIRPORT_MAX]) {
	struct cell_IATA *pc = malloc(sizeof(struct cell_IATA));
	strcpy(pc->airport,iata);
	pc->p_next = *pl_iata;
	*pl_iata = pc;
}

void info_airport(Liste_airports l_airports, Liste_IATA l_iata) {
	if (l_airports==NULL) // Ces 2 cas sont pratiquement sûrs de ne jamais être vérifiés
		return;
	if (l_iata==NULL)
		return;

	while (l_airports != NULL) // On parcourt toute la liste des aéroports (qu'on a préalablement load) pour trouver les infos de celui qui correspond au code iata du premier élément de l_iata
	{	
		if (strcmp(l_iata->airport, l_airports->airport.iata_airports)==0)
			printf("CODE IATA : %s --- AEROPORT : %s --- VILLE : %s --- ETAT : %s\n", l_airports->airport.iata_airports, l_airports->airport.airport, l_airports->airport.city, l_airports->airport.state);	
	l_airports = l_airports->pnext_airp;
	}
}

void show_airports(char airline[IATA_AIRPORT_MAX], Liste_airports l_airports, Liste_flights l_flights){ 
	Liste_IATA l_iata = NULL;
	while (l_flights != NULL) // On parcourt la liste des vols pour trouver ceux où la companie passée en argument est concernée pour les mettres dans la liste l_iata initialisée plus haut
	{
		if (strcmp(airline,l_flights->flight.airline)==0)
		{
			if (airport_already_in_list(l_iata, l_flights->flight.org_air)==0) // ici on vérifie s'il est déjà présent dans la liste afin d'éviter les doublons
				add_head(&l_iata, l_flights->flight.org_air);
		}
		l_flights = l_flights->pnext_fli;
	}

	if (l_iata == NULL) 
    	{ // Cas où on n'a trouvé aucun aéroport à afficher (possible erreur de l'utilisateur)
        printf("Aucun aéroport ne correspond à la compagnie '%s' que vous avez rentrée\n", airline);
        return;
    	}
	printf("\n-------------------- LISTE DES AEROPORTS DEPUIS LESQUELS LA COMPANIE %s OPERE DES VOLS --------------------\n",airline);
		
	while (l_iata != NULL)
	{ // Cas où on a stocké tous les codes IATA des aéroports à afficher dans la liste l_iata
		info_airport(l_airports, l_iata);
		l_iata = l_iata->p_next;
	}
	printf("\n");
}
