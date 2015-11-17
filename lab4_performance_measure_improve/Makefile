CFLAGS = -g -O3 -Wall

all:		timeissawtooth timenothing timeread timefread timewrite timefwrite

timenothing:	timenothing.o 
	$(CC) -o timenothing $(CFLAGS) timenothing.o 

timeread:	timeread.o 
	$(CC) -o timeread $(CFLAGS) timeread.o 

timefread:	timefread.o 
	$(CC) -o timefread $(CFLAGS) timefread.o 

timewrite:	timewrite.o 
	$(CC) -o timewrite $(CFLAGS) timewrite.o 

timefwrite:	timefwrite.o 
	$(CC) -o timefwrite $(CFLAGS) timefwrite.o 

timeissawtooth:	timeissawtooth.o issawtooth.o
	$(CC) -o timeissawtooth $(CFLAGS) timeissawtooth.o issawtooth.o

issawtooth.o:	issawtooth.s
	$(CC) -c $(CFLAGS) issawtooth.s

clean:
	rm -f *.o timeissawtooth timenothing timeread timefread timewrite timefwrite

run:	timeissawtooth 
	./timeissawtooth
