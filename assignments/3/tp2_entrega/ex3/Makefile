# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -pedantic -std=c11

# Libraries
LIBS = -lcurl -ljansson

# Targets and source files
TARGET = test_store
SRC = test_store.c store.c

# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Compiling source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJ) $(TARGET)

# Run target
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
