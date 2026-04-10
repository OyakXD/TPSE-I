SRC := src
INC := inc
OBJ := obj
BIN := bin

CC := gcc

release: countbit splitsbits deslocation

countbit: src/countbit.c
	$(CC) $(SRC)/countbit.c -Iinc -o $(OBJ)/countbit.o

splitsbits: src/splitsbits.c
	$(CC) $(SRC)/splitsbits.c -Iinc -o $(OBJ)/splitsbits.o

deslocation: src/deslocation.c
	$(CC) $(SRC)/deslocation.c -Iinc -o $(OBJ)/deslocation.o

clean:
	rm $(OBJ)/*.o $(BIN)/app
