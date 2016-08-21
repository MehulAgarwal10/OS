#include <stdio.h>
#include <sys/types.h>

int main()
{

	int pid;
	char ch;
	pid = fork();
	int i;
	if(pid == 0)
	{
		//Child 
		printf("Child process..\n");
		exit(0);
		//while(1);
	}
	else
	{
		printf("Process ID : %d\n",(int)getpid());
		sleep(10);
	}
}

