# Projet SE3 2021

## By Tom Carrere & Antoine Brossas


## Description 
  
Notre programme permet la recherche dans des bases de données de taille conséquente en ".csv" sur les vols, les aéroports et les compagnies aériennes américaines, à l'aide d'une interface utilisateur et de 11 requetes proposés ici:

1)**show-airports <airline_id>**: affiche tous les aéroports depuis lesquels la compagnie aérienne <airline_id> opère des volsshow-airlines <port_id>: affiche les compagnies aériens qui ont des vols qui partent de l'aéroport <port_id>

2)**show-airlines <port_id>**: affiche les compagnies aériens qui ont des vols qui partent de l'aéroport <port_id>

3)**show-flights <port_id> <date> [<time>] [limit=<xx>]**: affiche les vols qui partent de l'aéroport à la date, avec optionnellement une heure de début, et limité à xx vols

4)**most-delayed-flights** : donne les 5 vols qui ont subis les plus longs retards à l'arrivée

5)**most-delayed-airlines**: donne les 5 compagnies aériennes qui ont, en moyenne, le plus de retards

6)**delayed-airline <airline_id>**: donne le retard moyen de la compagnie aérienne passée en paramètre

7)**most-delayed-airlines-at-airport <airport_id>**: donne les 3 compagnies aériennes avec le plus de retard d'arrivé à l'aéroport passée en paramètre

8)**changed-flights <date>**: les vols annulés ou déviés à la date  (format M-D)

9)**avg-flight-duration <port_id> <port_id>**: calcule le temps de vol moyen entre deux aéroports

10)**find-itinerary <port_id> <port_id> <date> [<time>] [limit=<xx>]**: trouve un ou plusieurs itinéraires entre deux aéroports à une date donnée (l'heure est optionnel, requête peut être limité à xx propositions, il peut y avoir des escales)

11)**find-multicity-itinerary <port_id_depart> <port_id_dest1> <date> [<time>] <port_id_dest2> <date> [<time>] ... <port_id_destN> <date> [<time>]**: trouve un itinéraire multiville qui permet de visiter plusieurs villes (il peut y avoir des escales pour chaque vol intermediaire).


 ## Contenu

Notre fichier est composé d'un **bin** contenant l'exécutable, d'un fichier **data** dans lequel sont stockés les **fichiers csv** qui vont nous servir de base de donnée, d'un fichier **include** composé de de **data.h** et **requetes.h** qui contiennent respectivement les différentes structure de données utilisés et les structures des fonctions utilisées pour les requetes. Nous disposons également d'un fichier **lib** dans lequel figure nos ".o" tels que **data.o**, **main.o** et **requetes.o**, et pour finir un fichier source **src** dans lequel se trouve nos ".c" contenant nos requetes, notre main et nos differentes sous-fonctions respectivement dans **requetes.c**, **main.c** et **data.c**.


 ## Compilation

Pour ce qui est de la compilation, nous avons respecté les conventions de codage avec .**clang-format**, et nous avons également fait une compilation automatique avec un **Makefile**. Pour compiler, il suffira uniquement d'utiliser la commande **make** dans la racine.


 ## Utilisation

Pour que l'utilisateur puisse utiliser le code il faudra qu'il le compile de la manière vue précedemment puis il faudra se rendre dans **bin** et lancer l'exécutable à l'aide de la commande **./exec** ou **./exec < ../data/requetes.txt** (pour charger les requêtes depuis requetes.txt) qui lancera l'interface utilisateur en lisant les instructions comprises dans **requetes.txt**. Pour quitter cette interface, il suffira d'utiliser la commande **quit** (qui est à la fin de requetes.txt pour quitter l'interface automatiquement si on utilise cette méthode).






