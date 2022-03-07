objects: main.c class.c
	gcc -ansi -pedantic -Wall -o $@ $^

clean:
	rm objects

.PHONY: clean
