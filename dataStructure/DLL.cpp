#include<stdio.h>
#include<stdlib.h>

//DLL ����� ����
struct node {
	int data;
	struct node* front;
	struct node*next;
};

//DLL�� �ٽ� head
struct node* head = 0;

//DLL�� �� ��带 ����
//��ȯ : ���� ���� ����� ������
struct node * creatNode(int n)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	newNode->data = n;
	newNode->front = 0;
	newNode->next = 0;

	return newNode;
}

//DLL �� ������ ����� ��ġ�� �˷��ִ� �Լ�
//��ȯ : ������ ����� ������
struct node* findLast(void)
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


//��带 DLL�� �߰� ���ִ� �Լ�
void addNode(int n)
{
	struct node * newNode = creatNode(n);

	if (head == 0)
	{
		head = newNode;
		return;
	}

	struct node * lastNode = findLast();

	lastNode->next = newNode;
	newNode->front = lastNode;
	
	return;
}

//n�� ����ִ� ��带 ã���ִ� �Լ�
//��ȯ : n�� ����մ� ����� ������
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

//n�� ����ִ� ��带 dll���� �������ش�.
void deleteNode(int n)
{
	struct node*del = findNode(n);
	
	if (del == head)
	{
		if (head->next == 0)
		{
			head == 0;
			free(del);
			return;
		}
		else
		{
			head = head->next;
			head->front = 0;
			free(del);
			return;
		}
		
	}
	else if (del->next == 0)
	{
		del->front->next = 0;
		free(del);
	}
	else
	{
		del->front->next = del->next;
		del->next->front = del->front;
		free(del);
	}
}

//DLL�� ��� �����͸� �����ִ� �Լ�
void display(void)
{
	struct node* cur = head;
	
	if (head == 0)
	{
		return;
	}

	while (1)
	{
		printf("%d\n", cur->data);
		if (cur->next == 0)
		{
			return;
		}
		

		cur = cur->next;
	}
}

//DLL ��ü�� �������ִ� �Լ�
void destoryDLL(void)
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


//n�� ����ִ� ��带 ���ϴ� ��ġwhere�� �־��ִ� �Լ�
//�Է� : int n - �߰��ϰ����ϴ� ����� ������
//       int where - �߰��ϰ����ϴ� DLL�� ��� ��ġ�� ������
//       int mode - 1�̸� where�� �տ��ٰ� �߰� , -1�̸� where�� �ڿ��ٰ� ��带 �߰��Ѵ�.  
void insertNode(int n , int where, int mode)
{
	struct node* newNode = creatNode(n);
	struct node* whereInsert = findNode(where);

	if (mode == 1)
	{
		if (whereInsert == head)
		{
			
				newNode->next = head;
				head->front = newNode;
				head = newNode;
				return;
			
		}
		else
		{
			newNode->next = whereInsert;
			whereInsert->front->next = newNode;
			newNode->front = whereInsert->front;
			whereInsert->front = newNode;
			return;
		}
	}
	else if (mode == -1)
	{
		if (whereInsert == head)
		{
			if (head->next == 0)
			{
				head->next = newNode;
				newNode->front = head;
				return;
			}
			else
			{
				head->next->front = newNode;
				newNode->next = head->next;
				newNode->front = head;
				head->next = newNode;
				return;
			}
		}
		else
		{
			if (whereInsert->next == 0)
			{
				whereInsert->next = newNode;
				newNode->front = whereInsert;
				return;
			}
			else
			{
				whereInsert->next->front = newNode;
				newNode->next = whereInsert->next;
				newNode->front = whereInsert;
				whereInsert->next = newNode;
				return;
			}
		}
	}
	else
	{
		printf("�߸��� ��尪�� �Է��ϼ̽��ϴ�!!\n");
		return; 
	}
}

int main(void)
{
	
	addNode(1);
	addNode(2);
	addNode(3);
	addNode(4);

	display();


	insertNode(100, 1, -1);

	display();
	return 0;
}