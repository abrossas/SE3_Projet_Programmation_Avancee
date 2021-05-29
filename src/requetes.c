#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/requetes.h"

void add_head_iata (Liste_IATA *pl_iata, char iata[IATA_AIRPORT_MAX])
{
    struct cell_IATA *pc = malloc (sizeof (struct cell_IATA));
    strcpy (pc->iata, iata);
    pc->p_next = *pl_iata;
    *pl_iata   = pc;
}

void convert_int_to_weekday(int d, char weekday[MAX_WEEKDAY]) {
    if (d==1)
        strcpy(weekday,"MONDAY");
    if (d==2)
        strcpy(weekday,"TUESDAY");
    if (d==3)
        strcpy(weekday,"WEDNESDAY");
    if (d==4)
        strcpy(weekday,"THIRSDAY");
    if (d==5)
        strcpy(weekday,"FRIDAY");
    if (d==6)
        strcpy(weekday,"SATURDAY");
    if (d==7)
        strcpy(weekday,"SUNDAY");
}

int same_date(Date d1, Date d2) {
    // Cette fonction renvoie 1 si les dates sont similaires et 0 sinon
    return d1.day == d2.day && d1.month == d2.month;
}

void convert_int_to_hour(int h, char hour[MAX_HOUR], char minute[MAX_MINUTE]) { // convertir un int au format "dddd" en 2 chaines de caractères heure et minute
	snprintf (hour, MAX_HOUR, "%d",h/100);
	snprintf (minute, MAX_MINUTE, "%d",h%100);
	}

void convert_int_to_yes(int x, char c[MAX_DIVER]) { // cette fonction convertit un bouléen (0 ou 1) en NO ou YES
	if (x==0)
		strcpy(c,"NO");
	else
		strcpy(c,"YES");
}

//---------- PREMIERE REQUETE ----------//

int airport_already_in_list (Liste_IATA l_iata, char iata[IATA_AIRPORT_MAX])
{
    // Cette fonction renvoie 1 si un aéroport (identifié par son code IATA) est déjà présent dans une liste chainée de codes IATA et 0 sinon
    if (l_iata == NULL) return 0;
    while (l_iata != NULL) // on parcourt la liste chainée, si on trouve un élément similaire à iata, on renvoie 1 et on renvoie 0 si on a parcouru toute la liste sans jamais trouver
    {
        if (strcmp (iata, l_iata->iata) == 0) return 1;
        l_iata = l_iata->p_next;
    }
    return 0;
}

void info_airport (Liste_airports l_airports, Liste_IATA l_iata)
{
    if (l_airports == NULL) // Ces 2 cas sont pratiquement sûrs de ne jamais être vérifiés
        return;
    if (l_iata == NULL) return;

    while (l_airports != NULL) // On parcourt toute la liste des aéroports (qu'on a préalablement load) pour trouver les infos de celui qui correspond au code iata du premier élément de l_iata
    {
        if (strcmp (l_iata->iata, l_airports->airport.iata_airports) == 0)
            printf ("CODE IATA : %s --- AEROPORT : %s --- VILLE : %s --- ETAT : %s\n",
                    l_airports->airport.iata_airports, l_airports->airport.airport,
                    l_airports->airport.city, l_airports->airport.state);
        l_airports = l_airports->pnext_airp;
    }
}

