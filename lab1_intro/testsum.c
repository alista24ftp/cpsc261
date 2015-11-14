/*
 ============================================================================
 Name        : Testsum.c
 Author      : Norm Hutchinson
 Description : Test the correctness of an external sum function
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>

extern long sum(long *p, long c);

long vals[] = { 1, 2, 3, 4, -5 };

int main(int argc, char **argv)
{
    int fail = 0;
    if (sum(vals, 0) != 0) {
	printf("sum(vals, 0) bad: %ld\n", sum(vals, 0));
	fail ++;
    }
    if (sum(vals, 1) != 1) {
	printf("sum(vals, 1) bad: %ld\n", sum(vals, 1));
	fail ++;
    }
    if (sum(vals, 2) != 3) {
	printf("sum(vals, 2) bad: %ld\n", sum(vals, 2));
	fail ++;
    }
    if (sum(vals, 3) != 6) {
	printf("sum(vals, 3) bad: %ld\n", sum(vals, 3));
	fail ++;
    }
    if (sum(vals, 4) != 10) {
	printf("sum(vals, 4) bad: %ld\n", sum(vals, 4));
	fail ++;
    }
    if (sum(vals, 5) != 5) {
	printf("sum(vals, 5) bad: %ld\n", sum(vals, 5));
	fail ++;
    }
    if (fail == 0)
	printf("sum works\n");
    return fail;
}
