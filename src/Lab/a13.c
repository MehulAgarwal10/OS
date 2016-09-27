#include <sys/time.h>
#include <stdio.h>  
//#include <unistd.h>

int main(void) {
	struct timeval start, end;
	long mtime, secs, usecs;    
	printf("Input : ");
	char ch;
	gettimeofday(&start, NULL);
	scanf("%c",&ch);
	gettimeofday(&end, NULL);
	secs  = end.tv_sec  - start.tv_sec;
	usecs = end.tv_usec - start.tv_usec;
	mtime = ((secs) * 1000 + usecs/1000.0) + 0.5;
	printf("Elapsed time: %ld millisecs\n", mtime);
	return 0;
}



/*#include <stdio.h>
#include <time.h>

int main()
{
printf("Input : ");
clock_t begin = clock();

char ch;
scanf("%c",&ch);

clock_t end = clock();
double time = (double)(end-begin)*1.00;
printf("Begin at : %lf\n",(double)begin);
printf("End at : %lf\n",(double)end);
printf("Time Spent : %lf\n",time);
}
 */


