#include <stdio.h>
#include <string.h>

char* removeSpaces(char *str)
{
	int i,len;
	char ch;
	//char *output;
	len = strlen(str);
	char *output = (char *)(malloc(sizeof(char) * len));
	int outCount=0;
	for(i=0;i<len-1;i++)
	{
		ch = str[i];
		printf("Character : %c\n",ch);

		if(ch == ' ' || ch == '\t')
		{
			printf("WhiteSpace found\n");
			if(str[i+1] == ' ' )
			{
				printf("Trailing whitespace found too \n");
				continue;
			}
		}
		
			output[outCount++] = str[i];
	}

	output[outCount] = str[i];
	printf("Final : %s \n",output);
	return output;
}


int main()
{
	printf("Enter a string : ");
	char str[200];
	gets(str);

	char *output = removeSpaces(str);
	//removeSpaces(str,output);
	printf("\nAfter removing spaces : %s..\n",output);
}