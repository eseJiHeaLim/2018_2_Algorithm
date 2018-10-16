// SLL을 이용한 그래프 MPS
//입력순서는 알파벳 순
//엣지는 한번씩만 넣어도 됨

#include<stdio.h>
#include<stdlib.h>


//입력되는 엣지를 여기에 전부 연결 시킴, 줄줄이 
struct edge
{
	char src;
	char dst;
	int weight;
	struct edge *next;
};


//벌택스들만을 저장하는 SLL
struct vertex
{
	char v;
	char family;
	struct vertex *next;
};

//vertex sll의 맨앞은 가리키는 포인터
struct vertex * vertexes = 0;

struct edge* edges = 0;

int vertex_cnt = 0;

//v가 vertexs sll에 있으면 1을 반환
//없으면 0 반환
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
	//vertex sll에 v가 없을 경우에만 ,
	//sll에 추가 한다,

	//1. v가 이미 vertex sll에 있는지 확인
	if (checkVertex(v) == 1)// 이미 있으므로 종료
	{
		return;
	}
	//2.없으면 노드를 만들어서 맨끛에 추가
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

//v1과 v2가 같은 가족이면 1을 반환, 아니면 0을 반환
int areWeFamily(char v1, char v2)
{
	//v1과 v2의 가족 정보를 알아서
	//같은면 1, 아니면 0을 반환

	if (findFamily(v1) == findFamily(v2))
	{
		return 1;

	}
	else
	{
		return 0;
	}

}

//v1과 v2가 같은 가족이 되었기에 방금 결혼함
//둘을 같은 가족으로 표시
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
	
		// 같은 가족으로 바꿔줌

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

//SLL에 들어있는 노드들의 갯수를 센다.
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


	//SLL에 들어있는 node들의 갯수를 센다.
	int n = countSLL(edges);

	// edge들을 오름차순으로 정렬한다.
	//복사할 배열을 만든다.
	//n을 곱하여서  배열의 크기를 지정함
	struct edge * edgeArry = (struct edge*)malloc(sizeof(struct edge)*n);

	//SLL에 있는 내용을 앞에서부터 배열로 복사한다.
	struct edge * temp = edges;


	for (int i = 0; i < n; i++)
	{
		edgeArry[i].src = temp->src;
		edgeArry[i].dst = temp->dst;
		edgeArry[i].weight = temp->weight;
		temp = temp->next;
	}
	
	//배열에 대해서 bubble sort를 돌린다.
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


	//vertex가 몇개가 있고,
	//vertex 이름이 무엇인지를 알기 위해서
	//배열을 뒤지면서 하나씩 찾아간다.
	for (int i = 0; i < n; i++)
	{
		//vertex 를 새로운 SLL인
		addVertex(edgeArry[i].src);
		addVertex(edgeArry[i].dst);

	}

	/*
	//vertex 안에 정렬된 값이 제대로 나오는 확인
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

	//edge 들을 오름차순으로 하나씩 검사하면서 
	//mst에 추가 할수 있는지를 확인
	int mstCNT = 0;
	for (int i = 0; i < n; i++)
	{
		//같은 가족이 아니면 E를 MST에 추가
		if (areWeFamily(edgeArry[i].src, edgeArry[i].dst) == 0)
		{
			printf("add edge %c - %c to MST\n", edgeArry[i].src, edgeArry[i].dst);
			mstCNT+=1; //edge 개수 증가
			if (mstCNT == vertex_cnt - 1)
			{
				//개수는 sll의 개수랑 같음	
				break;
			}
			justMarried(edgeArry[i].src, edgeArry[i].dst);
		}
	}
	return 0;
}