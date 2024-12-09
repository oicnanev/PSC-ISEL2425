#include <stdio.h>

int main() {
	int imax1 = (~0 >> 1);
	int imax2 = (~0U >> 1);
	printf("imax1 = %d [0x%x]\n", imax1, imax1);
	printf("imax2 = %d [0x%x]\n", imax2, imax2);
	int imin = ~imax2;
	printf("imin = %d [0x%x]\n", imin, imin);
	return 0;
}
