#include <stdio.h>
#include <stdarg.h>

int sum(int n, ...) {
	va_list pa;
	va_start(pa, n);
	int sum = 0;
	
	while (n-- > 0)
		sum += va_arg(pa, int);
		
	va_end(pa);
	return sum;
}

int main() {
	
	printf("sum(3, 1, 2, 3) = %d\n", 
			sum(3, 1, 2, 3));
	printf("sum(7, 1, 2, 3, 10, 20, 30, 40) = %d\n", 
			sum(7, 1, 2, 3, 10, 20, 30, 40));
	printf("sum(4, 1, 2, 3, 10, 20, 30, 40) = %d\n", 
			sum(4, 1, 2, 3, 10, 20, 30, 40));
	printf("sum(4, 1, 2, 3) = %d\n", 
			sum(4, 1, 2, 3));
			
	return 0;
}
