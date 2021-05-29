#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(void) {
    printf("start to fork...\n");
    int pid = fork();
    if(pid < 0){
        printf(stderr, "Cannot fork...");
        exit(2);        
    }
    // if child
    if(pid == 0) {
        write(1, "hello ", 6);
        printf("\nchild process is done...\n");
        exit(0);        
    } 
    // parent
    else { 
        wait(0);
        write(1, "world\n", 6);
    }

    return 0;
}