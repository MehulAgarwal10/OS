#include <stdio.h>
#include <pthread.h>
#include <signal.h>

void *threadf()
{
	int j;
	char ch;
	printf("Thread PID : %d\n",getpid());
	ch = getchar();
	printf("%c..\n",ch);
	
}

void *sigFunc()
{
	printf("Main function, not quitting..! \n");
	;
}
int main()
{



	pthread_t tid;
	int i;
	printf("Main program thread : %d\n",getpid());
	pthread_create(&tid,NULL,threadf,NULL);
	signal(SIGINT,sigFunc);
	pthread_join(tid,NULL);
	
	char ch;
	ch = getchar();
	printf("%c\n",ch);
	pthread_exit(1);
}


