#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct node
{
	//������ ������ �ڵ带 sll�� ��� ������
	char c;
	char *code;
	struct node * next;
};

struct node *head = 0;

struct hnode
{
	char c;
	struct hnode *left;
	struct hnode *right;
};

struct hnode * root = 0;

void addHuffCode(char c, char * code)
{
	struct node * new_one = (struct node *)malloc(sizeof(struct node));
	new_one->c = c;
	new_one->next = 0;
	new_one->code = (char *)malloc(strlen(code) + 1);
	strcpy(new_one->code, code);

	if (head == 0)
	{
		head = new_one;
	}
	else
	{
		struct node * temp = head;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_one;
	}
}

//�����ؾ� �� ���ĺ��� ������ �˾Ƴ���.
int getNumOfCodes()
{
	struct node *temp = head;
	int cnt = 0;

	while (temp != 0)
	{
		cnt++;
		temp = temp->next;
	}

	return cnt;
}


int main2(void)
{
	FILE *f = fopen("alice.encoded", "rb");
	//encoeded ������ �о ������  Ʈ���� ���� 
	//1�ܰ� ��� ���ĺ��� �ִ��� �ľ�
	char num;
	fread(&num, sizeof(char), 1, f);
	printf("There are  %d alphabets\n", num);
	//2�ܰ� �� ���ĺ��� �����Ͽ� ������ �ڵ带 ���
	for (int i = 0; i < num; i++)
	{
		char c;
		fread(&c, sizeof(char), 1, f);
		printf("%c\n", c);

		char len;
		fread(&len, sizeof(char), 1, f);

		for (int j = 0; j < len; j++)
		{
			char v;
			fread(&v, sizeof(char), 1, f);
			if (v == '0')
			{
				printf("0");

			}
			else
			{
				printf("1");
			}

		}
		printf("\n");
	}

	fclose(f);
	
}
int main1(void)
{

	addHuffCode('a', "0");
	addHuffCode('b', "01");
	addHuffCode('c', "11");

	//������ �ڵ带 ���Ͽ� �Ế�ô�
	//Ȯ���ڴ� �� ����� ���ص� �� ���� �̷��� �ϰڴٰ� �����ϱ�
	FILE *f = fopen("alice.encoded", "wb");

	//1�ܰ� . �� ��� ���ĺ������� 1����Ʈ�� ���
		//int �� ũ�Ⱑ 4�ϱ� char �� �°� 1���� ������Ŵ
	char numOfchars = (char)getNumOfCodes();
	fwrite(&numOfchars, sizeof(char), 1, f);

	//2�ܰ� �� ���ĺ��� '���ĺ�'+'���� '+'�ڵ�'�� ���
	struct node *temp = head;
	while (temp != 0)
	{
		char c = temp->c;
		fwrite(&c, sizeof(char), 1, f);
		char len = (char) strlen(temp->code);
		fwrite(&len, sizeof(char), 1, f);

		for (int i = 0; i < len; i++)
		{
			/*
			���ڰ� �ƴ� ���ڷ� �ϰ� ������
			char v;
			if (temp->code=='0')
			{
				v=0;
			}
			else if (temp->code=='1')
			{
				v=1;
			}
			fwrite(&v,sizeof(char),1,f);
			*/
			fwrite((&temp->code[i]), sizeof(char), 1, f);
		}
		temp = temp->next;
	}
	//2�ܰ踦 �ݺ�!!



	
	return 0;
}


int main3()
{

	FILE *ff = fopen("alice.encoded", "rb");
	//encoeded ������ �о ������  Ʈ���� ���� 
	//1�ܰ� ��� ���ĺ��� �ִ��� �ľ�
	char num;
	fread(&num, sizeof(char), 1, ff);
	printf("There are  %d alphabets\n", num);

	root = (struct hnode *)malloc(sizeof(struct hnode));
	root->left = root->right = 0;

	//2�ܰ� �� ���ĺ��� �����Ͽ� ������ �ڵ带 ���
	for (int i = 0; i < num; i++)
	{
		struct hnode * temp = root;
		char c;
		fread(&c, sizeof(char), 1, ff);

		char len;
		fread(&len, sizeof(char), 1, ff);


		for (int j = 0; j < len; j++)
		{
			char v;
			fread(&v, sizeof(char), 1, ff);
			if (v == 0)
			{
				//���� �����ϴµ� 
				if (temp->left = 0)
				{
					temp->left = (struct hnode *)malloc(sizeof(struct hnode));
					temp->left->left = temp->left->right = 0;
				}
				temp = temp->left;
			}
			else
			{
				if (temp->right = 0)
				{
					temp->right = (struct hnode *)malloc(sizeof(struct hnode));
					temp->right->left = temp->right->right = 0;
				}
				temp = temp->right;
			}

		}
		temp->c = c;
	}

	fclose(ff);
}


int main(void)
{

	//"aaabbb" ���ڿ��� ���Ͽ� ���
	//a : 10 
	//b:00

	//-->10101000_0000

	//���ڿ��� �⺻������ �迭��
	char *strToWrite = "aaabbb";
	char *a = "10"; // a�� ������ �ڵ�� 10
	char *b = "00"; // b�� ������ �ڵ�� 00

	FILE *f = fopen("alice.bit", "wb");

	for (int i = 0; i < strlen(strToWrite); i++)
	{
		char c = strToWrite[i];

		char *toWrite;
		if (c == 'a')
		{
			strToWrite = a;
		}
		else
		{
			toWrite = b;
		}
		for (int j = 0; j < strlen(toWrite); j++)
		{

		}
	}
	

	fclose(f);
}






















//�� ������ ��ϳ�,,,,,,,,�ٺ���,,,,,,,,,,,,,


/*
int main(void)
{
	FILE *f = fopen("alice.bin", "wb");
	//write binary


	//fwrite
	//fread
		

	//�� ����Ʈ��
	char c;
	c = 'a';
	fwrite(&c, 1, 1, f);

	c = 2;
	fwrite(&c, 1, 1, f);
	c = 0;
	fwrite(&c, 1, 1, f);
	c = 0;
	fwrite(&c, 1, 1, f);


	fclose(f);

	return 0;
}
*/