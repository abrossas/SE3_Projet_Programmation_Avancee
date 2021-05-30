#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/interface.h"

int main ()
{
    // 1 - Chargement des données //

    Liste_flights  l_flights  = NULL;
    Liste_airports l_airports = NULL;
    Liste_airlines l_airlines = NULL;
    if (load_files (&l_flights, &l_airports, &l_airlines) == 1)
        printf ("--------------------------------------- CHARGEMENT DES DONNEES EFFECTUE "
                "---------------------------------------\n\n");
    else
    {
        printf ("--------------------------------------- ERREUR LORS DU CHARGEMENT DES DONNEES "
                "----------------------------------------\n\n");
        return 0;
    }

    // 2 - Interface utilisateur //

    printf (
    "Bonjour, vous pouvez rentrer les différentes requêtes et terminer en écrivant quit\n\n");

    char * line = NULL;
    size_t n    = 0;
    getline (&line, &n, stdin);
    while (strcmp (line, "quit\n") != 0)
    { // Tant que l'utilisateur n'a pas rentré quit

        char *requete = NULL;
        requete       = strtok (line, " ");

        if (strcmp (requete, "show-airports") == 0) // Requête show-airport <airline_id>
        {
            requete = strtok (NULL, "\n"); // requete <- airline_id
            show_airports (requete, l_airports, l_flights);
            printf ("\n");
        }

        if (strcmp (requete, "show-airlines") == 0) // Requete show-airlines <port_id>
        {
            requete = strtok (NULL, "\n"); // requete <- port_id
            show_airlines (requete, l_airlines, l_flights);
            printf ("\n");
        }

        if (strcmp (requete, "show-flights") == 0) // Requete show-flights <port_id> <date> [<time>] [limit=<xx>]
        {
            requete = strtok (NULL, " "); // requete <- port_id
            char port_id[IATA_AIRPORT_MAX];
            strcpy (port_id, requete); // requete <- "m/d"
            requete = strtok (NULL, " ");
            Date d  = convert_md_to_date (requete); // On convertit "m/d" en une date

            int time = 0;  // On initialise par défaut time à 0 (pour 00:00)
            int max  = 10; // Et max à 10

            // Traitement des arguments optionnels (ne fonctionne pas)
            /*
                            requete = strtok(NULL, " ");
                            printf("%s",requete);
                            if (requete != NULL) { // L'utilisateur a bien rentré une heure
                                time = atoi(requete); // On redéfinit time
                                printf("%d",time);
                            }
                            requete = strtok(NULL, " ");
                            if (requete != NULL) // Si l'utilisateur a aussi rentré un nombre
               maximal de vols à afficher max = atoi(requete); // On redéfinit donc max
            */

            show_flights (port_id, d, l_flights, max, time);
            printf ("\n");
        }

        if (strcmp (requete, "most-delayed-flights\n") == 0) // Requete most-delayed-flights
        {
            most_delayed_flights (l_flights);
            printf ("\n");
        }

        if (strcmp (requete, "most-delayed-airlines\n") == 0) // Requete most-delayed-airlines
        {
            most_delayed_airlines (l_flights, l_airlines);
            printf ("\n");
        }

        if (strcmp (requete, "delayed-airline") == 0) // Requete delayed-airline <airline_id>
        {
            requete = strtok (NULL, "\n"); // requete <- airline_id
            delayed_airline (requete, l_airlines, l_flights);
            printf ("\n");
        }

        if (strcmp (requete, "most-delayed-airlines-at-airport") == 0) // Requete most-delayed-airlines-at-airport <port_id>
        {
            requete = strtok (NULL, "\n"); // requete <- port_id
            most_delayed_airlines_at_airport (requete, l_airlines, l_flights);
            printf ("\n");
        }

        if (strcmp (requete, "changed-flights") == 0) // Requete changed-flights <date>
        {
            requete = strtok (NULL, "\n"); // requete <- "m/d"
            Date d2 = convert_md_to_date (requete);
            changed_flights (d2, l_flights);
            printf ("\n");
        }

        if (strcmp (requete, "avg-flight-duration") == 0) // Requete avg-flight-duration <port_id> <port_id>
        {
            requete = strtok (NULL, " "); // requete <- port_id1
            char port_id1[IATA_AIRPORT_MAX];
            strcpy (port_id1, requete);
            requete = strtok (NULL, "\n"); // requete <- port_id2
            char port_id2[IATA_AIRPORT_MAX];
            strcpy (port_id2, requete);
            avg_flight_duration (port_id1, port_id2, l_flights);
            printf ("\n");
        }

        if (strcmp (requete, "find-itinerary") ==
            0) // Requete find-itinerary <port_id> <port_id> <date> mais ne traite pas les arguments optionnels et renvoie un vol direct sans escale
        {
            requete = strtok (NULL, " ");
            char port_org[IATA_AIRPORT_MAX];
            strcpy (port_org, requete);
            requete = strtok (NULL, " ");
            char port_dest[IATA_AIRPORT_MAX];
            strcpy (port_dest, requete);
            requete = strtok (NULL, "\n");
            Date d3 = convert_md_to_date (requete);
            find_itinerary (port_org, port_dest, d3, l_flights);
        }

        getline (&line, &n, stdin); // On traite une nouvelle ligne
    }

    printf ("\n------------------------------------------- FERMETURE DES FICHIERS "
            "-------------------------------------------\n");

    // 3 - Désallocation de l'espace

    free_lflights (&l_flights);
    free_lairports (&l_airports);
    free_lairlines (&l_airlines);

    return 0;
}
