#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
int main()
{

	int pid;
	char ch;
	pid = fork();
	int i;
	if(pid == 0)
	{
		//Child 
		printf("Child process.. ID : %d\n",getpid());
		exit(0);
		//while(1);
	}
	else
	{
		printf("Process ID : %d\n",(int)getpid());
		sleep(10);
	}
}

