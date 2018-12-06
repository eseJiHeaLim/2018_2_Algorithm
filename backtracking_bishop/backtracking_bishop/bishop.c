/*
	
	bishop_1 
	비숍은 대각선으로만 이동을하며 
	체스판의 0인 부분은 말을 놓을수 없는 구역임

*/


#include <stdio.h>
#include <math.h>

#define SZ 5
int cheese[SZ][SZ] = {
	1, 1, 0, 1, 1,
	0 ,1 ,0 ,0 ,0,
	1 ,0 ,1 ,0, 1,
	1, 0 ,0 ,0 ,0,
	1, 0, 1, 1, 1
};

int cnt;

void show()
{
	printf("---------sol------------\n");
	for (int i = 0; i < SZ; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			printf("%d ", cheese[i][j]);
		}

		printf("\n");
	}
}


int checkOk(int _row, int _col)
{

	//대각선
	for (int i = 0; i< _row; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			if (cheese[i][j] == 2)
			{
				if (abs(i - _row) == abs(j - _col))
				{
					return 0;
				}
			}
		}
	}

	return 1;
}

void doBatracking(int _row)
{
	for (int i = 0; i < SZ; i++)
	{
		if (cheese[_row][i] == 1)
		{
			if (checkOk(_row, i) == 1)
			{
				cheese[_row][i] =2;
				cnt++;
				
				//cheese[_row][i] =1;
			}
		}
	}
	if (_row < SZ - 1)
	{
		doBatracking(_row + 1);
	}
}

int main(void)
{

	doBatracking(0);

	printf("%d", cnt);

	return 0;
}
