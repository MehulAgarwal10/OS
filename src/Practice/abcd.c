#include <stdio.h>


int main()
{

	int a,b;

	a = 5;
	b = 10;

	int i;
	for(i=0;i<10;i++)
	{
		a += b;
	}

	int fin = a * b;

	int prod = fin * b;
	printf("prof = %d\n", prod);
}
