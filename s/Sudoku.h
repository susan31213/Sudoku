#include <iostream>
#include <cstdlib>
#include <ctime>
class Sudoku {
public:
	Sudoku();
	Sudoku(const int init_map[]);
	void setMap(const int set_map[]);
	int getElement(int index);
	bool isCorrect();
	static const int sudokuSize = 81;
	void giveQuestion();
	void readIn();
	void solve();
	bool solve_check(int);
	void changeNum(int a, int b);
	void changeRow(int a, int b);
	void changeCol(int a, int b);
	void rotate(int n);
	void flip(int n);
	void transform();

private:
	bool checkUnity(int arr[]);
	int getNextBlank(int index);
	int map[sudokuSize];
	void printSudoku(int arr[]);
	void change();
};
