CC := gcc
LINKER_OPTIONS := -Wall -I./inc
COMPILER_OPTIONS := -lncurses

BIN = ./bin

SRCS = snake.c main.c
OBJS = $(SRCS:%.c=$(BIN)/%.o)

.PHONY: all
all: $(BIN) $(BIN)/main

$(BIN):
	mkdir $@

$(BIN)/main: $(OBJS)
	$(CC) $(COMPILER_OPTIONS) -o $@ $^

$(BIN)/%.o: %.c
	$(CC) $(LINKER_OPTIONS) -c -o $@ $<

.PHONY: clean
clean:
	rm -r $(BIN)

.PHONY: run
run:
	$(BIN)/main

