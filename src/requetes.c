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
    
    printf("---------------- LES %d VOLS QUI ONT SUBI LE PLUS DE RETARD A L'ARRIVEE ----------------\n", MAX_MOST);

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

// REQUETE 5 : most-delayed-airlines //

void init_tab_airlines_delay(Airline_delay* pairline_delay) {
	pairline_delay->mean_delay = 0;
}

float mean_delay_airline(Airline airline, Liste_flights l_flights) { 
	// Cette fonction renvoie la moyenne des retards à l'arrivée des vols associés à une companie
	// On va considérer qu'arriver en avance contre-balance avec le fait d'arriver en retard donc on va garder les ARR_DELAY négatifs
	float M = 0;
	float i = 0;
	while (l_flights != NULL) {
		Flight tmp = l_flights->flight;
		if (strcmp(airline.iata_airlines,tmp.airline) == 0) {
			M += tmp.arr_delay;
			i++;
		}
		l_flights = l_flights->pnext_fli;
	}
	if (i==0)
		return 0;
	return M/i;
}

int min_tab_airlines_delay(Airline_delay tab_airlines_delay[MAX_MOST]) { // retourne l'indice de la companie ayant la plus petite moyenne de retard parmi celles du tableau
    int i_min = 0;
    int min = tab_airlines_delay[0].mean_delay;
    for (int i=1; i<MAX_MOST; i++) {
        if (tab_airlines_delay[i].mean_delay < min) {
            min = tab_airlines_delay[i].mean_delay;
            i_min = i;
            
        }
    }
    return i_min;
}

void most_delayed_airlines(Liste_flights l_flights, Liste_airlines l_airlines) {
	// On initialise notre tableau contenant 5 companies avec leur moyenne de retard
	Airline_delay* tab_airlines_delay = malloc(MAX_MOST*sizeof(struct airline_delay));
	for (int i=0; i<MAX_MOST; i++)
		init_tab_airlines_delay(&tab_airlines_delay[i]);
	int i_min;
	while (l_airlines != NULL) {
		Airline tmp = l_airlines->airline;
        	i_min = min_tab_airlines_delay(tab_airlines_delay);
        	float mean = mean_delay_airline(tmp, l_flights);
		if (mean > tab_airlines_delay[i_min].mean_delay) { // Si la moyenne des retards associées à la companie tmp est plus grande que le min des moyennes des retards des companies stockées alors tmp prend sa place
			tab_airlines_delay[i_min].airline = tmp;
			tab_airlines_delay[i_min].mean_delay = mean;
		}
		l_airlines = l_airlines->pnext_airl;
	}

    // On a maintenant notre tableau qui contient les airlines ayant le plus de retard en moyenne à l'arrivée, il suffit de les afficher
    printf("-------- LES %d COMPANIES AYANT LE PLUS DE RETARD EN MOYENNE A L'ARRIVEE --------\n",MAX_MOST);
    for (int i=0; i<MAX_MOST; i++) {
        printf ("IATA CODE : %s ----------------- AIRLINE : %s ----------------- MEAN_DELAY : %f\n", tab_airlines_delay[i].airline.iata_airlines, tab_airlines_delay[i].airline.airline, tab_airlines_delay[i].mean_delay);
    }
}
	
// REQUETE 6 : delayed-airline // On utilisera la fonction mean_delay_airline codé précédemment

void delayed_airline(char iata_airline[IATA_AIRLINE_MAX], Liste_airlines l_airlines, Liste_flights l_flights) {
	// Pour pouvoir utiliser la fonction codée précédemment, il faut trouver la companie associée au code iata que l'utilisateur va rentrer
	Airline airline;
	bool trouve = false; // Ce bouléen permet de prévenir une éventuelle erreur de l'utilisateur et de le prévenir si on ne trouve aucune companie correspondante
	while (l_airlines != NULL && trouve == false) {
		Airline tmp = l_airlines->airline;
		if (strcmp(iata_airline,tmp.iata_airlines) == 0) {
			trouve = true;
			airline = tmp;
		}
		l_airlines = l_airlines->pnext_airl;
	}

	// Si on a trouvé

	if (trouve) {
		printf("------ RETARD MOYEN DE LA COMPANIE %s : %f ------\n",iata_airline,mean_delay_airline(airline, l_flights));
	}

	// Si on a pas trouvé

	else {
		printf("------ AUCUNE COMPANIE NE CORRESPOND A %s DANS LA BASE DE DONNEES ------\n",iata_airline);
	}
}

// REQUETE 7 : most-delayed-airlines-at-airport //

