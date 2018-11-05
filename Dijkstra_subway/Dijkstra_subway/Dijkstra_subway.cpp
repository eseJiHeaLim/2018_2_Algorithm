#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

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

struct Station * graph = 0;
struct StationInfo * stations = 0;

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
	new_one->stationId = (char *)malloc(strlen(_stationId)+1);
	//할당된 공간에 _stationId를 복사한다
	strcpy(new_one->stationId, _stationId); // new_one -> stationId에 _station의 값을 집어 넣는다. 이 아이는 널까지만 복사를 함
	new_one->stationName = (char *)malloc(sizeof(_stationName)+1);
	strcpy(new_one->stationName, _stationName);
	// _station의 값보다 new_one 안에 든값의 길이가 훠씬 타이트하게 작다
	new_one->lineNumber = (char *)malloc(sizeof(_lineNumber)+1);
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

struct Station * findStationFromGraph(char* _from)
{
	struct Station *temp = graph;
	while (temp->next!=0)
	{
		if (strcmp(temp->stationId, _from) == 0)
		{
			return temp;
		}
		temp = temp->next;

	}
	return 0;
}

void addEdgeToGraph(char* _fromStation, char * _toStation, int _distance)
{
	struct Station * cur = findStationFromGraph(_fromStation);
	cur = (struct Station*)malloc(sizeof(struct Station));
	cur->stationId = (char *)malloc(strlen(_fromStation) + 1);
	strcpy(cur->stationId, _fromStation);
	cur->next = 0;
	cur->connected = 0;

	if (cur == 0)//서 생긴 Statio을 만들어서 graph에 verticla 방향으로 넣는다.
	{
		if (graph == 0)
		{
			graph == cur;
		}
		else
		{
			struct Station * temp = graph;
			while (temp->next != 0)
			{
				temp = temp->next;
			}
			temp->next = cur;
		}
	}
	else
	{
		//struct ConnectedStation * temp = cur
	}
}

void showConnectedStation(char *_station)
{
	struct Station * temp = graph;
	struct ConnectedStation * cur = 0;
	while (temp->next != 0)
	{
	
			if (strcmp(temp->stationId, _station) == 0)
			{
				cur = temp->connected;
			}
			temp = temp->next;
	}

	struct ConnectedStation * temptemp = cur;
	while (temptemp->next != 0)
	{
		printf("%s\n", temptemp->stationId);
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
	}
	//최대 읽을 수있는 글자의 양 99개 --> 한줄씩 읽어 들일때 
	//fgets(buf, 99, f);

	while (!feof(f))
	{
		fgets(buf, 99, f);
		char fromStation[50];
		char toStation[50];
		int distance;
		sscanf(buf, "%s %s %d\n", fromStation, toStation, &distance);

		printf("From %s ----> To %s: %d\n", fromStation, toStation, distance);
		addEdgeToGraph(fromStation, toStation, distance);

		buf[0] = '\0';
	}


	// 파일 닫기 --> 운영체제에서 열려있는 파일의 개수가 제한이 있음
	fclose(f);

	showConnectedStation((char *)"100");

	return 0;
}