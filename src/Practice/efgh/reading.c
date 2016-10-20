#include <stdio.h>
#include <stdlib.h>

int main()
{


	printf("Reading content from the file : ");
	FILE *fp;

	fp = fopen("./thisFile.txt", "r");
	FILE *des;
	des = fopen("./output.txt", "w");
	char *s = (char*)(malloc(sizeof(char) * 40));
	char c;

	while((c = getc(fp)) != EOF)
	{
		printf("%c",c);
	}
	fclose(fp);
}