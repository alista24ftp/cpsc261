CC     = gcc
CFLAGS = -g -Wall
all:	client webclient 

client: client.o tcp.o
	$(CC)  -o $@ $(CFLAGS) $^

webclient: webclient.o tcp.o
	$(CC)  -o $@ $(CFLAGS) $^

clean:
	-rm -f *.o client webclient 
	-rm -rf *.dSYM
