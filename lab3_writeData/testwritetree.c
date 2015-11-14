#include <stdlib.h>
#include <stdio.h>
#include "endian.h"
#include "tree.h"

int main(int argc, char **argv){
	int iAmLittleEndian, swap;
	int index, count;
	FILE *f;
	    
	if (argc < 3 || argc > 4) {
		fprintf(stderr, "Incorrect number of arguments\n");
		exit(1);
	}
	
	f = fopen(argv[1], "wb");
	if (f == NULL) {
	 	fprintf(stderr, "Can't open file \"%s\"\n", argv[1]);
		exit(1);
	}
	
	// This computer's endianness
	iAmLittleEndian = isLittleEndian();
	printf("This computer is %s endian\n", iAmLittleEndian ? "little" : "big");
	
	// mark endianness of file
	writeInt(f, 0x01020304);
		
	// make a tree
	Tree *t = makeTree(argc - 2, &argv[2]);
	
	// print out the tree
	showTree(t);
	
	// write the tree to specified file
	writeTree(f, t);
	
	fclose(f);
	return 0;
}