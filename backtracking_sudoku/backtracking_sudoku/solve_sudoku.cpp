#include<stdio.h>
#include<string.h>

#define SZ 9
void solveSudoku(int _r, int _c);

//�ش��� ����
int solutionCnt = 0;

//������ ���� ������ �����ϴ� �������迭
//������ ���� ������ ���ڹ迭�� �������� �޾ƿ;���
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


// ���� ������ ���� �ʰ� ���� �п����⸸ �ϴ� ���� ������ 
int readOnlySudoku[SZ][SZ];

void initReadOnlySudoku()
{
	//readOnlySudoku�迭�� �־��� sudoku�� �����Ѵ�.
	//������ �ٲٴٰ��� �������� ���ư��� ������ �� �Լ��� �������� ���ư���

	//ù��W° �μ� : ī�� | �ι�° �μ� :������ ������ �μ� |ī�� ���� ũ��
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
	//��ǥ (_r,_c)�� �� _value�� ���� �ִ����� Ȯ��
	//��ȯ �� 1 : ���� �ִ�.
	//��ȯ 0 : �ȵȴ�


	//����
	for (int i = 0; i < SZ; i++)
	{
		if (sudoku[i][_c] == _value && i != _r)
		{
			// �̹� value ���� �����Ƿ� 
			return 0;
		}
	}
	//�¿�
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
	// ��� ���������� �����ִ� �� 
	// ���� ��ǥ�� 3�� ������ �ٽ� 3�� ���ϸ� �ش� reign�� ���� ��ǥ�� ���Ҽ� ����
	//sudoku[_r][_c] �� _value�� �־ ����.
	return 1;
}


void checkNext(int _r, int _c)
{
	//��ǥ (_r , _c)������ �湮�Ͽ� ���ڸ� ������ ��ġ�� �Ǵ��Ѵ�

	//�������� ���
	//������ ���� �� ���
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
	// ��ǥ (_r, _c)��ġ�� �� ���ڸ� �����Ѵ�

	if (sudoku[_r][_c] > 0)
	{
		//�̹� ������ �����迭���� �ش� ��ġ�� ���ڰ� �̹� �� ����
		//�׷��Ƿ� ���� ĭ���� �̵�
		checkNext(_r, _c);
	}
	else
	{
		//������ ä���� ���� ���� 
		for (int i = 1; i <= 9; i++)
		{
			memcpy(&sudoku[_r][_c], &readOnlySudoku[_r][_c], sizeof(int)*SZ*SZ - sizeof(int)*(_r*SZ + _c));
			//��ǥ (_r,_c)�� 1���� 9���� ���ڸ� �ϳ��� �����Ͽ� üũ
			if (isOK(_r, _c, i) == 1)
			{
				sudoku[_r][_c] = i;
				//����ĭ���� �̵� �ؼ� ó��
				checkNext(_r, _c);
			}
		}
	}
}

int main(void)
{
	initReadOnlySudoku();

	// �� ���ٺ��� �ذ� ����
	solveSudoku(0, 0);
	return 0;
}