CC := gcc
CC_OPTIONS := -Wall -Wextra -std=c11 -lncurses

.PHONY: all
all: main

main: main.c
	$(CC) $(CC_OPTIONS) -o $@ $<

.PHONY: clean
clean:
	rm main

.PHONY: run
run:
	./main
