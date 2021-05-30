#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/requetes.h"

// Cette fonction convertit un int en jour de la semaine (1 = lundi à 7 = dimanche)
void convert_int_to_weekday (int d, char weekday[MAX_WEEKDAY])
{
    if (d == 1) strcpy (weekday, "MONDAY");
    if (d == 2) strcpy (weekday, "TUESDAY");
    if (d == 3) strcpy (weekday, "WEDNESDAY");
    if (d == 4) strcpy (weekday, "THIRSDAY");
    if (d == 5) strcpy (weekday, "FRIDAY");
    if (d == 6) strcpy (weekday, "SATURDAY");
    if (d == 7) strcpy (weekday, "SUNDAY");
}

// Cette fonction renvoie 1 si les dates sont égales et 0 sinon
int same_date (Date d1, Date d2) { return d1.day == d2.day && d1.month == d2.month; }

// Cette fonction convertit un int au format "dddd" en 2 chaines de caractères heure et minute
void convert_int_to_hour (int h, char hour[MAX_HOUR], char minute[MAX_MINUTE])
{
    snprintf (hour, MAX_HOUR, "%d", h / 100);
    snprintf (minute, MAX_MINUTE, "%d", h % 100);
}

// Cette fonction convertit un bouléen (0 ou 1) en NO ou YES
void convert_int_to_yes (int x, char c[MAX_DIVER])
{
    if (x == 0)
        strcpy (c, "NO");
    else
        strcpy (c, "YES");
}

// Cette fonction renvoie 1 si l'aéroport identifié par son code IATA est dans la liste passée en argument et 0 sinon
int is_airport_in (char airport[IATA_AIRPORT_MAX], Liste_airports l_airports)
{
    if (l_airports == NULL) return 0;
    while (l_airports != NULL)
    {
        if (strcmp (airport, l_airports->airport.iata_airports) == 0) return 1;
        l_airports = l_airports->pnext_airp;
    }
    return 0;
}

// Cette fonction renvoie 1 si la compagnie aérienne identifié par son code IATA est dans la liste passée en argument et 0 sinon
int is_airline_in (char airline[IATA_AIRLINE_MAX], Liste_airlines l_airlines)
{
    if (l_airlines == NULL) return 0;
    while (l_airlines != NULL)
    {
        if (strcmp (airline, l_airlines->airline.iata_airlines) == 0) return 1;
        l_airlines = l_airlines->pnext_airl;
    }
    return 0;
}

// Cette fonction renvoie 1 si le vol est dans la liste passée en argument et 0 sinon
int is_flight_in (Flight flight, Liste_flights l_flights)
{
    if (l_flights == NULL) return 0;
    while (l_flights != NULL)
    {
        // On parcourt la liste chainée, si on trouve un élément similaire au vol flight, on renvoie 1 et on renvoie 0 si on a parcouru toute la liste sans jamais trouver
        Flight tmp = l_flights->flight;
        if (tmp.month == flight.month && tmp.day == flight.day && tmp.weekday == flight.weekday &&
            tmp.schep_dep == flight.schep_dep && tmp.dist == flight.dist && tmp.sched_arr == flight.sched_arr)
            return 1;
        l_flights = l_flights->pnext_fli;
    }
    return 0;
}

//---------- PREMIERE REQUETE ----------//

// Cette fonction renvoie toutes les informations des aéroports contenus dans la liste passée en argument
void info_airport (Liste_airports l_airports)
{
    if (l_airports == NULL) return;

    while (l_airports != NULL)
    // On parcourt toute la liste des aéroports et on affiche toutes les informations de chaque aéroport
    {
        printf ("CODE IATA : %s --- AEROPORT : %s --- VILLE : %s --- ETAT : %s\n",
                l_airports->airport.iata_airports, l_airports->airport.airport,
                l_airports->airport.city, l_airports->airport.state);
        l_airports = l_airports->pnext_airp;
    }
}

