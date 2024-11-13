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
valgrind --leak-check=full ./http_get_json
```

## Estrutura da pasta

```txt
exercicio1/
├── Makefile
├── main.c
└── http.c
```
