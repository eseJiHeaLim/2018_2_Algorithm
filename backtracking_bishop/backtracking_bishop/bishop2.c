/*
	비숍 1과 같은 문제이지만 
	이번에는 0을 통과해 놓을수가 없으므로 
	벽이 있으면 보호막이 생기는거임
	보호막이 아닌 경우와 다른거임
*/

#include <stdio.h>
#include <math.h>

#define SZ 5
int cnt;

int cheese[SZ][SZ] = {
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,0,0,0,
	0,0,0,0,0
};

int checkOk(int _row, int _col)
{
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			if (cheese[i][j] == 2)
			{
				if (abs(i - _row) == abs(j - _col))
				{
					//대각선임
					for (int k = 0; k < _row - i; k++)
					{
						if (cheese[i + k][j + k] == 1)
						{
							return 1;
						}
					}
					return 0;
				}
			}
		}
	}
	return 1;
}

void doBacktracking(int _row)
{
	for (int i = 0; i < SZ; i++)
	{
		if (cheese[_row][i] == 0)
		{
			if (checkOk(_row, i) == 1)
			{
				cheese[_row][i] = 2;
				cnt++;
			}
		}
	}
	if (_row < SZ - 1)
	{
		doBacktracking(_row + 1);
	}
}

int main(void)
{
	doBacktracking(0);

	printf("%d\n", cnt);

	return 0;
}