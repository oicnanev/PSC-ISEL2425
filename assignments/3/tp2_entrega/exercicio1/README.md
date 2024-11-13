# Notas exercício 1

## Preparação do ambiente

```bash
sudo apt update && sudo apt upgrade -y && sudo apt autoremove -y
sudo apt install libcurl4-gnutls-dev
sudo apt install libjansson-dev
sudo apt install valgrind
```

## Implementar a função `http_get_json` no ficheiro `http_get_json.c`

## Implementar ficheiro de teste no ficheiro `test_http_get_json.c`

## Criar o makefile para compilação e geração do executável

```Makefile
# Makefile
CC = gcc
CFLAGS = -Wall -g
LIBS = -lcurl -ljansson
OBJ = test_http_get_json.o http_get_json.o

all: http_get_json

http_get_json: $(OBJ)
	$(CC) $(CFLAGS) -o http_get_json $(OBJ) $(LIBS)

test_http_get_json.o: test_http_get_json.c
	$(CC) $(CFLAGS) -c test_http_get_json.c

http_get_json.o: http_get_json.c
	$(CC) $(CFLAGS) -c http_get_json.c

clean:
	rm -f *.o http_get_json
```

Para compilar:

```bash
make
./http_get_json
```

Para limpar os arquivos gerados:

```bash
make clean
```

## Verificação de leaks com valgrind

```bash
valgrind --leak-check=full -s ./http_get_json
```

Output do valgrind:

```txt
==446940== Memcheck, a memory error detector
==446940== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==446940== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==446940== Command: ./http_get_json
==446940== 
Title: Essence Mascara Lash Princess
==446940== 
==446940== HEAP SUMMARY:
==446940==     in use at exit: 0 bytes in 0 blocks
==446940==   total heap usage: 144,830 allocs, 144,830 frees, 26,850,357 bytes allocated
==446940== 
==446940== All heap blocks were freed -- no leaks are possible
==446940== 
==446940== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Estrutura da pasta

```txt
exercicio1/
├── Makefile
├── main.c
└── http.c
```
