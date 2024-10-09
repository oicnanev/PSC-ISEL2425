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

#define SINGLE_PRECISION_VALUE 127
#define NUM_DECIMAL_DIGITS 1000000

size_t int_to_string(int value, char *buffer, size_t buffer_size, int index) {
    char temp[12]; // suficiente para caber um int em string
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
        // Reverse da string
        for (int i = temp_index - 1; i >= 0; i--) {
            if (index < buffer_size - 1) {
                buffer[index++] = temp[i];
            }
        }
    }
    return index;
}

size_t hex_int_to_string(int value, char *buffer, size_t buffer_size, int index) {
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
            int nibble = value & 0xF;  // sacar 4 bits de cada vez
            temp[temp_index++] = nibble < 10 ? nibble + '0' : nibble - 10 + 'a';
            value >>= 4;  // avançar mais 4 bits
        }
        // Reverse da string
        for (int i = temp_index - 1; i >= 0; i--) {
            if (index < buffer_size - 1) {
                buffer[index++] = temp[i];
            }
        }
    }
    return index;
}

size_t float_to_string(float value, char *buffer, size_t buffer_size, int index) {
    // Ver se é zero
    if (value == 0.0f) {
        if (buffer_size < 4)
            return 0;

        buffer[index++] = '0';
        buffer[index++] = '.';
        buffer[index++] = '0';

        return index; 
    }

    typedef union {
        struct {
            unsigned int mantissa : 23;
            unsigned int exponent : 8;
            unsigned int signal : 1;
        };
        float _float;
    } Float_Bit_Fields;

    Float_Bit_Fields float_bit_fields;
    float_bit_fields._float = value; // passar o float recebido

    int signal = float_bit_fields.signal;
    int exponent = float_bit_fields.exponent - SINGLE_PRECISION_VALUE;
    int normalized_value = (1 << 23) | float_bit_fields.mantissa; // adicionar o '1,' que falta

    // parte inteira
    int deslocament = 23 - exponent;
    int integer_part = 0;

    if (exponent >= 0) // se  o expoente for < 0, a parte inteira é 0
        integer_part = normalized_value >> deslocament;

    int fraction_mask = (1 << deslocament) - 1; // menos 1 para transformar em zeros
    long fraction_part = normalized_value & fraction_mask;
    fraction_part = fraction_part * (long)NUM_DECIMAL_DIGITS;

    // deslocar para a direita para ficar com 6 casas decimais
    int fraction_value = fraction_part >> deslocament;

    // escrever sinal no buffer e noramalizar parte inteira se for negativo
    if (signal)
        buffer[index++] = '-';

    // Escrever parte inteira no buffer
    index += int_to_string(integer_part, buffer + index, buffer_size - index, index);

    // Escrever o ponto decimal
    buffer[index++] = '.';

    // Escrever a parte fracionária no buffer
    if (fraction_value < 1) { // preciso colocar 6 zeros antes
        for (int i = 6; i > 0; i--) {
            buffer[index++] = '0';
        }
        buffer[index] = '\0';
        return index;
    } else if (fraction_value < 10) { // colocar 5 zeros antes
        for (int i = 5; i > 0; i--) {
            buffer[index++] = '0';
        }
    } else if (fraction_value < 100) { // colocar 4 zeros antes
        for (int i = 4; i > 0; i--) {
            buffer[index++] = '0';
        }
    } else if (fraction_value < 1000) { // colocar 3 zeros antes
        for (int i = 3; i > 0; i--) {
            buffer[index++] = '0';
        }
    } else if (fraction_value < 10000) { // colocar 2 zeros antes
        for (int i = 2; i > 0; i--) {
            buffer[index++] = '0';
        }
    } else if (fraction_value < 100000) { // colocar 1 zero antes
        buffer[index++] = '0';
    }
    
    index += int_to_string(fraction_value, buffer + index, buffer_size - index, index);
    
    return index;
}

size_t mini_snprintf(char *buffer, size_t buffer_size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    size_t index = 0;

    while (*format != '\0' && index < buffer_size - 1) {
        if (*format == '%') {
            format++;
            if (*format == 'd') {
                int value = va_arg(args, int);
                index = int_to_string(value, buffer, buffer_size, index);
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
                index = hex_int_to_string(value, buffer, buffer_size, index);
            } else if (*format == 'f') {
                float value = (float)va_arg(args, double);
                if (index < buffer_size - 1) {
                    index += float_to_string(value, buffer, buffer_size, index);
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
