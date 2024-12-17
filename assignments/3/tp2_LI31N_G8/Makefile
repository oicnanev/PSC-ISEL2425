# Nome do executável
TARGET = psc_store
TEST_TARGET = test_api

# Compilador e flags
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lcurl -ljansson

# Pastas
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include
TEST_DIR = tests
LIB_DIR = lib

# Ficheiros fonte e objetos
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# Biblioteca compartilhada
LIBRARY = $(LIB_DIR)/libpsc.so

# Regras
all: $(BIN_DIR)/$(TARGET) $(BIN_DIR)/$(TEST_TARGET) $(LIBRARY) install

# Compilar o executável principal
$(BIN_DIR)/$(TARGET): $(OBJ_DIR)/main.o $(OBJ_DIR)/api.o $(OBJ_DIR)/http_utils.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilar os testes
$(BIN_DIR)/$(TEST_TARGET): $(OBJ_DIR)/test_api.o $(OBJ_DIR)/api.o $(OBJ_DIR)/http_utils.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilar a biblioteca compartilhada
$(LIBRARY): $(OBJ)
	@mkdir -p $(LIB_DIR)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

# Compilar os arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -fPIC -c -o $@ $<

# Compilar os arquivos de teste
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -fPIC -c -o $@ $<

# Instalar a biblioteca em /usr/lib
install: $(LIBRARY)
	sudo cp $(LIBRARY) /usr/lib
	sudo ldconfig

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIBRARY)

.PHONY: all clean install
