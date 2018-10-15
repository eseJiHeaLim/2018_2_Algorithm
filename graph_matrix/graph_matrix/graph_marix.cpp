#include<stdio.h>
#include <stdlib.h>

#define NUM_VERTEX 4



// �׷����� ǥ���� �迭�� ����
//���������� ó���� �����ϸ� �ڵ����� 0���� �ʱ�ȭ��
int graph[NUM_VERTEX][NUM_VERTEX];

int getIndex(char _c)
{
	return _c - 'A';
}


//�ƽ�Ű �ڵ带 �̿��� �ε������� �� ����
void addEdge(char src, char dst)
{

	int s = getIndex(src);
	int d = getIndex(dst);
	//src --> dst�� ���� edge�� �ְ�,
	graph[s][d] = 1;

	//src --> dst�� ���� edge�� �ְ�,
	graph[d][s] = 1;
}

void showConnectedVertexes(char _c)
{
	int index = getIndex(_c); // c�� �� �������� ���Ѵ�.

	int i;
	for (i = 0; i < NUM_VERTEX; i++)
	{
		if (graph[i][index] == 1)
		{
			//�ٽ� ���ڷ� �ٽ� �ٲٴ� ��
			printf("%c", i + 'A');
		}
	}
}

int main(void)
{

	// ��ε��� ��� �Է�����
	addEdge('A', 'B');  // graph[0][1] = 1; graph[1][0] = 1;
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
