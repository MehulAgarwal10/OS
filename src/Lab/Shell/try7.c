#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <malloc.h>
#include <signal.h>

#define ANSI_COLOR_GREEN   "\x1b[92m\x1b[1m"
#define ANSI_COLOR_RED "\x1b[91m\x1b[1m"
#define ANSI_COLOR_BLUE "\x1b[94m\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_CYAN "\x1b[96m\x1b[1m"
#define ANSI_COLOR_YELLOW "\x1b[93m\x1b[1m"

int val;
char **arrWords;
char **pipedCommands;
int commandCount;
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
	exit(0);
}

void *funcMain()
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
	int length = strlen(str);
	arrWords[val] = (char *)malloc(sizeof(char)* length+1);
	strcpy(arrWords[val],str);
	val++;
	commandCount++;
	arrWords[val] = '\0';
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
	input = (char *)(calloc(200,sizeof(char)));
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
			exit(0);
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

char* makePath(char *path, char *home)
{
	if (strcmp(path,home) == 0)
	{
		return "~";
	} 
	int k,flag,homeLength = strlen(home);
	flag = 0;
	for(k=0;k<homeLength;k++)
	{
		if(path[k] != home[k])
		{
			flag = 1;
			break;
		}
	}
	if(flag == 1)
	//if(strcmp(path,home) < 0)
	{
		return path;
	}
	//printf("Making the path.. \n");
	char temp;
	int i,j,len3,len2,len = strlen(home);
	len2 = strlen(path);
	len3 = len2 - len; len3++;
	char *newPath = (char *)(calloc(len3,sizeof(char)));
	newPath[0] = '~';
	//printf("Tilde : ~\n");
	//printf("newPath initial : %s\n",newPath);
	j = 1;
	for(i=len;i<len2;i++)
	{
		temp = path[i];
		//printf("Character : %c\n",temp);
		newPath[j++] = path[i];
	}
	//printf("newPath : %s\n",newPath);
	return newPath;

}

void childFunc()
{
	while(waitpid(-1,0,WNOHANG)>0);
}

int main()
{
	pipeCount = 0;
	historyCount = 0;
	int amp1;
	char amp2;
	//return;
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	char *argv[] = {"", "", NULL};
	commandCount = 0;
	int pid;
	char com[20];
	char path[200];
	val = 0;
	while(1)
	{
		signal(SIGINT,funcMain);
		getcwd(path,sizeof(path));
		pipeCount = 0;
		arrWords = (char**)realloc(arrWords,100*sizeof(char));
		val = 0;
		getcwd(path,sizeof(path));
		//printf("Path : %s, Home : %s\n",path,homedir);
		char *newPath = makePath(path,homedir);
		printf(ANSI_COLOR_GREEN "MyShell:" ANSI_COLOR_CYAN "%s" ANSI_COLOR_RED "$ " ANSI_COLOR_RESET,newPath);	
		input = (char *)(calloc(sizeof(char),1));
		takeInput();
		countPipes();
		if(input[0] == '\0')
		{
			continue;
		}
		fulllist[historyCount] = (char *)(calloc(50,sizeof(char)));
		strcpy(fulllist[historyCount++],input);
		if(pipeCount == 0)
		{
			addToList(input);
			//printf("Val : %d\n",val);
			amp1 = strlen(arrWords[val-1]);
			//printf("Amp1 : %d\n",amp1);
			amp2 = arrWords[val-1][amp1-1];
			//printf("Amp2 : %c\n",amp2);
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
			if(strcmp(arrWords[0],"history") == 0)
			{
				showHistory();
				continue;
			}
			pid = fork();
			if(pid == 0)
			{
				
				//else	
				//signal(SIGINT,func);
				if(strcmp(com,"exit") ==0)
				{
					printf("Goodbye\n");
					return;
				}
				if(amp2 == '&')
				{
					printf("Background, PPID : %d\n",getpid());
					//signal(SIGINT,funcMain);
					setpgid(0,0);
					printf("\nNew PPID : %d\n",getpid());
				}

				if(strcmp(arrWords[0], "ls") == 0)
				{
					char addit[] = "--color";
					addToList(addit);
				}
				if(execvp(arrWords[0], arrWords)<1)
				{
					printf("%s: command not found\n", arrWords[0]);
				}
				
				exit(0);
			}
			else
			{

				if(strcmp(com,"exit")==0)
					return;
				if(amp2 == '&')
				{
					printf("Ampersand Found.. Running in backgroun now\n");
					//signal(SIGCHLD,SIG_IGN);
					//while(waitpid(1,0,WNOHANG)>0);
					signal(SIGCHLD,childFunc);
				}
				else
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


