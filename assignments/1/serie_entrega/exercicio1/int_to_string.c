#include <stdio.h>

/*
 * Função: int_to_string
 * ---------------------
 * Converte um valor inteiro para uma string na base especificada (2, 8, 10 ou
 * 16) e armazena o resultado no buffer fornecido.
 *
 * Parâmetros:
 *  - unsigned value: o valor inteiro a ser convertido.
 *  - int base: a base de numeração para a conversão (2, 8, 10 ou 16).
 *  - char buffer[]: o array de caracteres onde a string resultante será
 * armazenada.
 *  - size_t buffer_size: o tamanho do array buffer.
 *
 * Retorna:
 *  - size_t: o comprimento da string produzida. Retorna 0 se o buffer for
 * insuficiente.
 *
 * Método:
 * 1. Verifica a base e adiciona o prefixo apropriado ao buffer (0b para
 * binário, 0o para octal, 0x para hexadecimal).
 * 2. Converte o valor inteiro para a string na base especificada, armazenando
 * os dígitos em ordem reversa num buffer temporário.
 * 3. Verifica se o buffer fornecido é suficiente para armazenar a string
 * resultante.
 * 4. Copia a string reversa do buffer temporário para o buffer final na ordem
 * correta.
 * 5. Adiciona o caractere nulo ('\0') ao final da string no buffer.
 *
 * Autor:
 * 45824 Nuno Venâncio
 */

#define INT_SIZE sizeof(int)
#define CHAR_SIZE sizeof(char)
#define BYTE 8 // 1 Byte = 8 bits

size_t int_to_string(unsigned value, int base, char buffer[],
                     size_t buffer_size) {

  // Um int em digitos binários são 32 digitos x 8 + '\0' = 40
  const long temp_buffer_size = (INT_SIZE * BYTE + CHAR_SIZE * BYTE);

  // Buffer temporário para armazenar a string reversa,
  // em 64bits, um int representados em digitos binários 32 + 1 para o '\0' = 33
  // depois cada char ocupa 8 bits, logo 33 * 8
  char temp[temp_buffer_size];
  size_t length = 0;
  int i = 0;

  // Prefixos para bases 0 (?), 2, 8 e 16
  if (base == 0) {
    return 0;
  } else if (base == 2) {
    buffer[length++] = '0';
    buffer[length++] = 'b';
  } else if (base == 8) {
    buffer[length++] = '0';
  } else if (base == 16) {
    buffer[length++] = '0';
    buffer[length++] = 'x';
  }

  // Conversão do valor para a string na base especificada
  do {
    int remainder = value % base;
    if (remainder < 10) {
      temp[i++] = remainder + '0';
    } else { //  A=10, B=11, C=12, D=13, E=14, F=15
      temp[i++] = remainder + 'a' - 10;
    }
    value /= base;
  } while (value > 0);

  // Verifica se o buffer é suficiente
  if (length + i >= buffer_size) {
    printf("Buffer insuficiente");
    return 0;
  }

  // Copia a string reversa para o buffer final
  while (i > 0) {
    buffer[length++] = temp[--i];
  }

  buffer[length] = '\0'; // Termina a string com null

  return length;
}

