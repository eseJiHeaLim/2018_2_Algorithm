#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>



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