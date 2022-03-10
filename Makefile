CC = gcc
CFLAGS = -ansi -pedantic -Wall -fPIC -O2 -DNDEBUG
ARFLAGS = rcs
SRC = cosine.c object.c class.c param.c value.c type.c
OBJ = cosine.o object.o class.o param.o value.o type.o

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
