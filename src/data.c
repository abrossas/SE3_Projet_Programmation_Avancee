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

void load_buf_strtok(char **c) {
// cette fonction sert à faire avancer le buffer lié à strtok afin de parcourir une ligne
	*c = strtok(NULL,",");
}

void read_flight(Flight *pflight, char buffer[MAX_BUFFER]) { 
// cette fonction sert à lire une ligne du fichier CSV des flights
	char *c = strtok(buffer, ",");
	pflight->month = atoi(c); // atoi convertit une chaine de caractère de type "int" en int
	c = strtok(NULL,",");
	pflight->day = atoi(c);
	c = strtok(NULL,",");
	strcpy(pflight->org_air,c); // on ne peut pas assigner directement un tableau il faut passer par strcpy
	c = strtok(NULL,",");
	strcpy(pflight->dest_air,c);
	c = strtok(NULL,",");
	pflight->schep_dep = atoi(c);
	c = strtok(NULL,",");
	pflight->dep_delay = atof(c); // atof agit comme atoi mais pour un float
	c = strtok(NULL,",");
	pflight->air_time = atof(c);
	c = strtok(NULL,",");
	pflight->dist = atoi(c);
	c = strtok(NULL,",");
	pflight->sched_arr = atoi(c);
	c = strtok(NULL,",");
	pflight->arr_delay = atof(c);
	c = strtok(NULL,",");
	pflight->diverted = atoi(c);
	c = strtok(NULL,",");
	pflight->cancelled = atoi(c);	
}

/*void read_airline(struct cell_airline *cell, char buffer[MAX_BUFFER]) { 
	char *c = strtok(buffer, ",");
	Airline airline = cell->airline;
	strcpy(airline.iata_airlines,c);
	load_buf_strtok(&c);
	strcpy(airline.airline,c);
}
*/
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
	
void load_flights(FILE* f_flights, Liste_flights *pl_flights) {
	// On considère que *pl_flight a été initialisée à vide et f_flights à NULL
	f_flights = fopen("../data/flights.csv","r");
	if (f_flights == NULL) {
		printf("Couldn't open file \n");
		return;
	}
	char buffer[MAX_BUFFER];
	fgets(buffer, 120, f_flights); // on "saute" la premiere ligne qui ne nous intéresse pas
	printf("%s\n",buffer);
	int i = 1;
	while (fgets(buffer, MAX_BUFFER, f_flights) != NULL) // On lit chaque ligne du fichier 1 par 1 jusqu'à la fin du fichier
		{
			Flight* pflight = malloc(sizeof(pflight));
			printf("%d ", i);
			read_flight(pflight, buffer);
		//	add_head_flight(pl_flights, *pflight);
			i++;
		}
	
	fclose(f_flights);
}

void free_lflights(Liste_flights *pl_flights) {
	while (*pl_flights != NULL) {
		struct cell_flight* tmp = *pl_flights;
		free(*pl_flights);
		*pl_flights = tmp->pnext_fli;
	}
}
