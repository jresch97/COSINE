CC      = gcc
CFLAGS  = -ansi -pedantic -Wall -fPIC -g -I../
LDFLAGS = -L../ -l:libcosine.a
OBJ     = example.o int.o string.o

all: example

example: example.o int.o string.o
	$(CC) -o $@ $^ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(OBJ)

.PHONY: clean
