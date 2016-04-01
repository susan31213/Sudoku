#include <iostream>
#include <cstdlib>
#include <ctime>
class Sudoku {
public:
	Sudoku();
	Sudoku(const int init_map[]);
	void setMap(const int (&set_map)[81]);
	int getElement(int index);
	bool isCorrect();
	static const int sudokuSize = 81;
	void giveQuestion();
	void readIn();
	void solve();
	void changeNum(int a, int b);
	void changeRow(int a, int b);
	void changeCol(int a, int b);
	void rotate(int n);
	void flip(int n);
	void transform();

private:
	bool checkUnity(int (&arr)[9]);
	int getNextBlank(int index);
	int map[sudokuSize];
	void printSudoku(int (&arr)[81]);
	void change();
};
