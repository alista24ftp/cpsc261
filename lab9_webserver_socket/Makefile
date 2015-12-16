CC     = gcc
CFLAGS = -g -Wall
all:	webserver 

webserver: webserver.o tcp.o header.o calculate.o webserver_init.o
	$(CC)  -o $@ $(CFLAGS) $^

clean:
	-rm -f *.o webserver
	-rm -rf *.dSYM
