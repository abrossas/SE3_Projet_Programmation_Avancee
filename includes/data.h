#define IATA_AIRLINE_MAX 2
#define IATA_AIRPORT_MAX 3

#define AIRPORT_MAX 100
#define CITY_MAX 50
#define AIRLINE_MAX 30

#define STATE_MAX 2
#define COUNTRY_MAX 3

#define NB_FLIGHTS 58592
#define NB_AIRPORTS 323
#define NB_AIRLINES 15

#define MAX_BUFFER 1024 // taille maximale du buffer qui stockera une ligne du fichier CSV

typedef struct flight
{
    unsigned short month;
    unsigned short day;
    unsigned short weekday;
    char           airline[IATA_AIRLINE_MAX];
    char           org_air[IATA_AIRPORT_MAX];
    char           dest_air[IATA_AIRPORT_MAX];
    unsigned short schep_dep;
    float          dep_delay;
    float          air_time;
    unsigned short dist;
    unsigned short sched_arr;
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
    Flight *pnext_fli;
};

typedef struct cell_flight *Liste_flights; // On utilisera une liste chaînée simple pour stocker les vols pour pouvoir facilement en ajouter de nouveaux

struct cell_airport
{
    Airport  airport;
    Airport *pnext_airp;
};

typedef struct cell_airport *Liste_airports; // Même raison que pour les vols

struct cell_airline
{
    Airline airline;
    Airline *pnext_airl;
};

typedef struct cell_airline *Liste_airlines; // Idem

// FONCTIONS :

void add_head_flight(Liste_flights *, Flight);

void read_flight(struct cell_flight *, Flight);

void add_head_airport(Liste_airports *, Airport);

void read_airport(struct cell_airport *, Airport);

void add_head_airline(Liste_airlines *, Airline);

void read_airline(struct cell_airline *, Airline);

void load_buf_strtok(char *);

void load_flights (FILE *, Liste_flights);

void load_airports (FILE *, Liste_airports);

void load_airlines (FILE *, Liste_airlines);
