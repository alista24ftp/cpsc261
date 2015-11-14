/*
  ============================================================================
  Name        : testfib.c
  Author      : Norm Hutchinson
  Description : Test the correctness of an external fib routine
  ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>

extern long fib(long a);

int main(int argc, char **argv)
{
    int fail = 0;
    if (fib(1) != 1) {
	printf("fib(1) bad: %d\n", fib(1));
	fail ++;
    }
    if (fib(2) != 1) {
	printf("fib(2) bad: %d\n", fib(2));
	fail ++;
    }
    if (fib(5) != 5) {
	printf("fib(5) bad: %d\n", fib(5));
	fail ++;
    }
    if (fib(18) != 2584) {
	printf("fib(18) bad: %d\n", fib(18));
	fail ++;
    }
    if (fail == 0)
	printf("fib works\n");
    return fail;
}

