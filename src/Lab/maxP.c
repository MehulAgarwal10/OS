#include <stdio.h>


int main()
{

	int count,pid;
	while(1)
	{
		pid = fork();
		if(pid < 0)
			break;
		if(pid == 0)
		{
			count++;
			//printf("Count = %d\n",count);
		}

	}
	printf("Count = %d\n",count);


}