# Makefile
CC = gcc
CFLAGS = -Wall -g
LIBS = -lcurl -ljansson
OBJ = test_http_post_json.o http_post_json.o

all: http_post_json

http_post_json: $(OBJ)
	$(CC) $(CFLAGS) -o http_post_json $(OBJ) $(LIBS)

test_http_post_json.o: test_http_post_json.c
	$(CC) $(CFLAGS) -c test_http_post_json.c

http_post_json.o: http_post_json.c
	$(CC) $(CFLAGS) -c http_post_json.c

clean:
	rm -f *.o http_post_json
