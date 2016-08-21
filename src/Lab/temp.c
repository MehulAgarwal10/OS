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
	printf("Current Process ID  : %d\n", currentContext);
	//gettimeofday(&start,NULL);
	pid = fork();
	int tempPid;
	for(i=0;i<50;i++)
	{
		tempPid = (int)getpid();
		printf("CurrentContext = %d, getpid() value : %d\n", currentContext, tempPid);
		
		if(currentContext != tempPid)
		{
			/*
			gettimeofday(&temp, NULL);
			secs = temp.tv_sec - start.tv_sec;
			usecs = temp.tv_sec - start.tv_sec;
			mtime = ((secs) * 1000 + usecs/1000.0) + 0.5;
			printf("Context switch time : %ld millisecs\n", mtime);
			//gettimeofday(&start,NULL);
			//currentContext = tempPid;
			*/
			printf("Context Change.. \n");

		}
		printf("Process ID : %d, Count = %d\n", (int)getpid(), i);
		//gettimeofday(&start,NULL);
		currentContext = (int)getpid();
		printf("CurrentContext = %d..\n", currentContext);
	}
}
