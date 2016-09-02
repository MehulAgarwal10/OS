#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <malloc.h>
#include <signal.h>

#define ANSI_COLOR_GREEN   "\x1b[92m\x1b[1m"
#define ANSI_COLOR_BLUE "\x1b[94m\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int val;
char **arrWords;
char **pipedCommands;
int commandCount;
int currentIndex;
int pipeCount;
char *input;
char *fulllist[200];
int historyCount;

void trim(char *input, char *output)
{


	int i,len;
	len = strlen(input);
	i = len-1;
	while(input[i] == ' ')
	{
		i--;
	}
	int lim = i;
	i = 0;
	while(input[i] == ' ')
	{
		i++;
	}
	int lowLim,j=0,size;
	lowLim = i;
	size = lim-lowLim+1;
	output = realloc(output,size * sizeof(char));
	for(i=lowLim;i<=lim;i++)
	{
		output[j] = input[i];
		j++;
	}
}

void *func()
{
	exit(-1);
}

void funcMain()
{
	;
}
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
	//char *str;
	//trim(str2,str);
	//printf("Command word : %s..\n",str);
	int length = strlen(str);
	arrWords[val] = (char *)malloc(sizeof(char)* length+1);
	strcpy(arrWords[val],str);
	//fulllist[historyCount] = (char *)(malloc(sizeof(char)*length+1));
	//strcpy(fulllist[historyCount++],str);
	val++;
	commandCount++;
	arrWords[val] = '\0';


}

int writeToFile()
{
	int i = 0,length;
}

void showHistory()
{
	int i =0;
	for(i=0;i<historyCount;i++)
	{
		printf("%d\t%s\n",(i+1),fulllist[i]);
	}
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

void takeInput()
{
	char *inputString = (char *)(malloc(200 * sizeof(char)));
	char *check = (char *)(malloc(200 * sizeof(char)));
	input = (char *)(malloc(200 * sizeof(char)));
	gets(inputString);
	trim(inputString,input);
}

void countPipes()
{
	int length = strlen(input);
	int i =0;
	char temp;
	for(i=0;i<length;i++)
	{
		temp = input[i];
		if(temp == '|')
		{
			pipeCount++;
		}
	}
}
void seperate()
{
	pipedCommands = (char **)(realloc(pipedCommands,sizeof(char) * 1));
	char *command = (char *)(malloc(sizeof(char) * 1));
	char temp;
	int length,i; 
	int commandLength = 0;
	length = strlen(input);

	int pipeI = 0;
	pipedCommands = (char **)(calloc(pipeCount+1,sizeof(char *)));
	for(i=0;i<length;i++)
	{
		temp = input[i];
		if(temp == '|')
		{
			char *comm = (char *)(malloc(sizeof(char)*commandLength));
			pipedCommands[pipeI] = (char *)(malloc(sizeof(char) * strlen(command+1)));
			strcpy(pipedCommands[pipeI++],command);
			command = (char *)(malloc(sizeof(char) * 1));
			commandLength = 0;
		}
		else
		{
			command = realloc(command, sizeof(char) * commandLength+1);
			command[commandLength] = temp;
			commandLength++;
		}
	}
	pipedCommands[pipeI] = (char *)(malloc(sizeof(char) * strlen(command+1)));
	char *comm = (char *)(malloc(sizeof(char)*commandLength));
	//trim(command, comm);

	strcpy(pipedCommands[pipeI++],command);
	command = (char *)(malloc(sizeof(char) * 1));
	commandLength = 0;

}


void pipedProcess()
{
	pid_t pid;
	int pfd[2];
	int fd;
	int i = 0;
	for(i=0;i<=pipeCount;i++)
	{
		val = 0;	
		arrWords = (char**)realloc(arrWords,(100*sizeof(char)));
		if(pipe(pfd) < 0)
		{
			printf("Error in piping \n");
		}
		pid = fork();
		if(pid < 0)
		{
			printf("Error in forking \n");
		}
		if(pid > 0)
		{
			signal(SIGINT,funcMain);
			//add random sigchld signal() here
			waitpid(-1,0,0);
			close(pfd[1]);
			fd = pfd[0];
			if(i == pipeCount)
			{
				exit(0);
			}
		}
		else if(pid == 0)
		{
			signal(SIGINT,func);
			//printf("%s..\n",pipedCommands[i]);
			char *tempString;
			trim(pipedCommands[i],tempString);
			//printf("%s\n",pipedCommands[i]);
			addToList(tempString);
			dup2(fd,0);
			if(i != pipeCount)
			{
				dup2(pfd[1],1);
			}
			else
			{
				dup2(1,1);
			}
			close(pfd[0]);
			close(pfd[1]);
			if(strcmp(arrWords[0], "ls") == 0)
			{
				char addit[] = "--color";
				addToList(addit);
			}
			if(strcmp(arrWords[0], "history") == 0)
			{
				showHistory();
			}
			else if(execvp(arrWords[0], arrWords)<1)
			{
				printf("%s: command not found\n", arrWords[0]);
			}
			//Execute
			exit(-1);
		}
	}

}


int isString(char *cc)
{
	char temp;
	int i = 0,len = strlen(cc);
	for(i=0;i<len;i++)
	{
		temp = cc[i];
		if(temp != ' ' || temp != '\n' || temp != '\t' || temp != '\0')
		{
			printf("Returning 1.. \n");
			return 1;
		}
	}
	return 0;
}

int main()
{
	pipeCount = 0;
	historyCount = 0;
	input = (char *)(calloc(2,sizeof(char)));
	//return;
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	char *argv[] = {"", "", NULL};
	commandCount = 0;
	currentIndex = 0;
	int pid;
	char com[20];
	char path[200];
	val = 0;
	while(1)
	{
		pipeCount = 0;
		arrWords = (char**)realloc(arrWords,100*sizeof(char));
		val = 0;
		currentIndex += commandCount;
		getcwd(path,sizeof(path));
		printf(ANSI_COLOR_BLUE "MyShell:" ANSI_COLOR_GREEN "$ " ANSI_COLOR_RESET);	
		takeInput();

		countPipes();
		//printf("Counted pipes ..\n");
		if(input[0] == NULL)
		{
			continue;
		}
		fulllist[historyCount] = (char *)(calloc(50,sizeof(char)));
		strcpy(fulllist[historyCount++],input);
		//if(pipeCount == 0)
		//{
		addToList(input);
		if(strcmp(arrWords[0],"cd") == 0)
		{
			if(arrWords[1] == NULL)
			{

				chdir(homedir);
				continue;
			}
			int len = strlen(arrWords[1]);
			char *pt = (char *)(calloc(len,sizeof(char)));
			strcpy(pt,arrWords[1]);

			if(chdir(pt)!=0)
			{
				printf("%s: no such directory\n",pt);
			}
			continue;
		}
		else if(strcmp(arrWords[0], "exit") == 0)
		{
			//printf("main() exit called .. \n");
			printf("Goodbye\n");
			return;
		}

		signal(SIGINT,funcMain);
		pid = fork();
		if(pid == 0)
		{
			seperate();
			pipedProcess();
		}	
		else
		{
			wait();
		}
		continue;

	}

	}


