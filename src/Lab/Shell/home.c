#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main()
{
	
	struct passwd *pw = getpwuid(getuid());

	const char *homedir = pw->pw_dir;
	printf("%s \n", homedir);
	char str[20];
	gets(str);
	printf("%s \n", str);
}