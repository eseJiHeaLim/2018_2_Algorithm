#include<stdio.h>
#include<stdlib.h>

// SLL �� ������ �� ������ ����ġ�� ���� ������ ����� ����
struct node {
	int data;
	struct node* next;
};

//SLL �� �ٽ��� ���� ���� ����Ű��  ��� ����
struct node* head = 0;

//SLL ���ο� ��带 ����� �Լ��� �����͸� �����ϴ� �Լ�
//��ȯ : ���θ��� ����� ������
struct node* createNode(int n)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	newNode->data = n;
	newNode->next = 0;

	return newNode;
}

//���� SLL�� ���� ������ ��带 ã�� �Լ�
// ��ȯ : ������ ����� ������
struct node* findLastNode(struct node* head)
{
	struct node* cur = head;

	while (1)
	{
		if (cur->next == 0)
		{
			return cur;
		}
		cur = cur->next;
	}
}

//SLL�� ��带 �߰��ϴ� �Լ�
void addNode(int n)
{
	struct node* newNode = createNode(n);

	if (head == 0)
	{
		head = newNode;
		return;
	}
	else
	{
		struct node * lastNode = findLastNode(head);
		lastNode->next = newNode;
		return;
	}
}

//n�� ����Ǿ� �ִ� ��带 ã���ִ� �Լ�
//��ȯ : n�� ����ִ� ����� ������
struct node* findNode(int n)
{
	struct node* cur = head;

	while (1)
	{
		if (cur->data == n)
		{
			return cur;
		}
		cur = cur->next;
	}
}

struct node* findDelNextNode(int n)
{
	struct node* cur = head;

	while (1)
	{
		if (cur->next->data == n)
		{
			return cur;
		}
		cur = cur->next;
	}

}


// n�� ����Ǿ��ִ� ��带 ���� �ϴ� �Լ�
void deleteNode(int n)
{
	struct node* delNode = head;

	//���� �ϰ����ϴ� ��尡 ����� ���
	if (head->data == n)
	{
		head = head->next;
		free(delNode);
		return;
	}
	else
	{
		struct node* del_next = findDelNextNode(n);
		delNode = del_next->next;
		del_next->next = delNode->next;
		free(delNode);
		return;
	}
	
}


//SLL ��ü�� ���ִ� �Լ�
void destory(void)
{
	struct node* cur = head;

	while (1)
	{
		if (head == 0)
		{
			return;
		}
		head = head->next;
		free(cur);
		cur = head;
	}
}

//where�� ���� ����ִ� ����� �ڿ� n�� ���� ����	��带 ����� ���� �ֱ�
void insertNode(int n, int where)
{
	struct node* newNode = createNode(n);
	struct node* whereInsert = findNode(where);

	newNode->next = whereInsert->next;
	whereInsert->next = newNode;
	return;
}

//SLL �� �� ���� ������� ���� �����ִ� �Լ�
void displaySLL(void)
{
	struct node* cur = head;
	while (1)
	{
		if (cur==0)
		{
			break;
		}
		printf("%d\n", cur->data);
		cur = cur->next;

	}
}

int main(void)
{
	addNode(1);
	addNode(2);
	addNode(3);
	addNode(4);

	displaySLL();

	destory();

	addNode(5);
	addNode(6);

	displaySLL();

	insertNode(10, 5);

	displaySLL();

	deleteNode(10);

	displaySLL();

	return 0;
}


