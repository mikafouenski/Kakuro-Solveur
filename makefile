CC=gcc

LIBS = -lm 
CCFLAGS=-Wall -W -ggdb -std=c99 -pedantic -I./header -I/usr/include
LDFLAGS=

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

EXEC=compilateur-l

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

%.o: %.clean
	$(CC) -o $@ -c $< $(CCFLAGS)

analyseur_lexical.o: analyseur_lexical.c
	$(CC) $(CCFLAGS) -c $^

.PHONY : clean

clean:
	@echo "Clean .o files"
	rm -rf */*.o

mrproper: clean
	@echo "Remove $(EXEC) file"
	rm -rf $(EXEC)

rebuild:
	@echo " --- Cleaning --- "
	make mrproper
	@echo
	@echo
	@echo " --- Building --- "
	make all
