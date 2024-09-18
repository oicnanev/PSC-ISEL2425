# Class Exercices

## 1

### 1.1 Contar dígitos de um texto
Apresentar no *stdout* o número de caracteres dígito presentes num ficheiro de texto
 - [code](src/digit_counter.c)

### 1.2 Valor máximo do tipo *int*
Apresentar no *stdout* o valor máximo sem sinal e o valor minimo com sinal do tipo *int*
 - [code](src/int_size.c)

### 1.3 Compactador/descompactador de uma data
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

## 2
### 2.1 Ordenador de arrays
Ordenar um *array* de inteiros (*unsigned short*) de acordo com o algoritmo *selection sort*
```c
void array_sort( unsigned short *a, int size );
void array_swap( unsigned short *i1, unsigned short *i2 );
void array_print( unsigned short *a, int size );
```
- [code](src/array_sort.c)

### 2.2 Descompactar data
Descompactar uma data recorrendo à função *getbits*
```c
void date_unpack( short date, int *py, int *pm, int *pd );
int getbits( short v, int high, int low );
```
- [code](src/date_unpack_getbits.c)

### 2.3 Comparar strings
Comparar duas strings (*ls* e *rs*) *case-insensitive* retornando  **\< 0** se *ls* < *rs*, **0** se *ls* = *rs*, e **> 0** se *ls* > *rs*

```c
int strcasecmp( const char *ls, const char *rs );
```
- [code](/src/string_cmp.c)

### 2.4 Concatenar strings
Concatenar a string *src* na string *dst*
```c
char *strcat( char *dst, const char *src );
```
- [code](/src/string_concat.c)

