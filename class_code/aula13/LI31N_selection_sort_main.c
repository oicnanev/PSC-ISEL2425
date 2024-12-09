#include <stdio.h>
#include <string.h>

int a1[] = {-1000, 10, 20, 30};
int a1_res[] = {-1000, 10, 20, 35};
int a2[] = {500, 100, -1, -1000, 10, 20, 5, 30};
int a2_res[] = {-1000, -1, 5, 10, 20, 30, 100, 500};


struct {
	int *a;
	int a_size;
	int *result;
} vtest[] = {
	{.a=a1, .a_size=sizeof(a1) / sizeof(a1[0]), .result=a1_res},
	{.a=a2, .a_size=sizeof(a2) / sizeof(a2[0]), .result=a2_res},
};

void selection_sort(int a[], int);

void swap(int * l, int * r) {
	int tmp = *l;
	*l = *r;
	*r = tmp;
}

void print_array(const char *msg, int a[], int size) {
	printf("%s:\n", msg);
	for (int i = 0; i < size; i++) 
		printf("\t[%d] = %d\n", i, a[i]);
}

void validate(int vect_idx) {
	int r = memcmp(
		vtest[vect_idx].a, 
		vtest[vect_idx].result, 
		vtest[vect_idx].a_size * sizeof(int));
	const char * m = r != 0 ? "Erro" : "OK";
	printf("[%d] - %s\n", vect_idx, m);
}
int main() {
	for (int i = 0; i < sizeof(vtest) / sizeof(vtest[0]); i++) {
		print_array("Original", vtest[i].a, vtest[i].a_size);
		selection_sort(vtest[i].a, vtest[i].a_size);
		print_array("Ordenado", vtest[i].a, vtest[i].a_size);
		validate(i);
	}
	
	return 0;
}
