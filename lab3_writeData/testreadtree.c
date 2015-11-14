#include <stdlib.h>
#include <stdio.h>
#include "endian.h"
#include "tree.h"




int main(int argc, char **argv) {
	int magic, iAmLittleEndian, fileIsLittleEndian, swap;
	int index, count;
	FILE *f;
	    
	if (argc != 2) {
		fprintf(stderr, "Incorrect number of arguments\n");
		exit(1);
	}
	f = fopen(argv[1], "rb");
	if (f == NULL) {
	 	fprintf(stderr, "Can't open file \"%s\"\n", argv[1]);
		exit(1);
	}

	iAmLittleEndian = isLittleEndian();
	printf("This computer is %s endian\n", iAmLittleEndian ? "little" : "big");
	readInt(f, 0, &magic);
	if (magic == 0x01020304) 
		fileIsLittleEndian = iAmLittleEndian;
	else if (magic == 0x04030201)
		fileIsLittleEndian = !iAmLittleEndian;
	else {
	fprintf(stderr, "Invalid magic tag in file %08x\n", magic);
	fclose(f);
	exit(1);
	}
	printf("The data file is %s endian\n", fileIsLittleEndian ? "little" : "big");
	swap = iAmLittleEndian != fileIsLittleEndian;
	
	while(!feof(f)){
		Tree *tr = readTree(f,swap);
		printTree(tr);
		showTree(tr);
	}   
	fclose(f);
	return 0;
}





