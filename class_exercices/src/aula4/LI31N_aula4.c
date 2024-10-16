#include <stdio.h>
void array_swap(unsigned short *p1, unsigned short *p2) {
	long tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void array_sort(unsigned short *a, int a_size) {
	for (int i = 0; i < a_size - 1; i++) {
		int idx_max = 0;
		
		for (int j = 1; j < a_size -i; j++)
			if (a[j] > a[idx_max])
				idx_max = j;
		
		array_swap(a + idx_max /*&a[idx_max]*/, a + a_size-i-1 /*&a[a_size-i-1]*/);
	}
}

void array_print(unsigned short *a, int a_size) {
	for (int i = 0; i < a_size - 1; i++)
		printf("%d, ", a[i]);
	printf("%d\n", a[a_size-1]);
}

void test_array_sort() {
	unsigned short l1[] = {10, 20, -1, -100, 5, 10};
	int size = sizeof(l1)/sizeof(l1[0]);
	printf("Original: "); array_print(l1, size);
	array_sort(l1, size);
	printf("Resultado: "); array_print(l1, size);
}

int getbits(short v, int high, int low) {
	v >>= low;
	v &= (1 << (high - low + 1)) - 1;
	return v;
}
int getbits2(short v, int high, int low) {
	v <<= sizeof(short)*8 - high - 1;
	v = (unsigned short)v >> (sizeof(short)*8 - high - 1 + low);
	return v;
}

void date_unpack(short date, int *py, int *pm, int *pd) {
	*py = getbits(date, 15, 9) + 2000;
	*pm = getbits(date, 8, 5);
	*pd = getbits(date, 4, 0);
}

unsigned short date_pack(int y, int m, int d) {
	unsigned short date;
	date = d & 0x1F;
	date |= ((m & 0xF) << 5);
	date = date | ((y-2000) << 9);
	return date;
}

void test_date_unpack() {
	short date = date_pack(2024, 9, 20);
	int y, m, d;
	date_unpack(date, &y, &m, &d);
	printf("y=%d, m=%d, d=%d\n", y, m, d);
}

int tolower(int c) {
	if (c >= 'A' && c <= 'Z') 
		c = c - 'A' + 'a';
	return c;
}

int strcasecmp(const char *sl, const char *sr) {
	char cl, cr;
	do {
		cl = tolower(*sl++);
		cr = tolower(*sr++);
	} while (cl == cr && cl != 0);
	return cl - cr;
}

void test_strcasecmp() {
	const char * s1 = "xpTO";
	const char * s2 = "xPTo1";
	int cmp = strcasecmp(s1, s2);
	printf("\"%s\" %c \"%s\"\n", s1, cmp < 0 ? '<' : cmp == 0 ? '=' : '>', s2);
	cmp = strcasecmp(s2, s1);
	printf("\"%s\" %c \"%s\"\n", s2, cmp < 0 ? '<' : cmp == 0 ? '=' : '>', s1);
	const char * s3 = "XPTo";
	cmp = strcasecmp(s3, s1);
	printf("\"%s\" %c \"%s\"\n", s3, cmp < 0 ? '<' : cmp == 0 ? '=' : '>', s1);
}

int main() {
	test_array_sort();
	test_date_unpack();
	test_strcasecmp();
	return 0;
}
