#define MAX_DATE 5

//#include "data.h" // fonctions en rapport avec nos structures de données (déclaration, load..)

void show_airports(char*, Liste_airports);

void show_airlines(char*, Liste_airlines);

void show_flights(char*, char); // optionnel : heure de début et nombre limites de vol à afficher

void most_delayed_flights(Liste_flights);

void most_delayed_airlines(Liste_flights, Liste_airlines);

void delayed_airline(char*, Liste_airlines);

void most_delayed_airlines_at_airport(char*, Liste_airlines, Liste_airports);

void changed_flights(char*);

void avg_flight_duration(char*, char*);

void find_itinerary(char*, char*, char*); // optionnel : préciser l'heure, limité à X propositions
