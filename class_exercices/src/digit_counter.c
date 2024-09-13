#include <stdio.h>
/* Count the number of digits in a text file.
 * Use CTRL^D to produce EOF from command line.
 * Use ./digit_counter < file to redirect stdin to file. */

int main() {
	int nextChar; 	// char readed
	int count = 0;  // digits counter

	while (( nextChar = getchar()) != EOF ) {
		// in ASCII table '0' is 48 and '9' is 57 
		// so characters between 48 and 57 are digits
		// if (nextChar > 47 && nextChar < 58) {  // option 1
		// if (nextChar >= '0' && nextChar <= '9' {  // option 2
		//	count++; 
		//}
		count += (nextChar >= '0' && nextChar <= '9'); // option3
	}

	printf("Digits count = %d\n", count);
	return 0;
}
