CC      = gcc
CFLAGS  = -ansi -pedantic -Wall -fPIC -g -I../include
LDFLAGS = -L../ -l:libcosine.a
OBJ     = object.o string.o

all: object string

object: object.o
	$(CC) -o $@ $^ $(LDFLAGS)

string: string.o
	$(CC) -o $@ $^ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(OBJ)

.PHONY: clean
