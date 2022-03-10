CC = gcc
CFLAGS = -ansi -pedantic -Wall -g
LDFLAGS = -lm

SRC = main.c int.c cosine.c object.c class.c param.c value.c type.c
OBJ = main.o int.o cosine.o object.o class.o param.o value.o type.o

cosine: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm cosine $(OBJ)

.PHONY: clean