float mean_delay_airline_at_airport(char iata_airport[IATA_AIRPORT_MAX], Airline airline, Liste_flights l_flights) {
	float M = 0;
	float i = 0;
	while (l_flights != NULL) {
		Flight tmp = l_flights->flight;
		if (strcmp(iata_airport,tmp.dest_air) == 0 && strcmp(airline.iata_airlines,tmp.airline) == 0) {
			M += tmp.arr_delay;
			i++;
		}
		l_flights = l_flights->pnext_fli;
	}
	if (i==0)
		return 0;
	return M/i;
}

void most_delayed_airlines_at_airport(char iata_airport[IATA_AIRPORT_MAX], Liste_airlines l_airlines, Liste_flights l_flights) {
	// On initialise notre tableau contenant 3 companies avec leur moyenne de retard à l'arrivée de l'aéroport
	Airline_delay* tab_airlines_delay = malloc(MAX_MOST2*sizeof(struct airline_delay));
	for (int i=0; i<MAX_MOST2; i++)
		init_tab_airlines_delay(&tab_airlines_delay[i]);
	int i_min;
	while (l_airlines != NULL) {
		Airline tmp = l_airlines->airline;
        	i_min = min_tab_airlines_delay(tab_airlines_delay);
        	float mean = mean_delay_airline_at_airport(iata_airport, tmp, l_flights);
		if (mean > tab_airlines_delay[i_min].mean_delay) { // Si la moyenne des retards associées à la companie tmp est plus grande que le min des moyennes des retards des companies stockées alors tmp prend sa place
			tab_airlines_delay[i_min].airline = tmp;
			tab_airlines_delay[i_min].mean_delay = mean;
		}
		l_airlines = l_airlines->pnext_airl;
	}

    // On a maintenant notre tableau qui contient les airlines ayant le plus de retard en moyenne à l'arrivée, il suffit de les afficher

    printf("-------- LES %d COMPANIES AYANT LE PLUS DE RETARD EN MOYENNE A L'ARRIVEE DE L'AEROPORT %s --------\n",MAX_MOST2, iata_airport);
    for (int i=0; i<MAX_MOST2; i++) {
        printf ("IATA CODE : %s ----------------- AIRLINE : %s ----------------- MEAN_DELAY : %f\n", tab_airlines_delay[i].airline.iata_airlines, tab_airlines_delay[i].airline.airline, tab_airlines_delay[i].mean_delay);
    }
}

// REQUETE 8 : changed-flights

int is_changed_flight_at_date(Flight flight, Date d) { // Renvoie 1 si le vol flight a été dévié ou annulé à la date d et 0 sinon
	return ((flight.diverted || flight.cancelled) && flight.month == d.month && flight.day == d.day);
}

void changed_flights(Date date, Liste_flights l_flights) {
	Liste_flights l_changed_flights = NULL;
	int i=0;
	while (l_flights != NULL) {
		Flight tmp = l_flights->flight;
		if (is_changed_flight_at_date(tmp, date)) {
			i++;
			add_head_flight(&l_changed_flights, tmp);
		}
		l_flights = l_flights->pnext_fli;
	}
	printf("-------- LISTE DES VOLS ANNULES OU DEVIES A LA DATE %d/%d --------\n",date.month, date.day);
	info_flight(l_changed_flights, i);
}

// REQUETE 9 :

float mean_airtime(Liste_flights l_flights_airtime) { // Donne la moyenne des airtime des vols dans la liste passée en argument
	float m = 0;
	float i = 0;
	Flight tmp;
	while (l_flights_airtime != NULL) {
		tmp = l_flights_airtime->flight;
		m += tmp.air_time;
		i++;
		l_flights_airtime = l_flights_airtime->pnext_fli;
	}
	if (i==0)
		return 0;
	return m/i;
}

int is_flight_between_airports(char airport1[IATA_AIRPORT_MAX], char airport2[IATA_AIRPORT_MAX], Flight flight) { // Renvoie 1 si le vol flight est entre les aéroports passés en argument
	return ((strcmp(airport1,flight.org_air) == 0 && strcmp(airport2,flight.dest_air) == 0) || (strcmp(airport1, flight.dest_air) == 0 && strcmp(airport2, flight.org_air) == 0)); 
}

void avg_flight_duration(char airport1[IATA_AIRPORT_MAX], char airport2[IATA_AIRPORT_MAX], Liste_flights l_flights) {
	Liste_flights l_flights_airtime = NULL;
	Flight tmp;
	int nb_flights = 0;
	while (l_flights != NULL) {
		tmp = l_flights->flight;
		if (is_flight_between_airports(airport1, airport2, tmp)) {
			add_head_flight(&l_flights_airtime, tmp);
		}
		nb_flights++;
		l_flights = l_flights->pnext_fli;
	}

	float mean = mean_airtime(l_flights_airtime);

	printf("------- TEMPS DE VOL MOYEN ENTRE LES AEROPORTS %s ET %s : %f (%d VOLS) -------\n",airport1, airport2, mean, nb_flights);
}

// REQUETE 10 :


