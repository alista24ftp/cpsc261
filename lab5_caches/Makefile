CFLAGS = -g

all:		timegraph generate simulate

timegraph.o:	graph.h timegraph.c
	$(CC) -c $(CFLAGS) -O3 timegraph.c
graph.o:	graph.h graph.c
	$(CC) -c $(CFLAGS) -O3 graph.c

timegraph:	timegraph.o graph.o
	$(CC) -o timegraph $(CFLAGS) timegraph.o graph.o

generate:	generate.o
	$(CC) -o generate $(CFLAGS) generate.o 

simulate:	simulate.o
	$(CC) -o simulate $(CFLAGS) simulate.o 

clean:
	rm -f *.o timegraph generate simulate

run:	timegraph 
	./timegraph
