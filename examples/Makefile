CC      = gcc
CFLAGS  = -ansi -pedantic -Wall -fPIC -g
LDFLAGS = -L../ -l:libcosine.a
TESTS   = object.c
OBJ     = object.o

all: example

example: example.o
	$(CC) -o $@ $^ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(OBJ)

.PHONY: clean