// Cette fonction extrait un aéroport identifié par son code IATA
void extract_airport (Airport *pairport, char airport[IATA_AIRPORT_MAX], Liste_airports l_airports)
{
    if (l_airports == NULL) return;
    Airport tmp;
    while (l_airports != NULL)
    {
        tmp = l_airports->airport;
        if (strcmp (airport, tmp.iata_airports) == 0) *pairport = tmp;
        l_airports = l_airports->pnext_airp;
    }
}

void show_airports (char airline[IATA_AIRPORT_MAX], Liste_airports l_airports, Liste_flights l_flights)
{
    Liste_airports l_airports_airline = NULL;
    while (l_flights != NULL)
    // On parcourt la liste des vols pour trouver ceux où la companie passée en argument est concernée pour les mettre dans la liste l_airports_airline initialisée plus haut
    {
        Airport tmp;
        if (strcmp (airline, l_flights->flight.airline) == 0) // On cherche les vols concernés par la companie passée en argument
        {
            if (is_airport_in (l_flights->flight.org_air, l_airports_airline) ==
                0) // Ici on vérifie si l'aéroport est déjà présent dans la liste afin d'éviter les doublons
            {
                extract_airport (&tmp, l_flights->flight.org_air, l_airports);
                add_head_airport (&l_airports_airline, tmp);
            }
        }
        l_flights = l_flights->pnext_fli;
    }

    if (l_airports_airline == NULL) // Cas où on n'a trouvé aucun aéroport à afficher (possible erreur de l'utilisateur)
    {
        printf ("Aucun aéroport ne correspond à la compagnie '%s' que vous avez saisi\n", airline);
        return;
    }

    // Cas où on a stocké tous les aéroports à afficher dans la liste l_airports_airline

    printf ("-------------------- LISTE DES AEROPORTS DEPUIS LESQUELS LA COMPANIE %s OPERE DES "
            "VOLS --------------------\n",
            airline);

    info_airport (l_airports_airline);
}

//---------- DEUXIEME REQUETE ----------//

// Cette fonction renvoie toutes les informations des compagnies contenues dans la liste passée en argument
void info_airline (Liste_airlines l_airlines)
{
    if (l_airlines == NULL) return;
    Airline tmp;
    while (l_airlines != NULL)
    // On parcourt toute la liste des compagnies et on affiche toutes les informations de chaque compagnie
    {
        tmp = l_airlines->airline;
        printf ("IATA CODE : %s ----------------------------------------------- AIRLINE : %s",
                tmp.iata_airlines, tmp.airline);
        l_airlines = l_airlines->pnext_airl;
    }
}

// Cette fonction extrait une compagnie identifiée par son code IATA
void extract_airline (Airline *pairline, char airline[IATA_AIRLINE_MAX], Liste_airlines l_airlines)
{
    if (l_airlines == NULL) return;
    Airline tmp;
    while (l_airlines != NULL)
    {
        tmp = l_airlines->airline;
        if (strcmp (airline, tmp.iata_airlines) == 0) *pairline = tmp;
        l_airlines = l_airlines->pnext_airl;
    }
}

void show_airlines (char port_id[IATA_AIRPORT_MAX], Liste_airlines l_airlines, Liste_flights l_flights)
{
    Liste_airlines l_airlines_airport = NULL;
    while (l_flights != NULL)
    {
        if (strcmp (port_id, l_flights->flight.org_air) ==
            0) // On cherche les vols qui ont pour aéroport de départ celui passé en argument
        {
            if (is_airline_in (l_flights->flight.airline, l_airlines_airport) ==
                0) // Ici on vérifie si la compagnie est déjà présente dans la liste afin d'éviter les doublons
            {
                Airline tmp;
                extract_airline (&tmp, l_flights->flight.airline, l_airlines);
                add_head_airline (&l_airlines_airport, tmp);
            }
        }
        l_flights = l_flights->pnext_fli;
    }

    if (l_airlines_airport == NULL) // Cas où on n'a trouvé aucune compagnie à afficher (possible erreur de l'utilisateur)
    {
        printf ("Aucune compagnie ne correspond à l'aéroport de départ '%s' que vous avez saisi\n", port_id);
        return;
    }

    // Cas où on a stocké toutes les compagnies à afficher dans la liste l_airports_airline
    printf ("--------------- LISTE DES COMPAGNIES AYANT DES VOLS PARTANT DE L'AEROPORT %s "
            "---------------\n",
            port_id);
    info_airline (l_airlines_airport);
}

