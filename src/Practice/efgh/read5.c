#include <stdio.h>
#include <stdlib.h>

int main()
{


	printf("Reading content from the file : \n");
	FILE *fp;

	fp = fopen("./thisFile.txt", "r");
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
		printf("%c ",c);
	}
	printf("\n");
	fclose(fp);
}
