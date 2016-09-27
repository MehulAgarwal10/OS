#include <stdio.h>
#include <sys/types.h>
#include <sched.h>

int main()
{

    struct timespec tp;
    long int tq;
    int a = 5;
    pid_t pid;

    printf("Process id of parent process : %d\n",getpid());
    fork();

    pid = getpid();
    printf("Process id : %d,\nVariable value : %d,\nAddress Space : %p..\n",pid,a,&a);
    sched_rr_get_interval(pid,&tp);
    tq = (tp.tv_nsec);
    printf("Child time quantum : %ld..\n",tq);
}