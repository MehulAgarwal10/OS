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
	//printf("Entering parse function .. \n");
	int length = strlen(str);
	arrWords[val] = (char *)malloc(sizeof(char)* length+1);

	strcpy(arrWords[val],str);
	//printf("Copied command to arrWords.. \n");
	val++;
	commandCount++;
	arrWords[val] = '\0';
	//printf("Made character null .. \n");

}

void addToList(char *sentence)
{
	//printf("Parsing sentence .. %s.. \n", sentence);
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
	//printf("Done parsing.. \n");
}

void takeInput()
{
	input = (char *)(malloc(200 * sizeof(char)));
	gets(input);
	//printf("%s", input);

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
			//printf("Reading line : \n");
		if(temp == '|')
		{
			//printf("Pipe found .. \n");
			char *comm = (char *)(malloc(sizeof(char)*commandLength));
			//trim(command, comm);
			//printf("Trimmed string : %s..\n", comm);
					//pipedCommands = (char **)(realloc(pipedCommands, sizeof(char) * (i+1)));
			pipedCommands[pipeI] = (char *)(malloc(sizeof(char) * strlen(command+1)));
			strcpy(pipedCommands[pipeI++],command);
			//pipeCount++;
			//pipedCommands[i+1] = '\0';
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
			//pipeCount++;
			//pipedCommands[i+1] = '\0';
			command = (char *)(malloc(sizeof(char) * 1));
			commandLength = 0;

	//printf("Seperated commands .. : \n");
	for(i=0;i<=pipeCount;i++)
	{
		//printf("%s - ", pipedCommands[i]);
	}
	//printf("\n");

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
		//printf("Reading Command List (%d) ..\n", (i+1));
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
				//printf("Reached end of full command now.. \n");
				exit(0);
			}
		}
		else if(pid == 0)
		{
			//printf("In Child for process %d.. Command : %s..\n", (i+1), pipedCommands[i]);
			char *tempString;
			trim(pipedCommands[i],tempString);
			addToList(tempString);
			//printf("Executing the command .. %s.. \n", arrWords[0]);
			// Add to execution list here
			
			dup2(fd,0);
			if(i != pipeCount)
			{
				//printf("Sending to Standard Output.. \n");
				dup2(pfd[1],1);
			}
			else
			{
				dup2(1,1);
			}
			close(pfd[0]);
			close(pfd[1]);
			//printf("Commands here : ");
			for(i=0;i<commandCount;i++)
			{
				//printf("%s, ",arrWords[i]);
			}
			//printf("\n");
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
			//printf("Beginning execution .. \n");
			if(execvp(arrWords[0], arrWords)<1)
			{
				printf("%s: command not found\n", arrWords[0]);
			}
					//Execute
					exit(-1);
				}
			}

}

int main()
{
	pipeCount = 0;
	
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
	//char *arg[100];
	
	//char path2[205];
	while(1)
	{
	pipeCount = 0;
	arrWords = (char**)realloc(arrWords,100*sizeof(char));
	//commandCount = 0;
	val = 0;
	currentIndex += commandCount;

	getcwd(path,sizeof(path));
	//printf(ANSI_COLOR_BLUE 	"MyShell:" ANSI_COLOR_RESET);
	//printf(ANSI_COLOR_GREEN 	"$ "  ANSI_COLOR_RESET, path);
	printf(ANSI_COLOR_BLUE "MyShell:" ANSI_COLOR_GREEN "$ " ANSI_COLOR_RESET);	
	//printf(path2);		
	                      //  Old get command _ gets(com);
	//parse(com, arrWords);
	                         //   Old Parse Command __ addToList(com);
	//char *arg[] = {"", NULL};
	//arg[0] = com;
	takeInput();
	//printf("Input read : %s.. \n",input);
	countPipes();
	//printf("Pipes found : %d..\n", pipeCount);
	
	
	if(pipeCount == 0)
	{
		//printf("No pipes found .. \n");
		addToList(input);
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
	else if(strcmp(arrWords[0], "exit") == 0)
	{
		printf("Goodbye\n");
		return;
	}
	///printf("Forking .. \n");
	

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


