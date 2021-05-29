#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/data.h"

void add_head_flight (Liste_flights *pliste, Flight flight)
{
    struct cell_flight *new = malloc (sizeof (struct cell_flight));
    new->flight             = flight;
    new->pnext_fli          = *pliste;
    *pliste                 = new;
}

void add_head_airline (Liste_airlines *pliste, Airline airline)
{
    struct cell_airline *new = malloc (sizeof (struct cell_airline));
    new->airline             = airline;
    new->pnext_airl          = *pliste;
    *pliste                  = new;
}

void add_head_airport (Liste_airports *pliste, Airport airport)
{
    struct cell_airport *new = malloc (sizeof (struct cell_airport));
    new->airport             = airport;
    new->pnext_airp          = *pliste;
    *pliste                  = new;
}

void read_flight (Liste_flights *pl_flights, char *line)
{
    // cette fonction sert à lire une ligne du fichier CSV des flights et à mettre les données dans une structure Flight puis à la mettre dans la liste des flights
    char *strToken;
    char *Token[14];

    for (int i = 0; i < 14; i++)
    {
        strToken = strsep (&line, ","); // strsep permet de séparer la chaine de caractère et renvoie la chaine de caractère juste avant l'apparition de ","
        if (strlen (strToken) != 0)
            Token[i] = strToken;
        else                 // cas où 2 virgules se suivent
            Token[i] = "-1"; // on choisit arbitrairement de mettre -1 pour les valeurs manquantes
    }

    //------------------ LECTURE DES DONNEES DANS LA STRUCTURE FLIGHT --------------------//

    Flight flight;

    flight.month   = atoi (Token[0]);
    flight.day     = atoi (Token[1]);
    flight.weekday = atoi (Token[2]);
    strcpy (flight.airline, Token[3]);
    strcpy (flight.org_air, Token[4]);
    strcpy (flight.dest_air, Token[5]);
    flight.schep_dep = atoi (Token[6]);
    flight.dep_delay = atof (Token[7]);
    flight.air_time  = atof (Token[8]);
    flight.dist      = atoi (Token[9]);
    flight.sched_arr = atoi (Token[10]);
    flight.arr_delay = atof (Token[11]);
    flight.diverted  = atoi (Token[12]);
    flight.cancelled = atoi (Token[13]);

    //------------------ AJOUT DU NOUVEAU FLIGHT A LA LISTE ------------------//

    add_head_flight (pl_flights, flight);
}

void read_airline (Liste_airlines *pl_airlines, char *line)
{
    // cette fonction sert à lire une ligne du fichier CSV des airlines et à mettre les données dans une structure Airline puis à la mettre dans la liste des airlines
    char *strToken;
    char *Token[2];

    for (int i = 0; i < 2; i++)
    {
        strToken = strsep (&line, ","); // strsep permet de séparer la chaine de caractère et renvoie la chaine de caractère juste avant l'apparition de ","
        if (strlen (strToken) != 0)
            Token[i] = strToken;
        else                 // cas où 2 virgules se suivent
            Token[i] = "-1"; // on choisit arbitrairement de mettre -1 pour les valeurs manquantes
    }

    //------------------ LECTURE DES DONNEES DANS LA STRUCTURE AIRLINE --------------------//

    Airline airline;

    strcpy (airline.iata_airlines, Token[0]);
    strcpy (airline.airline, Token[1]);

    //------------------ AJOUT DU NOUVEAU AIRLINE A LA LISTE ------------------//

    add_head_airline (pl_airlines, airline);
}


void read_airport (Liste_airports *pl_airports, char *line)
{
    // cette fonction sert à lire une ligne du fichier CSV des airports et à mettre les données dans une structure Airport puis à la mettre dans la liste des airports
    char *strToken;
    char *Token[7];

    for (int i = 0; i < 7; i++)
    {
        strToken = strsep (&line, ","); // strsep permet de séparer la chaine de caractère et renvoie la chaine de caractère juste avant l'apparition de ","
        if (strlen (strToken) != 0)
        {
            Token[i] = strToken;
        }
        else
        {                    // cas où 2 virgules se suivent
            Token[i] = "-1"; // on choisit arbitrairement de mettre -1 pour les valeurs manquantes
        }
    }

    //------------------ LECTURE DES DONNEES DANS LA STRUCTURE AIRPORT --------------------//

    Airport airport;

    strcpy (airport.iata_airports, Token[0]);
    strcpy (airport.airport, Token[1]);
    strcpy (airport.city, Token[2]);
    strcpy (airport.state, Token[3]);
    strcpy (airport.country, Token[4]);
    airport.latitude  = atof (Token[5]);
    airport.longitude = atof (Token[6]);

    //------------------ AJOUT DU NOUVEAU AIRPORT A LA LISTE ------------------//

    add_head_airport (pl_airports, airport);
}


