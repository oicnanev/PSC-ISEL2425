#include <stdio.h>

char *strcat( char *dst, const char *src );

char *strcat( char *dst, const char *src) {

	// Advance until the end of dst string
	while (*dst != '\0') {
		dst++;
	}

	// Copy chars from src to dst one at the time
	do {
		*dst = *src;
		dst++;
		src++;
	} while (*src != '\0'); // in do while it copies the '\0' too

	//*dst = '\0';  // add string terminator in the final

	return dst;
}

int main() {
	char dst[100] = "Hello, ";  // must have space for concatenation
	const char *src = "PSC-ISEL!";

	printf("Before: %s\n", dst);
	strcat(dst, src);
	printf("After: %s\n", dst);

	return 0;
}
