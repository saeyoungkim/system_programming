#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int p[2];

    // create pipe
    if (pipe(p) == -1) {
        exit(1);
    }

    // child process
    if(fork() == 0) {
        close(0);
        dup(p[0]);
        close(p[0]);
        close(p[1]);
        const char* argv[2];
        argv[0] = "wc";
        argv[1] = 0;
        execv("/usr/bin/wc", argv);
    }
    // parent process
    else {
        close(p[0]);
        write(p[1], "Hello world\n", 12);
        sleep(5);
        write(p[1], "Hello world\n", 12);
        close(p[1]);
    }
}