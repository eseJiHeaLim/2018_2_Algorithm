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
	int family;
	struct vertex * next;
	struct edge * connected;
};

struct dijkstra
{
	int vertex;
	int found;
	int dist;
	int prev;
};

struct dijkstra * dtable = 0;
struct edge * edges = 0;
struct vertex * graph = 0;
struct vertex * stack_visited = 0;
struct vertex * stack = 0;
struct vertex * queue = 0;
struct vertex * queue_visited = 0;
struct edge * MSTedgeArry;
struct vertex * Dijkstra_visited = 0;

int NUM1_value;
int NUM2_value;
int NUM3_value;
int NUM4_value[2];


int howMAntVvertexs(void)
{
	int cnt = 0;
	struct vertex * temp = graph;

	while (temp != 0)
	{
		cnt += 1;
		temp = temp->next;
	}
	return cnt;
}

int checkVertex(int v)
{
	struct vertex * temp = graph;

	while (temp != 0)
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
	return 0;
}


struct vertex * findVertex(int v)
{
	struct vertex * temp = graph;

	while (temp != 0)
	{
		if (temp->v == v)
		{
			return temp;
		}
		temp = temp->next;
	}
}

void addVertex(int v)
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
		new_one->family = v;
		new_one->connected = 0;


		if (graph == 0)
		{
			graph = new_one;
			return;
		}
		else
		{
			struct vertex * temp = graph;

			while (1)
			{
				if (temp->next == 0)
				{
					temp->next = new_one;
					return;
				}
				temp = temp->next;
			}
		}
	}
}

void addEdge(int v1, int v2, int weight)
{
	addVertex(v1);
	addVertex(v2);

	struct edge * new_one = (struct edge*)malloc(sizeof(struct edge));
	new_one->src = v1;
	new_one->dst = v2;
	new_one->w = weight;
	new_one->next = 0;

	if (edges == 0)
	{
		edges = new_one;
		return;
	}
	else
	{
		struct edge * temp = edges;

		while (1)
		{
			if (temp->next == 0)
			{
				temp->next = new_one;
				return;
			}
			temp = temp->next;
		}
	}
}

void readDataFile(void)
{
	FILE *f = 0;

	f = fopen("my2_data.txt", "rt");

	while (!feof(f))
	{
		int v1, v2, w;

		fscanf(f, "%d %d %d", &v1, &v2, &w);
		if (v1 == -1 && v2 == -1 && w == -1)
		{
			
			break;
		}
		addEdge(v1, v2, w);

		//printf("%d %d %d \n", v1, v2, w);
	}
	fscanf(f, "%d", &NUM1_value);
	fscanf(f, "%d", &NUM2_value);
	fscanf(f, "%d", &NUM3_value);
	fscanf(f, "%d %d", &NUM4_value[0], &NUM4_value[1]);
	fclose(f);
	return;
}

