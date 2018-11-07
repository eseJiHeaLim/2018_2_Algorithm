#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct StationInfo
{
	// char stationId[100] --> �̷����ϸ� 100�� �Ѿ�� ���̸� �޾� ���ϼ��� ����
	char * stationId;  // �ٴ� �̷��� �ϸ� ���ϴ� �̸��� ���̸�ŭ �Ҵ��� �ް� �ּҰ��� �޾ƿ�
	char * stationName;
	char * lineNumber;
	struct StationInfo * next;
};

//����������  �޸����� �޷������� ����
struct ConnectedStation
{
	char * stationId;
	int distance;
	struct ConnectedStation * next;
};

//�Ʒ������� �޸����� �������� ����
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
	// �Ʒ� �ڵ尡 �ȵǴ� ���� : ���� ���۸� ����Ű�� ���뿡���� ���� ��� �ٲ�� �����ϱ� ������ �ȵ� --> ��ȸ�ؼ� ������
	/*
	new_one->stationId = _stationId;
	new_one->stationName = _stationName;
	new_one->lineNumber = _lineNumber;
	new_one->next = 0;
	*/
	//����ö�� �̸���ŭ�� ������ �Ҵ� �޴´�
	new_one->stationId = (char *)malloc(strlen(_stationId) + 1);
	//�Ҵ�� ������ _stationId�� �����Ѵ�
	strcpy(new_one->stationId, _stationId); // new_one -> stationId�� _station�� ���� ���� �ִ´�. �� ���̴� �α����� ���縦 ��
	new_one->stationName = (char *)malloc(sizeof(_stationName) + 1);
	strcpy(new_one->stationName, _stationName);
	// _station�� ������ new_one �ȿ� �簪�� ���̰� �̾� Ÿ��Ʈ�ϰ� �۴�
	new_one->lineNumber = (char *)malloc(sizeof(_lineNumber) + 1);
	strcpy(new_one->lineNumber, _lineNumber);

	new_one->next = 0;


	//SLL ���̱�
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

	if (cur == 0) // ���� Station�� ���� graph�� vertical �������� �ٿ��ش�.
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

	// cur�� �����ٰ� ConnectedStation�� ���� ���δ�.
	struct ConnectedStation *new_one =
		(struct ConnectedStation *)malloc(sizeof(struct ConnectedStation));
	new_one->stationId = (char *)malloc(strlen(_toStation) + 1);
	strcpy(new_one->stationId, _toStation);
	new_one->distance = _distance;
	new_one->next = 0;

	// cur�� ���� new_one�� ���δ�.
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



int main(void)
{
	//������ �����ִ� ������ ���� ������
	FILE *f = 0;

	// ���� ����
	// R : read
	// T : text <--> ���̳ʸ� ����
	f = fopen("seoul.txt", "rt");

	char buf[100];

	while (!feof(f))
	{
		fgets(buf, 99, f);
		// �Ʒ� if���� ������ ������������� ������ �ڵ尡 �ǹ����°���
		if (buf[0] == '\n')
		{
			break;
		}

		//buf : 100 �ҿ�� 1 
		//100���� �� ���� : ���̸��� ��� ���� ���� �׳� �ִ�� �ڸ��� ���� --> �ӽ� �迭
		char stationid[100];
		char stationname[100];
		char lineNumber[100];
		// �� �Լ��� ������ �߽����� �ϳ��� ��� �о��
		sscanf(buf, "%s %s %s\n", stationid, stationname, lineNumber);
		//printf("StationID : %s, StationName: %s, Line:%s\n", stationid, stationname, lineNumber);
		//��� ������ sll�� ������ ��Ű���� �� 
		addStationNode(stationid, stationname, lineNumber);
		// �� ��Ʈ���� ������ ���ھտ� ���ڿ��� �͵� �ֱ� ����
		//printf("%s", buf);
		//���� ���� ���������
		buf[0] = '\0';
		while (!feof(f))
		{
			fgets(buf, 99, f);

			char fromStation[50];
			char toStation[50];
			int distance;
			sscanf(buf, "%s %s %d\n", fromStation, toStation, &distance);

			printf("From %s ----> To %s : %d\n", fromStation, toStation, distance);

			addEdgeToGraph(fromStation, toStation, distance);

			buf[0] = '\0';
		}
	}
	//�ִ� ���� ���ִ� ������ �� 99�� --> ���پ� �о� ���϶� 
	//fgets(buf, 99, f);



	// ���� �ݱ� --> �ü������ �����ִ� ������ ������ ������ ����
	fclose(f);

	printf("\n");

	//���� �ܴ���Ÿ�
	showConnectedStation((char *)"823");

	printf("------------------------------------------\n");
	//�����
	showConnectedStation((char *)"826");

	printf("------------------------------------------\n");
	//��ž��
	showConnectedStation((char *)"K226");

	printf("------------------------------------------\n");
	//����
	showConnectedStation((char *)"I120");

	return 0;
}