#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>

void *func()
{

	pthread_t tid;
	tid = pthread_self();
	//pthread_detach(pthread_self());
	sleep(2);
	printf("Thread ID in int : %d\n",(int)tid);
	printf("Thread ID : %02x\n",tid);
	printf("Thread Process ID : %d\n",getpid());
	exit(0);
}
int main()
{


	pthread_t tid,tmain;
	pthread_create(&tid,NULL,func,NULL);
	tmain = pthread_self();
	printf("Main Thread ID : %02x\nPeer thread ID : %02x\nMain Process ID : %d\n",tmain,tid,getpid());
	pthread_detach(tid);
	pthread_exit(0);
}