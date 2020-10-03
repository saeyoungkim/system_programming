#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int value = 5;

    pid_t pid;

    pid = fork();

    if(pid > 0) // parent process
    {
        wait(NULL);
        fprintf(stdout, "Parent process : the value is %d\n", value);
        return 0;
    }
    else if(pid == 0) // child process
    {
        fprintf(stdout, "Chlid process : the value is %d\n", value);
        value += 15;
        return 0;
    }
}