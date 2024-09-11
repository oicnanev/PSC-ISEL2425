# Class Exercices

## 1

## 1.1 Contar dígitos de um texto
Apresentar no *stdout* o número de caracteres dígito presentes num ficheiro de texto
 - [code](src/digit_counter.c)

## 1.2 Valor máximo do tipo *int*
Apresentar no *stdout* o valor máximo sem sinal e o valor minimo com sinal do tipo *int*
 - [code](src/int_size.c)

# 1.3 Compactador/descompactador de uma data
 - Assuma que o ano compactado codifica apenas um ano a partir do ano 2000 (inclusive)
 ```c
 unsigned short date_pack(int y, int m, int d);
 int date_unpack_year(unsigned short date);
 int date_unpack_month(unsigned short date);
 int date_unpack_day(unsigned short day);
 ```
 - Formato da data compactada:
  - year - bits 15..9
  - month - bits 8..5
  - day -bits 4..0

 - [code](src/pack_unpack_date.c)



