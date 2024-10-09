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
#define NUM_DECIMAL_DIGITS 1000000 // para multiplicar e obter 6 digitos de precisão na parte fracionaria


size_t decimal_int_to_string(unsigned value, char buffer[], size_t buffer_size){
  const unsigned char BASE = 10;
  char temp[BUFFER_SIZE];
  size_t length = 0;
  int i = 0;

  // Conversão do valor para string
  do {
    int remainder = value % BASE;
    temp[i++] = remainder + '0';
    value /= BASE;
  } while (value > 0);

  // copia a string reversa para o buffer final
  while (i > 0) {
    buffer[length++] = temp[--i];
  }

  return length;
}


size_t float_to_string(float value, char buffer[], size_t buffer_size) {
    // Ver se é zero
    if (value == 0.0f) {
        if (buffer_size < 8) // "-0.000000" precisa de 8 characters
            return 0;

        buffer[0] = '0';
        buffer[1] = '.';
        buffer[2] = '0';
        buffer[3] = '0';
        buffer[4] = '0';
        buffer[5] = '0';
        buffer[6] = '0';
        buffer[7] = '0';
        buffer[8] = '\0';
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
  index += decimal_int_to_string(integer_part, buffer + index, buffer_size - index);

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
      
  index += decimal_int_to_string(fraction_value, buffer + index, buffer_size - index);

  // Garantir que o buffer seja nulo-terminado
  buffer[index] = '\0';

  return index;
}