void show_airports (char airline[IATA_AIRPORT_MAX], Liste_airports l_airports, Liste_flights l_flights)
{
    Liste_IATA l_iata = NULL;
    while (l_flights != NULL) // On parcourt la liste des vols pour trouver ceux où la companie passée en argument est concernée pour les mettres dans la liste l_iata initialisée plus haut
    {
        if (strcmp (airline, l_flights->flight.airline) == 0)
        {
            if (airport_already_in_list (l_iata, l_flights->flight.org_air) ==
                0) // ici on vérifie s'il est déjà présent dans la liste afin d'éviter les doublons
                add_head_iata (&l_iata, l_flights->flight.org_air);
        }
        l_flights = l_flights->pnext_fli;
    }

    if (l_iata == NULL)
    { // Cas où on n'a trouvé aucun aéroport à afficher (possible erreur de l'utilisateur)
        printf ("Aucun aéroport ne correspond à la compagnie '%s' que vous avez rentrée\n", airline);
        return;
    }
    printf ("\n-------------------- LISTE DES AEROPORTS DEPUIS LESQUELS LA COMPANIE %s OPERE DES "
            "VOLS --------------------\n",
            airline);

    while (l_iata != NULL)
    { // Cas où on a stocké tous les codes IATA des aéroports à afficher dans la liste l_iata
        info_airport (l_airports, l_iata);
        l_iata = l_iata->p_next;
    }
    printf ("\n");
}

//---------- DEUXIEME REQUETE ----------//

int airline_already_in_list (Liste_IATA l_iata, char airline[IATA_AIRLINE_MAX])
{
    // Cette fonction renvoie 1 si une companie (identifiée par son code IATA) est déjà présente dans une liste de companies et 0 sinon
    if (l_iata == NULL) return 0;
    while (l_iata != NULL) // on parcourt la liste, si on trouve un élément similaire à airline, on renvoie 1 et on renvoie 0 si on a parcouru toute la liste sans jamais trouver
    {
        if (strcmp (airline, l_iata->iata) == 0) return 1;
        l_iata = l_iata->p_next;
    }
    return 0;
}

void info_airline (Liste_airlines l_airlines, Liste_IATA l_iata)
{
    if (l_iata == NULL) return;
    if (l_airlines == NULL) return;
    while (l_airlines != NULL)
    {
        if (strcmp (l_airlines->airline.iata_airlines, l_iata->iata) == 0)
            printf ("IATA CODE : %s ----------------------------------------------- AIRLINE : %s",
                    l_airlines->airline.iata_airlines, l_airlines->airline.airline);
        l_airlines = l_airlines->pnext_airl;
    }
}

void show_airlines (char port_id[IATA_AIRPORT_MAX], Liste_airlines l_airlines, Liste_flights l_flights)
{
    Liste_IATA l_iata = NULL;
    while (l_flights != NULL)
    {
        if (strcmp (port_id, l_flights->flight.org_air) ==
            0) // On cherche les aéroports de départ pour différents vols qui sont les mêmes que port_id
        {
            if (airline_already_in_list (l_iata, l_flights->flight.airline) == 0)
                add_head_iata (&l_iata, l_flights->flight.airline);
        }
        l_flights = l_flights->pnext_fli;
    }

    if (l_iata == NULL) // Cas où on n'a trouvé aucune companie à afficher (possible erreur de l'utilisateur)
        return;

    printf ("--------------- LISTE DES COMPANIES AYANT DES VOLS PARTANT DE L'AEROPORT %s "
            "---------------\n",
            port_id);
    while (l_iata != NULL)
    {
        info_airline (l_airlines, l_iata);
        l_iata = l_iata->p_next;
    }
}


//---------- TROISIEME REQUETE ----------//

int flight_already_in_list (Flight flight, Liste_flights l_flights) {
    if (l_flights == NULL)
            return 0;
    while (l_flights != NULL)
    { // on parcourt la liste chainée, si on trouve un élément similaire au vol flight, on renvoie 1 et on renvoie 0 si on a parcouru toute la liste sans jamais trouver 
        Flight tmp = l_flights->flight;
        if (tmp.month == flight.month &&  tmp.day == flight.day &&  tmp.weekday == flight.weekday
&&  tmp.schep_dep == flight.schep_dep &&  tmp.dist == flight.dist && tmp.sched_arr == flight.sched_arr) 
    return 1;
    l_flights = l_flights->pnext_fli;
    }
    return 0;
}

