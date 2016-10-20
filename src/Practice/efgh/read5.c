#include <stdio.h>
#include <stdlib.h>

int main()
{


	printf("Reading every 5th byte from the file and writing to output.txt. \n");
	FILE *fp;

	fp = fopen("./thisFile.txt", "r");
	FILE *write;
	write = fopen("./output.txt", "w");
	FILE *read;
	read = fopen("./output.txt", "r");
	char *s = (char*)(malloc(sizeof(char) * 40));
	char c;
	char d;
	while(1)
	{
		c = getc(fp);
		if(c == EOF)
		{
			break;
		}
		fseek(fp,5,SEEK_CUR);
		fprintf(write,"%c-",c);
	}
	fclose(write);
	printf("Done.\nReading from the output file.. \n");
	while(1)
	{
		c = getc(read);
		if(c == EOF)
		{
			printf("\nReached end of file. \n");
			break;
		}
		printf("%c",c);
	}
	
	fclose(read);
	fclose(fp);
}
