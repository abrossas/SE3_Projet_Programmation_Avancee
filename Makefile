CC = gcc
CFLAGS = -W -Wall -Wextra -g -O0

bin/exec : lib/main.o lib/data.o lib/requetes.o
	$(CC) lib/main.o lib/data.o lib/requetes.o -o bin/exec

lib/main.o : src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o lib/main.o

lib/data.o : src/data.c
	$(CC) $(CFLAGS) -c src/data.c -o lib/data.o

lib/requetes.o : src/requetes.c
	$(CC) $(CFLAGS) -c src/requetes.c -o lib/requetes.o

clean:
	rm -f *.o core

mrproper: clean
	rm -f 
	
.PHONY : clean
