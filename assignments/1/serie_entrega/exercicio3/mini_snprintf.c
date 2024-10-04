/*
 * Função: mini_snprintf
 * ---------------------
 * Formata e armazena uma string no buffer fornecido, de acordo com o formato especificado.
 *
 * Parâmetros:
 *  - char *buffer: o array de caracteres onde a string resultante será armazenada.
 *  - size_t buffer_size: o tamanho do array buffer.
 *  - const char *format: a string de formato que especifica como os argumentos devem ser formatados.
 *  - ...: uma lista de argumentos variáveis que serão formatados de acordo com a string de formato.
 *
 * Retorna:
 *  - size_t: o comprimento da string produzida. Retorna 0 se o buffer for insuficiente.
 *
 * Método:
 * 1. Inicializa a lista de argumentos variáveis.
 * 2. Percorre a string de formato e processa cada especificador de formato (%d, %s, %b, %c, %x, %e, %f).
 * 3. Converte e armazena os valores correspondentes no buffer, respeitando o tamanho máximo do buffer.
 * 4. Adiciona o caractere nulo ('\0') ao final da string no buffer.
 * 5. Finaliza a lista de argumentos variáveis.
 *
 * Autor:
 * 45824 Nuno Venâncio
 */

#include <stdarg.h>
#include <stdio.h>

size_t mini_snprintf(char *buffer, size_t buffer_size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    size_t index = 0;

    while (*format != '\0' && index < buffer_size - 1) {
        if (*format == '%') {
            format++;
            if (*format == 'd') {
                int value = va_arg(args, int);
                char temp[12]; // Enough to hold an int as a string
                int temp_index = 0;
                if (value == 0) {
                    temp[temp_index++] = '0';
                } else {
                    if (value < 0) {
                        if (index < buffer_size - 1) {
                            buffer[index++] = '-';
                        }
                        value = -value;
                    }
                    while (value > 0) {
                        temp[temp_index++] = (value % 10) + '0';
                        value /= 10;
                    }
                    // Reverse the string
                    for (int i = temp_index - 1; i >= 0; i--) {
                        if (index < buffer_size - 1) {
                            buffer[index++] = temp[i];
                        }
                    }
                }
            } else if (*format == 's') {
                const char *value = va_arg(args, const char *);
                while (*value != '\0' && index < buffer_size - 1) {
                    buffer[index++] = *value++;
                }
            } else if (*format == 'b') {
                int value = va_arg(args, int);
                for (int i = 31; i >= 0; i--) {
                    if (index < buffer_size - 1) {
                        buffer[index++] = (value >> i) & 1 ? '1' : '0';
                    }
                }
            } else if (*format == 'c') {
                char value = va_arg(args, int);
                if (index < buffer_size - 1) {
                    buffer[index++] = value;
                }
            } else if (*format == 'x') {
                int value = va_arg(args, int);
                char temp[9]; // Enough to hold an int in hex
                int temp_index = 0;
                if (index < buffer_size - 1) {
                    buffer[index++] = '0';
                }
                if (index < buffer_size - 1) {
                    buffer[index++] = 'x';
                }
                if (value == 0) {
                    temp[temp_index++] = '0';
                } else {
                    while (value > 0) {
                        int nibble = value & 0xF;
                        temp[temp_index++] = nibble < 10 ? nibble + '0' : nibble - 10 + 'a';
                        value >>= 4;
                    }
                    // Reverse the string
                    for (int i = temp_index - 1; i >= 0; i--) {
                        if (index < buffer_size - 1) {
                            buffer[index++] = temp[i];
                        }
                    }
                }
            } else if (*format == 'e' || *format == 'f') {
                double value = va_arg(args, double);
                // Simple implementation for demonstration purposes
                if (index < buffer_size - 1) {
                    index += sprintf(buffer + index, *format == 'e' ? "%e" : "%f", value);
                }
            }
        } else {
            if (index < buffer_size - 1) {
                buffer[index++] = *format;
            }
        }
        format++;
    }
    buffer[index] = '\0';
    va_end(args);
    return index;
}
