CC = gcc
CFLAGS = -Wall -g

all:	phil phil-ordered phil-random 

phil:	phil.c
	$(CC) $(CFLAGS) -o phil phil.c -pthread

phil-ordered:	phil-ordered.c
	$(CC) $(CFLAGS) -o phil-ordered phil-ordered.c -pthread

phil-random:	phil-random.c
	$(CC) $(CFLAGS) -o phil-random phil-random.c -pthread

clean:
	rm -f phil phil-ordered phil-random *.o *~
	rm -rf *.dSYM
