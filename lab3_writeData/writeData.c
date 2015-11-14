#include <stdio.h>
#include "endian.h"

#include "tree.h"

void writeChar(FILE *f, char c){
	fwrite(&c, 1, 1, f);
}

void writeString(FILE *f, char *c){
	int i=0;
	char str = *c;
	while(str!='\0'){
		fwrite(&str, 1, 1, f);
		i++;
		str = *(c+i);
	}	
	fwrite(&str, 1, 1,f);
}

void writeInt(FILE *f, int c){
	fwrite(&c, 4, 1, f);
}

void writeLong(FILE *f, long c){
	fwrite(&c, 8, 1, f);
}

void writePtr(FILE *f, void *c){
	fwrite(&c, 8, 1, f);
}
