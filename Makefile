CC=gcc

LIBS = -lm
CCFLAGS= -Wall -I./inc
LDFLAGS=

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

EXEC=kakuro

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CCFLAGS)

clean:
	rm -fv src/*.o
	rm -fv $(EXEC)
