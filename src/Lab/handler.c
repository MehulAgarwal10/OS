#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

void func();

int main()
{

	int pid,i;
	pid = fork();

	if(pid == 0)
	{
		//Child
		printf("Child here.. Executing.. \n");
		sleep(5);
		printf("Child execution complete .. \n");
	}
	else
	{
		signal(SIGCHLD, func);
		printf("Parent here.. executing.. \n");
		sleep(30);
		printf("Parent exiting.. \n");
	}
}

void func()
{
	printf("Child has been killed .. \n");
	wait();
}
