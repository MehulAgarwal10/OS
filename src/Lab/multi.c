#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


pthread_t tid[3];

void *func(void *arg)
{
    
    long i  = 0;
    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0]))
    {
        //First thread
        printf("First Thread here .. Sleeping for 10s..\n");
        sleep(10);
        printf("First thread execution complete .. \n");
    }
    else if(pthread_equal(id, tid[1]))
    {
        //Second thread
        printf("Second thread here .. \n");
        //printf("Sleeping for 5 secs.. \n");
	printf("Waiting for keyboard input.. \n");
        char c = getchar();
        printf("Second thread execution complete \n");
    }
    else 
    {
        //Third thread
        printf("Third thread here .. Sleeping for 20s ..\n");
        sleep(20);
        printf("Third thread execution compete .. \n");
    }
    return NULL;
}

int main()
{

    int i = 0;
    int temp;
    for(i=0;i<3;i++)
    {
        temp = pthread_create(&(tid[i]), NULL, func, NULL);
        if(temp)
        {
            printf("cannot create threads .. \n");
        }
        else
            printf("Thread %d created successfully.. \n", (i+1));
    }

    //sleep(50);
    while(1);
    printf("Main program executing.. \n");

}
