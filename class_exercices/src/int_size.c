#include <stdio.h>
/* Prints to stdout:
 *  - the max value of an unsigned int
 *  - the min value of a signed int */

int main() {
	int byte = 8;  // bits in a byte
	unsigned int max_unsigned = ~0;  // Every bit is 1
	int min_signed = 1 << (sizeof(int) * byte - 1);  // Most significant bit is 1, others are 0

	printf("Max value of an unsigned int: %u\n", max_unsigned);
	printf("Min value of a signed int: %d\n", min_signed);

    // código da aula
    int imax = ~(~0U >> 1);
    int imin = (~0U >> 1);
    
    printf("Min negative int = %d [0x%x]\n", imax, imax);
    printf("Max signed int = %d [0x%x]\n", imin, imin);

	return 0;
}
