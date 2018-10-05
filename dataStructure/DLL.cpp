#include<stdio.h>
#include<stdlib.h>

//DLL 노드의 구성
struct node {
	int data;
	struct node* front;
	struct node*next;
};

//DLL의 핵심 head
struct node* head = 0;

//DLL에 들어갈 노드를 생성
//반환 : 새로 만든 노드의 포인터
struct node * creatNode(int n)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	newNode->data = n;
	newNode->front = 0;
	newNode->next = 0;

	return newNode;
}

//DLL 의 마지막 노드의 위치를 알려주는 함수
//반환 : 마지막 노드의 포인터
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


//노드를 DLL에 추가 해주는 함수
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

//n이 들어있는 노드를 찾아주는 함수
//반환 : n이 들어잇는 노드의 포인터
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

//n이 들어있는 노드를 dll에서 삭제해준다.
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

//DLL의 모든 데이터를 보여주는 함수
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

//DLL 전체를 삭제해주는 함수
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


//n이 들어있는 노드를 원하는 위치where에 넣어주는 함수
//입력 : int n - 추가하고자하는 노드의 데이터
//       int where - 추가하고자하는 DLL의 노드 위치의 데이터
//       int mode - 1이면 where의 앞에다가 추가 , -1이면 where의 뒤에다가 노드를 추가한다.  
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
		printf("잘못된 모드값을 입력하셨습니다!!\n");
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