//---------- TROISIEME REQUETE ----------//

void info_flight (Liste_flights l_flights, int max)
{
    if (l_flights == NULL) return;
    Flight tmp;
    int    i = 0; // Compteur pour afficher le nombre maximum de vols que l'utilisateur désire voir
    while (l_flights != NULL && i < max)
    {
        tmp = l_flights->flight;
        char weekday[MAX_WEEKDAY];
        convert_int_to_weekday (tmp.day, weekday);
        char hourdep[MAX_HOUR];
        char minutedep[MAX_MINUTE];
        convert_int_to_hour (tmp.schep_dep, hourdep, minutedep);
        char hourarr[MAX_HOUR];
        char minutearr[MAX_MINUTE];
        convert_int_to_hour (tmp.sched_arr, hourarr, minutearr);
        char diverted[MAX_DIVER];
        convert_int_to_yes (tmp.diverted, diverted);
        char cancelled[MAX_DIVER];
        convert_int_to_yes (tmp.cancelled, cancelled);

        printf ("%s %d/%d -- AIRLINE : %s -- DEST : %s -- DEP HOUR %s:%s -- DEP DELAY : %.2f -- "
                "AIRTIME : %.2f -- DIST : %d -- ARR HOUR %s:%s -- ARR DELAY : %.2f -- DIVERTED : "
                "%s -- CANCELLED : %s\n",
                weekday, tmp.month, tmp.day, tmp.airline, tmp.dest_air, hourdep, minutedep, tmp.dep_delay,
                tmp.air_time, tmp.dist, hourarr, minutearr, tmp.arr_delay, diverted, cancelled);
        l_flights = l_flights->pnext_fli;
        i++;
    }
}

void show_flights (char port_id[IATA_AIRPORT_MAX], Date d, Liste_flights l_flights, int max, int hourdep)
{
    Liste_flights l_tmp = NULL;
    while (l_flights != NULL)
    {
        Flight tmp      = l_flights->flight;
        Date   d_flight = { tmp.month, tmp.day };
        if (strcmp (port_id, l_flights->flight.org_air) == 0 && same_date (d, d_flight) && tmp.schep_dep > hourdep)
        // On cherche les vols qui partent de port_id à la même date que d
        {
            if (is_flight_in (tmp, l_tmp) == 0) add_head_flight (&l_tmp, tmp);
        }
        l_flights = l_flights->pnext_fli;
    }

    if (l_tmp == NULL)
    {
        // Cas où on n'a trouvé aucun vol à afficher
        printf ("Aucun vol ne correspond à vos critères de recherche\n");
        return;
    }

    // Cas où on a stocké tous les vols à afficher dans l_tmp

    char heuredep[MAX_HOUR];
    char minutedep[MAX_MINUTE];
    convert_int_to_hour (hourdep, heuredep, minutedep);

    printf ("----------------------------------------- LISTE DES VOLS PARTANT DE L'AEROPORT %s A "
            "LA DATE %d/%d APRES %s:%s (MAX %d PAR DEFAUT A 10)"
            " -----------------------------------------\n",
            port_id, d.month, d.day, heuredep, minutedep, max);
    info_flight (l_tmp, max);
}

//---------- QUATRIEME REQUETE ----------//

// Cette fonction retourne l'indice du vol ayant le plus petit retard parmi le tableau de flights passé en argument
int min_tab_flight (Flight tab_flights[MAX_MOST])
{
    int i_min = 0;
    int min   = tab_flights[0].arr_delay;
    for (int i = 1; i < MAX_MOST; i++)
    {
        if (tab_flights[i].arr_delay < min)
        {
            min   = tab_flights[i].arr_delay;
            i_min = i;
        }
    }
    return i_min;
}

