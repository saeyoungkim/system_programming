#include <stdio.h>
#include <stdlib.h>

int g = 10;

int main() {
    int* p = malloc(10 * sizeof(int));
    for(int i = 0; i < 10; ++i) {
        p[i] = i;
    }

    int pid = fork();
    if(pid == -1) {
        exit(1);
    }

    // parent process
    if(pid > 0) {
        wait(0);
        for(int i = 0; i < 10; ++i) {
            printf("%d ", p[i]);
        }
        printf("\n");
        printf("g = %d\n", g);
    } 
    // child process
    else {
        for(int i = 0; i < 10; ++i) {
            p[i] *= 3;
            printf("%d ", p[i]);
        }
        printf("\n");
        g *= 10;
        printf("g = %d\n", g);
    }
    printf("free!!\n");
    free(p);
}