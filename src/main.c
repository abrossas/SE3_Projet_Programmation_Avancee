#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../includes/data.h"
#include "../includes/requetes.h"

int main () {
	printf("0");
	FILE* f_flights = NULL;
	Liste_flights l_flights = NULL;
	printf("x");
	load_flights(f_flights, &l_flights);
	printf("y");
	free_lflights(&l_flights);

	return 0; }
