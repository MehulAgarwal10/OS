#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
int main()
{
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;
	int pid;
	char com[10];
	char path[200];
	
	
	//char path2[205];
	while(1)
	{
		
		
	getcwd(path,sizeof(path));
	printf(ANSI_COLOR_GREEN  "MyShell: $ "  ANSI_COLOR_RESET, path);
	//printf(path2);		
	gets(com);
	char *arg[] = {"", NULL};
	arg[0] = com;
	pid = fork();
	if(pid == 0)
	{
	if(strcmp(com,"exit") ==0)
	{
		printf("Goodbye\n");
		return;
	}
	execvp(arg[0], arg);
	exit(0);
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

