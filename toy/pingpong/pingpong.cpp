#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>

void perror(const std::string& str, int code) {
    std::cout << str << std::endl;
    exit(code);
}

int main() {
    int p[2];

    if(pipe(p) == -1) {
        perror("cannot create pipe...");
    }

    // child process
    if(fork() == 0) {
        char ch;
        read(p[0], &ch, 1);
        close(p[0]);
        printf("%u: received ping with byte %c\n", getpid(), ch);
        write(p[1], "child", 1);
        close(p[1]);
    }
    // parent process
    else {
        write(p[1], "parent", 1);
        close(p[1]);
        wait(0);
        char ch;
        read(p[0], &ch, 1);
        close(p[0]);
        printf("%u: received pong with byte %c\n", getpid(), ch);
    }
}