CFLAGS = -g
CC=gcc -m64

all:		testreadtree testwritetree encode

testreadtree:	testreadtree.o readTree.o isLittleEndian.o readData.o swapInt.o swapLong.o printTree.o 
	$(CC) -o testreadtree $(CFLAGS) testreadtree.o readTree.o isLittleEndian.o readData.o swapInt.o swapLong.o printTree.o 

testwritetree:	testwritetree.o writeTree.o isLittleEndian.o writeData.o swapInt.o swapLong.o printTree.o makeTree.o  
	$(CC) -o testwritetree $(CFLAGS) testwritetree.o writeTree.o isLittleEndian.o writeData.o swapInt.o swapLong.o printTree.o makeTree.o 

encode:	encode.o writeData.o
	$(CC) -o encode $(CFLAGS) encode.o writeData.o 

clean:
	rm -f *.o testreadtree testwritetree encode
