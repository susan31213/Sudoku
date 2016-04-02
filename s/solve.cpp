#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sudoku.h"
using namespace std;

int main()
{
	Sudoku s;
	s.solve();
	cout << s.time1 << endl;
	return 0;
}
