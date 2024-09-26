#include <stdio.h>

#define BUFFER_SIZE 35  // 2 do prefixo + 32 digitos binarios + '/0' para o maior unsigned int em binário
#define BIG_UNSIGNED 4294967295  // maior unsigned int
#define SMALL_UNSIGNED 1
#define ZERO 0

size_t int_to_string(unsigned value, int base, char buffer[], size_t buffer_size);

int main() {
    const int BIN = 2;
    const int OCT = 8;
    const int DEC = 10;
    const int HEX = 16;

    char buffer[BUFFER_SIZE];
    size_t length;

    printf("Teste com maior unsigned\n");

    length = int_to_string(BIG_UNSIGNED, BIN, buffer, sizeof(buffer));
    printf("Binário: %s (length: %zu)\n", buffer, length);

    length = int_to_string(BIG_UNSIGNED, OCT, buffer, sizeof(buffer));
    printf("Octal: %s (length: %zu)\n", buffer, length);

    length = int_to_string(BIG_UNSIGNED, DEC, buffer, sizeof(buffer));
    printf("Decimal: %s (length: %zu)\n", buffer, length);

    length = int_to_string(BIG_UNSIGNED, HEX, buffer, sizeof(buffer));
    printf("Hexadecimal: %s (length: %zu)\n\n", buffer, length);


    // ----------------------------------------------------------------
    printf("Teste com menor unsigned\n");

    length = int_to_string(SMALL_UNSIGNED, BIN, buffer, sizeof(buffer));
    printf("Binário: %s (length: %zu)\n", buffer, length);

    length = int_to_string(SMALL_UNSIGNED, OCT, buffer, sizeof(buffer));
    printf("Octal: %s (length: %zu)\n", buffer, length);

    length = int_to_string(SMALL_UNSIGNED, DEC, buffer, sizeof(buffer));
    printf("Decimal: %s (length: %zu)\n", buffer, length);

    length = int_to_string(SMALL_UNSIGNED, HEX, buffer, sizeof(buffer));
    printf("Hexadecimal: %s (length: %zu)\n\n", buffer, length);

    // ------------------------------------------------------------------
    printf("Teste com menor unsigned\n");

    length = int_to_string(ZERO, BIN, buffer, sizeof(buffer));
    printf("Binário: %s (length: %zu)\n", buffer, length);

    length = int_to_string(ZERO, OCT, buffer, sizeof(buffer));
    printf("Octal: %s (length: %zu)\n", buffer, length);

    length = int_to_string(ZERO, DEC, buffer, sizeof(buffer));
    printf("Decimal: %s (length: %zu)\n", buffer, length);

    length = int_to_string(ZERO, HEX, buffer, sizeof(buffer));
    printf("Hexadecimal: %s (length: %zu)\n\n", buffer, length);

    return 0;
}
