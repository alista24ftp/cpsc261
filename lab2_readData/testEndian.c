#include "endian.h"

int main(int argc, char **argv) {
    printf("This computer is %s endian\n",
	   isLittleEndian() ? "little" : "big");
    return 0;
}