// Si le retard du vol flight est supérieur au minimum des retards des vols de tab_flights alors il prend sa place
void elt_more_tab_flights (Flight flight, Flight tab_flights[MAX_MOST])
{
    int i_min = min_tab_flight (tab_flights);
    if (flight.arr_delay > tab_flights[i_min].arr_delay)
    {
        tab_flights[i_min] = flight;
    }
}

// Cette fonction initialise un vol avec arr_delay à nul
void init_tab_flights_arr_delay (Flight *pflight)
{
    pflight->arr_delay =
    0; // On met arr_delay à 0 car on veut trouver des arr_delay assez grands (comme on a mis -1 pour
       // les valeurs manquantes, si arr_delay est à -1 il ne prendra pas la place d'un vol qui a vraiment eu lieu)
}

void most_delayed_flights (Liste_flights l_flights)
{
    Flight *tab_flights = malloc (MAX_MOST * sizeof (struct flight));
    for (int i = 0; i < MAX_MOST; i++)
        // On initialise les éléments de notre tableau, si on ne fait pas ça le programme va bugger une fois sur deux
        init_tab_flights_arr_delay (&tab_flights[i]);

    while (l_flights != NULL)
    {
        // On parcourt tous les éléments et on récupère les 5 vols qui ont subis les plus longs retards à l'arrivée dans le tableau tab_flights
        Flight tmp = l_flights->flight;
        elt_more_tab_flights (tmp, tab_flights);
        l_flights = l_flights->pnext_fli;
    }

    // Il ne reste plus qu'à afficher tous les vols que le tableau contient

    printf ("--------------------------------------------------------------- LES %d VOLS QUI ONT "
            "SUBI LE PLUS DE RETARD A L'ARRIVEE "
            "---------------------------------------------------------------\n",
            MAX_MOST);

    for (int i = 0; i < MAX_MOST; i++)
    {
        Flight tmp = tab_flights[i];
        char   weekday[MAX_WEEKDAY];
        convert_int_to_weekday (tmp.day, weekday);
        char hourdep[MAX_HOUR];
        char minutedep[MAX_MINUTE];
        convert_int_to_hour (tmp.schep_dep, hourdep, minutedep);
        char hourarr[MAX_HOUR];
        char minutearr[MAX_MINUTE];
        convert_int_to_hour (tmp.sched_arr, hourarr, minutearr);
        char diverted[MAX_DIVER];
        convert_int_to_yes (tmp.diverted, diverted);
        char cancelled[MAX_DIVER];
        convert_int_to_yes (tmp.cancelled, cancelled);
        printf ("%s %d/%d -- AIRLINE : %s -- DEST : %s -- DEP HOUR %s:%s -- DEP DELAY : %.2f -- "
                "AIRTIME : %.2f -- DIST : %d -- ARR HOUR %s:%s -- ARR DELAY : %.2f -- DIVERTED : "
                "%s -- CANCELLED : %s\n",
                weekday, tmp.month, tmp.day, tmp.airline, tmp.dest_air, hourdep, minutedep, tmp.dep_delay,
                tmp.air_time, tmp.dist, hourarr, minutearr, tmp.arr_delay, diverted, cancelled);
    }
}

// REQUETE 5 : most-delayed-airlines //

// Cette fonction initialise une struct Airline_delay (voir requete.h) avec mean_delay à nul
void init_tab_airlines_delay (Airline_delay *pairline_delay) { pairline_delay->mean_delay = 0; }

// Cette fonction renvoie la moyenne des retards à l'arrivée des vols associés à une compagnie
float mean_delay_airline (Airline airline, Liste_flights l_flights)
{
    // On va considérer qu'arriver en avance contre-balance avec le fait d'arriver en retard donc on va garder les ARR_DELAY négatifs
    float M = 0;
    float i = 0;
    while (l_flights != NULL)
    {
        Flight tmp = l_flights->flight;
        if (strcmp (airline.iata_airlines, tmp.airline) == 0 && tmp.cancelled == 0 && tmp.diverted == 0)
        { // On ne prend pas les vols annulés ou déviés en compte pour le calcul de la moyenne
            M += tmp.arr_delay;
            i++;
        }
        l_flights = l_flights->pnext_fli;
    }
    if (i == 0) return 0;
    return M / i;
}

