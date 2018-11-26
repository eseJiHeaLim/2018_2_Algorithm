#include<stdio.h>
#include<string.h>

#define SZ 9
void solveSudoku(int _r, int _c);

//해답의 개수
int solutionCnt = 0;

//스도쿠에 대한 정보를 저장하는 이차원배열
//스도쿠에 대한 정보를 숫자배열의 형식으로 받아와야함
int sudoku[SZ][SZ] = {
	0,0,0,0,0,0,0,9,0,
	8,0,2,9,7,0,0,0,0,
	9,0,0,2,0,0,3,0,0,
	0,0,0,0,4,9,0,5,7,
	0,1,0,0,5,0,9,2,0,
	0,7,9,1,0,0,0,0,0,
	0,0,7,0,0,2,6,0,3,
	0,0,0,0,3,8,2,0,0,
	0,2,0,5,0,0,0,0,0
};


// 내용 변경을 하지 않고 오직 읽오오기만 하는 원본 스도쿠 
int readOnlySudoku[SZ][SZ];

void initReadOnlySudoku()
{
	//readOnlySudoku배열에 주어진 sudoku를 저장한다.
	//내용을 바꾸다가도 원본으로 돌아가고 싶으면 이 함수로 원본으로 돌아간다

	//첫번W째 인수 : 카피 | 두번째 인수 :목적지 세번쨰 인수 |카피 내용 크기
	memcpy(readOnlySudoku, sudoku, SZ*SZ * sizeof(int));
}

void printSolution()
{
	solutionCnt++;
	printf("--------------------Solution # %d ---------------------\n", solutionCnt);
	for (int i = 0; i < SZ; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			printf("%d", sudoku[i][j]);
		}
		printf("\n");
	}

}

int isOK(int _r, int _c, int _value)
{
	//좌표 (_r,_c)에 값 _value가 들어갈수 있는지를 확인
	//반환 값 1 : 들어갈수 있다.
	//반환 0 : 안된다


	//상하
	for (int i = 0; i < SZ; i++)
	{
		if (sudoku[i][_c] == _value && i != _r)
		{
			// 이미 value 값을 가지므로 
			return 0;
		}
	}
	//좌우
	for (int i = 0; i < SZ; i++)
	{
		if (sudoku[_r][i] == _value && i != _c)
		{
			return 0;
		}
	}

	//region
	int region_row = _r / 3;
	int region_col = _c / 3;

	for (int i = region_row * 3; i <= region_row * 3 + 2; i++)
	{
		for (int j = region_col * 3; j <= region_col * 3 + 2; j++)
		{
			if (sudoku[i][j] == _value && i != _r && j != _c)
			{
				return 0;
			}
		}
	}
	// 어느 구역인지를 구해주는 법 
	// 현재 좌표에 3을 나누고 다시 3을 곱하면 해당 reign의 시작 좌표를 구할수 잇음
	//sudoku[_r][_c] 에 _value를 넣어도 좋다.
	return 1;
}


void checkNext(int _r, int _c)
{
	//좌표 (_r , _c)다음에 방문하여 숫자를 결정할 위치를 판단한다

	//예외적인 경우
	//마지막 까지 온 경우
	if (_r == (SZ - 1) && _c == (SZ - 1))
	{
		printSolution();
		return;
	}

	_c++;

	if (_c == SZ)
	{
		_c = 0;
		_r++;
	}
	solveSudoku(_r, _c);

}

void solveSudoku(int _r, int _c)
{
	// 좌표 (_r, _c)위치에 들어갈 숫자를 결정한다

	if (sudoku[_r][_c] > 0)
	{
		//이미 스도투 문제배열에서 해당 위치에 숫자가 이미 들어가 있음
		//그러므로 다음 칸으로 이동
		checkNext(_r, _c);
	}
	else
	{
		//스도쿠가 채워져 있지 않음 
		for (int i = 1; i <= 9; i++)
		{
			memcpy(&sudoku[_r][_c], &readOnlySudoku[_r][_c], sizeof(int)*SZ*SZ - sizeof(int)*(_r*SZ + _c));
			//좌표 (_r,_c)에 1부터 9까지 숫자를 하나씩 대입하여 체크
			if (isOK(_r, _c, i) == 1)
			{
				sudoku[_r][_c] = i;
				//다음칸으로 이동 해서 처리
				checkNext(_r, _c);
			}
		}
	}
}

int main(void)
{
	initReadOnlySudoku();

	// 맨 앞줄부터 해결 시작
	solveSudoku(0, 0);
	return 0;
}