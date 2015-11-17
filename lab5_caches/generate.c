#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define HOWMANY 64000 // 64
#define MAXADDR ((1 << 8) - 1) //((1 << 8) - 1)
#define LOG2NSAMPLES 3
#define HOT 640000// 
#define HOTPERCENTAGE 0.75
#define HOTFRACTION   0.25

long sample() {
    int i;
    long s = 0;
#ifdef HOT
    s = random() % (1L << 30);
    // printf("%ld\n", s);
    if ((double)s / (1L << 30) < HOTPERCENTAGE) {
	s = random() % (int)(HOTFRACTION * (MAXADDR + 1));
	// printf("Hot: %lx\n", s);
    } else {
	s = (int)(HOTFRACTION * (MAXADDR + 1)) + random() % (int)((1.0 - HOTFRACTION) * (MAXADDR + 1));
	// printf("Cold: %lx\n", s);
    }
#endif
#ifdef NORMAL
    for (i = 0; i < (1 << LOG2NSAMPLES); ++i) {
	s += random() % ((MAXADDR + 1) >> LOG2NSAMPLES);
    }
#endif
#ifdef UNIFORM
    s = random() % (MAXADDR + 1);
#endif
    return s;
}

int main(int argc, char **argv) {
    int i;
    srandom(time(0));
    for (i = 0; i < HOWMANY; ++i) {
	printf("%#lx\n", sample());
    }
}
