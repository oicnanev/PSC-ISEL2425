#include <stdio.h>

long my_abs(long v);
//int my_toupper(int car);
long my_abs_v2(long v);

int main() {
	printf("my_abs(20)=%ld\n", my_abs(20));
	printf("my_abs(-15)=%ld\n", my_abs(-15));
	printf("my_abs_v2(20)=%ld\n", my_abs_v2(20));
	printf("my_abs_v2(-15)=%ld\n", my_abs_v2(-15));
//	printf("my_toupper(\'G\')=\'%c\'\n", my_toupper('G'));
//	printf("my_toupper(\'b\')=\'%c\'\n", my_toupper('b'));	
	
	return 0;
}
