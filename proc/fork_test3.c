/**
 * waitが水平な二つの子プロセスにも効くのかを試す
 * */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    pid_t pid;
    
    pid = fork();

    if(pid == 0) // chlid process 
    {
        fprintf(stdout, "chlid process pid : %d\n", getpid());
        return 0;
    }
    else if(pid > 0) // parent process 
    {
        pid_t pid_2;

        pid_2 = fork();

        if(pid_2 == 0) // chlid process 
        {
            fprintf(stdout, "chlid process pid : %d\n", getpid());
            return 0;
        }
        else if(pid_2 > 0) // parent process 
        {
            wait(NULL);
            fprintf(stdout, "parent process pid: %d\n", getpid());
            return 0;
        }
    }
}