// Cette fonction retourne l'indice de la compagnie ayant la plus petite moyenne de retard parmi celles du tableau passé en argument
int min_tab_airlines_delay (Airline_delay tab_airlines_delay[MAX_MOST])
{
    int i_min = 0;
    int min   = tab_airlines_delay[0].mean_delay;
    for (int i = 1; i < MAX_MOST; i++)
    {
        if (tab_airlines_delay[i].mean_delay < min)
        {
            min   = tab_airlines_delay[i].mean_delay;
            i_min = i;
        }
    }
    return i_min;
}

void most_delayed_airlines (Liste_flights l_flights, Liste_airlines l_airlines)
{
    // On initialise notre tableau contenant 5 compagnies avec leur moyenne de retard
    Airline_delay *tab_airlines_delay = malloc (MAX_MOST * sizeof (struct airline_delay));
    for (int i = 0; i < MAX_MOST; i++) init_tab_airlines_delay (&tab_airlines_delay[i]);

    int i_min;
    while (l_airlines != NULL)
    {
        // On parcourt l_airlines et on remplace les valeurs du tableau à chaque fois qu'on trouve une moyenne plus grande que le minimum de celles contenues dans le tableau
        Airline tmp = l_airlines->airline;
        i_min       = min_tab_airlines_delay (tab_airlines_delay);
        float mean  = mean_delay_airline (tmp, l_flights);
        if (mean > tab_airlines_delay[i_min].mean_delay)
        {
            // Si la moyenne des retards associées à la companie tmp est plus grande que le min des moyennes des retards des compagnies stockées alors tmp prend sa place
            tab_airlines_delay[i_min].airline    = tmp;
            tab_airlines_delay[i_min].mean_delay = mean;
        }
        l_airlines = l_airlines->pnext_airl;
    }

    // On a maintenant notre tableau qui contient les compagnies ayant le plus de retard en moyenne à l'arrivée, il suffit alors de les afficher

    printf ("------------------- LES %d COMPAGNIES AYANT LE PLUS DE RETARD EN MOYENNE A L'ARRIVEE "
            "-------------------\n",
            MAX_MOST);
    for (int i = 0; i < MAX_MOST; i++)
    {
        printf ("IATA CODE : %s ----------------- MEAN_DELAY : %.2f ----------------- AIRLINE : %s",
                tab_airlines_delay[i].airline.iata_airlines, tab_airlines_delay[i].mean_delay,
                tab_airlines_delay[i].airline.airline);
    }
}

// REQUETE 6 : delayed-airline // On utilisera la fonction mean_delay_airline codée précédemment

void delayed_airline (char iata_airline[IATA_AIRLINE_MAX], Liste_airlines l_airlines, Liste_flights l_flights)
{
    // Pour pouvoir utiliser la fonction codée précédemment, il faut trouver la compagnie associée au code iata que l'utilisateur va rentrer
    Airline airline;
    bool    trouve = false; // Ce bouléen permet de prévenir une éventuelle erreur de l'utilisateur et de le prévenir si on ne trouve aucune compagnie correspondante

    while (l_airlines != NULL && trouve == false)
    {
        Airline tmp = l_airlines->airline;
        if (strcmp (iata_airline, tmp.iata_airlines) == 0)
        {
            trouve  = true;
            airline = tmp;
        }
        l_airlines = l_airlines->pnext_airl;
    }

    // Si on a trouvé

    if (trouve)
    {
        printf ("------ RETARD MOYEN DE LA COMPAGNIE %s : %.2f ------\n", iata_airline,
                mean_delay_airline (airline, l_flights));
    }

    // Si on a pas trouvé

    else
    {
        printf ("------ AUCUNE COMPAGNIE NE CORRESPOND A %s DANS LA BASE DE DONNEES ------\n", iata_airline);
    }
}

