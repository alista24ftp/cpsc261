/*
 ============================================================================
 Name        : Testadd.c
 Author      : Norm Hutchinson
 Description : Test the correctness of an external add function
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>

extern long add(long a, long b);

int main(int argc, char **argv)
{
    int fail = 0;
    if (add(1, 2) != 3) {
	printf("add(1, 2) bad: %ld\n", add(1, 2));
	fail ++;
    }
    if (add(2, 1) != 3) {
	printf("add(2, 1) bad: %ld\n", add(2, 1));
	fail ++;
    }
    if (add(-1, 2) != 1) {
	printf("add(-1, 2) bad: %ld\n", add(-1, 2));
	fail ++;
    }
    if (add(2, -1) != 1) {
	printf("add(2, -1) bad: %ld\n", add(2, -1));
	fail ++;
    }
    if (add(-1, -2) != -3) {
	printf("add(-1, -2) bad: %ld\n", add(-1, -2));
	fail ++;
    }
    if (add(-2, -1) != -3) {
	printf("add(-2, -1) bad: %ld\n", add(-2, -1));
	fail ++;
    }
    if (fail == 0)
	printf("add works\n");
    return fail;
}

