CC      = gcc
CFLAGS  = -ansi -pedantic -Wall -fPIC -g
LDFLAGS = -L../ -l:libcosine.a
OBJ     = object.o

all: object

object: object.o
	$(CC) -o $@ $^ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm $(OBJ)

.PHONY: clean
