#define IATA_AIRLINE_MAX 4
#define IATA_AIRPORT_MAX 5

#define AIRPORT_MAX 102
#define CITY_MAX 52
#define AIRLINE_MAX 32

#define STATE_MAX 4
#define COUNTRY_MAX 5

#define NB_FLIGHTS 58592
#define NB_AIRPORTS 323
#define NB_AIRLINES 15

#define MAX_BUFFER 60 // taille maximale du buffer qui stockera une ligne du fichier CSV

typedef struct flight
{
    int month;
    int day;
    int weekday;
    char           airline[IATA_AIRLINE_MAX];
    char           org_air[IATA_AIRPORT_MAX];
    char           dest_air[IATA_AIRPORT_MAX];
    int schep_dep;
    float          dep_delay;
    float          air_time;
    int dist;
    int sched_arr;
    float          arr_delay;
    bool           diverted;
    bool           cancelled;
} Flight;

typedef struct airport
{
    char  iata_airports[IATA_AIRPORT_MAX];
    char  airport[IATA_AIRPORT_MAX];
    char  city[CITY_MAX];
    char  state[STATE_MAX];
    char  country[COUNTRY_MAX];
    float latitude;
    float longitude;
} Airport;

typedef struct airline
{
    char iata_airlines[IATA_AIRLINE_MAX];
    char airline[AIRLINE_MAX];
} Airline;

struct cell_flight
{
    Flight  flight;
    struct cell_flight *pnext_fli;
};

typedef struct cell_flight *Liste_flights; // On utilisera une liste chaînée simple pour stocker les vols pour pouvoir facilement en ajouter de nouveaux

struct cell_airport
{
    Airport  airport;
    struct cell_airport *pnext_airp;
};

typedef struct cell_airport *Liste_airports; // Même raison que pour les vols

struct cell_airline
{
    Airline airline;
    struct cell_airline *pnext_airl;
};

typedef struct cell_airline *Liste_airlines; // Idem

// FONCTIONS :

void add_head_flight(Liste_flights *, Flight);

void read_flight(Flight*, char*);

void free_lflights(Liste_flights*);

void add_head_airport(Liste_airports *, Airport);

void read_airport(struct cell_airport *, char*);

void free_lairports(Liste_airports *);

void add_head_airline(Liste_airlines *, Airline);

void read_airline(struct cell_airline *, char*);

void free_lairlines(Liste_airlines*);

void load_buf_strtok(char **);

void load_flights(FILE *, Liste_flights*);

void load_airports(FILE *, Liste_airports*);

void load_airlines(FILE *, Liste_airlines*);
