#include <stdio.h>

unsigned short date_pack(int y, int m, int d) {
	unsigned short date;
	date = d & 0x1F;
	date |= ((m & 0xF) << 5);
	date = date | ((y-2000) << 9);
	return date;
}

int date_unpack_day(unsigned short date) {
	return 0;
}
int date_unpack_month(unsigned short date) {
	return 0;
}
int date_unpack_year(unsigned short date) {
	return 0;
}

int main() {
	unsigned short d1 = date_pack(2024, 9, 13);	
	printf("Date pack = 0x%x\n", d1);
	// Date unpack
	return 0;
}
