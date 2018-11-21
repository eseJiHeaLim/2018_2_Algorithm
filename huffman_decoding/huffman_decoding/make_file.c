#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct node
{
	//들어오는 허프만 코드를 sll로 모두 저장함
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

//저장해야 할 알파벳의 개수를 알아낸다.
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
	//encoeded 파일을 읽어서 허프만  트리를 복구 
	//1단계 몇개의 알파벳이 있는지 파악
	char num;
	fread(&num, sizeof(char), 1, f);
	printf("There are  %d alphabets\n", num);
	//2단계 각 알파베을 복수하여 허프만 코드를 출력
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

	//허프만 코드를 파일에 써봅시다
	//확장자는 내 맘대로 정해도 됨 내가 이렇게 하겠다고 했으니깐
	FILE *f = fopen("alice.encoded", "wb");

	//1단계 . 총 몇개의 알파벳인지를 1바이트로 기록
		//int 는 크기가 4니깐 char 에 맞게 1개로 변형시킴
	char numOfchars = (char)getNumOfCodes();
	fwrite(&numOfchars, sizeof(char), 1, f);

	//2단계 각 알파벳을 '알파벳'+'길이 '+'코드'로 기록
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
			문자가 아닌 숫자로 하고 싶은때
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
	//2단계를 반복!!



	
	return 0;
}


int main3()
{

	FILE *ff = fopen("alice.encoded", "rb");
	//encoeded 파일을 읽어서 허프만  트리를 복구 
	//1단계 몇개의 알파벳이 있는지 파악
	char num;
	fread(&num, sizeof(char), 1, ff);
	printf("There are  %d alphabets\n", num);

	root = (struct hnode *)malloc(sizeof(struct hnode));
	root->left = root->right = 0;

	//2단계 각 알파베을 복수하여 허프만 코드를 출력
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
				//왼쪽 가야하는데 
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

/*
char *a = "100"; // a의 허프만 코드는 10
char *b = "11"; // b의 허프만 코드는 00
char *c = "101";
char *d = "0";
*/

char * codeTable[4] = { "100","11","101","0" };

int main92(void)
{

	//"aaabbb" 문자열을 파일에 기록
	//a : 10 
	//b:00

	//-->10101000_0000

	//문자열은 기본적으로 배열임
	char *strToWrite = "abbccdccbba";

	FILE *f = fopen("alice.bit", "wb");


	// 비트 개수를 기록할 공간 (4byte )을 비워둔다
	fseek(f, 4, SEEK_SET);

	char ineByteBuffer = 0; //초기값은 0
	int shiftCnt = 7; //얘가 0이면 1바이트가 채워진거임
	int numOfBits = 0;

	
	for (int i = 0; i < strlen(strToWrite); i++)
	{
		char c = strToWrite[i];
		char *code = codeTable[c - 'a'];
		
		for (int j = 0; j < strlen(code); j++)
		{
			//bitvalue는 쓰고하는 비트의 값
			char bitValue = 0;

			//0일때는 아무것도 안해도 됨
			if (code[j] == '1')
			{
				//맨 오른쪽이 자동으로 1로됨 
				bitValue = 1;
				bitValue = bitValue << shiftCnt;
				ineByteBuffer = ineByteBuffer | bitValue;
			}
			shiftCnt -=1;
			numOfBits += 1; //기록된 비트 개수를 저장

			if (shiftCnt < 0)
			{
				fwrite(&ineByteBuffer, sizeof(char), 1, f);
				shiftCnt = 7;
				ineByteBuffer = 0;
			}
		}
	}
	
	if (shiftCnt < 7)
	{
		fwrite(&ineByteBuffer, sizeof(char), 1, f);
	}
	//파일의 맨 처음으로 돌아가서
	//비트의 개수를 쓴다
	fseek(f, 0, SEEK_SET);
	fwrite(&numOfBits, sizeof(int), 1, f);

	fclose(f);
}



//비트스트림 파일을 열어서 , 파일 내용을 읽어내어 
//코드 스트링을 출력
int main(void)
{
	FILE *f = fopen("alice.bit", "rb");

	int numOfBits = 0;
	fread(&numOfBits, sizeof(int), 1, f);

	printf("읽을 비트 수 : %d\n", numOfBits);

	char andMask = 0x80;

	while (1)
	{
		char readBuf;
		int n = fread(&readBuf, sizeof(char), 1, f);
		//파일에서 읽기 실패의 경우 도 생각
		if (n <= 0)
		{
			break;

		}

		while (1)
		{
			if ((readBuf&andMask) == 0)
			{
				printf("0");
			}
			else
			{
				printf("1");
			}

			//마스크에 오른쪽 시프트하는것은  위험한 일이다
			//andMask = andMask >> 1;
			//하지만 이렇게 하면 됨
			numOfBits -= 1;
			andMask = (andMask >> 1) & 0x7f;
			//readBuf = readBuf << 1;

			if (andMask == 0||numOfBits<=0)
			{
				andMask = 0x80;
				break;
			}
		}
	}

	fclose(f);

	return 0;
}

















//다 날리면 어떻하냐,,,,,,,,바보야,,,,,,,,,,,,,


/*
int main(void)
{
	FILE *f = fopen("alice.bin", "wb");
	//write binary


	//fwrite
	//fread
		

	//한 바이트임
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