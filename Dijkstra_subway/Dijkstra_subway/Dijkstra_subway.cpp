#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
//1. Dilkstra table �� �ʱ�ȭ �Ѵ�
	(found=false , dist = infinite, prev)
//2. ���� ��vertex s�� ���ؼ� 
	table[s].dist =0
3. (table[i].found==false)&& minimum(table[i].dist)�� �����ϴ� vertex i�� ã�Ƽ�
4. table[i].founf=true
5/ vertex [i] �� neighbor vertex�鿡 ���ؼ� dist �� prev�� update (���� ���� �� ������ ���� ���� ��쿡��)
6. 3������ �ݺ� ... �� �̻� found == false �� vertex�� ������ ���� 

*/

int main(void)
{
	//������ �����ִ� ������ ���� ������
	FILE *f = 0;

	// ���� ����
	// R : read
	// T : text <--> ���̳ʸ� ����
	f = fopen("seoul.txt", "rt");

	char buf[100];

	while (1)
	{
		if (feof(f))
		{
			break;
		}
		fgets(buf, 99, f);
		printf("%s", buf);
		//���� ���� ���������
		buf[0] = '\0';
	}
	//�ִ� ���� ���ִ� ������ �� 99�� --> ���پ� �о� ���϶� 
	//fgets(buf, 99, f);


	// ���� �ݱ� --> �ü������ �����ִ� ������ ������ ������ ����
	fclose(f);

	return 0;
}