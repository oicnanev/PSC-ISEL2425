# Makefile
CC = gcc
CFLAGS = -Wall -g
LIBS = -lcurl -ljansson
OBJ = test_api.o api.o http_get_json.o http_post_json.o

all: test_api

test_api: $(OBJ)
	$(CC) $(CFLAGS) -o test_api $(OBJ) $(LIBS)

test_api.o: test_api.c
	$(CC) $(CFLAGS) -c test_api.c

api.o: api.c
	$(CC) $(CFLAGS) -c api.c

http_get_json.o: http_get_json.c
	$(CC) $(CFLAGS) -c http_get_json.c

http_post_json.o: http_post_json.c
	$(CC) $(CFLAGS) -c http_post_json.c

clean:
	rm -f *.o test_api
