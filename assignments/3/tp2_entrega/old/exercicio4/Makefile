CC = gcc
CFLAGS = -Wall -fPIC -Iinclude
LDFLAGS = -lcurl -ljansson
SRC = src/http_utils.c src/api.c
OBJ = $(SRC:.c=.o)

all: lib/libpsc.so test/test_program

# Compila a biblioteca dinâmica
lib/libpsc.so: lib $(OBJ)
	@echo "Compilando libpsc.so com $(OBJ)..."
	$(CC) -shared -o $@ $(OBJ) $(LDFLAGS)

# Compila o programa de teste
test/test_program: test/main.c lib/libpsc.so
	@echo "Compilando programa de teste..."
	$(CC) $(CFLAGS) test/main.c -o $@ -Llib -lpsc $(LDFLAGS)

# Regras de compilação para os arquivos objeto
%.o: %.c
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	@echo "Limpando arquivos..."
	rm -f $(OBJ) lib/libpsc.so test/test_program

