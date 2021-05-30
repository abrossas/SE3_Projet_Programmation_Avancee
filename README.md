# Projet SE3 2021

## By Tom Carrere & Antoine Brossas


## Description 
  
Notre programme permet la recherche dans des bases de données de taille conséquente en ".csv" sur les vols d'une année, les aéroports et les compagnies aériennes américaines, à l'aide d'une interface utilisateur et de 10 requetes proposées ici:

1) **show-airports** <airline_id> : affiche tous les aéroports depuis lesquels la compagnie aérienne <airline_id> opère des vols

2) **show-airlines** <port_id> : affiche les compagnies aériens qui ont des vols qui partent de l'aéroport <port_id>

3) **show-flights** <port_id> *date* [time] [limit=xx] : affiche les vols qui partent de l'aéroport <port_id> à la date *date*, avec optionnellement une heure de début, et limité à xx vols (les arguments optionnels ne fonctionnent pas)

4) **most-delayed-flights** : donne les 5 vols qui ont subis les plus longs retards à l'arrivée

5) **most-delayed-airlines** : donne les 5 compagnies aériennes qui ont, en moyenne, le plus de retards

6) **delayed-airline** <airline_id> : donne le retard moyen de la compagnie aérienne <airline_id>

7) **most-delayed-airlines-at-airport** <airport_id> : donne les 3 compagnies aériennes avec le plus de retard d'arrivée à l'aéroport <airport_id> passé en paramètre

8) **changed-flights** *date* : les vols annulés ou déviés à la date *date* (format M-D)

9) **avg-flight-duration** <port_id> <port_id> : calcule le temps de vol moyen entre les aéroports <port_id> passés en paramètre

10) **find-itinerary** <port_org> <port_dest> *date* : trouve un itinéraire direct entre l'aéroport de départ <port_org> et d'arrivée <port_dest> à la date *date*

 ## Contenu

Notre répertoire GIT est composé d'un **bin** contenant l'exécutable, d'un fichier **data** dans lequel sont stockés les **fichiers csv** qui vont nous servir de base de données sur lesquels effectuer les requêtes, d'un fichier **include** composé de de **data.h**, **requetes.h** et **interface.h** qui contiennent respectivement les différentes structure de données utilisés et les prototypes de fonctions associées au chargement des données, les prototypes des différentes fonctions utilisées pour les requetes et les fonctions liées à l'interface pour l'utilisateur. Nous disposons également d'un fichier **lib** dans lequel figure nos ".o" tels que **data.o**, **main.o** et **requetes.o**, et pour finir un fichier source **src** dans lequel se trouve nos ".c" contenant les fonctions de nos requetes, notre main et nos differentes sous-fonctions respectivement dans **requetes.c**, **main.c**, **data.c** et **interface.c**.

 ## Compilation

Pour ce qui est de la compilation, nous avons respecté les conventions de codage avec .**clang-format**, et nous avons également fait une compilation automatique avec un **Makefile** avec diverses options de compilation (-Wall, -Wextra, -g et -0x). Pour compiler, il suffira uniquement d'utiliser la commande **make** dans la racine.

 ## Utilisation

Pour que l'utilisateur puisse utiliser le code il faudra qu'il le compile de la manière vue précedemment puis il faudra se rendre dans **bin** et lancer l'exécutable à l'aide de la commande **./exec** ou **./exec < ../data/requetes.txt** (pour charger les requêtes depuis requetes.txt) qui lancera l'interface utilisateur en lisant les instructions comprises dans **requetes.txt**. Pour quitter cette interface, il suffira d'utiliser la commande **quit** (qui est à la fin de requetes.txt pour quitter l'interface automatiquement si on utilise cette méthode).
La commande **help** permet d'afficher les informations à propos des différentes requêtes disponibles.

## Remarques

Bug à résoudre pour l'instant pour la requête **most-delayed-airlines-at-airport**, il faut l'utiliser en dernier et ne pas faire d'autres requêtes par la suite sinon il y a un SegFault (probablement dû à l'utilisation de la fonction **strtok**).

De même une erreur de l'utilisateur peut aussi provoquer un SegFault.

De plus, les arguments optionnels ne fonctionnent pas pour la requête **show-flights** <port_id> <date> [time] [limit=xx], l'utilisateur peut les renseigner mais ils ne seront malheureusement pas pris en compte.




