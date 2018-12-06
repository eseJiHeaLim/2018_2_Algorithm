#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>


struct Station* findStationFromGraph(char *_fromStation);

struct StationInfo
{
	// char stationId[100] --> 이렇게하면 100이 넘어가는 아이를 받아 들일수가 없음
	char * stationId;  // 근대 이렇게 하면 원하는 이름의 길이만큼 할당을 받고 주소값만 받아옴
	char * stationName;
	char * lineNumber;
	struct StationInfo * next;
};

//오른쪽으로  쭈르르륵 달려나가는 아이
struct ConnectedStation
{
	char * stationId;
	int distance;
	struct ConnectedStation * next;
};

//아래쪽으로 쭈르르륵 내려가는 아이
struct Station
{
	char *stationId;
	struct ConnectedStation * connected;
	struct Station * next;
};

struct dijkstra {
	char * my_id;
	int final;
	int dist;
	char * prev;
};


struct Station * graph = 0;
struct StationInfo * stations = 0;
//방문 했던 노드를 저장하는 sll
struct Station * vistited = 0;
struct Station * steak = 0;

void push(char* _stationID)
{
	struct Station * new_one = (struct Station*)malloc(sizeof(struct Station));
	new_one->connected = 0;
	new_one->next = 0;
	new_one->stationId = (char *)malloc(strlen(_stationID)+1);
	strcpy(new_one->stationId, _stationID);
	if (steak == 0)
	{
		steak = new_one;
		return;
	}
	else
	{
		new_one->next = steak;
		steak = new_one;
		return;
	}
}

char * pop()
{
	struct Station * temp = steak;
	steak = steak->next;
	return temp->stationId;
}

void addVistied(char * _visit)
{
	struct Station  * new_one = (struct Station*)malloc(sizeof(struct Station));
	new_one->connected = 0;
	new_one->next = 0;
	new_one->stationId = (char *)malloc(strlen(_visit)+1);
	strcpy(new_one->stationId, _visit);

	if (vistited == 0)
	{
		vistited = new_one;
		return;
	}
	else
	{
		new_one->next = steak;
		steak = new_one;
		return;
	}
}

