#include <stdio.h>

void aprint(int a[], int size) {
	for (int i = 0; i < size-1; i++)
		printf("a[%d]=%d, ", i, a[i]);
	if (size > 0)
		printf("a[%d]=%d\n", size-1, a[size-1]);
}

int asum(int a[], int size) {
    int r = 0;
    for (int i = 0; i < size; i++)
        r += a[i];
    return r;
}