CC = clang
CFLAGS = -Wall -Wextra -g -O0
EXEC = prg_princ

INCLUDES = -I$(PATHLIBH)

CFILES = $(EXEC).c
OBJS = $(patsubst %.c,%.o,$(CFILES))


all : $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	rm -f *.o core

mrproper: clean
	rm -f $(EXEC)
	
.PHONY : clean
