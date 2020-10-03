#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    fork();
    fork();
    fork();
    fprintf(stdout, "pid is %d\n", getpid());
    return 0;
}