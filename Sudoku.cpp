#include "Sudoku.h"
using namespace std;

Sudoku::Sudoku()
{
	for(int i=0; i<sudokuSize;i++)
		map[i]=0;
}

Sudoku::Sudoku(const int init_map[])
{
	for(int i=0;i<sudokuSize;i++)
		map[i] = init_map[i];
}

void Sudoku::setMap(const int set_map[])
{
	for(int i=0;i<sudokuSize;i++)
		map[i] = set_map[i];
}

int Sudoku::getElement(int index)
{
	return map[index];
}

bool Sudoku::checkUnity(int arr[])
{
	int arr_unity[9]; //counter

	for(int i=0;i<9;++i)
		arr_unity[i] = 0; //初始化
	for(int i=0;i<9;++i)
	{
		if(arr[i]!=0)		//等於0(未填)的不算
			++arr_unity[arr[i]-1]; //count
	}
	for(int i=0;i<9;++i)
		if(arr_unity[i]>1)
			return false;
	return true;
}

bool Sudoku::isCorrect()
{
	bool check_result;
	int check_arr[9];
	int loc;
	int i,j;
	for(i=0;i<81;i+=9)	//check row
	{
		for(j=0;j<9;j++)
			check_arr[j] = map[i+j];
		check_result = checkUnity(check_arr);
		if(check_result == false)
			return false;
	}
	for(i=0;i<9;++i)	//check colume
	{
		for(j=0;j<9;++j)
			check_arr[j] = map[i+j*9];
		check_result = checkUnity(check_arr);
		if(check_result == false)
			return false;
	}
	for(i=0;i<9;++i)	//check cell
	{
		for(j=0;j<9;++j)
		{
			loc = 27*(i/3)+3*(i%3)+9*(j/3)+(j%3);
			check_arr[j] = map[loc];
		}
			check_result = checkUnity(check_arr);
			if(check_result == false)
				return false;
	}
	return true;
}

void Sudoku::printSudoku(int arr[])
{
	int i;
	char c;
	for(i=0;i<81;i++)
	{
		c = (i+1)%9==0?'\n':' ';	//print space or \n
		cout << arr[i] << c;
	}
}

void Sudoku::giveQuestion()
{
	int arr[81] = {5,0,8,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,1,0,6,0,0,0,2,4,2,8,0,5,0,0,9,0,3,0,0,9,0,0,4,5,7,0,6,0,0,0,0,0,8,0,0,0,0,0,9,0,6,0,0,0,0,0,0,0,4,0,7,3,0,0,0,0,0,1,0,0,0,0};
	setMap(arr);
	change();
	printSudoku(map);
}

void Sudoku::readIn()
{
	int i;
	for(i=0;i<81;i++)
		cin >> map[i];
}

void Sudoku::solve()
{
	readIn();
	if(isCorrect()==true && getNextBlank(-1) == sudokuSize) {
		cout << '1' << endl;
		printSudoku(map);
		return;
	}
	int tmpNum[sudokuSize];	//上次填數位置
	int tmpidx=0;	//上次填數位置地點
	int ansNum=0;	//已知答案組數量
	int cur=getNextBlank(-1);	//目前測試答案所在地點
	int ans[81];

	do {
		map[cur]++;	//將第一個空格+1測試
		if(map[cur] > 9)	//若測試數字超過9則回上一格測試
		{
			map[cur]=0;
			if(tmpidx<=0)	//若沒有上一格(死路)將cur設成-1(離開do while迴圈)
				cur = -1;
			else
				cur = tmpNum[--tmpidx];	//若有上一格則回上一格並將儲存上次填數位置到上次填數陣列裡
		}
		else
		{
			if(isCorrect() == true)	//若測試數字無矛盾
			{
				tmpNum[tmpidx++] = cur;		//將上次填數位置更新
				cur = getNextBlank(cur);	//移到下一個空格
				if(cur == sudokuSize)		//若找空格已經找到最後一格
				{
					ansNum++;				//已知答案數+1
					for(int i=0;i<81;i++)
						ans[i] = map[i];
					if(tmpidx<=0)			//若沒有上一格(死路)將cur設成-1(離開do while迴圈)
						cur = -1;
					else
						cur = tmpNum[--tmpidx];	//若有上一格則回上一格並將儲存上次填數位置到上次填數陣列裡
				}
			}
		}
	} while(cur>=0 && cur < sudokuSize && ansNum<2);	//若測試位置合法(不是-1) 且 還沒找完所有空格 且還沒發現第二組答案則繼續
		
	if(ansNum == 0)
		cout << '0' << endl;
	else if(ansNum > 1)
		cout << '2' << endl;
	else
	{
		cout << '1' << endl;
		printSudoku(ans);
	}

}

int Sudoku::getNextBlank(int index)
{
	do {
		index++;
	} while(index < sudokuSize && map[index] > 0);
	
	return index;
}

void Sudoku::transform()
{
	readIn();
	change();
	printSudoku(map);
}

void Sudoku::change()
{
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
}

void Sudoku::changeNum(int a, int b)
{
	int i;
	for(i=0;i<81;i++)
	{
		if(map[i]==a)	//若數字是a就換成b
			map[i]=b;
		else if(map[i]==b)	//若數字是b就換成a
			map[i]=a;
	}
}

void Sudoku::changeRow(int a, int b)
{
	int tmp[3][9] = {0};	//暫存陣列
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<9;j++)
			tmp[i][j] = map[a*3*9+i*9+j];	//將第a大列存到temp
	for(i=0;i<3;i++)
		for(j=0;j<9;j++)
			map[a*3*9+i*9+j] = map[b*3*9+i*9+j];	//將第b大列存到第a大列
	for(i=0;i<3;i++)
		for(j=0;j<9;j++)
			map[b*3*9+i*9+j] = tmp[i][j];	//將temp(a)存到大b大列
}

void Sudoku::changeCol(int a, int b)	//同changeRow 改成換Col
{
	int tmp[3][9] = {0};
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<9;j++)
			tmp[i][j] = map[a*3+i+j*9];
	for(i=0;i<3;i++)
		for(j=0;j<9;j++)
			map[a*3+i+j*9] = map[b*3+i+j*9];
	for(i=0;i<3;i++)
		for(j=0;j<9;j++)
			map[b*3+i+j*9] = tmp[i][j];
}

void Sudoku::rotate(int n)
{
	int tmp[81] = {0};
	int i;
	switch (n%4) 
	{
		case 1:	//轉90度
			for(i=0;i<9;i++)
				for(int j=0;j<9;j++)
					tmp[j*9+(8-i)] = map[i*9+j];
			break;

		case 2:	//轉180度
			for(i=0;i<9;i++)
				for(int j=0;j<9;j++)
					tmp[(8-i)*9+(8-j)] = map[i*9+j];
			break;

		case 3:	//轉270度
			for(i=0;i<9;i++)
				for(int j=0;j<9;j++)
					tmp[(8-j)*9+i] = map[i*9+j];
			break;
		default:
			break;
	}
	
	if(n%4!=0)	//若結果和原本map不同就取代
		setMap(tmp);
}

void Sudoku::flip(int n)
{
	int tmp[81] = {0};
	int i,j;
	if(n==0)
	{
		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
				tmp[(8-i)*9+j] = map[i*9+j];
	}
	else
	{
		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
				tmp[i*9+(8-j)] = map[i*9+j];
	}
	
	setMap(tmp);
}
