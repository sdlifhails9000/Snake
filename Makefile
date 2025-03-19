CC := gcc
CCFLAGS := -Wall -Wextra -std=c11 
LDFLAGS =

LIB = ncurses 
LDFLAGS += -l$(LIB) 

INC = inc
CCFLAGS += -I$(INC)

SRCS = main.c snake.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: main $(OBJS)

main: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm main $(OBJS)

