#include <stdlib.h>
#include "endian.h"


int main(int argc, char **argv) {
    int magic, iAmLittleEndian, fileIsLittleEndian, swap;
    int index, count;
    FILE *f;
    char tag;
    char c;
    int i;
    long l;
    void *p;
    char s[4096];

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
	
    while (!feof(f)) {
	readChar(f, 0, &tag);
	if (feof(f)) break;
	readInt(f, swap, &count);
	for (index = 0; index < count; ++index) {
	    switch(tag) {
	    case 1:
		readChar(f, swap, &c);
		printf("char: %c\n", c);
		break;
	    case 2:
		readString(f, swap, s);
		printf("string: %s\n", s);
		break;
	    case 3:
		readInt(f, swap, &i);
		printf("int: %d\n", i);
		break;
	    case 4:
		readLong(f, swap, &l);
		printf("long: %ld\n", l);
		break;
	    case 5:
		readPtr(f, swap, &p);
		printf("pointer: %p\n", p);;
		break;
	    default:
		fprintf(stderr, "Bogus tag %d in file\n", tag);
		fclose(f);
		exit(1);
	    }
	}
    }
    fclose(f);
    return 0;
}