// REQUETE 7 : most-delayed-airlines-at-airport //

// Cette fonction renvoie la moyenne des retards à l'arrivée d'une compagnie passée en argument et identifiée par son code iata
float mean_delay_airline_at_airport (char iata_airport[IATA_AIRPORT_MAX], Airline airline, Liste_flights l_flights)
{
    float M = 0;
    float i = 0;
    while (l_flights != NULL)
    {
        Flight tmp = l_flights->flight;
        if (strcmp (iata_airport, tmp.dest_air) == 0 &&
            strcmp (airline.iata_airlines, tmp.airline) == 0 && tmp.diverted == 0 && tmp.cancelled == 0)
        { // On ne prend pas en compte les vols déviés ou annulés
            M += tmp.arr_delay;
            i++;
        }
        l_flights = l_flights->pnext_fli;
    }
    if (i == 0) return 0;
    return M / i;
}

void most_delayed_airlines_at_airport (char iata_airport[IATA_AIRPORT_MAX], Liste_airlines l_airlines, Liste_flights l_flights)
{
    // On initialise notre tableau contenant 3 compagnies avec leur moyenne de retard à l'arrivée de l'aéroport
    Airline_delay *tab_airlines_delay = malloc (MAX_MOST2 * sizeof (struct airline_delay));
    for (int i = 0; i < MAX_MOST2; i++) init_tab_airlines_delay (&tab_airlines_delay[i]);

    int i_min;
    while (l_airlines != NULL)
    {
        Airline tmp = l_airlines->airline;
        i_min       = min_tab_airlines_delay (tab_airlines_delay);
        float mean  = mean_delay_airline_at_airport (iata_airport, tmp, l_flights);
        if (mean > tab_airlines_delay[i_min].mean_delay)
        {
            // Si la moyenne des retards associées à la compagnie tmp est plus grande que le min des moyennes des retards des compagnies stockées alors tmp prend sa place
            tab_airlines_delay[i_min].airline    = tmp;
            tab_airlines_delay[i_min].mean_delay = mean;
        }
        l_airlines = l_airlines->pnext_airl;
    }

    // On a maintenant notre tableau qui contient les airlines ayant le plus de retard en moyenne à l'arrivée, il suffit de les afficher

    printf ("-------- LES %d COMPAGNIES AYANT LE PLUS DE RETARD EN MOYENNE A L'ARRIVEE DE "
            "L'AEROPORT %s --------\n",
            MAX_MOST2, iata_airport);
    for (int i = 0; i < MAX_MOST2; i++)
    {
        printf ("IATA CODE : %s ----------------- MEAN_DELAY : %.2f ----------------- AIRLINE : %s",
                tab_airlines_delay[i].airline.iata_airlines, tab_airlines_delay[i].mean_delay,
                tab_airlines_delay[i].airline.airline);
    }
}

// REQUETE 8 : changed-flights

// Cette fonction renvoie 1 si le vol flight a été dévié ou annulé à la date d et 0 sinon
int is_changed_flight_at_date (Flight flight, Date d)
{
    return ((flight.diverted || flight.cancelled) && flight.month == d.month && flight.day == d.day);
}

void changed_flights (Date date, Liste_flights l_flights)
{
    Liste_flights l_changed_flights =
    NULL; // On crée une liste temporaire qui va contenir tous les vols qu'on voudra afficher
    int i = 0;
    while (l_flights != NULL)
    {
        // On parcourt toutes la liste des vols et quand on trouve un vol annulé ou dévié on l'ajoute à la liste des vols à afficher
        Flight tmp = l_flights->flight;
        if (is_changed_flight_at_date (tmp, date))
        {
            i++;
            add_head_flight (&l_changed_flights, tmp);
        }
        l_flights = l_flights->pnext_fli;
    }

    // On affiche maintenant les vols contenus dans la liste temporaire
    printf ("------------------------ LISTE DES VOLS ANNULES OU DEVIES A LA DATE %d/%d "
            "------------------------\n",
            date.month, date.day);
    info_flight (l_changed_flights, i);
}

