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
