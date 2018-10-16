// SLL�� �̿��� �׷��� MPS
//�Է¼����� ���ĺ� ��
//������ �ѹ����� �־ ��

#include<stdio.h>
#include<stdlib.h>


//�ԷµǴ� ������ ���⿡ ���� ���� ��Ŵ, ������ 
struct edge
{
	char src;
	char dst;
	int weight;
	struct edge *next;
};


//���ý��鸸�� �����ϴ� SLL
struct vertex
{
	char v;
	char family;
	struct vertex *next;
};

//vertex sll�� �Ǿ��� ����Ű�� ������
struct vertex * vertexes = 0;

struct edge* edges = 0;

int vertex_cnt = 0;

//v�� vertexs sll�� ������ 1�� ��ȯ
//������ 0 ��ȯ
int checkVertex(char v)
{
	struct vertex*temp = vertexes;
	while (temp != 0)
	{
		if (temp->v == v)
		{
			return 1;
		}
		temp = temp->next;

	}
	return 0;
}


void addVertex(char v)
{
	//vertex sll�� v�� ���� ��쿡�� ,
	//sll�� �߰� �Ѵ�,

	//1. v�� �̹� vertex sll�� �ִ��� Ȯ��
	if (checkVertex(v) == 1)// �̹� �����Ƿ� ����
	{
		return;
	}
	//2.������ ��带 ���� �ǅƿ� �߰�
	vertex_cnt++;

	struct vertex *new_one = (struct vertex*)malloc(sizeof(struct vertex));
	new_one->v = v;
	new_one->family = v;
	new_one->next = 0;

	if (vertexes == 0)
	{
		vertexes = new_one;
		return;
	}
	else
	{
		struct vertex *temp = vertexes;
		while (temp ->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_one;
		return;
	}
}

char findFamily(char v)
{
	struct vertex *temp = vertexes;
	
	while (temp != 0)
	{
		if (temp->v == v)
		{
			return temp->family;
		}
		temp = temp->next;
	}
}

//v1�� v2�� ���� �����̸� 1�� ��ȯ, �ƴϸ� 0�� ��ȯ
int areWeFamily(char v1, char v2)
{
	//v1�� v2�� ���� ������ �˾Ƽ�
	//������ 1, �ƴϸ� 0�� ��ȯ

	if (findFamily(v1) == findFamily(v2))
	{
		return 1;

	}
	else
	{
		return 0;
	}

}

//v1�� v2�� ���� ������ �Ǿ��⿡ ��� ��ȥ��
//���� ���� �������� ǥ��
void justMarried(char v1, char v2)
{
	int f1 = findFamily(v1);
	int f2= findFamily(v2);

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
	
		// ���� �������� �ٲ���

		struct vertex * temp = vertexes;
		while (1)
		{
			if (temp== 0)
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


void addEdge(char _scr, char _dst, int _weight)

{
	struct edge * new_one = (struct edge*)malloc(sizeof(struct edge));
	new_one->src = _scr;
	new_one->dst = _dst;
	new_one->weight = _weight;
	new_one->next = 0;

	if (edges == 0)
	{
		edges = new_one;
		return;
	}
	else
	{
		struct edge*temp = edges;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_one;
	}
}

//SLL�� ����ִ� ������ ������ ����.
int countSLL(struct edge* _head)

{
	int _cnt = 0;
	struct edge*temp = _head;

	while (temp != 0)
	{
		_cnt += 1;
		temp = temp->next;
	}
	return _cnt;
}


int main(void)
{
	addEdge('A', 'B', 8);
	addEdge('A', 'C', 5);
	addEdge('A', 'D', 3);
	addEdge('B', 'E', 13);
	addEdge('B', 'C', 7);
	addEdge('C', 'E', 20);
	addEdge('C', 'D', 4);
	addEdge('C', 'F', 80);
	addEdge('C', 'G', 17);
	addEdge('E', 'F', 15);
	addEdge('D', 'G', 2);


	//SLL�� ����ִ� node���� ������ ����.
	int n = countSLL(edges);

	// edge���� ������������ �����Ѵ�.
	//������ �迭�� �����.
	//n�� ���Ͽ���  �迭�� ũ�⸦ ������
	struct edge * edgeArry = (struct edge*)malloc(sizeof(struct edge)*n);

	//SLL�� �ִ� ������ �տ������� �迭�� �����Ѵ�.
	struct edge * temp = edges;


	for (int i = 0; i < n; i++)
	{
		edgeArry[i].src = temp->src;
		edgeArry[i].dst = temp->dst;
		edgeArry[i].weight = temp->weight;
		temp = temp->next;
	}
	
	//�迭�� ���ؼ� bubble sort�� ������.
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (edgeArry[j].weight > edgeArry[j + 1].weight)
			{
				struct edge _temp = edgeArry[j];
				edgeArry[j] = edgeArry[j + 1];
				edgeArry[j + 1] = _temp;
			}
		}
	}


	//vertex�� ��� �ְ�,
	//vertex �̸��� ���������� �˱� ���ؼ�
	//�迭�� �����鼭 �ϳ��� ã�ư���.
	for (int i = 0; i < n; i++)
	{
		//vertex �� ���ο� SLL��
		addVertex(edgeArry[i].src);
		addVertex(edgeArry[i].dst);

	}

	/*
	//vertex �ȿ� ���ĵ� ���� ����� ������ Ȯ��
	struct vertex * tt = vertexes;

	while (1)
	{
		if (tt == 0)
		{
			break;
		}
		printf("%c ", tt->family);
		tt = tt->next;
	}
	*/

	//edge ���� ������������ �ϳ��� �˻��ϸ鼭 
	//mst�� �߰� �Ҽ� �ִ����� Ȯ��
	int mstCNT = 0;
	for (int i = 0; i < n; i++)
	{
		//���� ������ �ƴϸ� E�� MST�� �߰�
		if (areWeFamily(edgeArry[i].src, edgeArry[i].dst) == 0)
		{
			printf("add edge %c - %c to MST\n", edgeArry[i].src, edgeArry[i].dst);
			mstCNT+=1; //edge ���� ����
			if (mstCNT == vertex_cnt - 1)
			{
				//������ sll�� ������ ����	
				break;
			}
			justMarried(edgeArry[i].src, edgeArry[i].dst);
		}
	}
	return 0;
}