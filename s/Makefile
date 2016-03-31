all: Sudoku.o solve.cpp
	g++ -o solve solve.cpp Sudoku.o

Sudoku.o: Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp -o Sudoku.o

clean:
	rm solve *.o
