#include "data.h"

#define IATA_MAX 5

#define MAX_WEEKDAY 10
#define MAX_DIVER 4
#define MAX_HOUR 3
#define MAX_MINUTE 3


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
} Date;

//----------- FONCTIONS POUR LES REQUETES -----------//

void add_head_iata (Liste_IATA *, char *);

// REQUETE 1 : show-airport

int airport_already_in_list (Liste_IATA, char *);

void show_airports (char *, Liste_airports, Liste_flights);

void info_airport (Liste_airports, Liste_IATA);

// REQUETE 2 : show-airline

int airline_already_in_list (Liste_IATA, char *);

void show_airlines (char *, Liste_airlines, Liste_flights);

void info_airline (Liste_airlines, Liste_IATA);

// REQUETE 3 : show-flights

int flight_already_in_list (Flight, Liste_flights);

void show_flights (char*, Date, Liste_flights, int); // optionnel : heure de début et nombre limites de vol à afficher

int same_date(Date, Date);

void convert_int_to_weekday(int , char*);

void info_flight(Liste_flights, int max);





void most_delayed_flights (Liste_flights);

void most_delayed_airlines (Liste_flights, Liste_airlines);

void delayed_airline (char *, Liste_airlines);

void most_delayed_airlines_at_airport (char *, Liste_airlines, Liste_airports);

void changed_flights (char *);

void avg_flight_duration (char *, char *);

void find_itinerary (char *, char *, char *); // optionnel : préciser l'heure, limité à X propositions
