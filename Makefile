objects: main.c cosine.c
	gcc -ansi -pedantic -Wall -o $@ $^

clean:
	rm objects

.PHONY: clean
