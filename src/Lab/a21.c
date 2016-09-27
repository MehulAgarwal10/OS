#include <stdio.h>
#include <sys/types.h>

int main()
{

	pid_t pid = getpid();

	printf("Process ID : %d\n",pid);
	//while(1);
	
	pid = fork();
	if(pid == 0)
	{
		//Child process
		pid_t pid2 = getpid();
		printf("Child process ID : %d\n",pid2);
		int num = 5;
		printf("Address space : %p\n", &num);
	}
	else
	{
		//Parent process
		pid_t pid2 = getpid();
		printf("Parent process ID : %d\n",pid2);
		int num = 5;
		printf("Address space : %p\n",&num);
	}
}

