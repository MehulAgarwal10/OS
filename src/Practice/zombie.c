#include <stdio.h>
#include <stdlib.h>	


int main()
{
	int ppid = getpid();
	printf("Parent PID : %d\n",ppid);
	int pid = fork();
	if(pid == 0)
	{
		printf("Child [%d], quitting..\n",getpid());
		exit(0);
	}
	else
	{
		printf("Parent [%d] here.. \n",ppid);
		char ch = getchar();

	}
}