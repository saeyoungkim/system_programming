/**
 * waitが垂直な二つの子プロセスにも効くのかを試す
 * */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    pid_t pid;
    
    pid = fork();

    if(pid == 0) // chlid process 
    {
        pid_t pid_2;

        pid_2 = fork();

        if(pid_2 == 0) // chlid process 
        {
            for(int i = 0; i < 100000; ++i) {
                fprintf(stdout, "chlid child process pid : %d - %d\n", getpid(), i);
            }
            return 0;
        }
        else if(pid_2 > 0) {
            wait(NULL);
            for(int i = 0; i < 100000; ++i) {
                fprintf(stdout, "chlid process pid : %d - %d\n", getpid(), i);
            }
            return 0;
        }
    }
    else if(pid > 0) // parent process 
    {
        wait(NULL);
        for(int i = 0; i < 100000; ++i) {
            fprintf(stdout, "parent process pid : %d - %d\n", getpid(), i);
        }
        return 0;
    }
}