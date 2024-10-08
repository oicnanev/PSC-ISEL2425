/*
 *	Programação em Sistemas Computacionais
 *	Semestre de inverno de 2024/2025
 *	Série de exercícios
 *
 *	Programa de teste do 1º exercício
 *
 *	Utilização:
 *
 *	$ gcc int_to_string_test.c int_to_string.c -o int_to_string_test -g -Wall
 *
 *	$ ./int_to_string_test
 */

#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

size_t int_to_string(int value, int base, char buffer[], size_t buffer_size);

struct {
	char buffer[20];
	size_t buffer_size;
	unsigned value;
	int base;
	size_t result_size;
	char *result_string;
} test_array[] = {
	{.value = 10,  .base = 10, .buffer_size = 3, .result_size = 2, .result_string = "10"},
	{.value = 4567,.base = 10, .buffer_size = 5, .result_size = 4, .result_string = "4567"},
	{.value = 0,   .base = 10, .buffer_size = 2, .result_size = 1, .result_string = "0"},
	{.value = 10,  .base = 10, .buffer_size = 2, .result_size = 0 },
	{.value = 0,   .base = 10, .buffer_size = 0, .result_size = 0 },
	{.value = 0,   .base = 0,  .buffer_size = 0, .result_size = 0 },
	{.value = 10,  .base = 2,  .buffer_size = 10,.result_size = 6, .result_string = "0b1010"},
	{.value = 10,  .base = 16, .buffer_size = 4, .result_size = 3, .result_string = "0xa"},
	{.value = 10,  .base = 16, .buffer_size = 3, .result_size = 0 },
	{.value = 0x7fffffff, .base = 16, .buffer_size = 11, .result_size = 10, .result_string = "0x7fffffff"},
	{.value = 0xffffffff, .base = 10, .buffer_size = 20, .result_size = 10, .result_string = "4294967295"},
	{.value = 244, .base = 8, .buffer_size = 5, .result_size = 4, .result_string = "0364"},
};

int error;

void print_result(int i, size_t result_size) {
	if (result_size != test_array[i].result_size) {
		printf("[%d] - Error, expected size = %zd, returned size = %zd\n",
			i, test_array[i].result_size, result_size);
		error = 1;
	}
	else if (result_size > 0 && strcmp(test_array[i].buffer, test_array[i].result_string) != 0) {
		printf("[%d] - Error, expected string = %s, returned string = %s\n",
			i, test_array[i].result_string, test_array[i].buffer);
			error = 1;
	}
	else
		printf("[%d] - OK\n", i);
}

int main() {
	for (int i = 0; i < ARRAY_SIZE(test_array); ++i) {
		size_t result = int_to_string(test_array[i].value,
							test_array[i].base,
								test_array[i].buffer,
									test_array[i].buffer_size);
		print_result(i, result);
	}
	return error;
}

