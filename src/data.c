#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/data.h"

void add_head_flight(Liste_flights *pliste, Flight flight) {
	struct cell_flight *new = malloc(sizeof(new));
	new->flight = flight;
	new->pnext_fli = *pliste;
	*pliste = new;
}

void load_buf_strtok(char **c) {
// cette fonction sert à faire avancer le buffer lié à strtok afin de parcourir une ligne
	*c = strtok(NULL,",");
}

void read_flight(Flight flight, char buffer[MAX_BUFFER]) { 
// cette fonction sert à lire une ligne du fichier CSV des flights
	char *c = strtok(buffer, ",");
	flight.month = atoi(c); // atoi convertit une chaine de caractère de type "int" en int
	load_buf_strtok(&c);
	flight.day = atoi(c);
	load_buf_strtok(&c);
	strcpy(flight.org_air,c); // on ne peut pas assigner directement un tableau il faut passer par strcpy
	load_buf_strtok(&c);
	strcpy(flight.dest_air,c);
	load_buf_strtok(&c);
	flight.schep_dep = atoi(c);
	load_buf_strtok(&c);
	flight.dep_delay = atof(c); // atof agit comme atoi mais pour un float
	load_buf_strtok(&c);
	flight.air_time = atof(c);
	load_buf_strtok(&c);
	flight.dist = atoi(c);
	load_buf_strtok(&c);
	flight.sched_arr = atoi(c);
	load_buf_strtok(&c);
	flight.arr_delay = atof(c);
	load_buf_strtok(&c);
	flight.diverted = atoi(c);
	load_buf_strtok(&c);
	flight.cancelled = atoi(c);
}

void read_airline(struct cell_airline *cell, char buffer[MAX_BUFFER]) { 
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
	
void load_flights(FILE* f_flights, Liste_flights *pl_flights) {
	// On considère que *pl_flight a été initialisée à vide et f_flights à NULL
	f_flights = fopen("../data/flights.csv","r");
	if (f_flights == NULL) {
		printf("Couldn't open file \n");
		return;
	}
	char buffer[MAX_BUFFER];
	Flight flight;
	while (fgets(buffer, MAX_BUFFER, f_flights) != NULL) { // On lit chaque ligne du fichier 1 par 1 jusqu'à la fin du fichier
		{
			read_flight(flight, buffer);
			add_head_flight(pl_flights, flight);
		}
	fclose(f_flights);
	}
}
