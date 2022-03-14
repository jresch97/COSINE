CC = gcc
CFLAGS = -ansi -pedantic -Wall -fPIC -g -I./include
ARFLAGS = rcs
SRC = src/cosine.c src/object.c src/class.c
OBJ = src/cosine.o src/object.o src/class.o

all: libcosine.a libcosine.so

libcosine.a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

libcosine.so: $(OBJ)
	$(CC) -shared $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm libcosine.a libcosine.so $(OBJ)

.PHONY: clean
