#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_BUF 1024


int main()
{
    int fd,fd2;
    char * myfifo = "/tmp/myfifo";
    char *myfifo2 = "/tmp/myfifo2";
    char buf[MAX_BUF];

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);
    int count = 1;
    fd = open(myfifo, O_WRONLY);
    char temp;
    //scanf("%c",&temp);
    fd2 = open(myfifo2, O_RDONLY);
    char *s = (char *)(malloc(sizeof(char) * 1024));
    printf("Terminal 1\n__________\n\n");
    /* write "Hi" to the FIFO */
    while(1)
    {
    printf("User 1 : ");
    gets(s);
    write(fd, s, MAX_BUF);
    if(strcmp("exit",s) == 0 )
    {
        printf("(Exiting ..) \n");
        break;
    }
    read(fd2, buf, MAX_BUF);
    printf("User 2 : %s\n",buf);
    if(strcmp("exit",buf) == 0)
    {
        printf("(User 2 has left, Exiting..)\n");
        break;
    }
    count++;
}
    /* remove the FIFO */
close(fd);
close(fd2);
    unlink(myfifo);

    return 0;
}
