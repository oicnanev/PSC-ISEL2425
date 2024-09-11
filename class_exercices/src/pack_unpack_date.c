#include <stdio.h>

unsigned short date_pack(int y, int m, int d) {
	// Code years from 2000
	unsigned short year = (y - 2000) << 9;  // year uses bits 15..9
	unsigned short month = m << 5;          // month uses bits 8..5
	unsigned day = d;
	return year | month | day; // the bitwise OR sums all bits
}

int date_unpack_year(unsigned short date) {
	// right shift date by 9, then AND it with 0111 1111 (0x7F) mask, and sum 2000
	return (( date >> 9 ) & 0x7F) + 2000; 
}

int date_unpack_month(unsigned short date) {
	// right shift by 5 and then AND with 1111 (0xF) mask
	return ( date >> 5 ) & 0xF;
}

int date_unpack_day(unsigned short date) {
	// AND mask with 0001 1111 (0x1F)
	return date & 0x1F
}

int main() {
	int year = 2024, month = 9, day = 13;

	unsigned short packed_date = date_pack(year, month, day);

	printf("Packed date - %u\n", packed_date);
	printf("Unpacked year - %d\n", date_unpack_year(packed_date));
	printf("Unpacked month - %d\n", date_unpack_month(packed_date));
	printf("Unpacked day - %d\n", date_unpack_day(packed_date));

	return 0;
}