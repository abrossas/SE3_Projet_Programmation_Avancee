#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../includes/requetes.h"

int main ()
{

    FILE *        f_flights = NULL;
    Liste_flights l_flights = NULL;

    FILE *         f_airports = NULL;
    Liste_airports l_airports = NULL;

    FILE *         f_airlines = NULL;
    Liste_airlines l_airlines = NULL;

    printf ("%d\n", load_flights (f_flights, &l_flights));
    printf ("%d\n", load_airports (f_airports, &l_airports));
    printf ("%d\n", load_airlines (f_airlines, &l_airlines));

    printf ("1ere requête :\n");
    show_airports ("UA", l_airports, l_flights);

    printf ("2e requete :\n");
    show_airlines ("LAX", l_airlines, l_flights);

    free_lflights (&l_flights);
    free_lairports (&l_airports); // erreur ici jcp pk tom a toi de jouer lol
    free_lairlines (&l_airlines);
    return 0;
}
