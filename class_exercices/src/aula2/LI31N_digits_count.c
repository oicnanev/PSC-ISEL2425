#include <stdio.h>

int main() {
	int c, n = 0;
	
	while ((c = getchar()) != EOF) {
		//if (c >= '0' && c <= '9')
		//	n += 1;
		n += (c >= '0' && c <= '9'); 
	}
	printf("Digits count = %d\n", n);
	return 0;
}
