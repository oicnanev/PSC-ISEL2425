/*
 * Função: float_to_string
 * -----------------------
 * Converte um valor de ponto flutuante para uma string com precisão de 6 casas decimais
 * e armazena o resultado no buffer fornecido.
 *
 * Parâmetros:
 *  - float value: o valor de ponto flutuante a ser convertido.
 *  - char buffer[]: o array de caracteres onde a string resultante será armazenada.
 *  - size_t buffer_size: o tamanho do array buffer.
 *
 * Retorna:
 *  - size_t: o comprimento da string produzida. Retorna 0 se o buffer for insuficiente.
 *
 * Método:
 * 1. Verifica se o valor é zero e armazena "0.000000" no buffer se for o caso.
 * 2. Verifica se o buffer fornecido é suficiente para armazenar a string resultante.
 * 3. Utiliza uma união para acessar os campos de bits do valor de ponto flutuante.
 * 4. Calcula a parte inteira e a parte fracionária do valor.
 * 5. Escreve o sinal, a parte inteira e a parte fracionária no buffer.
 * 6. Adiciona o caractere nulo ('\0') ao final da string no buffer.
 *
 * Autor:
 * 45824 Nuno Venâncio
 */

#include <stdio.h>

#define BUFFER_SIZE 14
#define SINGLE_PRECISION_VALUE 127
#define NUM_DECIMAL_DIGITS                                                     \
  1000000 // para multiplicar e obter 6 digitos de precisão na parte fracionaria

size_t float_to_string(float value, char buffer[], size_t buffer_size) {
  // Check for zero value
    if (value == 0.0f) {
        if (buffer_size < 8) // "-0.000000" precisa de 8 characters
            return 0;
        snprintf(buffer, buffer_size, "0.000000");
        return 8;
    }

  // Ver se o buffer_size é suficiente pelo menos as 6 casas decimais
  if (buffer_size < 9 && value > 0)
    return 0;
  else if (buffer_size < 10 && value < 0)
    return 0;

  size_t index = 0;

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
  /*printf("Signal: %d\n", signal);
  printf("Exponent: %d\n", exponent);
  printf("Normalized Value: %d\n", normalized_value);
  printf("Deslocament: %d\n", deslocament);
  printf("Integer part: %d\n", integer_part);
  printf("Fraction mask: %d\n", fraction_mask);
  printf("Fraction part: %ld\n", fraction_part);
  printf("Fraction value: %d\n", fraction_value);*/
  // ################################################################################

  // escrever sinal no buffer e noramalizar parte inteira se for negativo
  if (signal)
    buffer[index++] = '-';

  // Escrever parte inteira no buffer
  index += snprintf(buffer + index, buffer_size - index, "%d", integer_part);

  // Escrever ponto decimal e parte fracionária no buffer
  index +=
      snprintf(buffer + index, buffer_size - index, ".%06d", fraction_value);

  // Garantir que o buffer seja nulo-terminado
  //buffer[index] = '\0';

  return index;
}
