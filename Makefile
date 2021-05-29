CC = gcc
CFLAGS = -W -Wall -Wextra -g -O0

bin/exec : lib/main.o lib/data.o lib/requetes.o lib/interface.o
	$(CC) lib/main.o lib/data.o lib/requetes.o lib/interface.o -o bin/exec

lib/main.o : src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o lib/main.o

lib/data.o : src/data.c
	$(CC) $(CFLAGS) -c src/data.c -o lib/data.o

lib/requetes.o : src/requetes.c
	$(CC) $(CFLAGS) -c src/requetes.c -o lib/requetes.o

lib/interface.o : src/interface.c
	$(CC) $(CFLAGES) -c src/interface.c -o lib/interface.o

clean:
	rm -f *.o core

mrproper: clean
	rm -f 
	
.PHONY : clean
