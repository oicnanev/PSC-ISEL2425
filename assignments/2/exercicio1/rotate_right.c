#include <stdio.h>

void rotate_right(unsigned long value[], size_t n) {
  unsigned long low = value[0];
  unsigned long high = value[1];

  n %= 128; // Garantir que n esteja no intervalo de 0 a 127

  if (n == 0)
    return;

  unsigned long new_low, new_high;
  if (n < 64) {
    new_low = (low >> n) | (high << (64 - n));
    new_high = (high >> n) | (low << (64 - n));
  } else {
    new_low = (high >> (n - 64)) | (low << (128 - n));
    new_high = (low >> (n - 64)) | (high << (128 - n));
  }

  value[0] = new_low;
  value[1] = new_high;
}

int main() {
  unsigned long value[2] = {0x0123456789abcdef, 0xfedcba9876543210};
  size_t n = 20;

  printf("Original: %016lx %016lx\n", value[1], value[0]);

  rotate_right(value, n);
  printf("Result: %016lx %016lx\n", value[1], value[0]);
  return 0;
}
