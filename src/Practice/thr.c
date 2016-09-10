#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


void *f();

int main()
{

	pthread_t tid;
	printf("Before thread \n");
	int i;
	for(i=1;i<=5;i++)
	{
		pthread_create(&tid, NULL,f, NULL);
		//pthread_join(tid, NULL);
	}
	printf("After thread .. \n");
	//sleep(70);
	pthread_exit(1);
}

void *f(void *vargp)
{

	printf("\nHello world from thread ! \n");
	printf("Enter a number : ");
	int num;
	scanf("%d",&num);
	printf("Square of given number is : %d\n",(num*num));
	return NULL;
}

