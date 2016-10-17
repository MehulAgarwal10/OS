#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

FILE *fp;

void func(int *num)
{

	printf("Exiting.. \n");
	fclose(fp);
}
int main()
{
	signal(SIGINT,func);
	printf("Enter content to add to file : ");
	char *s;
	s = (char *)(malloc(sizeof(char) * 40));

	

	
	fp = fopen("./thisFile.txt", "a+");
	while(1)
		{
			gets(s);
			fprintf(fp,"%s\n",s);
		}
	//fclose(fp);
}