void info_flight(Liste_flights l_flights, int max) {
    if (l_flights == NULL)
        return;
    Flight tmp;
    int i=0; // compteur pour afficher le nombre maximum de vols que l'utilisateur désire voir
    while (l_flights != NULL && i<max)
    {
        tmp = l_flights->flight;
        char weekday[MAX_WEEKDAY];
        convert_int_to_weekday(tmp.day,weekday);
	    char hourdep[MAX_HOUR];
	    char minutedep[MAX_MINUTE];
	    convert_int_to_hour(tmp.schep_dep, hourdep, minutedep);
	    char hourarr[MAX_HOUR];
	    char minutearr[MAX_MINUTE];
	    convert_int_to_hour(tmp.sched_arr, hourarr, minutearr);
	    char diverted[MAX_DIVER];
	    convert_int_to_yes(tmp.diverted, diverted);
	    char cancelled[MAX_DIVER];
	    convert_int_to_yes(tmp.cancelled, cancelled);

        printf("%s %d/%d -- AIRLINE : %s -- DEST : %s -- DEP HOUR %s:%s -- DEP DELAY : %f -- AIRTIME : %f -- DIST : %d -- ARR HOUR %s:%s -- ARR DELAY : %f -- DIVERTED : %s -- CANCELLED : %s\n", weekday, tmp.month, tmp.day, tmp.airline, tmp.dest_air, hourdep, minutedep, tmp.dep_delay, tmp.air_time, tmp.dist, hourarr, minutearr, tmp.arr_delay, diverted, cancelled);
        l_flights = l_flights->pnext_fli;
    }
}

void show_flights (char port_id[IATA_AIRPORT_MAX], Date d, Liste_flights l_flights, int max, int hourdep) {   
   Liste_flights l_tmp = NULL;
    while (l_flights != NULL)
    {
        Flight tmp = l_flights->flight;
        Date d_flight = {tmp.month,tmp.day};
        if (strcmp (port_id, l_flights->flight.org_air) == 0 && same_date(d,d_flight) && tmp.schep_dep > hourdep) // On cherche les vols qui partent de port_id à la même date que d
        {
            if (flight_already_in_list (tmp, l_tmp) == 0)
                add_head_flight(&l_tmp, tmp); // fonction déjà codée dans data.c
        }
        l_flights = l_flights->pnext_fli;
    }

    if (l_tmp == NULL) { // Cas où on n'a trouvé aucun vol à afficher
        printf("Aucun vol ne correspond à vos critères de recherche\n");
        return;
    }
    char heuredep[MAX_HOUR];
    char minutedep[MAX_MINUTE];
    convert_int_to_hour(hourdep, heuredep, minutedep);
    printf ("--------------- LISTE DES VOLS PARTANT DE L'AEROPORT %s A LA DATE %d/%d APRES %s:%s (MAX %d PAR DEFAUT A 10)"
            " ---------------\n",port_id,d.month,d.day,heuredep,minutedep,max);
    info_flight(l_tmp, max);
}

//---------- QUATRIEME REQUETE ----------//

int min_tab_flight(Flight tab_flights[MAX_MOST]) { // retourne l'indice du vol ayant le plus petit retard parmi le tableau de flights
    int i_min = 0;
    int min = tab_flights[0].arr_delay;
    for (int i=1; i<MAX_MOST; i++) {
        if (tab_flights[i].arr_delay < min) {
            min = tab_flights[i].arr_delay;
            i_min = i;
        }
    }
    return i_min;
}

void elt_more_tab_flights(Flight flight, Flight tab_flights[MAX_MOST]) { // si le retard du vol flight est supérieur au minimum des retards des vols de tab_flights alors il prend sa place
    int i_min = min_tab_flight(tab_flights);
    if (flight.arr_delay>tab_flights[i_min].arr_delay) {
        tab_flights[i_min] = flight;
    }
}

void init_tab_flights_arr_delay(Flight *pflight) {
	pflight->arr_delay = 0; // On met arr_delay à 0 car on veut trouver des arr_delay très grands
}

