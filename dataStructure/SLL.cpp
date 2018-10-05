#include<stdio.h>
#include<stdlib.h>

// SLL 의 데이터 와 다음을 가르치는 값을 저장할 노드의 형식
struct node {
	int data;
	struct node* next;
};

//SLL 의 핵심은 가장 앞을 가르키는  헤드 선언
struct node* head = 0;

//SLL 새로운 노드를 만드는 함수고 데이터를 저장하는 함수
//반환 : 새로만든 노드의 포인터
struct node* createNode(int n)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	newNode->data = n;
	newNode->next = 0;

	return newNode;
}

//현재 SLL의 가장 마지막 노드를 찾는 함수
// 반환 : 마지막 노드의 포인터
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

//SLL에 노드를 추가하는 함수
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

//n이 저장되어 있는 노드를 찾아주는 함수
//반환 : n이 들어있는 노드의 포인터
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


// n이 저장되어있는 노드를 삭제 하는 함수
void deleteNode(int n)
{
	struct node* delNode = head;

	//삭제 하고자하는 노드가 헤드인 경우
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


//SLL 전체를 없애는 함수
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

//where의 값이 들어있는 노드의 뒤에 n의 값을 갖는	노드를 만들어 집러 넣기
void insertNode(int n, int where)
{
	struct node* newNode = createNode(n);
	struct node* whereInsert = findNode(where);

	newNode->next = whereInsert->next;
	whereInsert->next = newNode;
	return;
}

//SLL 에 든 값을 순서대로 전부 보여주는 함수
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


