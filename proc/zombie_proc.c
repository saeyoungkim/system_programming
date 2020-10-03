#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    pid_t pid;

    pid = fork();

    if(pid < 0)
    {
        perror("fork() does not work well");
        return 1;
    }
    else if(pid == 0) // child process
    {
        while(1){
        }
        printf("I'm child\n");
        return 2;
    }
    else // parent process
    {
        printf("I'm parent\n");
        return 0;
    }

    return 0;
}