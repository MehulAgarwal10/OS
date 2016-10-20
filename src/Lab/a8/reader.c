#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#define MAX_BUF 1024

int main()
{
    int fd,fd2;
    char *myfifo2 = "/tmp/myfifo2";
    char * myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];
    mkfifo(myfifo2, 0666);
    /* open, read, and display the message from the FIFO */

    fd = open(myfifo, O_RDONLY);
    fd2 = open(myfifo2, O_WRONLY);
    char *s = (char *)(malloc(sizeof(char) * 1024));
    printf("Terminal 2 \n__________\n\n");
    while(1)
    {
    read(fd, buf, MAX_BUF);
    printf("User 1 : %s\n", buf);
    if(strcmp("exit",buf) == 0)
    {
        printf("(User 1 has left, Exiting..)\n");
        break;
    }
    printf("User 2 : ");
    gets(s);
    write(fd2, s, MAX_BUF);
    if(strcmp("exit",s) == 0)
    {
        printf("(Exiting ..) \n");
        break;
    }
}
    close(fd);
    close(fd2);
    unlink(myfifo2);
    return 0;
}