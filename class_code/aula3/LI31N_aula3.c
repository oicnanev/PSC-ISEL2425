#include <stdio.h>
void array_swap(long a[], int i1, int i2) {
	long tmp = a[i1];
	a[i1] = a[i2];
	a[i2] = tmp;
}

void array_sort(long a[], int a_size) {
	for (int i = 0; i < a_size - 1; i++) {
		int idx_max = 0;
		
		for (int j = 1; j < a_size -i; j++)
			if (a[j] > a[idx_max])
				idx_max = j;
		
		array_swap(a, idx_max, a_size-i-1);
	}
}

void array_print(long a[], int a_size) {
	for (int i = 0; i < a_size - 1; i++)
		printf("%ld, ", a[i]);
	printf("%ld\n", a[a_size-1]);
}

int main() {
	long l1[] = {10, 20, -1, -100, 5, 10};
	int size = sizeof(l1)/sizeof(l1[0]);
	printf("Original: "); array_print(l1, size);
	array_sort(l1, size);
	printf("Resultado: "); array_print(l1, size);
	
	return 0;
}
