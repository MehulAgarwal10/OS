#include <stdio.h>


int main()
{

	int a,b;
	a = 10;
	b = 5;

	pid = fork();
	if(pid == 0)
	{
		int num = a;
		printf("%d\n",num);
	}
	else
	{
		int n2 = a+2;
		printf("%d\n",n2);
	}
}