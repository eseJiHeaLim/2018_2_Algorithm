#include<stdio.h>
#include <stdlib.h>

#define NUM_VERTEX 4



// 그래프를 표현할 배열을 만듬
//전역변수로 처음에 선언하면 자동으로 0으로 초기화됨
int graph[NUM_VERTEX][NUM_VERTEX];

int getIndex(char _c)
{
	return _c - 'A';
}


//아스키 코드를 이용한 인덱시으로 값 저장
void addEdge(char src, char dst)
{

	int s = getIndex(src);
	int d = getIndex(dst);
	//src --> dst로 가는 edge가 있고,
	graph[s][d] = 1;

	//src --> dst로 가는 edge가 있고,
	graph[d][s] = 1;
}

void showConnectedVertexes(char _c)
{
	int index = getIndex(_c); // c가 몇 행인지를 구한다.

	int i;
	for (i = 0; i < NUM_VERTEX; i++)
	{
		if (graph[i][index] == 1)
		{
			//핵심 문자로 다시 바꾸는 법
			printf("%c", i + 'A');
		}
	}
}

int main(void)
{

	// 경로들을 모두 입력해줌
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