// REQUETE 9 :

// Cette fonction retourne la moyenne des airtime des vols dans la liste passée en argument
float mean_airtime (Liste_flights l_flights_airtime)
{
    float  m = 0;
    float  i = 0;
    Flight tmp;
    while (l_flights_airtime != NULL)
    {
        tmp = l_flights_airtime->flight;
        m += tmp.air_time;
        i++;
        l_flights_airtime = l_flights_airtime->pnext_fli;
    }
    if (i == 0) return 0;
    return m / i;
}

// Cette fonction renvoie 1 si le vol flight est entre les aéroports passés en argument et qu'il n'a ni été dévie ni été annulé
int is_flight_between_airports (char airport1[IATA_AIRPORT_MAX], char airport2[IATA_AIRPORT_MAX], Flight flight)
{
    return ((strcmp (airport1, flight.org_air) == 0 && strcmp (airport2, flight.dest_air) == 0) ||
            (strcmp (airport1, flight.dest_air) == 0 && strcmp (airport2, flight.org_air) == 0 &&
             flight.cancelled == 0 && flight.diverted == 0));
}

void avg_flight_duration (char airport1[IATA_AIRPORT_MAX], char airport2[IATA_AIRPORT_MAX], Liste_flights l_flights)
{
    Liste_flights l_flights_airtime =
    NULL; // On crée une liste temporaire qui va contenir tous les vols entre airport1 et airport2
    Flight tmp;
    int    nb_flights = 0;
    while (l_flights != NULL)
    {
        // On parcourt tous les vols pour trouver ceux entre les 2 aéroports passés en argument et on les ajoute à la liste temporaire
        tmp = l_flights->flight;
        if (is_flight_between_airports (airport1, airport2, tmp))
        {
            add_head_flight (&l_flights_airtime, tmp);
            nb_flights++;
        }
        l_flights = l_flights->pnext_fli;
    }

    float mean = mean_airtime (l_flights_airtime); // On calcule la moyenne des temps de vol

    printf ("------- TEMPS DE VOL MOYEN ENTRE LES AEROPORTS %s ET %s : %.2f (%d VOLS) -------\n",
            airport1, airport2, mean, nb_flights);
}

// REQUETE 10 : version simplifiée (trouve des vols directs sans escale)

// Cette fonction renvoie 1 si le vol flight est entre les aéroports d'origine et de destination passés en paramètre à une date donnée
int is_direct_flight_date (char airport_org[IATA_AIRPORT_MAX], char airport_dest[IATA_AIRPORT_MAX], Date d, Flight flight)
{
    return (strcmp (flight.org_air, airport_org) == 0 && strcmp (flight.dest_air, airport_dest) == 0 &&
            d.month == flight.month && d.day == flight.day);
}

void find_itinerary (char airport_org[IATA_AIRPORT_MAX], char airport_dest[IATA_AIRPORT_MAX], Date d, Liste_flights l_flights)
{
    Liste_flights tmp = NULL;
    while (l_flights != NULL)
    {
        // On parcourt tous les vols pour trouver celui (s'il existe) entre les aéroports passés en argument
        if (is_direct_flight_date (airport_org, airport_dest, d, l_flights->flight))
        {
            add_head_flight (&tmp, l_flights->flight);
            break; // Si on l'a trouvé on casse la boucle
        }
        l_flights = l_flights->pnext_fli;
    }

    if (tmp == NULL) // On a trouvé aucun vol
    {
        printf ("Aucun vol direct n'existe entre %s et %s\n", airport_org, airport_dest);
    }
    else
    { // On a trouvé un vol

        printf ("------------------------------------------- VOL DIRECT ENTRE LES AEROPORTS %s et "
                "%s LE %d/%d -------------------------------------------\n",
                airport_org, airport_dest, d.month, d.day);

        info_flight (tmp, 1);
    }
}
