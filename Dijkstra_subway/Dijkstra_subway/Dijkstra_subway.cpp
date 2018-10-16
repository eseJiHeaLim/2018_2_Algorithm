#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>



int main(void)
{
	//파일을 열러주는 파일이 열린 포인터
	FILE *f = 0;

	// 파일 열기
	// R : read
	// T : text <--> 바이너리 파일
	f = fopen("seoul.txt", "rt");

	char buf[100];

	while (1)
	{
		if (feof(f))
		{
			break;
		}
		fgets(buf, 99, f);
		printf("%s", buf);
		//버퍼 쓰고 지워줘야함
		buf[0] = '\0';
	}
	//최대 읽을 수있는 글자의 양 99개 --> 한줄씩 읽어 들일때 
	//fgets(buf, 99, f);


	// 파일 닫기 --> 운영체제에서 열려있는 파일의 개수가 제한이 있음
	fclose(f);

	return 0;
}