void addToGraph(struct vertex *v1, struct vertex *v2, int weight)
{

	struct edge * new_one = (struct edge *)malloc(sizeof(struct edge));
	new_one->dst = v2->v;
	new_one->next = 0;
	new_one->w = weight;


	struct edge * temp = v1->connected;

	if (temp == 0)
	{
		v1->connected = new_one;
		return;
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

void processGraph(void)
{
	struct edge * edgeTemp = edges;

	while (edgeTemp != 0)
	{
		struct vertex *v1 = findVertex(edgeTemp->src);
		struct vertex *v2 = findVertex(edgeTemp->dst);
		addToGraph(v1, v2, edgeTemp->w);
		addToGraph(v2, v1, edgeTemp->w);

		edgeTemp = edgeTemp->next;
	}
}


/*
----------DFS--------------------
*/

void push(int v)
{
	struct vertex * new_one = (struct vertex*)malloc(sizeof(struct vertex));
	new_one->v = v;
	new_one->next = 0;

	new_one->next = stack;
	stack = new_one;
	return;
}

int pop(void)
{
	if (stack == 0)
	{
		return -888;
	}
	struct vertex* temp = stack;
	int v = stack->v;
	stack = stack->next;
	free(temp);
	return v;

}

void addToVisited(int v)
{
	struct vertex *new_one = (struct vertex *)malloc(sizeof(struct vertex));
	new_one->v = v;
	new_one->next = 0;

	if (stack_visited == 0)
	{
		stack_visited = new_one;
		return;
	}
	struct vertex * temp = stack_visited;
	
	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new_one;
	return;

}

int checkVisite(int _v)
{
	struct vertex * temp = stack_visited;

	while (temp != 0)
	{
		if (temp == 0)
		{
			return 0;
		}
		if (temp->v == _v)
		{
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

void performDFS(int v)
{
	int cnt = -1;

	push(v);

	while (1)
	{

		int x = pop();

		if (x == -888)
		{
			printf("question1: %d\n", cnt);
			return;
		}

		int res = checkVisite(x);
		if (res == 1)
		{

			continue;
		}

		cnt++;
		addToVisited(x);

		struct edge * temp = findVertex(x)->connected;
		while (1)
		{
			if (temp == 0)
			{
				break;
			}
			if (checkVisite(temp->dst) == 1)
			{
				temp = temp->next;

			}
			else
			{
				push(temp->dst);
				temp = temp->next;
			}
		}
	}
}


/*
----------BFS--------------------
*/

void inqueue(int _v)
{
	struct vertex *new_one = (struct vertex *)malloc(sizeof(struct vertex));
	new_one->v = _v;
	new_one->next = 0;

	if (queue == 0)
	{
		queue = new_one;
		return;
	}

	struct vertex *temp = queue;
	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new_one;
	return;
}

int dequeue()
{
	if (queue == 0)
	{
		return -888;
	}

	int v = queue->v;
	struct vertex * temp = queue;
	queue = queue->next;
	free(temp);
	return v;

}

void BFS_addToVisited(int v)
{
	struct vertex *new_one = (struct vertex *)malloc(sizeof(struct vertex));
	new_one->v = v;
	new_one->next = 0;

	if (queue_visited == 0)
	{
		queue_visited = new_one;
		return;
	}
	struct vertex * temp = queue_visited;

	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new_one;
	return;
}

int BFS_checkVisite(int _v)
{
	struct vertex * temp = queue_visited;

	while (temp != 0)
	{
		if (temp == 0)
		{
			return 0;
		}
		if (temp->v == _v)
		{
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

void performBFS(int v)
{
	int cnt = -1;
	inqueue(v);

	while (1)
	{

		int x = dequeue();

		if (x == -888)
		{
			printf("question2: %d\n", cnt);
			return;
		}

		int res = BFS_checkVisite(x);
		if (res == 1)
		{
			continue;
		}

		BFS_addToVisited(x);

		//printf("--> %d\n", x);
		cnt = cnt + x;

		struct edge * temp = findVertex(x)->connected;
		while (1)
		{
			if (temp == 0)
			{
				break;
			}
			if (BFS_checkVisite(temp->dst) == 1)
			{
				temp = temp->next;

			}
			else
			{
				inqueue(temp->dst);
				temp = temp->next;
			}
		}
	}
}

/*
----------MST--------------------
*/

int findFamily(int v)
{
	struct vertex *temp = graph;

	while (temp != 0)
	{
		if (temp->v == v)
		{
			return temp->family;
		}
		temp = temp->next;
	}
}

int areWeFamily(int v1, int v2)
{
	if (findFamily(v1) == findFamily(v2))
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void marrying(int v1, int v2)
{
	int f1 = findFamily(v1);
	int f2 = findFamily(v2);

	int smaller, bigger;

	if (f1 > f2)
	{
		bigger = f1;
		smaller = f2;
	}
	else
	{
		bigger = f2;
		smaller = f1;
	}

	struct vertex * temp = graph;
	while (1)
	{
		if (temp == 0)
		{
			return;
		}

		if (temp->family == bigger)
		{
			temp->family = smaller;
			return;
		}
		temp = temp->next;
	}
}

int countEdge()

{
	int _cnt = 0;
	struct edge*temp =edges;

	while (temp != 0)
	{
		_cnt += 1;
		temp = temp->next;
	}
	return _cnt;
}

void sortingByWeight()
{
	int n = countEdge();

	MSTedgeArry = (struct edge*)malloc(sizeof(struct edge)*n);

	struct edge * temp = edges;

	for (int i = 0; i < n; i++)
	{
		MSTedgeArry[i].src = temp->src;
		MSTedgeArry[i].dst = temp->dst;
		MSTedgeArry[i].w = temp->w;
		temp = temp->next;
	}

	//배열에 대해서 bubble sort를 돌린다.
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (MSTedgeArry[j].w > MSTedgeArry[j + 1].w)
			{
				struct edge _temp = MSTedgeArry[j];
				MSTedgeArry[j] = MSTedgeArry[j + 1];
				MSTedgeArry[j + 1] = _temp;
			}
		}
	}

}

void performMST()
{
		int n = howMAntVvertexs();
	sortingByWeight();

	int mstCNT = 0;
	int sumOfWeight = 0;

	for (int i = 0; i < n; i++)
	{
		if (areWeFamily(MSTedgeArry[i].src, MSTedgeArry[i].dst) == 0)
		{
			sumOfWeight = sumOfWeight + MSTedgeArry[i].w;
			mstCNT += 1; 
			if (mstCNT == n - 1)
			{
				break;
			}
			marrying(MSTedgeArry[i].src, MSTedgeArry[i].dst);
		}
	}
	printf("question3: %d\n", sumOfWeight);
}


/*
----------Dijstra--------------------
*/

void initDijkstraTable(void)
{
	int vcnt = howMAntVvertexs();


	dtable = (struct dijkstra*)malloc(sizeof(struct dijkstra)*vcnt);

	struct vertex * temp = graph;

	for (int i = 0; i < vcnt; i++)
	{
		dtable[i].vertex = temp->v;
		temp = temp->next;
		dtable[i].found = 0;
		dtable[i].dist = 200000000;
		dtable[i].prev = 0;
	}
}

int findVertexIndexFromDTable(int v)
{

	int vcnt = howMAntVvertexs();
	for (int i = 0; i < vcnt; i++)
	{
		if (dtable[i].vertex == v)
		{
			return i;
		}
	}
}

int nextShortestVertex(void)
{
	int vcnt = howMAntVvertexs();
	int shortestDist = 20000000;
	int shortestIdx = -1;

	for (int i = 0; i < vcnt; i++)
	{
		if (dtable[i].found == 0 && dtable[i].dist < shortestDist)
		{
			shortestIdx = i;
			shortestDist = dtable[i].dist;
		}
	}
	return shortestIdx;
}

int findWeight(int _v)
{
	struct edge * temp = edges;
	while (temp != 0)
	{
		if (temp->src == _v)
		{
			return temp->w;
		}
		temp = temp->next;
	}
}


void runDijkstra(int sVertex,int dVertex)
{
	initDijkstraTable();

	int idx = findVertexIndexFromDTable(sVertex);
	dtable[idx].dist = 0; 

	while (1)
	{
		int i = nextShortestVertex();
		if (i == -1)
		{

			return;
		}
		
		dtable[i].found = 1; 

	
		struct edge * connectOnes = findVertex(dtable[i].vertex)->connected;

		while (connectOnes !=0)
		{
			int neighborIdx = findVertexIndexFromDTable(connectOnes->dst);

			if (dtable[neighborIdx].dist > dtable[i].dist + connectOnes->w) 
			{
				dtable[neighborIdx].dist = dtable[i].dist + connectOnes->w; 
				dtable[neighborIdx].prev = dtable[i].vertex;    
				if (dtable[i].vertex == dVertex)
				{
					return;
				}
			}
			connectOnes = connectOnes->next;
		}
	}
	
}

void Dijkstra_addToVisited(int v)
{
	struct vertex *new_one = (struct vertex *)malloc(sizeof(struct vertex));
	new_one->v = v;
	new_one->next = 0;

	if (Dijkstra_visited == 0)
	{
		Dijkstra_visited = new_one;
		return;
	}
	struct vertex * temp = Dijkstra_visited;

	while (temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new_one;
	return;

}

int Dijkstra_checkVisite(int _v)
{
	struct vertex * temp = Dijkstra_visited;

	while (temp != 0)
	{
		if (temp == 0)
		{
			return 0;
		}
		if (temp->v == _v)
		{
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

void performDijkstra(int sVertex, int dVertex)
{
	runDijkstra(sVertex,dVertex);
	int c = howMAntVvertexs();
	for (int i = 0; i < c; i++)
	{
		printf("%d %d %d %d \n", dtable[i].vertex, dtable[i].found, dtable[i].dist, dtable[i].prev);
	}
	int n = howMAntVvertexs();
	int sumOfWeight = 0;
	for (int i = 0; i <n; i++)
	{
		if (dtable[i].found == 1 && dtable[i].dist != 0)
		{
			if (Dijkstra_checkVisite(dtable[i].prev) == 0)
			{
				sumOfWeight = sumOfWeight + findWeight(dtable[i].prev);
				Dijkstra_addToVisited(dtable[i].prev);
			}
		}
	}
	
	printf("question4: %d\n", sumOfWeight);
}

int main(void)
{
	readDataFile();

	processGraph();
	printf("%d %d", NUM4_value[0], NUM4_value[1]);
	performDFS(NUM1_value);
	performBFS(NUM2_value);
	performMST(NUM3_value);
	performDijkstra(NUM4_value[0], NUM4_value[1]);

	return 0;
}

