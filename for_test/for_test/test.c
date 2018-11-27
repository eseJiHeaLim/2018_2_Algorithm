#include<stdio.h>
#include<math.h>

#define SZ 4

int chess[SZ][SZ];


void showChess()
{
	printf("----------solution-----------\n");
	for (int i = 0; i < SZ; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			printf("%d ", chess[i][j]);
		}
		printf("\n");
	}
}

int checkUp(int _r, int _c)
{
	for (int i = 0; i < _r; i++)
	{
		if (chess[i][_c] == 1)
		{
			return 1;
		}
	}
	return 0;
}

int checkDiag(int _r, int _c)
{
	for (int i = 0; i < _r;i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			if (chess[i][j] == 1)
			{
				if (abs(i - _r) == abs(j - _c))
				{
					return 1;
				}
				else
				{
					break;
				}
			}
		}
	}
	return 0;
}

void doBacktracking(int _r)
{
	for (int i = 0; i < SZ; i++)
	{
		if (checkDiag(_r, i) == 0 && checkUp(_r, i) == 0)
		{
			chess[_r][i] = 1;

			if (_r < SZ - 1)
			{
				doBacktracking(_r + 1);
			}
			else
			{
				showChess();
			}
			chess[_r][i] = 0;
		}
	}
}

int main(void)
{
	doBacktracking(0);
	return 0;
}