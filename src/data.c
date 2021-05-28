#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/data.h"

void add_head_flight(Liste_flights *pliste, Flight flight) {
	struct cell_flight *new = malloc(sizeof(struct cell_flight));
	new->flight = flight;
	new->pnext_fli = *pliste;
	*pliste = new;
}

// void add_head_airline(Liste_airlines *pliste, Airline airline)

// void add_head_airport(Liste_airport *pliste, Airport airport)

void read_flight(Liste_flights *pl_flights, char* line) { 
// cette fonction sert à lire une ligne du fichier CSV des flights et à mettre les données dans une structure Flight puis à la mettre dans la liste des flights
	char* strToken;
	char* Token[14];

	for (int i=0;i<14;i++) {
		strToken = strsep(&line,","); // strsep permet de séparer la chaine de caractère et renvoie la chaine de caractère juste avant l'apparition de ","
		if (strlen(strToken) != 0)
			Token[i]=strToken;
		else // cas où 2 virgules se suivent
			Token[i]="-1"; // on choisit arbitrairement de mettre -1 pour les valeurs manquantes
	}

//------------------ LECTURE DES DONNEES DANS LA STRUCTURE FLIGHT --------------------//
	
	Flight flight;

	flight.month = atoi(Token[0]);
	flight.day = atoi(Token[1]);
	flight.weekday = atoi(Token[2]);
	strcpy(flight.airline,Token[3]);
	strcpy(flight.org_air,Token[4]);
	strcpy(flight.dest_air,Token[5]);
	flight.schep_dep = atoi(Token[6]);
	flight.dep_delay = atof(Token[7]);
	flight.air_time = atof(Token[8]);
	flight.dist = atoi(Token[9]);
	flight.sched_arr = atoi(Token[10]);
	flight.arr_delay = atof(Token[11]);
	flight.diverted = atoi(Token[12]);
	flight.cancelled = atoi(Token[13]);

//------------------ AJOUT DU NOUVEAU FLIGHT A LA LISTE ------------------//  

	add_head_flight(pl_flights,flight);

}		

/*void read_airline(struct cell_airline *cell, char buffer[MAX_BUFFER]) { 
	char *c = strtok(buffer, ",");
	Airline airline = cell->airline;
	strcpy(airline.iata_airlines,c);
	load_buf_strtok(&c);
	strcpy(airline.airline,c);
}



void read_airport(struct cell_airport *cell, char buffer[MAX_BUFFER]) {
	char *c = strtok(buffer, ",");
	Airport airport = cell->airport;
	strcpy(airport.iata_airports,c);
	load_buf_strtok(&c);
	strcpy(airport.airport,c);
	load_buf_strtok(&c);
	strcpy(airport.city,c);
	load_buf_strtok(&c);
	strcpy(airport.state,c);
	load_buf_strtok(&c);
	strcpy(airport.country,c);
	load_buf_strtok(&c);
	airport.latitude = atof(c);
	load_buf_strtok(&c);
	airport.longitude = atof(c);
}
*/

int load_flights(FILE* f_flights, Liste_flights *pl_flights) { // Retourne 1 si succès, 0 sinon
	// On considère que *pl_flight a été initialisée à vide et f_flights à NULL
	f_flights = fopen("../data/flights.csv","r");
	if (f_flights == NULL) {
		printf("Couldn't open file \n");
		return 0;
	} 
	char *line = NULL;
	size_t len = 0;
	getline(&line, &len, f_flights); // on "saute" la premiere ligne qui ne nous intéresse pas

	while (getline(&line,&len,f_flights) != -1) // On lit chaque ligne du fichier 1 par 1 jusqu'à la fin du fichier
		{
			read_flight(pl_flights, line); // On écrit le flight dans l_flight
		}

	free(line);
	fclose(f_flights);
	return 1;
}

// int load_airlines(FILE* f_airlines, Liste_airlines *pl_airlines)

// int load_airports(FILE* f_airports, Liste_airports *pl_airports)

void free_lflights(Liste_flights *pl_flights) {
	while (*pl_flights != NULL) {
		struct cell_flight* tmp = *pl_flights;
		free(*pl_flights);
		*pl_flights = tmp->pnext_fli;
	}
}

// void free_lairlines(Liste_airlines *pl_airlines) //

// void free_lairports(Liste_airports *pl_airports) //

