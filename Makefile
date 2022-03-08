objects: main.c cosine.c
	gcc -ansi -pedantic -Wall -g -o $@ $^

clean:
	rm objects

.PHONY: clean
