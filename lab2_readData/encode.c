#include <stdlib.h>
#include "endian.h"

int main(int argc, char **argv) {
    int magic;
    FILE *f;
    char tag;
    char c;
    int i;
    long l;
    void *p;
    char *s;

    if (argc != 2) {
	fprintf(stderr, "Incorrect number of arguments\n");
	exit(1);
    }
    f = fopen(argv[1], "wb");
    if (f == NULL) {
 	fprintf(stderr, "Can't open file \"%s\"\n", argv[1]);
	exit(1);
    }

    writeInt(f, 0x01020304);
    writeChar(f, 2);
    writeInt(f, 0);
    writeChar(f, 2);
    writeInt(f, 1);
    writeString(f, "abcdefghijklmnopqrstuvwxyz");
    writeChar(f, 3);
    writeInt(f, 4);
    writeInt(f, 2);
    writeInt(f, 4);
    writeInt(f, 6);
    writeInt(f, 8);
    writeChar(f, 4);
    writeInt(f, 2);
    writeLong(f, 4);
    writeLong(f, -4);
    writeChar(f, 5);
    writeInt(f, 3);
    writePtr(f, (void *)0xfffe0024540);
    writePtr(f, (void *)0);
    writePtr(f, (void *)0x0fffffffffffff00);
    writeChar(f, 2);
    writeInt(f, 1);
    writeString(f, "zyxwvutsrqponmlkjihgfedcba");
    fclose(f);
    return 0;
}
