#include<stdio.h>
#include <stdlib.h>

#define NUM_VERTEX 4


struct node {
	char data;
	struct node* next;
};


struct node*graph[NUM_VERTEX];

struct node * createNode(char _c)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data = _c;
	newNode->next = 0;

	return newNode;
}

int getIndex(char _c)
{
	return _c - 'A';
}

struct node * findLast(int n)
{
	struct node* cur = graph[n];

	while (1)
	{
		if (cur->next == 0)
		{
			return cur;
		}
		cur = cur->next;
	}
}

void addEdge(char s, char d)
{
	int whereGraph_s = getIndex(s);
	int whereGraph_d = getIndex(d);

	struct node*src = createNode(s);
	struct node* dre = createNode(d);

	if (graph[whereGraph_s] == 0)
	{
		graph[whereGraph_s] = dre;
	}
	else
	{
		struct node* lastNode = findLast(whereGraph_s);
		lastNode->next = dre;
	}

	if (graph[whereGraph_d] == 0)
	{
		graph[whereGraph_d] = src;
		return;
	}
	else
	{
		struct node* lastNode = findLast(whereGraph_d);
		lastNode->next = src;
	}
	return;
}

void showConnectedVertexes(char _c)
{
	int whereToShow = getIndex(_c);

	struct node*cur = graph[whereToShow];

	while (1)
	{
		if (cur == 0)
		{
			return;
		}
		printf("%c", cur->data);
		cur = cur->next;
	}
}

int main(void)
{
	addEdge('A', 'B');
	addEdge('B', 'D');
	addEdge('C', 'A');
	addEdge('C', 'D');
	
	showConnectedVertexes('A');
	printf("\n");
	showConnectedVertexes('B');
	printf("\n");
	showConnectedVertexes('C');
	printf("\n");
	showConnectedVertexes('D');
	return 0;
}
