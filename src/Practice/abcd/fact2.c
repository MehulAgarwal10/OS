#include <stdio.h>


int itFact(int num)
{

	int i;
	int prod=1;
	for(i=1;i<=num;i++)
	{
		prod = prod * i;
	}

	return prod;
}
