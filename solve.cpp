#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sudoku.h"
using namespace std;

int main()
{
	Sudoku s;
	s.readIn();
	s.solve();
	return 0;
}
