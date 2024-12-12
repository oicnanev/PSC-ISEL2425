CC = gcc
CFLAGS = -Wall -fPIC -Iinclude
LDFLAGS = -lcurl -ljansson -Llib -lpsc
SRC = src/http_utils.c src/api.c src/main.c
OBJ = $(SRC:.c=.o)

# Alvo principal que compila o executável principal
all: psc

psc: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o psc_store -Llib -lpsc $(LDFLAGS)

# Alvo para compilar o programa de teste
test/test_program: test/test_main.c lib/libpsc.so
	$(CC) $(CFLAGS) test/test_main.c -o test/test_program -Llib -lpsc $(LDFLAGS)

# Limpeza dos arquivos objeto e do programa de teste
clean:
	rm -f src/*.o test/test_program psc_store

# Limpeza dos arquivos objeto e do programa de teste (inclusive a libpsc.so caso necessário)
clean_all: clean
	rm -f lib/libpsc.so
