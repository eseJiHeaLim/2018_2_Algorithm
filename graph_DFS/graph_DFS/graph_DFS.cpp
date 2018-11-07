#include<stdio.h>
#include<stdlib.h>

#define SZ 6

struct node {
	char v;
	struct node *next;
	//BST��
	struct node *left;
	struct node*right;
};

struct node *graph[SZ];
//bst�� 
struct node * visited = 0;
//SLL�� �� ���� ����Ű�� ���������� �������� ����
struct node* stack = 0;


void addToVisited(char v)
{
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->v = v;
	new_one->left = new_one->right = 0;

	if (visited == 0)
	{
		visited = new_one;
		return;
	}
	struct node * temp = visited;

	while (1)
	{
		//���� �̷��� �� �ʿ�x
		//if (visited->left->v - 'A')
		if (temp->v > v)
		{

			if (temp->left == 0)
			{
				temp->left = new_one;
				return;
			}
			temp = temp->left;
		}
		else
		{

			if (temp->right == 0)
			{
				temp->right = new_one;
				return;
			}
			temp = temp->right;
		}
	}

}

//
//���� v�� vistied �� ������ 1�� ��ȯ
//������ 0��ȯ
//
int checkVisite(char v)
{
	struct node * temp = visited;

	while (1)
	{
		if (temp == 0)
		{
			return 0;
		}
		else if (temp->v == v)
		{
			return 1;
		}

		if (temp->v > v)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}
}

void push(char v)
{
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->v = v;
	new_one->next = 0;
	//stack(head)�� ����� �־ �Ȱ��� �۵���
	new_one->next = stack;
	stack = new_one;
	return;
}

char pop(void)
{
	if (stack == 0)
	{
		//������ ����ٴ� ǥ��
		return '-';
	}
	struct node* temp = stack;
	char v = stack->v;
	stack = stack->next;
	//���۷��� ������ �����ؼ� ������ ����
	free(temp);
	return v;

}


void addEdgeMini(char src, char dst)
{
	int idx = src - 'A';

	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->v = dst;
	new_one->next = 0;

	if (graph[idx] == 0)
	{
		graph[idx] = new_one;
		return;
	}

	struct node * temp = graph[idx];

	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new_one;
	return;
}

void addEdge(char src, char dst)
{
	addEdgeMini(src, dst);
	addEdgeMini(dst, src);
}

void performDFS(char v)
{
	//1.�ܰ�
	push(v);
	//2. �ܰ�
	while (1)
	{

		char x = pop();
		//������ ������� �׳� �Լ� ����
		if (x == '-')
		{
			return;
		}

		int res = checkVisite(x);
		if (res == 1)
		{
			//while �� ó������ ��
			continue;
		}
		printf("----> %c\n", x);

		addToVisited(x);

		int idx = x - 'A';
		struct node * temp = graph[idx];
		while (1)
		{
			if (temp == 0)
			{
				break;
			}
			if (checkVisite(temp->v) == 1)
			{
				temp = temp->next;

			}
			else
			{
				push(temp->v);
				temp = temp->next;
			}
		}
	}
}


int main(void)
{
	//�������� �������� ������ ���x
	addEdge('A', 'C');
	addEdge('C', 'B');
	addEdge('C', 'F');
	addEdge('B', 'E');
	addEdge('D', 'B');
	addEdge('D', 'F');


	performDFS('A');


	return 0;
}