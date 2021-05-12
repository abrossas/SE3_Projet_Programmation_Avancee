#define MAX_DATE 5

#include <data.h> // fonctions en rapport avec nos structures de données

void show-airports(char airline_id[IATA_AIRLINE_MAX], Liste_airports liste);

void show-airlines(char port_id[IATA_AIRPORT_MAX], Liste_airlines liste);

void show-flights(char port_id[IATA_AIRPORT_MAX], char date[MAX_DATE]); // optionnel : heure de début et nombre limites de vol à afficher

void most-delayed-flights(Liste_flights liste);

void most-delayed-airlines(Liste_flights liste_flights, Liste_airlines liste_airlines);

void delayed-airline(char airline_id[IATA_AIRLINE_MAX], Liste_airlines liste);

void most-delayed-airlines-at-airport(char port_id[IATA_AIRPORT_MAX], Liste_airlines liste_airports, Liste_airports liste_airports)

void changed-flights(char date[MAX_DATE]);

void avg-flight-duration(char port_id1[IATA_AIRPORT_MAX], char port_id2[IATA_AIRPORT_MAX]);

void find-itinerary(char port_id2[IATA_AIRPORT_MAX], char port_id2[IATA_AIRPORT_MAX], char date[MAX_DATE]); // optionnel : préciser l'heure, limité à X propositions
