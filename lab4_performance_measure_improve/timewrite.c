/*
 ============================================================================
 Name        : timewrite.c
 Author      : Yours truly, alista24ftp
 Description : Time the write() function
 ============================================================================
 */

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static struct timeval start_ts, end_ts, diff_ts;

void startClock() {
    gettimeofday(&start_ts, 0);
}

void endClock() {
    gettimeofday(&end_ts, 0);
}

struct timeval timeminus(struct timeval a, struct timeval b)
{
    struct timeval res;
    res.tv_sec = a.tv_sec - b.tv_sec;
    if (a.tv_usec > b.tv_usec) {
	res.tv_usec = a.tv_usec - b.tv_usec;
    } else {
	res.tv_usec = 1000000 + a.tv_usec - b.tv_usec;
	res.tv_sec--;
    }
    return res;
}

long usecClock() {
    diff_ts = timeminus(end_ts, start_ts);
    return diff_ts.tv_usec + 1000000 * diff_ts.tv_sec;
}

int main(int argc, char **argv)
{
    long l, limit = 8 * 1024 * 1024, size = 1;
    
    int null = open("/dev/null", O_WRONLY);
    
    if (argc > 2)
	limit = strtol(argv[2], 0, 0);
    if (argc > 1)
	size = strtol(argv[1], 0, 0);
    char *buffer = (char *)malloc(size * sizeof(char));
    printf("Timing write()\n");
    volatile long x = 0;
    startClock();
    for (l = 0; l < limit; l += size) {
		write(null,buffer,size);	
		x += size;
    }
    endClock();
    if (x != (limit / size) * size)
	printf("Got the wrong answer\n");

    printf("%ld invocations of write(%ld) took: %ld usec\n", (limit / size), size, usecClock());
    
    close(null);
	free(buffer);
    return 0;
}
	    
