#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 1000

struct node
{
	char c;
	int cnt;
	struct node * next;
	struct node * left;
	struct node * right;

};


struct node *head = 0;
struct node * stack = 0;

void push(int _v)
{
	struct node * new_one = (struct node *)malloc(sizeof(struct node));
	new_one->cnt = _v;
	new_one->next = 0;

	if (stack == 0)
	{
		stack = new_one;
		return;
	}
	else
	{
		struct node * temp = stack;

		while (temp->next!=0)
		{
			temp = temp->next;
		}
		temp->next = new_one;
	}
}

int pop()
{
	struct node * temp = stack;
	stack = stack->next;
	return temp->cnt;
}

struct node  * findNode(int _cnt)
{
	struct node *temp = head;

	while (1)
	{
		if (temp->next == 0)
		{
			return 0;
		}
		if (temp->cnt == _cnt)
		{
			return temp;
		}
		temp = temp->next;
	}
}

struct node  * findNextNode(struct node * find)
{
	struct node *temp = head;

	while (1)
	{
		if (temp->next == 0)
		{
			return 0;
		}
		if (temp->next->cnt == find->cnt)
		{
			return temp;
		}
		temp = temp->next;
	}
}

void deleteSLLMe(int tempdata)
{
	struct node * me = findNode(tempdata);

	if (me == head)
	{
		head = head->next;
		return;
	}
	//�Ǹ�����
	else if (me->next == 0)
	{
		findNextNode(me)->next = 0;
		return;
	}
	else
	{
		findNextNode(me)->next = me->next;
		me->next = 0;
		return;
	}
	
}

struct node * findSmallestFrequency()
{
	struct node *temp = head;
	
	int tempdata = 1000;
	while (1)
	{
		if (temp->next == 0)
		{
			break;
		}
		if (temp->cnt < tempdata)
		{
			tempdata = temp->cnt;
		}
		temp = temp->next;
	}
	struct node * data = findNode(tempdata);
	deleteSLLMe(tempdata);
	return data;

}

struct node *  createTree(struct node * _first, struct node * _second)
{
	struct node * temp = (struct node *)malloc(sizeof(struct node));
	temp->c = 0;
	temp->cnt = 0;
	temp->left = temp->next = temp->right = 0;

	if (_first->cnt > _second->cnt)
	{
		temp->left = _second;
		temp->right = _first;
	}
	else
	{
		temp->left = _first;
		temp->right = _second;
	}
	temp->cnt = _first->cnt + _second->cnt;
	return temp;
}


void inorder_Traversal(struct node * _n)
{
	if (_n != 0)
	{
		pop();

		return;
	}
	push(0);
	inorder_Traversal(_n->left);
	if ((_n->left == 0) && _n->right == 0)
	{
		//�ڵ� ������
		//���ĺ��� _n->c �� ���� code�� ����
		
	}
	push(1);
	inorder_Traversal(_n->right);
	
}

void showHuffmanTree(struct node * _htree)
{
	inorder_Traversal(_htree);
}

void addToSLL(struct node * _temp)
{
	if (head == 0)
	{
		head = _temp;
	}
	else
	{
		struct node * temp = head;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = _temp;
	}
}

struct node *buildHuffmanTree()
{
	while(1)
	{
		struct node * first = findSmallestFrequency();
		// �����°��� 
		printf("%d\n", first->cnt);


		struct node * second = findSmallestFrequency();
		printf("%d\n", second->cnt);
		//�̰� Ʈ���� ����ٴ°Ŷ� �������̴ϱ� �ϳ��� ����
		if (second == 0)
		{
			return first;
		}

		struct node * temp = createTree(first, second);

		addToSLL(temp);

	}

}

void addCharFreq(char _c, int _cnt)
{
	struct node * new_one = (struct node *)malloc(sizeof(struct node));
	new_one->c = _c;
	new_one->cnt = _cnt;
	new_one->next =new_one->left=new_one->right= 0;
	
	if (head == 0)
	{
		head = new_one;
		return;
	}
	else
	{
		struct node * temp = head;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_one;
		return;
	}
}
// ���� ���� �󵵼��� �ΰ��� ����� ���� 
void miniheap()
{

}

int readFile_countAlphabet()
{
	FILE * f = 0;
	f = fopen("c:||alice.txt", "rt");
	char buf[max];
	char ch;
	int cnt = 0;
	while (1)
	{
		if (feof(f) != 0)
		{
			break;
		}
		fgets(buf, max,f);

		printf("%s", buf); // �� ���� �о� ����մϴ�. 

		for (int i = 0; i < strlen(buf); i++) // �� ���� ���� ��ŭ �ݺ����� �����ϴ�.
		{
			ch = buf[i]; // �� ���ڸ� �����մϴ�.
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) // ���ĺ��ΰ�?
			{
				cnt++;
			}
		}
	}
	return cnt;
}

void initTestData(void)
{
	addCharFreq('a', 10);
	addCharFreq('b', 300);
	addCharFreq('c', 1);
	addCharFreq('k', 50);
	addCharFreq('x', 20);

}
void checkHuffmanTree(struct node * _n)
{
	if (_n != 0)
	{

		return;
	}
	inorder_Traversal(_n->left);
	printf("%d\n", _n->cnt);
	inorder_Traversal(_n->right);

}
int main(void)
{
	initTestData();

	struct node  * res = buildHuffmanTree();
	printf("%d", res->left->cnt);
	checkHuffmanTree(res);
	/*
	// ���ڶ� �󵵼� ���� sll�� ������ �־����
	int res = 0;
	res = readFile_countAlphabet();
	printf("%d\n", res);
	return 0;
	*/

	// �Ʒ����� �����ð���

	return 0;
}