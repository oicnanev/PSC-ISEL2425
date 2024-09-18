#include <stdio.h>

// Functions declaration ---------------------------------------------------
void array_sort( unsigned short *a, int size );
void array_swap( unsigned short *i1, unsigned short *i2 );
void array_print( unsigned short *a, int size );

void array_swap( unsigned short *i1, unsigned short *i2) {
	unsigned short tmp = *i1;
	*i1 = *i2;
	*i2 = tmp;
}

void array_print( unsigned short *a, int size ) {
	for( int i = 0; i < size - 1; i++ )
		printf( "%d, ", *(a + i) );
	printf("%d\n", *(a + size - 1));
}

void array_sort( unsigned short *a, int size ) {
	for( int i = 0; i < size - 1; i++ ) {
		int idx_max = i;
		for (int j = i + 1; j < size; j++) {
			if (*(a + j) < *(a + idx_max)) {
				idx_max = j;
			}
		}
		array_swap(a + i, a + idx_max);
	}
}

int main() {
	unsigned short arr[] = {100, 23, 67, 2, 40, 55}; 
	unsigned short *a = arr; 
	int size = sizeof(arr) / sizeof(arr[0]);

	printf("Original: ");
	array_print(a, size);
	array_sort(a, size);
	printf("Sorted: ");
	array_print(a, size);

	return 0;
}