#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

void add_head_flight(Liste_flights *pliste, Flight flight) {
	struct cell_flight *new = malloc(sizeof(new));
	new->flight = flight
	new->pnext_flight = *pliste;
	*pliste = new;
}

void load_buf_strtok(c) {
// cette fonction sert à faire avancer le buffer lié à strtok afin de parcourir une ligne
	c = strtok(NULL,",");
}

void read_flight(struct cell_flight *cell, char buffer[MAX_BUFFER]) { 
// cette fonction sert à lire une ligne du fichier CSV des flights
	char *c = strtok(buffer, ",");
	Flight flight = cell_flight->flight
	flight.month = atoi(c); // atoi convertit une chaine de caractère de type "int" en int
	load_buf_strtok(c);
	flight.day = atoi(c)
	load_buf_strtok(c);
	flight.org_air = c;
	load_buf_strtok(c);
	flight.dest_air = c;
	load_buf_strtok(c);
	flight.schep_dep = atoi(c);
	load_buf_strtok(c);
	flight.dep_delay = atof(c); // atof agit comme atoi mais pour un float
	load_buf_strtok(c);
	flight.air_time = atof(c);
	load_buf_strtok(c);
	flight.dist = atoi(c);
	load_buf_strtok(c);
	flight.sched_arr = atoi(c);
	load_buf_strtok(c);
	flight.arr_delay = atof(c);
	load_buf_strtok(c);
	flight.diverted = atoi(c);
	load_buf_strtok(c);
	flight.cancelled = atoi(c);
}

void read_airline(struct cell_airline *cell, char buffer[MAX_BUFFER]) { // TOM FAIS LE EN ADAPTANT CELUI DU DESSUS A AIRLINE
}

void read_airport(struct cell_airport *cell, char buffer[MAX_BUFFER]) {
// PAREIL}
