#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int main()
{

	int pid,i;
	pid = fork();

	if(pid == 0)
	{
		printf("Child.. PID : %d\n", getpid());
		int p2id = fork();
		if(p2id == 0)
		{
			printf("Grandchild.. PID : %d\n", getpid());
			sleep(6);
			printf("Grandchild over.. \n");
		exit(0);
		}
		printf("Child over.. \n");
		exit(0);
	}
	else
	{
		printf("Main process.. PID : %d\n",getpid());
		wait();
		sleep(30);
		exit(0);
	}
}
