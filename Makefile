CC := gcc
CC_OPTIONS := -Wall -lncurses

.PHONY: all
all: main

main: main.c
	$(CC) $(CC_OPTIONS) -o $@ $^

.PHONY: clean
clean:
	rm -r main

.PHONY: run
run:
	./main

