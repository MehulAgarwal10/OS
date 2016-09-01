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
char **pipedCommands;
int commandCount;
int currentIndex;
int pipeCount;
char *input;
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
void display()
{
	int i;
	for(i=0;i<commandCount;i++)
	{
		if(arrWords[currentIndex+i] != NULL)
		{
			printf("%s\t",arrWords[currentIndex+i]);
		}
	}
	printf("\n");
}


void parse(char *str)
{

	int length = strlen(str);
	arrWords[currentIndex+val] = (char *)malloc(sizeof(char)* length+1);

	strcpy(arrWords[currentIndex+val],str);
	val++;
	commandCount++;
	printf("CommandCount increased .. \n");
	arrWords[currentIndex+val] = '\0';
	

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
	input = (char *)(malloc(200 * sizeof(char)));
	gets(input);

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
		//arrWords = (char**)realloc(arrWords,(100*sizeof(char)));
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
			char *tempString;
			trim(pipedCommands[i],tempString);
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
			if(strcmp(arrWords[currentIndex], "ls") == 0)
			{
				char addit[] = "--color";
				addToList(addit);
			}
			if(execvp(arrWords[currentIndex], arrWords)<1)
			{
				printf("%s: command not found\n", arrWords[currentIndex]);
			}
					//Execute
					exit(-1);
				}
			}

}

int main()
{
	pipeCount = 0;
	arrWords = (char**)realloc(arrWords,100*sizeof(char));
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
	printf("Command List : ");
	display();
	printf("Command Number : %d..\n",commandCount);
	currentIndex = commandCount;
	pipeCount = 0;
	//arrWords = (char**)realloc(arrWords,100*sizeof(char));
	val = 0;
	//currentIndex += commandCount;

	getcwd(path,sizeof(path));
	printf(ANSI_COLOR_BLUE "MyShell:" ANSI_COLOR_GREEN "$ " ANSI_COLOR_RESET);	
	takeInput();
	countPipes();
	if(input == '\'')
		continue;
	
	if(pipeCount == 0)
	{
		addToList(input);
	if(strcmp(arrWords[currentIndex],"cd") == 0)
	{
		if(arrWords[currentIndex + 1] == NULL)
		{
			
			chdir(homedir);
			continue;
		}
		int len = strlen(arrWords[currentIndex + 1]);
		char *pt = (char *)(calloc(len,sizeof(char)));
		strcpy(pt,arrWords[currentIndex + 1]);

		if(chdir(pt)!=0)
		{
			printf("%s: no such directory\n",pt);
		}
		continue;
	}
	else if(strcmp(arrWords[currentIndex], "exit") == 0)
	{
		printf("Goodbye\n");
		return;
	}

	pid = fork();
	if(pid == 0)
	{
	if(strcmp(com,"exit") ==0)
	{
		printf("Goodbye\n");
		return;
	}
	if(strcmp(arrWords[currentIndex], "ls") == 0)
	{
		char addit[] = "--color";
		addToList(addit);
		printf("CommandCount value : %d.. \n",commandCount);
	}
	if(execvp(arrWords[currentIndex], arrWords)<1)
	{
		printf("%s: command not found\n", arrWords[currentIndex]);
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
else
{
	//printf("Pipe found here .. ! \n");
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

}


