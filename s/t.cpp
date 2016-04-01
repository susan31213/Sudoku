#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void setMap(const int set_map[]);
int getElement(int index);
bool isCorrect();
static const int sudokuSize = 81;
void giveQuestion();
void readIn();
void solve();
bool solve_check(int cur);
void changeNum(int a, int b);
void changeRow(int a, int b);
void changeCol(int a, int b);
void rotate(int n);
void flip(int n);
void transform();

bool checkUnity(int (&arr)[9]);
int getNextBlank(int index);
int map[sudokuSize];
void printSudoku(int (&arr)[81]);
void change();

int main()
{
	solve();
	return 0;
}

void setMap(const int set_map[])
{
	for(int i=0;i<sudokuSize;i++)
		map[i] = set_map[i];
}

int getElement(int index)
{
	return map[index];
}

bool checkUnity(int (&arr)[9])
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

bool isCorrect()
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

void printSudoku(int (&arr)[81])
{
	int i;
	char c;
	for(i=0;i<81;i++)
	{
		c = (i+1)%9==0?'\n':' ';	//print space or \n
		cout << arr[i] << c;
	}
}

void giveQuestion()
{
	int arr[81] = {5,0,8,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,1,0,6,0,0,0,2,4,2,8,0,5,0,0,9,0,3,0,0,9,0,0,4,5,7,0,6,0,0,0,0,0,8,0,0,0,0,0,9,0,6,0,0,0,0,0,0,0,4,0,7,3,0,0,0,0,0,1,0,0,0,0};
	setMap(arr);
	change();
	printSudoku(map);
}

void readIn()
{
	int i;
	for(i=0;i<81;i++)
		cin >> map[i];
}

void solve()
{
	readIn();
	if(isCorrect()==false) {
		cout << '0' << endl;
		return;
	}
	else if(isCorrect()==true && getNextBlank(-1) == sudokuSize) {
		cout << '1' << endl;
		printSudoku(map);
		return;
	}
	int tmpNum[sudokuSize];	//上次填數位置
	int tmpidx=0;	//上次填數位置地點
	int ansNum=0;	//已知答案組數量
	int cur=getNextBlank(-1);	//目前測試答案所在地點
	int ans[81];
	bool corr = true;
	
	do {
		corr = true;
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
			int check_arr[9];
			int loc;
			int i,j;
			
			for(i=0;i<9;i++)	//check row
				check_arr[i] = map[cur/9*9+i];
			corr = checkUnity(check_arr);
			if(corr == false)
				continue;
			for(i=0;i<9;++i)	//check colume
				check_arr[i] = map[i*9+(cur%9)];
			corr = checkUnity(check_arr);
			if(corr == false)
				continue;
			for(j=0;j<9;++j)	//check cell
			{
				loc = 27*(cur%9/3)+3*(cur%9%3)+9*(j/3)+(j%3);
				check_arr[j] = map[loc];
			}
			corr = checkUnity(check_arr);
			if(corr == false)
				continue;
			
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

bool solve_check(int cur)
{
	bool check_result,corr;
	int check_arr[9];
	int loc;
	int i,j;
	for(i=0;i<9;i++)	//check row
		check_arr[i] = map[cur/9*9+i];
	check_result = checkUnity(check_arr);
	if(check_result == false)
		corr = false;
	for(i=0;i<9;++i)	//check colume
		check_arr[i] = map[i*9+(cur%9)];
	check_result = checkUnity(check_arr);
	if(check_result == false)
		corr = false;

	for(j=0;j<9;++j)	//check cell
	{
		loc = 27*(cur%9/3)+3*(cur%9%3)+9*(j/3)+(j%3);
		check_arr[j] = map[loc];
	}
	check_result = checkUnity(check_arr);
	if(check_result == false)
		corr = false;
}

int getNextBlank(int index)
{
	do {
		index++;
	} while(index < sudokuSize && map[index] > 0);
	
	return index;
}

void transform()
{
	readIn();
	change();
	printSudoku(map);
}

void change()
{
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
}

void changeNum(int a, int b)
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

void changeRow(int a, int b)
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

void changeCol(int a, int b)	//同changeRow 改成換Col
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

void rotate(int n)
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

void flip(int n)
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

