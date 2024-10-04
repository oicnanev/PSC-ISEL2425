#include <stdio.h>

#define BUFFER_SIZE 14
#define SINGLE_PRECISION_VALUE 127
#define NUM_DECIMAL_DIGITS                                                     \
  1000000 // para multiplicar e obter 6 digitos de precisão na parte fracionaria

size_t float_to_string(float value, char buffer[], size_t buffer_size) {
  size_t index = 0;

  // Se valor for zero retornar já 10 (sinal + 0 + ponto + 6 digitos de precisão
  // + '\0')
  if (value == 0)
    return 10;

  // criação de uma união constituida por uma extrutura de 'bit fields' e um
  // float
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
  int normalized_value =
      (1 << 23) | float_bit_fields.mantissa; // adicionar o '1,' que falta

  // parte inteira
  int deslocament = 23 - exponent;
  int integer_part = 0;

  if (exponent >= 0) // se  o expoente for < 0, a parte inteira é 0
    integer_part = normalized_value >> deslocament;

  int fraction_mask =
      (1 << deslocament) - 1; // menos 1 para transformar em zeros
  long fraction_part = normalized_value & fraction_mask;
  fraction_part = fraction_part * (long)NUM_DECIMAL_DIGITS;

  // deslocar para a direita para ficar com 6 casas decimais
  int fraction_value = fraction_part >> deslocament;

  // DEBUG LINES
  // ####################################################################
  printf("Signal: %d\n", signal);
  printf("Exponent: %d\n", exponent);
  printf("Normalized Value: %d\n", normalized_value);
  printf("Deslocament: %d\n", deslocament);
  printf("Integer part: %d\n", integer_part);
  printf("Fraction mask: %d\n", fraction_mask);
  printf("Fraction part: %ld\n", fraction_part);
  printf("Fraction value: %d\n", fraction_value);
  // ################################################################################

  // escrever sinal no buffer e noramalizar parte inteira se for negativo
  if (signal) {
    buffer[index++] = '-';
    integer_part *= -1;
  } else {
    buffer[index++] = '+';
  }

  // Escrever parte inteira no buffer
  index += snprintf(buffer + index, buffer_size - index, "%d", integer_part);

  // Escrever ponto decimal e parte fracionária no buffer
  index +=
      snprintf(buffer + index, buffer_size - index, ".%06d", fraction_value);

  // Garantir que o buffer seja nulo-terminado
  buffer[index] = '\0';

  return index;
}

int main() {
  float num = -123.123459;
  char buffer[BUFFER_SIZE];
  printf("The number %f is stored in %ld characters\n\n", num,
         float_to_string(num, buffer, sizeof(buffer)));

  num = 0.001;
  printf("The number %f is stored in %ld characters\n\n", num,
         float_to_string(num, buffer, sizeof(buffer)));

  num = 1.1;
  printf("The number %f is stored in %ld characters\n\n", num,
         float_to_string(num, buffer, sizeof(buffer)));

  num = 123.123456789;
  printf("The number %f is stored in %ld characters\n\n", num,
         float_to_string(num, buffer, sizeof(buffer)));
  return 0;
}
