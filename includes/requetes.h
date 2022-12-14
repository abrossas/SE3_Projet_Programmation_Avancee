#include "data.h"

#define MAX_WEEKDAY 10
#define MAX_DIVER 4
#define MAX_HOUR 3
#define MAX_MINUTE 3
#define MAX_MOST 5
#define MAX_MOST2 3

//----------- STRUCTURES DE DONNEES POUR LES REQUETES -----------//

// On utilise cette structure lorsqu'il faut afficher les x compagnies ayant le plus de retard en moyenne
typedef struct airline_delay
{
    Airline airline;
    float   mean_delay;
} Airline_delay;

// On utilise cette structure pour stocker des dates au format M/D
typedef struct Date
{
    int month;
    int day;
} Date;

//----------- FONCTIONS POUR PLUSIEURS REQUETES -----------//

int same_date (Date, Date);

void convert_int_to_weekday (int, char *);

void convert_int_to_yes (int, char *);

void convert_int_to_hour (int, char *, char *);

int is_airport_in (char *, Liste_airports);

int is_airline_in (char *, Liste_airlines);

int is_flight_in (Flight, Liste_flights);

//----------- FONCTIONS SPECIFIQUES A UNE REQUETE -----------//

// REQUETE 1 : show-airport

void extract_airport (Airport *, char *, Liste_airports);

void show_airports (char *, Liste_airports, Liste_flights);

void info_airport (Liste_airports);

// REQUETE 2 : show-airline

void extract_airline (Airline *, char *, Liste_airlines);

void show_airlines (char *, Liste_airlines, Liste_flights);

void info_airline (Liste_airlines);

// REQUETE 3 : show-flights

void show_flights (char *, Date, Liste_flights, int, int); // optionnel : heure de début et nombre limites de vol à afficher

void info_flight (Liste_flights, int max);

// REQUETE 4 : most-delayed-flights

void most_delayed_flights (Liste_flights);

void elt_more_tab (Flight, Flight[MAX_MOST]);

int min_tab_flight (Flight[MAX_MOST]);

void init_tab_flights_arr_delay (Flight *);

// REQUETE 5 : most-delayed-airlines

void init_tab_airlines_delay (Airline_delay *);

void most_delayed_airlines (Liste_flights, Liste_airlines);

float mean_delay_airline (Airline, Liste_flights);

int min_tab_airlines_delay (Airline_delay *);

// REQUETE 6 : delayed-airline (on va utiliser mean_delay_airline de la requête 5)

void delayed_airline (char *, Liste_airlines, Liste_flights);

// REQUETE 7 : most-delayed-airlines-at-airports (on utilisera min_tab_arlines_delay et la structure définie dans la requete 5)

void most_delayed_airlines_at_airport (char *, Liste_airlines, Liste_flights);

float mean_delay_airline_at_airport (char *, Airline, Liste_flights);

// REQUETE 8 : changed-flights

void changed_flights (Date, Liste_flights);

int is_changed_flight_at_date (Flight, Date);

// REQUETE 9 : avg-flight-duration

void avg_flight_duration (char *, char *, Liste_flights);

float mean_airtime (Liste_flights);

int is_flight_between_airports (char *, char *, Flight);

// REQUETE 10 : find_itinerary

int is_direct_flight_date (char *, char *, Date d, Flight);

void find_itinerary (char *, char *, Date d, Liste_flights); // optionnel : préciser l'heure, limité à X propositions
