#include <stdio.h>

extern void readChar(FILE *f, int swap, char *c);
extern void readString(FILE *f, int swap, char *c);
extern void readInt(FILE *f, int swap, int *c);
extern void readLong(FILE *f, int swap, long *c);
extern void readPtr(FILE *f, int swap, void **c);

extern void writeChar(FILE *f, char c);
extern void writeString(FILE *f, char *c);
extern void writeInt(FILE *f, int c);
extern void writeLong(FILE *f, long c);
extern void writePtr(FILE *f, void *c);

extern long swapLong(long);
extern int swapInt(int);
extern long isLittleEndian(void);
