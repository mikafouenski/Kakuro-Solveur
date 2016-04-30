CC=gcc

CCFLAGS=-I./inc -o3

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

EXEC=kakuro

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	rm -fv src/*.o
	rm -fv $(EXEC)
