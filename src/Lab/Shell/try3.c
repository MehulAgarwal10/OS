#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <malloc.h>

#define ANSI_COLOR_GREEN   "\x1b[92m\x1b[1m"
#define ANSI_COLOR_BLUE "\x1b[94m\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int val;
char **arrWords;
int commandCount;
int currentIndex;

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
	commandCount++;
	arrWords[val] = '\0';

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
			const char *homedir = pw->pw_dir;
	char *argv[] = {"", "", NULL};
	commandCount = 0;
	currentIndex = 0;
	int pid;
	char com[20];
	char path[200];
	val = 0;
	//char *arg[100];
	
	//char path2[205];
	while(1)
	{
	val = 0;
	arrWords = (char**)realloc(arrWords,(100*sizeof(char)));
	currentIndex += commandCount;

	getcwd(path,sizeof(path));
	printf(ANSI_COLOR_BLUE 	"MyShell:" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_GREEN 	"$ "  ANSI_COLOR_RESET, path);
	//printf(path2);		
	gets(com);
	//parse(com, arrWords);
	addToList(com);
	//char *arg[] = {"", NULL};
	//arg[0] = com;
	if(strcmp(arrWords[0],"cd") == 0)
	{
		if(arrWords[1] == NULL)
		{
			
			chdir(homedir);
			continue;
		}
		int len = strlen(arrWords[1]);
		//char path[len+1] = arrWords[1];
		char *pt = (char *)(calloc(len,sizeof(char)));
		strcpy(pt,arrWords[1]);

		if(chdir(pt)!=0)
		{
			printf("%s: no such directory\n",pt);
		}
		continue;
	}

	pid = fork();
	if(pid == 0)
	{
	if(strcmp(com,"exit") ==0)
	{
		printf("Goodbye\n");
		return;
	}
	if(strcmp(arrWords[0], "ls") == 0)
	{
		char addit[] = "--color";
		addToList(addit);
		/*
		printf("Executing ls..");
		argv[0] = "ls";
		argv[1] = "--color";
		execvp(argv[0], argv);
		exit(1);
		*/
	}
	if(execvp(arrWords[0], arrWords)<1)
	{
		printf("%s: command not found\n", com);
	}
	exit(1);
	}
	else
	{
		if(strcmp(com,"exit")==0)
			return;
		wait();
		continue;
	}
}

}


