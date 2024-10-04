/*
 * mini_snprintf.c
 * Limitada aos especificadores de conversão b, c, s, d, x, e, f.
 *  Created on: 19/10/2017
 */
#include <stdarg.h>
#include <stdio.h>

size_t mini_snprintf(char *buffer, size_t buffer_size, const char *format,
                     ...) {
  va_list args;
  va_start(args, format);
  size_t index = 0;

  while (*format != '\0') {
    if (*format == '%') {
      format++;
      if (*format == 'd') {
        int value = va_arg(args, int);
        while (value > 0) {
          buffer[index++] = value % 10 + '0';
          value /= 10;
        }
      } else if (*format == 's') {
        const char *value = va_arg(args, const char *);
        while (*value != '\0') {
          buffer[index++] = *value++;
        }
      } else if (*format == 'b') {
        int value = va_arg(args, int);
        for (int i = 31; i >= 0; i--) {
          buffer[index++] = (value >> i) & 1 ? '1' : '0';
        }
      } else if (*format == 'c') {
        char value = va_arg(args, int);
        buffer[index++] = value;
      } else if (*format == 'x') {
        int value = va_arg(args, int);
        for (int i = 28; i >= 0; i -= 4) {
          int nibble = (value >> i) & 0xF;
          buffer[index++] = nibble < 10 ? nibble + '0' : nibble - 10 + 'A';
        }
      } else if (*format == 'e') {
        float value = va_arg(args, double);
      } else if (*format == 'f') {
        float value = va_arg(args, double);
      }
    } else {
      buffer[index++] = *format;
    }
    format++;
  }
  buffer[index] = '\0';
  va_end(args);
  return index;
}
