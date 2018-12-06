/*
	��� 1�� ���� ����������
	�̹����� 0�� ����� �������� �����Ƿ�
	���� ������ ��ȣ���� ����°���
	��ȣ���� �ƴ� ���� �ٸ�����
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

void show()
{
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
	int falg = 0;

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < SZ; j++)
		{
			if (cheese[i][j] == 2)
			{
				if (abs(i - _row) == abs(j - _col))
				{
					for (int k = 0; k < _row - i; k++)
					{
						if (cheese[i + k][j + k] == 1)
						{
							falg++;
						}
						else if (cheese[i + k][j + k] == 2)
						{
							falg --;
						}
					}
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
	if (_row < SZ )
	{
		doBacktracking(_row + 1);
	}
}

int main(void)
{
	doBacktracking(0);
	show();
	printf("%d\n", cnt);

	return 0;
}