#include <stdio.h>
#include <string.h>

void selection_sort_generic(void * a, int size, int elem_size, int (*cmp)(void *, void*));


void memswap(void * elem1, void * elem2, int elem_size) {
	char tmp[elem_size];
	memcpy(tmp, elem1, elem_size);
	memcpy(elem1, elem2, elem_size);
	memcpy(elem2, tmp, elem_size);
}

void print_array_short(const char *msg, const short *a, int size) {
	printf("%s:\n", msg);
	for (int i = 0; i < size; i++)
		printf("\t[%d] = %d\n", i, a[i]);
}
void print_array_long(const char *msg, const long *a, int size) {
	printf("%s:\n", msg);
	for (int i = 0; i < size; i++)
		printf("\t[%d] = %ld\n", i, a[i]);
}

int cmp_short(void *p1, void *p2) {
	return *(short*)p1 - *(short*)p2;
}
int cmp_long(void *p1, void *p2) {
	return *(long*)p1 - *(long*)p2;
}
	
int main() {
	short a1[] = {-10, 100, -100, 30, 3, 500, -1000};
	int size = sizeof(a1) / sizeof(a1[0]);
	print_array_short("Original", a1, size);
	selection_sort_generic(a1, size, sizeof(short), cmp_short);
	print_array_short("Ordenado", a1, size);
	long a2[] = {-10, 100, -100, 30, 3, 500, -1000};
	size = sizeof(a2) / sizeof(a2[0]);
	print_array_long("Original", a2, size);
	selection_sort_generic(a2, size, sizeof(long), cmp_long);
	print_array_long("Ordenado", a2, size);
	return 0;
	
}
