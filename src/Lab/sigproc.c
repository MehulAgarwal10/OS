#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

void handler();

int main()
{

	signal(SIGINT, handler);
		
	while(1)
		;

}

void handler()
{
	printf("\nI will not terminate ! \n");
	
	/*sleep(3);
	printf("Ok nevermind exiting.. \n");
	exit(0);
	*/
	
}


