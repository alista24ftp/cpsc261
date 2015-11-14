CFLAGS = -g
CC=gcc -m64

all:		testEndian testSwap decode 

testEndian:	testEndian.o isLittleEndian.o
	$(CC) -o testEndian $(CFLAGS) testEndian.o isLittleEndian.o

testSwap:	testSwap.o swapLong.o swapInt.o
	$(CC) -o testSwap $(CFLAGS) testSwap.o swapLong.o swapInt.o

decode:	decode.o readData.o isLittleEndian.o swapInt.o swapLong.o
	$(CC) -o decode $(CFLAGS) decode.o readData.o isLittleEndian.o swapInt.o swapLong.o

clean:
	rm -f *.o testEndian testSwap decode 

run:	testEndian testSwap decode 
	./testEndian
	./testSwap
	./decode little.dat
	./decode big.dat
	./decode complex.dat

.s.o:;	gcc $(CFLAGS) -c -o $*.o $*.s
