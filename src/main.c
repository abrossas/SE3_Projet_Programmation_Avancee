#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/requetes.h"

int main ()
{
	// 1 - Chargement des données //

    	Liste_flights l_flights = NULL;
    	Liste_airports l_airports = NULL;
    	Liste_airlines l_airlines = NULL;
	if (load_files(&l_flights, &l_airports, &l_airlines) == 1)
		printf("------ CHARGEMENT DES DONNEES EFFECTUE ------\n\n\n");
    	else {
		printf("------ ERREUR LORS DU CHARGEMENT DES DONNEES ------\n\n\n");
		return 0;
	}
	
	// 2 - Interface utilisateur //
	
	char texte[MAX_LINE];
	fgets(texte, sizeof(texte), stdin);
	char *requete;
	requete = strtok(texte, " ");
	while (strcmp(requete, "quit") != 0) {

		if (strcmp(requete,"show-airports") == 0) // Requête show-airport
			{
				requete = strtok(NULL," ");
				show_airports(requete, l_airports, l_flights);
			}
		requete = strtok(

		}

	
	

/*    printf ("1ere requête :\n");
    show_airports ("UA", l_airports, l_flights);

    printf ("2e requete :\n");
    show_airlines ("LAX", l_airlines, l_flights);
	
	printf("3e requete :\n");
	Date d = {1,1};
	show_flights("LAX",d,l_flights, 10, 1700);

	printf("4e requete :\n");
	most_delayed_flights(l_flights);

	printf("5e requete :\n");
	most_delayed_airlines(l_flights, l_airlines);

	printf("6e requete :\n");
	delayed_airline("UA", l_airlines, l_flights);
	delayed_airline("ZZ", l_airlines, l_flights);

	printf("7e requete :\n");
	most_delayed_airlines_at_airport("SLC",l_airlines,l_flights);

	printf("8e requete :\n");
	Date d2 = {12,24};
	changed_flights(d2, l_flights);
	
	printf("9e requete :\n");
	avg_flight_duration("SLC", "LAX", l_flights);
*/
    free_lflights (&l_flights);
    free_lairports (&l_airports);
    free_lairlines (&l_airlines);
    return 0;
}