int load_flights (FILE *f_flights, Liste_flights *pl_flights)
{ // Retourne 1 si succès, 0 sinon
    // On considère que *pl_flight a été initialisée à vide et f_flights à NULL
    f_flights = fopen ("../data/flights.csv", "r");
    if (f_flights == NULL)
    {
        printf ("Couldn't open file \n");
        return 0;
    }
    char * line = NULL;
    size_t len  = 0;
    getline (&line, &len, f_flights); // on "saute" la premiere ligne qui ne nous intéresse pas

    while (getline (&line, &len, f_flights) != -1) // On lit chaque ligne du fichier 1 par 1 jusqu'à la fin du fichier
    {
        read_flight (pl_flights, line); // On écrit le flight dans l_flights
    }

    free (line);
    fclose (f_flights);
    return 1;
}

int load_airlines (FILE *f_airlines, Liste_airlines *pl_airlines)
{ // Retourne 1 si succès, 0 sinon
    // On considère que *pl_airlines a été initialisée à vide et f_airlines à NULL
    f_airlines = fopen ("../data/airlines.csv", "r");
    if (f_airlines == NULL)
    {
        printf ("Couldn't open file \n");
        return 0;
    }
    char * line = NULL;
    size_t len  = 0;
    getline (&line, &len, f_airlines); // on "saute" la premiere ligne qui ne nous intéresse pas
    while (getline (&line, &len, f_airlines) != -1) // On lit chaque ligne du fichier 1 par 1 jusqu'à la fin du fichier
    {
        read_airline (pl_airlines, line); // On écrit le airline dans l_airlines
    }

    free (line);
    fclose (f_airlines);
    return 1;
}

int load_airports (FILE *f_airports, Liste_airports *pl_airports)
{ // Retourne 1 si succès, 0 sinon
    // On considère que *pl_airports a été initialisée à vide et f_airports à NULL
    f_airports = fopen ("../data/airports.csv", "r");
    if (f_airports == NULL)
    {
        printf ("Couldn't open file \n");
        return 0;
    }
    char * line = NULL;
    size_t len  = 0;
    getline (&line, &len, f_airports); // on "saute" la premiere ligne qui ne nous intéresse pas

    while (getline (&line, &len, f_airports) != -1) // On lit chaque ligne du fichier 1 par 1 jusqu'à la fin du fichier
    {
        read_airport (pl_airports, line); // On écrit le airport dans l_airports
    }

    free (line);
    fclose (f_airports);
    return 1;
}

void free_lflights (Liste_flights *pl_flights)
{
    if (*pl_flights == NULL)
    {
        return; // aucune allocation mémoire n'a été fait
    }
    struct cell_flight *tmp = NULL;
    while (*pl_flights != NULL)
    {
        tmp = (*pl_flights)->pnext_fli;
        free (*pl_flights);
        *pl_flights = tmp;
    }
}

void free_lairlines (Liste_airlines *pl_airlines)
{
    if (*pl_airlines == NULL)
    {
        return;
    }
    struct cell_airline *tmp = NULL;
    while (*pl_airlines != NULL)
    {
        tmp = (*pl_airlines)->pnext_airl;
        free (*pl_airlines);
        *pl_airlines = tmp;
    }
}

void free_lairports (Liste_airports *pl_airports)
{
    if (*pl_airports == NULL)
    {
        return;
    }
    struct cell_airport *tmp = NULL;
    while (*pl_airports != NULL)
    {
        tmp = (*pl_airports)->pnext_airp;
        free (*pl_airports);
        *pl_airports = tmp;
    }
}

// Cette fonction charge tous les fichiers dans nos structures de données et renvoie 1 si l'opération a réussi et 0 sinon
int load_files(Liste_flights *pl_flights, Liste_airports *pl_airports, Liste_airlines *pl_airlines) {
	FILE *f_flights = NULL;
	FILE *f_airports = NULL;
	FILE *f_airlines = NULL;
	if (load_flights(f_flights, pl_flights) == 0)
		return 0;
	if (load_airports(f_airports, pl_airports) == 0)
		return 0;
	if (load_airlines(f_airlines, pl_airlines) == 0)
		return 0;
	return 1;
}

