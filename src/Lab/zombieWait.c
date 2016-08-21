#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

int main()
{

	int pid;

	pid = fork();
	
	if(pid == 0)
	{
		printf("This is the child.. \n");
		//sleep(5);
		printf("Child execution over .. \n");
		
	}
	else
	{
		//wait();
		//signal(SIGCHLD,SIG_IGN);
		printf("Parent process ID : %d..\n", getpid());
		sleep(30);
		printf("Parent execution.. \n");
		printf("Zombie state.. \n");
		//while(1);
	}
}
