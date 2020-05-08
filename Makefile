CC=gcc
FLAGS=-Wall -pedantic
EXE=bin/kbi

all:
	mkdir bin/
	$(CC) $(FLAGS) -o $(EXE) src/kbi.c

clean:
	rm -rf bin/
