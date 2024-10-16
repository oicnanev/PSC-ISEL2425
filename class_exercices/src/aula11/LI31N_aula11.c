#include <stdio.h>

int my_toupper(int c);
int my_strlen(const char *);

int main() {
	
	printf("my_toupper('a') = \'%c\'\n", my_toupper('a'));
	printf("my_toupper('z') = \'%c\'\n", my_toupper('z'));
	printf("my_toupper('s') = \'%c\'\n", my_toupper('s'));
	printf("my_toupper('0') = \'%c\'\n", my_toupper('0'));
	printf("my_toupper('V') = \'%c\'\n", my_toupper('V'));
	
	printf("my_strlen(\"xpto\") = %d chars\n", my_strlen("xpto"));
	printf("my_strlen(\"\") = %d chars\n", my_strlen(""));
	printf("my_strlen(NULL) = %d chars\n", my_strlen(NULL));
	
	
	return 0;
}
