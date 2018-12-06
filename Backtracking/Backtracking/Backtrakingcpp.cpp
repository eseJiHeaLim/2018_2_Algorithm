#include<stdio.h>

#define SZ 5

int chessBoard[SZ][SZ]; 


int checkUpside(int i, int j)
{
	for (int k = i - 1; k >= 0; k--)
	{
		if (chessBoard[k][j] != 0)
		{
			return 1;
		}
	}
	return 0;
}

int makeAbsolute(int v)
{
	if (v < 0)
	{
		return -v;
	}
	return v;
}


int checkDiagonal(int _i, int _j)
{
	for (int i = 0; i <= _i - 1; i++)
	{
		for (int j = 0; j < SZ; j++) 
		{
			if (chessBoard[i][j] != 0)
			{
				if (makeAbsolute(i - _i) == makeAbsolute( j - _j))
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

void showChessBoard()
{
	printf("---------------------------------------\n");
	for (int i = 0; i < SZ; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			printf("%d ", chessBoard[i][j]);
		}
		printf("\n");
	}
}

void doBacktracking(int row)
{
	for (int i = 0; i < SZ; i++)
	{
		if (checkDiagonal(row, i) == 0 && checkUpside(row, i) == 0)
		{
			chessBoard[row][i] = 1;

			if (row < SZ - 1)  
			{
				doBacktracking(row + 1);
			}
			else 
			{
				showChessBoard();

			}
			chessBoard[row][i] = 0;
		}
	}
	
}

int main(void)
{
	doBacktracking(0); 

	return 0;
}