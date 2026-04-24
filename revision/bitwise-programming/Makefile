BIN := bin
INC := inc
SRC := src
OBJ := obj

CC := gcc

release: countbit deslocation splitsbits

countbit:
	$(CC) $(SRC)/countbit.c -o $(OBJ)/countbit.o

deslocation:
	$(CC) $(SRC)/deslocation.c -o $(OBJ)/deslocation.o

splitsbits:
	$(CC) $(SRC)/splitsbits.c -o $(OBJ)/splitsbits.o

clean:
	rm obj/*.o

