#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


void *f();

int main()
{

	pthread_t tid;
	printf("Before thread \n");
	pthread_create(&tid, NULL,f, NULL);
	pthread_join(tid, NULL);
	printf("After thread .. \n");

}

void *f(void *vargp)
{

	printf("Hello world from thread ! \n");
	return NULL;
}

