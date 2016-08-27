#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <malloc.h>


int val;
char *arrWords[100];


void display()
{
	int i;
	for(i=0;i<=val;i++)
	{
		if(arrWords[i] != NULL)
		{
			printf("%s\t",arrWords[i]);
		}
	}
	printf("\n");
}


void parse(char *str)
{

	int length = strlen(str);
	arrWords[val] = (char *)malloc(sizeof(char)* length+1);
	strcpy(arrWords[val],str);
	val++;

}

void addToList(char *sentence)
{
	int length = strlen(sentence);
	char *word = (char *)calloc(1, sizeof(char));
	int wordI=0;
	char temp;
	int i;
	for(i=0;i<length;i++)
	{
		temp = sentence[i];
		if(temp == ' ' || temp == '\n' ||temp == '\t' || temp == '\0')
		{
			parse(word);
			word = (char *)(calloc(1,sizeof(char)));
			wordI = 0;
			continue;
		}
		else
		{
			word = realloc(word,sizeof(char) * (wordI+1));
			word[wordI] = temp;
			wordI++;
		
		}
	}
	parse(word);
	word = (char *)(calloc(1,sizeof(char)));
	wordI = 0;
}

int main()
{
	
	struct passwd *pw = getpwuid(getuid());
	val = 0;
	const char *homedir = pw->pw_dir;
	printf("%s \n", homedir);
	chdir("..");
	char pth[40];
	getcwd(pth,sizeof(pth));
	printf("Current Working directory .. ");
	printf("%s \n", pth);
	char str[30];
	//char *arrWords[100];
	int i;	
	for(i=0;i<3;i++)
	{
		gets(str);
		addToList(str);
	}
	printf("Printing the final array\n");
	display();

}
