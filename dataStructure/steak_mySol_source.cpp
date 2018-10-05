#include <stdio.h>
#define STACK_SZ 10

int stack[STACK_SZ];
int top = -1;

void push(int n)
{
	if (top == STACK_SZ - 1)
	{
		printf("stack is full!\n");
		return;
	}

	top++;
	stack[top] = n;
}

int pop()
{
	if (top < 0) //여기 부분이 맞는 건인가? 확인 
		         // 교수님은 그냥 top==-1 로 -> 어짜피 같은 말이다.
	{
		printf("stack is empty!\n");
		return -888;
	}
	int temp = stack[top];
	top--;
	return temp;
}

int main(void)
{
	push(1);
	push(2);
	push(3);
	push(4);

	for (int i = 0; i < 4; i++)
	{
		printf("%d\n", pop());
	}

	return 0;
}