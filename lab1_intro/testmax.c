/*
 ============================================================================
 Name        : Testmax.c
 Author      : Norm Hutchinson
 Description : Test the correctness of an external max function
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>

extern long max(long a, long b);

int main(int argc, char **argv)
{
    int fail = 0;
    if (max(1, 2) != 2) {
	printf("max(1, 2) bad: %ld\n", max(1, 2));
	fail ++;
    }
    if (max(2, 1) != 2) {
	printf("max(2, 1) bad: %ld\n", max(2, 1));
	fail ++;
    }
    if (max(-1, 2) != 2) {
	printf("max(-1, 2) bad: %ld\n", max(-1, 2));
	fail ++;
    }
    if (max(2, -1) != 2) {
	printf("max(2, -1) bad: %ld\n", max(2, -1));
	fail ++;
    }
    if (max(-1, -2) != -1) {
	printf("max(-1, -2) bad: %ld\n", max(-1, -2));
	fail ++;
    }
    if (max(-2, -1) != -1) {
	printf("max(-2, -1) bad: %ld\n", max(-2, -1));
	fail ++;
    }
    if (fail == 0)
	printf("max works\n");
    return fail;
}
