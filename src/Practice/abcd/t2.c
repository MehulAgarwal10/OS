#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



void *func()
{
    //(*count)++;
//    printf("Hello world from thread !\n");
    return NULL;
}


int main()
{
    long count =0;
    int temp;
    pthread_t tid;
    while(1)
    {
        temp = pthread_create(&tid, NULL, func, NULL);
        count++;
        //pthread_join(tid, NULL);
        if(temp != 0)
        {
            printf("Maximum number of threads : %ld\n", count);
            return;
        }
    }
    return;
}