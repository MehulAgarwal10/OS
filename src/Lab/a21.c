#include <stdio.h>
#include <sys/types.h>

int main()
{

	int pid = (int)getpid();

	printf("Process ID : %d\n",pid);
	//while(1);
	
	pid = fork();
	if(pid == 0)
	{
		//Child process
		int pid2 = (int)getpid();
		printf("Child process ID : %d\n",pid2);
		int num = 5;
		printf("Address space : %p\n", &num);
	}
	else
	{
		//Parent process
		int pid2 = (int)getpid();
		printf("Parent process ID : %d\n",pid2);
		int num = 5;
		printf("Address space : %p\n",&num);
	}
}

