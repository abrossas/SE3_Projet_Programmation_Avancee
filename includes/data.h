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

typedef struct flights
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
} Flights;

typedef struct airports
{
    char  iata_airports[IATA_AIRPORT_MAX];
    char  airport[IATA_AIRPORT_MAX];
    char  city[CITY_MAX];
    char  state[STATE_MAX];
    char  country[COUNTRY_MAX];
    float latitude;
    float longitude;
} Airports;

typedef struct airlines
{
    char iata_airlines[IATA_AIRLINE_MAX];
    char airline[AIRLINE_MAX];
} Airlines;

struct cell_flights
{
    Flights  flight;
    Flights *pnext;
};

typedef struct cell_flights *Liste_flights; // On utilisera une liste chaînée simple pour stocker les vols pour pouvoir facilement en ajouter de nouveaux

struct cell_airports
{
    Airports  airport;
    Airports *pnext;
};

typedef struct cell_airports *Liste_airports; // Même raison que pour les vols

struct cell_airlines
{
    Airlines  airline;
    Airlines *pnext;
};

typedef struct cell_airlines *Liste_airlines; // Idem


void load_flights (FILE *, Liste_flights);

void load_airports (FILE *, Liste_airports);

void load_airlines (FILE *, Liste_airlines);
