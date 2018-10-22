/*
1. Dilkstra table 을 초기화 한다
	(found=false , dist = infinite, prev)
2. 시작 vertex s에 대해서
	table[s].dist =0
3. (table[i].found==false)&& minimum(table[i].dist)를 만족하는 vertex i를 찾아서
4. table[i].founf=true
5/ vertex [i] 의 neighbor vertex들에 대해서 dist 와 prev를 update (나를 통해 더 빠르게 갈수 있을 경우에만)
6. 3번으로 반복 ... 더 이상 found == false 인 vertex가 없을때 까지

*/
#include<stdio.h>
#include<stdlib.h>


struct dijkstra
{
	char vertex;
	int found;
	int dist;
	char prev;
};

struct dijkstra * dtable = 0;




struct edge {
	char v1;
	char v2;
	int weight;
	struct edge * next;
};

//모든 edge들을 줄줄이 연결
struct edge * edges = 0;

struct vertex {
	char v;
	struct vertex * next;
	struct edge * connected; // 이 위에의 엣지를 사용하지만 char v1은 사용하지 않음
};
//vertex 들만을 줄줄이 연결
struct vertex * vertexs = 0;


int howMAntVvertexs(void)
{
	int cnt = 0;
	struct vertex * temp = vertexs;

	while (temp != 0)
	{
		cnt += 1;
		temp = temp->next;
	}

	return cnt;
}

//있으면 1, 없으면 0
int checkVertex(char v)
{
	struct vertex * temp = vertexs;

	while (1)
	{
		if (temp->v == v)
		{
			return 1;
		}
		if (temp->next == 0)
		{
			return 0;
		}
		temp = temp->next;
	}
}

void addVertex(char v)
{
	//vertex SLL에 v가 있는지를 확인하고
	//없으면 추가 
	//있으면 return 

	if (checkVertex(v) == 1)
	{
		// 이미 v가 들어가 있는 노드가 있으면 그냥 넘어감
		return;
	}
	else
	{
		struct vertex * new_one = (struct vertex *)malloc(sizeof(struct vertex));
		new_one->v = v;
		new_one->next = 0;
		new_one->connected = 0;

		if (vertexs == 0)
		{
			vertexs = new_one;
			return;
		}
		else
		{
			struct vertex * temp = vertexs;

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


void addEdge(char v1, char v2, int weight)
{
	// vertex 들만 뽑아서 , vertex SLL에 넣는다.
	addVertex(v1);
	addVertex(v2);

	struct edge * new_one = (struct edge*)malloc(sizeof(struct edge));
	new_one->v1 = v1;
	new_one->v2 = v2;
	new_one->weight = weight;
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


void addEdgeInfo(struct vertex *v1, struct vertex *v2, int weight)
{
	//sll로 구한 그래프
	struct edge * new_one = (struct edge *)malloc(sizeof(struct edge));
	new_one->v2 = v2->v;
	new_one->next = 0;
	new_one->weight = weight;


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


// vertexs SLL에서 v를 담고 있는 노드를 찾아서
// 그 주소를 반환한다.
struct vertex * findVertex(char v)
{
	struct vertex * temp = vertexs;

	while (temp != 0)
	{
		if (temp->v)
		{
			return temp;
		}
		temp = temp->next;
	}
}

void processEdge(void )
{
	struct edge * edgeTemp = edges;

	while (edgeTemp != 0)
	{
		// edge를 하나씩 뒤져가면서, graph 정보를 넣는다.

		// edgeTemp.v1 -> edgeTemp.v2 : 이 edge 를 하나 넣고
		// edgeTemp.v2 -> edgeTemp.v1 : 이 edge 도 넣어야함 

		struct vertex *v1 = findVertex(edgeTemp->v1);
		struct vertex *v2 = findVertex(edgeTemp->v2);
		addEdgeInfo(v1, v2, edgeTemp->weight);
		addEdgeInfo(v2, v1, edgeTemp->weight);

		edgeTemp = edgeTemp->next;
	}
}

void initDijkstraTable(void)
{
	//vertex 개수를 파악 
	int vcnt = howMAntVvertexs();

	//테이블 생성
	dtable= (struct dijkstra*)malloc(sizeof(struct dijkstra)*vcnt);

	// 초기화
	struct vertex * temp = vertexs;

	for (int i = 0; i < vcnt; i++)
	{
		dtable[i].vertex = temp->v;
		temp = temp->next;
		dtable[i].found = 0;
		dtable[i].dist = 2000000000000;
		dtable[i].prev = 0;
	}
}

int findVertexIndexFromDTable(char v)
{
	// vertex v에 해당하는 dijkstra의 위치를 반환

	int vcnt = howMAntVvertexs();
	for (int i = 0; i < vcnt; i++)
	{
		if (dtable[i].vertex == v)
		{
			return i;
		}
	}
}

//아직까지 최단경로가 결정되지 않았고,
//최소 dist 를 가진 vertex의 dtable의 index를 반환한다.
//만약, 그런 vertex가 없으면 , -1을 반환한다.
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

// 시작을 svertex에서 한다.
void runDijkstra(char sVertex)
{
	int idx = findVertexIndexFromDTable(sVertex);
	dtable[idx].dist = 0; // pseudo 의 두번째 스텝

	while (1)
	{
		int i = nextShortestVertex();
		if (i == -1)
		{
			//더 이상 최단거리 찾을 것이 없으므로 return 
			return;
		}
		dtable[i].found = 1; //최단거리를 찾았음!!!!
		
		// 5 . vertex[i] 의 neighbor vertex들에 대해서 dist 와 prev를 update(나를 통해 더 빠르게 갈수 있을 경우에만)
		struct edge * connectOnes = findVertex(dtable[i].vertex)->connected;

		while (connectOnes != 0)
		{
			int neighborIdx = findVertexIndexFromDTable(connectOnes->v2);

			if (dtable[neighborIdx].dist > dtable[i].dist + connectOnes->weight) // 나를 통해가는것이 기존 보다 짧느냐를 확인
			{
				dtable[neighborIdx].dist = dtable[i].dist + connectOnes->weight; // 나를 통해서 더 빠르니깐 이웃의 weight는 내가됨
				dtable[neighborIdx].prev = dtable[i].vertex;                     // 이제 prve는 내가 되는것
			}
			connectOnes = connectOnes->next;
		}

	}
}

int main(void)
{
	//버택스 , 엣지에 개수를 모르므로 addEdge는 엣지에 대한 정보만을 계속 받아들임
	addEdge('A', 'B', 8);
	addEdge('A', 'C', 2);
	addEdge('B', 'C', 4);
	addEdge('B', 'D', 5);
	addEdge('C', 'D', 40);

	// 이 함수를 사용하여 그래프로 저장
	processEdge();

	initDijkstraTable();

	runDijkstra('A'); //시작 vertex A로 부터 dijkstra를 돌려봅시다. 이건 모든걸 다 찾는 거임

	int c = howMAntVvertexs();
	for (int i = 0; i < c; i++)
	{
		printf("%c %d %d %c \n", dtable[i].vertex, dtable[i].found, dtable[i].dist, dtable[i].prev);
	}

	return 0;
}