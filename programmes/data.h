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

typedef struct flights {
	unsigned short month;
	unsigned short day;
	unsigned short weekday;
	char airline[IATA_AIRLINE_MAX];
	char org_air[IATA_AIRPORT_MAX];
	char dest_air[IATA_AIRPORT_MAX];
	unsigned short schep_dep;
	float dep_delay;
	float air_time;
	unsigned short dist;
	unsigned short sched_arr;
	float arr_delay;
	bool diverted;
	bool cancelled;
} Flights;

typedef struct airports {
	char iata_airports[IATA_AIRPORT_MAX];
	char airport[IATA_AIRPORT_MAX];
	char city[CITY_MAX];
	char state[STATE_MAX];
	char country[COUNTRY_MAX];
	float latitude;
	float longitude;
} Airports;

typedef struct airlines {
	char iata_airlines[IATA_AIRLINE_MAX];
	char airline[AIRLINE_MAX];
} Airlines;


typedef struct liste_flights { // Comme on a un nombre fixe de vols à analyser, il est préférable d'utiliser une structure simple de tableau pour privilégier une rapidité d'exécution la plus performante possible. Si on voulait ajouter des vols pour mettre à jour le programme, ce serait plus complexe et il faudrait alors utiliser une liste chainée et le coût mémoire serait fortement augmenté par ailleurs (allocation des pointeurs).
	Flights liste_flights[NB_FLIGHTS];
} Liste_flights;

typedef struct liste_airports { // Vu le nombre faible d'aéroports (323) dans la dataset, on utilisera un tableau toujours par soucis de rapidité d'exécution
	Airports liste_airports[NB_AIRPORTS];
} Liste_airports;

typedef struct liste_airlines { // Pareil que pour Liste_airports (15 companies aériennes)
	Airlines liste_airlines[NB_AIRLINES];
} Liste_airlines;

void load_flights(FILE*, struct Liste_flights);

void load_airports(FILE*, struct Liste_airports);

void load_airlines(FILE*, struct Liste_airlines);