int checkVisit(char* _visit)
{
	struct Station *temp = vistited;
	char * compare = (char *)malloc(strlen(_visit) + 1);
	strcpy(compare, _visit);

	while (temp!=0)
	{
		if (temp->next == 0)
		{
			return 0;
		}
		if (strcmp(temp->stationId, compare) == 0)
		{
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}


void DFS(char * _start)
{
	char * src = 0;
	char * v = 0;
	src=(char *)malloc(strlen(_start) + 1);
	strcpy(src, _start);

	push(src);

	while (1)
	{
		char * temp = pop();
		v = (char *)malloc(strlen(temp) + 1);
		strcpy(v, temp);

		if (v == 0)
		{
			break;
		}
		if (checkVisit(v) == 1)
		{
			continue;
		}
		
			addVistied(v);
			printf("%s\n", v);


			struct ConnectedStation * _temp = findStationFromGraph(v)->connected;
			while (1)
			{
				if (_temp == 0)
				{
					break;
				}
				
				char * tempdata = (char *)malloc(sizeof(_temp->stationId) + 1);
				strcpy(tempdata, _temp->stationId);

				if (checkVisit(tempdata) == 1)
				{
					_temp = _temp->next;
				}
				else
				{
					push(tempdata);
					_temp = _temp->next;
				}
				
			}	
	}
}

int countVertex()
{
	struct StationInfo * temp = stations;

	int cnt = 1;
	while (1)
	{
		if (temp->next == 0)
		{
			return cnt;
		}
		temp = temp->next;
		cnt++;
	}
}

void addStationNode(char * _stationId, char * _stationName, char * _lineNumber)
{
	struct StationInfo *new_one = (struct StationInfo*)malloc(sizeof(struct StationInfo));
	// 아래 코드가 안되는 이유 : 공용 버퍼를 가르키면 공용에서는 값이 계속 바뀌고 있으니깐 저장이 안됨 --> 우회해서 가야함
	/*
	new_one->stationId = _stationId;
	new_one->stationName = _stationName;
	new_one->lineNumber = _lineNumber;
	new_one->next = 0;
	*/
	//지하철역 이름만큼의 공간을 할당 받는다
	new_one->stationId = (char *)malloc(strlen(_stationId) + 1);
	//할당된 공간에 _stationId를 복사한다
	strcpy(new_one->stationId, _stationId); // new_one -> stationId에 _station의 값을 집어 넣는다. 이 아이는 널까지만 복사를 함
	new_one->stationName = (char *)malloc(sizeof(_stationName) + 1);
	strcpy(new_one->stationName, _stationName);
	// _station의 값보다 new_one 안에 든값의 길이가 훠씬 타이트하게 작다
	new_one->lineNumber = (char *)malloc(sizeof(_lineNumber) + 1);
	strcpy(new_one->lineNumber, _lineNumber);

	new_one->next = 0;


	//SLL 붙이기
	if (stations == 0)
	{
		stations = new_one;
		return;
	}
	else
	{
		struct StationInfo  * temp = stations;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_one;
	}
}

struct Station* findStationFromGraph(char *_fromStation)
{
	struct Station *temp = graph;
	while (temp != 0)
	{
		if (strcmp(temp->stationId, _fromStation) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	return 0;
}

void addEdgeToGraph(char* _fromStation, char* _toStation, int _distance)
{

	struct Station *cur = findStationFromGraph(_fromStation);



	if (cur == 0) // 새로 Station을 만들어서 graph에 vertical 방향으로 붙여준다.
	{
		cur = (struct Station *)malloc(sizeof(struct Station));
		cur->stationId = (char *)malloc(strlen(_fromStation) + 1);
		strcpy(cur->stationId, _fromStation);
		cur->next = 0;
		cur->connected = 0;

		if (graph == 0)
		{
			graph = cur;
		}
		else
		{
			struct Station *temp = graph;
			while (temp->next != 0)
			{
				temp = temp->next;
			}
			temp->next = cur;
		}
	}

	// cur의 옆에다가 ConnectedStation을 만들어서 붙인다.
	struct ConnectedStation *new_one =
		(struct ConnectedStation *)malloc(sizeof(struct ConnectedStation));
	new_one->stationId = (char *)malloc(strlen(_toStation) + 1);
	strcpy(new_one->stationId, _toStation);
	new_one->distance = _distance;
	new_one->next = 0;

	// cur의 옆에 new_one을 붙인다.
	struct ConnectedStation *temp = cur->connected;
	if (temp == 0)
	{
		cur->connected = new_one;
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




void showConnectedStation(char *_station)
{
	struct Station * temp = findStationFromGraph(_station);

	if (temp == 0)
	{
		printf("No Connected Station\n");
		return;
	}
	struct ConnectedStation * con = temp->connected;
	while (con != 0)
	{
		printf("%s\n", con->stationId);
		con = con->next;

	}

}

void connectSameStation()
{
	struct StationInfo * temp = stations;
	struct StationInfo * compare = temp->next;

	printf("+++++++++++++++++++++++++++++++++++++++++++++=\n");
	while (temp->next != 0)
	{ 
		/*
			리셋 하렴 
			리셋 중요함
		*/
		compare = temp->next;
	
		while (compare->next != 0)
		{
			if (strcmp(temp->stationName, compare->stationName) == 0)
			{
				addEdgeToGraph(temp->stationId, compare->stationId, 0);
				addEdgeToGraph(compare->stationId, temp->stationId, 0);
			}
			compare = compare->next;
		}
		temp = temp->next;

	}
}

int main(void)
{
	//파일을 열러주는 파일이 열린 포인터
	FILE *f = 0;

	// 파일 열기
	// R : read
	// T : text <--> 바이너리 파일
	f = fopen("seoul.txt", "rt");

	char buf[100];

	while (!feof(f))
	{
		fgets(buf, 99, f);
		// 아래 if문을 넣으면 에버랜드까지만 나오는 코드가 되버리는거임
		if (buf[0] == '\n')
		{
			break;
		}

		//buf : 100 소요산 1 
		//100으로 한 이유 : 역이름이 어떻게 될지 몰라서 그냥 최대로 자리를 만듬 --> 임시 배열
		char stationid[100];
		char stationname[100];
		char lineNumber[100];
		// 이 함수는 공백을 중심으로 하나씩 끊어서 읽어옴
		sscanf(buf, "%s %s %s\n", stationid, stationname, lineNumber);
		//printf("StationID : %s, StationName: %s, Line:%s\n", stationid, stationname, lineNumber);
		//모든 정보를 sll에 저장을 시키려고 함 
		addStationNode(stationid, stationname, lineNumber);
		// 다 스트링인 이유는 숫자앞에 문자오는 것도 있기 때문
		//printf("%s", buf);
		//버퍼 쓰고 지워줘야함
		buf[0] = '\0';
		//최대 읽을 수있는 글자의 양 99개 --> 한줄씩 읽어 들일때 
	//fgets(buf, 99, f);
		
	}


	while (!feof(f))
	{
		fgets(buf, 99, f);

		char fromStation[50];
		char toStation[50];
		int distance;
		sscanf(buf, "%s %s %d\n", fromStation, toStation, &distance);

		//printf("From %s ----> To %s : %d\n", fromStation, toStation, distance);

		addEdgeToGraph(fromStation, toStation, distance);

		buf[0] = '\0';
	}


	// 파일 닫기 --> 운영체제에서 열려있는 파일의 개수가 제한이 있음
	fclose(f);

	printf("\n");
	connectSameStation();
	
	printf("-------------------------- ----------------\n");
	//부평역
	showConnectedStation((char *)"I120");

	printf("%d\n", countVertex());


	DFS((char *)"100");

	return 0;
}