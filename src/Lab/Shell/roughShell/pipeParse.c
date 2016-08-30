#include <stdio.h>
#include <malloc.h>
#include <string.h>

char *input;
int pipeCount;
char **pipedCommands;

void trim(char *input, char *output)
{
	int i,j=0;
	for(i=0;input[i] == ' '; i++)
	{
		;
	}
	while(input[i] != '\0')
	{
		output[i] = input[i];
		i++;
	}
}

int main()
{
	pipeCount = 0;
	input = (char *)(malloc(sizeof(char) * 100));
	gets(input);
	seperate();
	int i;
	for(i=0;i<=pipeCount;i++)
	{
		if(pipedCommands[i] != NULL)
		{
			printf("%s\n", pipedCommands[i]);
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
	for(i=0;i<length;i++)
	{
		temp = input[i];
		if(temp == '|')
		{
			pipeCount++;
		}
	}
	int pipeI = 0;
	pipedCommands = (char **)(calloc(pipeCount+1,sizeof(char *)));
	for(i=0;i<length;i++)
	{
		temp = input[i];
		printf("Reading line : \n");
		if(temp == '|')
		{
			printf("Pipe found .. \n");
			char *comm = (char *)(malloc(sizeof(char)*commandLength));
			trim(command, comm);
			printf("Trimmed string : %s..\n", comm);
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
			trim(command, comm);

			strcpy(pipedCommands[pipeI++],command);
			//pipeCount++;
			//pipedCommands[i+1] = '\0';
			command = (char *)(malloc(sizeof(char) * 1));
			commandLength = 0;

}

/*

void seperate()
{
	pipedCommands = (char **)(realloc(pipedCommands,sizeof((char) * 1)));
	char *command = (char *)(malloc(sizeof(char) * 1));
	char temp;
	int length,i; 
	int commandLength = 0;
	length = strlen(input);
	for(i=0;i<length;i++)
	{
		temp = input[i];
		if(temp == '|')
		{
			pipedCommands = (char **)(realloc(pipedCommands, sizeof((char) * (i+1))));
			pipedCommands[i] = (char *)(malloc(sizeof(char) * strlen(command+1)));
			strcpy(pipedCommands[i],command);
			pipeCount++;
			pipedCommands[i+1] = '\0';
			char *command = (char *)(malloc(sizeof(char) * 1));
			commandlength = 0;
		}
		else
		{
			command = realloc(command, sizeof(char) * commandLength+1);
			command[commandLength] = temp;
			commandLength++;
		}
	}
}
*/