void most_delayed_flights (Liste_flights l_flights) {
	Flight* tab_flights = malloc(MAX_MOST*sizeof(struct flight));
    	for (int i=0; i<MAX_MOST; i++) // On initialise les éléments de notre tableau, si on ne fait pas ça le programme bug une fois sur deux
		init_tab_flights_arr_delay(&tab_flights[i]);

    while (l_flights != NULL) { // on parcourt tous les éléments et on récupère les 5 vols qui ont subis les plus longs retards à l'arrivée dans le tableau tab_flights
        Flight tmp = l_flights->flight;
        elt_more_tab_flights(tmp, tab_flights);
        l_flights = l_flights->pnext_fli;
    }
    
    printf("---------------- LES 5 VOLS QUI ONT SUBI LE PLUS DE RETARD A L'ARRIVEE ----------------\n");

    for (int i=0; i<MAX_MOST; i++) {
        Flight tmp = tab_flights[i];
        char weekday[MAX_WEEKDAY];
        convert_int_to_weekday(tmp.day,weekday);
	    char hourdep[MAX_HOUR];
	    char minutedep[MAX_MINUTE];
	    convert_int_to_hour(tmp.schep_dep, hourdep, minutedep);
	    char hourarr[MAX_HOUR];
	    char minutearr[MAX_MINUTE];
	    convert_int_to_hour(tmp.sched_arr, hourarr, minutearr);
	    char diverted[MAX_DIVER];
	    convert_int_to_yes(tmp.diverted, diverted);
	    char cancelled[MAX_DIVER];
	    convert_int_to_yes(tmp.cancelled, cancelled);
        printf("%s %d/%d -- AIRLINE : %s -- DEST : %s -- DEP HOUR %s:%s -- DEP DELAY : %f -- AIRTIME : %f -- DIST : %d -- ARR HOUR %s:%s -- ARR DELAY : %f -- DIVERTED : %s -- CANCELLED : %s\n", weekday, tmp.month, tmp.day, tmp.airline, tmp.dest_air, hourdep, minutedep, tmp.dep_delay, tmp.air_time, tmp.dist, hourarr, minutearr, tmp.arr_delay, diverted, cancelled);
    }
}

// REQUETE 4 //

typedef struct airline_delay {
	Airline airline;
	int mean_delay;
} Airline_delay;

void init_tab_airlines_delay(Airline_delay* pairline_delay) {
	pairline_delay->mean_delay = 0;
}

int mean_delay_airline(Airline airline, Liste_flights) { 
	// Cette fonction renvoie la moyenne des retards à l'arrivée des vols associés à une companie
	// On va considérer qu'arriver en avance contre-balance avec le fait d'arriver en retard donc on va garder les ARR_DELAY négatifs
	int M = 0;
	int i = 0;
	while (l_flights != NULL) {
		Flight tmp = Liste_flights->flight;
		if (airline.iata_code == tmp.airline) {
			M += flight.arr_delay;
			i++;
		}
		l_flights = l_flights->pnext_fli
	}
	return M/i;
}

void most_delayed_airlines(Liste_flights l_flights, Liste_airlines l_airlines) {
	// On initialise notre tableau contenant 5 companies avec leur moyenne de retard
	Airline_delay* tab_airlines_delay = malloc(MAX_MOST*sizeof(struct airline_delay));
	for (int i=0; i<MAX_MOST; i++)
		init_tab_airlines_delay(&tab_airlines_delay[i];

	
	char IATA[MAX_IATA_AIRLINE];
	char airline[MAX_AIRLINE];
	while (l_airlines != NULL) {
		Airline tmp = l_airlines->airline;
		if (mean_delay_airline(tmp, l_flights) > mean) {
			mean = mean_delay_airline(tmp, l_flights);
			strcpy(IATA,tmp.iata_code);
			strcpy(airline,tmp.airline);
		}
		l_airlines = l_airlines->pnext_airl;
	}

	







