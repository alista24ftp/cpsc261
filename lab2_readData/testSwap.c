#include "endian.h"

extern long swapLong(long);

int main(int argc, char **argv) {
    int faillong = 0, failint = 0;
    
    if (swapLong(0x0102030405060708L) != 0x0807060504030201L) {
	printf("swapLong failed on 0x0102030405060708L\n");
	faillong++;
    }
    if (swapLong(0x0L) != 0x0L) {
	printf("swapLong failed on 0x0L\n");
	faillong++;
    }
    if (faillong == 0)
	printf("swapLong works\n");

    if (swapInt(0x01020304) != 0x04030201) {
	printf("swapInt failed on 0x01020304\n");
	failint++;
    }
    if (swapInt(0x0) != 0x0) {
	printf("swapInt failed on 0x0\n");
	failint++;
    }
    if (failint == 0)
	printf("swapInt works\n");

    return faillong + failint;
}
