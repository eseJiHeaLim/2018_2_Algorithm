#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct edge {
	int src;
	int dst;
	int w;
	struct edge *next;
};

struct vertex {
	int v;
	int w;
	struct vertex * next;
	struct edge * connect;
};

struct dijkstra
{
	char v;
	int F;
	int dst;
	char pre;
};

struct dijkstra * table = 0;
struct vertex * graph = 0;
struct vertex * visited = 0;
struct vertex * stack = 0;
struct vertex * queue = 0;

int checkVertex(int v)
{
	struct vertex * temp = graph;

	while (1)
	{
		if (temp == 0)
		{
			return 0;
		}
		if (temp->v == v)
		{
			return 1;
		}
		temp = temp->next;
	}
}

void addVertex(int v, int w)
{
	if (checkVertex(v) == 1)
	{
		return;
	}
	else
	{
		struct vertex * new_one = (struct vertex *)malloc(sizeof(struct vertex));
		new_one->v = v;
		new_one->next = 0;
		new_one->connect = 0;
		new_one->w = w;

		if (graph == 0)
		{
			graph = new_one;
			return;
		}
		else
		{
			struct vertex * temp = graph;

			while (temp->next != 0)
			{
				temp = temp->next;
			}
			temp->next = new_one;
		}
	}
}

struct vertex * findVertex(int v)
{
	struct vertex * temp = graph;

	while (1)
	{
		if (temp == 0)
		{
			return 0;
		}
		if (temp->v == v)
		{
			return temp;
		}
		temp = temp->next;
	}
}

void addEdgemini(int src, int dst, int w)
{
	struct edge * new_one = (struct edge *)malloc(sizeof(struct edge));
	new_one->dst = dst;
	new_one->next = 0;
	new_one->w = w;

	struct edge * idxsrc = findVertex(src)->connect;

	if (findVertex(src)->connect == 0)
	{
		findVertex(src)->connect = new_one;
		return;
	}
	else
	{
		struct edge * temp = idxsrc;

		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_one;

	}

}

void addEdge(int v1, int v2, int w)
{
	addVertex(v1, w);
	addVertex(v2, w);

	addEdgemini(v1, v2, w);
	addEdgemini(v2, v1, w);

}

int cntVertex()
{
	struct vertex * temp = graph;
	int vcnt = 0;
	while (1)
	{
		if (temp->next == 0)
		{
			return vcnt;
		}
		vcnt++;
		temp = temp->next;
	}

}

void initTable()
{
	int vcnt = cntVertex();

	table = (struct dijkstra *)malloc(sizeof(struct dijkstra)*vcnt);

	struct vertex * temp = graph;

	for (int i = 0; i < vcnt; i++)
	{
		table[i].v = temp->v;
		if (temp->next != 0)
		{
			temp = temp->next;
		}

		table[i].dst = 20000;
		table[i].F = 0;
		table[i].pre = 0;


	}
}

int tableIdx(int v)
{
	int vcnt = cntVertex();
	for (int i = 0; i < vcnt; i++)
	{
		if (table[i].v == v)
		{
			return i;
		}
	}
}

int findNeibor()
{
	int vcnt = cntVertex();
	int small = 200000000;
	int smallIdx = -1;

	for (int i = 0; i < vcnt; i++)
	{
		if (table[i].F == 0 && table[i].dst < small)
		{
			small = table[i].dst;
			smallIdx = i;
		}
	}
	return smallIdx;
}

void dijkstra(int start)
{
	int vcnt = cntVertex();
	int idx = tableIdx(start);
	table[start].dst = 0;

	while (1)
	{
		int x = findNeibor();
		if (x == -1)
		{
			return;
		}
		table[x].F = 1;


		for (int i = 0; i < vcnt; i++)
		{
			if (table[i].dst > table[i].dst + table[x].dst)
			{
				table[i].dst = table[i].dst + table[x].dst;
				table[i].pre = table[x].v;
			}
		}
	}
}

void push(int v)
{
	struct vertex * new_one = (struct vertex *)malloc(sizeof(struct vertex));
	new_one->v = v;
	new_one->next = 0;

	new_one->next = stack;
	stack = new_one;
	return;
}

int pop()
{
	if (stack == 0)
	{
		return -888;
	}

	struct vertex * temp = stack;
	temp = stack;
	stack = stack->next;
	return temp->v;
}


void addVisited(int t)
{
	struct vertex * new_one = (struct vertex *)malloc(sizeof(struct vertex));
	new_one->v = t;
	new_one->next = 0;

	if (visited == 0)
	{
		visited = new_one;
		return;
	}
	else
	{
		struct vertex * temp = visited;
		while (temp->next != 0)

		{
			temp = temp->next;
		}
		temp->next = new_one;
	}
}

int chedckVisited(int t)
{
	struct vertex * temp = visited;
	while (1)
	{
		if (temp == 0)
		{
			return 0;
		}
		if (temp->v == t)
		{
			return 1;
		}
		temp = temp->next;
	}
}

int cnt = 0;
void DFS(int start)
{
	push(start);

	while (1)
	{
		int x = pop();
		if (x == -888)
		{
			return;
		}

		if (chedckVisited(x) == 1)
		{
			continue;
		}

		cnt++;

		addVisited(x);

		struct edge *temp = findVertex(x)->connect;
		while (temp->next != 0)
		{
			if (temp->next == 0)
			{
				return;
			}
			if (chedckVisited(temp->dst) == 0)
			{
				push(temp->dst);
				temp = temp->next;
			}
			else
			{
				temp = temp->next;
			}
		}


	}
}
void enqueue(int v)
{
	struct vertex * new_one = (struct vertex *)malloc(sizeof(struct vertex));
	new_one->v = v;
	new_one->next = 0;

	struct vertex * temp = queue;

	if (queue == 0)
	{
		queue = new_one;
	}
	else
	{
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_one;
	}
}

int dequeue()
{
	if (queue == 0)
	{
		return -888;
	}

	struct vertex * temp = queue;
	temp = queue;
	queue = queue->next;
	return temp->v;
}

void BFS(int start)
{
	enqueue(start);

	while (1)
	{
		int x = dequeue();
		if (x == -888)
		{
			return;
		}

		if (chedckVisited(x) == 1)
		{
			continue;
		}

		cnt++;

		addVisited(x);

		struct edge *temp = findVertex(x)->connect;
		while (temp->next != 0)
		{
			if (temp->next == 0)
			{
				return;
			}
			if (chedckVisited(temp->dst) == 0)
			{
				enqueue(temp->dst);
				temp = temp->next;
			}
			else
			{
				temp = temp->next;
			}
		}


	}
}
int main(void)
{
	FILE *f = 0;

	f = fopen("mid_data.txt", "rt");

	while (!feof(f))
	{
		int v1, v2, w;

		fscanf(f, "%d %d %d", &v1, &v2, &w);

		addEdge(v1, v2, w);

		//printf("%d %d %d \n", v1, v2, w);

		if (v1 == -1 && v2 == -1 && w == -1)
		{
			fclose(f);
			break;
		}
	}
	//DFS(2);
	//printf("Question1 : %d\n", cnt);

	BFS(1);

	printf("Question2 : %d\n", cnt);

	printf("Question3 : 알고리즘 50시간 공부하겠습니다!\n");
	initTable();
	printf("Question4 : 시험끝나고 꼭 성공시키겠습니다\n");
	dijkstra(1);

	int vcnt = cntVertex();
	for (int i = 0; i < vcnt; i++)
	{
		printf("%c %d %d %c\n", table[i].v, table[i].dst, table[i].F, table[i].pre);
	}

	return 0;
}