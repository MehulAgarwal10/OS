#include <stdio.h>
#include <sys/types.h>
#include <signal.h>


int main()
{

	int pid,i;
	pid = fork();

	if(pid == 0)
	{
		int p2id = fork();
		if(p2id == 0)
		{
			sleep(2);
		
		exit(0);
		}
		exit(0);
	}
	else
	{
		wait();
		sleep(30);
		exit(0);
	}
}
