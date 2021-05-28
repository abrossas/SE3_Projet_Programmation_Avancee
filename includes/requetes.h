#include "data.h"

#define IATA_MAX 5

//----------- STRUCTURES DE DONNEES POUR LES REQUETES -----------//

struct cell_IATA // on utilise cette structure de données pour stocker uniquement les codes IATA des aéroports pour la requête 1 (show-airport)
{
    char              iata[IATA_MAX];
    struct cell_IATA *p_next;
};

typedef struct cell_IATA *Liste_IATA;


typedef struct Date // on utilise cette structure pour stocker des dates de départ
{
    int month;
    int day;
    int weekday;
} Date;

//----------- FONCTIONS POUR LES REQUETES -----------//

void add_head_iata(Liste_IATA *, char *);

// REQUETE 1 : show-airport

int airport_already_in_list (Liste_IATA, char *);

void show_airports (char *, Liste_airports, Liste_flights);

void info_airport (Liste_airports, Liste_IATA)

// REQUETE 2 : show-airline

int airline_already_in_list (Airline, Liste_airlines);

void show_airlines (char *, Liste_airlines);

void info_airline (Liste_airlines, Liste)

// REQUETE 3 : show-flights

int flight_already_in_list (Flight, Liste_flights);

void show_flights (char *, char); // optionnel : heure de début et nombre limites de vol à afficher



void most_delayed_flights (Liste_flights);

void most_delayed_airlines (Liste_flights, Liste_airlines);

void delayed_airline (char *, Liste_airlines);

void most_delayed_airlines_at_airport (char *, Liste_airlines, Liste_airports);

void changed_flights (char *);

void avg_flight_duration (char *, char *);

void find_itinerary (char *, char *, char *); // optionnel : préciser l'heure, limité à X propositions
