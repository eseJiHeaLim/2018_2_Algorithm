/*
1. Dilkstra table �� �ʱ�ȭ �Ѵ�
	(found=false , dist = infinite, prev)
2. ���� vertex s�� ���ؼ�
	table[s].dist =0
3. (table[i].found==false)&& minimum(table[i].dist)�� �����ϴ� vertex i�� ã�Ƽ�
4. table[i].founf=true
5/ vertex [i] �� neighbor vertex�鿡 ���ؼ� dist �� prev�� update (���� ���� �� ������ ���� ���� ��쿡��)
6. 3������ �ݺ� ... �� �̻� found == false �� vertex�� ������ ����

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

//��� edge���� ������ ����
struct edge * edges = 0;

struct vertex {
	char v;
	struct vertex * next;
	struct edge * connected; // �� ������ ������ ��������� char v1�� ������� ����
};
//vertex �鸸�� ������ ����
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

//������ 1, ������ 0
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
	//vertex SLL�� v�� �ִ����� Ȯ���ϰ�
	//������ �߰� 
	//������ return 

	if (checkVertex(v) == 1)
	{
		// �̹� v�� �� �ִ� ��尡 ������ �׳� �Ѿ
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
	// vertex �鸸 �̾Ƽ� , vertex SLL�� �ִ´�.
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
	//sll�� ���� �׷���
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


// vertexs SLL���� v�� ��� �ִ� ��带 ã�Ƽ�
// �� �ּҸ� ��ȯ�Ѵ�.
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
		// edge�� �ϳ��� �������鼭, graph ������ �ִ´�.

		// edgeTemp.v1 -> edgeTemp.v2 : �� edge �� �ϳ� �ְ�
		// edgeTemp.v2 -> edgeTemp.v1 : �� edge �� �־���� 

		struct vertex *v1 = findVertex(edgeTemp->v1);
		struct vertex *v2 = findVertex(edgeTemp->v2);
		addEdgeInfo(v1, v2, edgeTemp->weight);
		addEdgeInfo(v2, v1, edgeTemp->weight);

		edgeTemp = edgeTemp->next;
	}
}

void initDijkstraTable(void)
{
	//vertex ������ �ľ� 
	int vcnt = howMAntVvertexs();

	//���̺� ����
	dtable= (struct dijkstra*)malloc(sizeof(struct dijkstra)*vcnt);

	// �ʱ�ȭ
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
	// vertex v�� �ش��ϴ� dijkstra�� ��ġ�� ��ȯ

	int vcnt = howMAntVvertexs();
	for (int i = 0; i < vcnt; i++)
	{
		if (dtable[i].vertex == v)
		{
			return i;
		}
	}
}

//�������� �ִܰ�ΰ� �������� �ʾҰ�,
//�ּ� dist �� ���� vertex�� dtable�� index�� ��ȯ�Ѵ�.
//����, �׷� vertex�� ������ , -1�� ��ȯ�Ѵ�.
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

// ������ svertex���� �Ѵ�.
void runDijkstra(char sVertex)
{
	int idx = findVertexIndexFromDTable(sVertex);
	dtable[idx].dist = 0; // pseudo �� �ι�° ����

	while (1)
	{
		int i = nextShortestVertex();
		if (i == -1)
		{
			//�� �̻� �ִܰŸ� ã�� ���� �����Ƿ� return 
			return;
		}
		dtable[i].found = 1; //�ִܰŸ��� ã����!!!!
		
		// 5 . vertex[i] �� neighbor vertex�鿡 ���ؼ� dist �� prev�� update(���� ���� �� ������ ���� ���� ��쿡��)
		struct edge * connectOnes = findVertex(dtable[i].vertex)->connected;

		while (connectOnes != 0)
		{
			int neighborIdx = findVertexIndexFromDTable(connectOnes->v2);

			if (dtable[neighborIdx].dist > dtable[i].dist + connectOnes->weight) // ���� ���ذ��°��� ���� ���� ª���ĸ� Ȯ��
			{
				dtable[neighborIdx].dist = dtable[i].dist + connectOnes->weight; // ���� ���ؼ� �� �����ϱ� �̿��� weight�� ������
				dtable[neighborIdx].prev = dtable[i].vertex;                     // ���� prve�� ���� �Ǵ°�
			}
			connectOnes = connectOnes->next;
		}

	}
}

int main(void)
{
	//���ý� , ������ ������ �𸣹Ƿ� addEdge�� ������ ���� �������� ��� �޾Ƶ���
	addEdge('A', 'B', 8);
	addEdge('A', 'C', 2);
	addEdge('B', 'C', 4);
	addEdge('B', 'D', 5);
	addEdge('C', 'D', 40);

	// �� �Լ��� ����Ͽ� �׷����� ����
	processEdge();

	initDijkstraTable();

	runDijkstra('A'); //���� vertex A�� ���� dijkstra�� �������ô�. �̰� ���� �� ã�� ����

	int c = howMAntVvertexs();
	for (int i = 0; i < c; i++)
	{
		printf("%c %d %d %c \n", dtable[i].vertex, dtable[i].found, dtable[i].dist, dtable[i].prev);
	}

	return 0;
}