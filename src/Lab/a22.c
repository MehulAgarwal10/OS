#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main()
{
	struct timeval start, temp;
	long mtime, secs, usecs;
	int currentContext;
	int i,j;
	int pid;
	currentContext = (int)getpid();
	gettimeofday(&start,NULL);
	pid = fork();
	int tempPid;
	for(i=0;i<200;i++)
	{
		tempPid = (int)getpid();
		if(currentContext != tempPid)
		{
			gettimeofday(&temp, NULL);
			secs = temp.tv_sec - start.tv_sec;
			usecs = temp.tv_sec - start.tv_sec;
			mtime = ((secs) * 1000 + usecs/1000.0) + 0.5;
			printf("Context switch time : %ld millisecs\n", mtime);
			//gettimeofday(&start,NULL);
			//currentContext = tempPid;

		}
		printf("Process ID : %d, Count = %d\n", tempPid, i);
		gettimeofday(&start,NULL);
		currentContext = tempPid;
	}
	/*
	if(pid == 0)
	{
		//Child process
		for(i=1;i<100;i++)
		{
			printf("Child process id : %d, Count = %d\n",(int)getpid(), i);
		}
	}
	else
	{
		//Parent
		for(j=1;j<100;j++)
		{
			printf("Parent process id : %d, Count = %d\n", (int)getpid(), j);
		}
	}
	*/
}
