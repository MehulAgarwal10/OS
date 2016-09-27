#include <stdio.h>



int recFact(int num)
{

	if(num == 1)
		return 1;
	if(num == 0)
		return 1;

	return (num * recFact(num-1));
}

