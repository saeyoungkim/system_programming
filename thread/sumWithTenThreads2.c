#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#define WORKERS_SIZE 10

int sum;
int j = 0;

void* runner(void* param);

int main(int argc, char* argv[]) {
    sum = 0;
    // create thread identifiers
    pthread_t workers[WORKERS_SIZE];
    // create thread identifier's attribute
    pthread_attr_t attr;
    // init all attribute
    pthread_attr_init(&attr);
    // create
    for(int i = 0; i < WORKERS_SIZE; ++i){
        j = i;
        pthread_create(&workers[i], &attr, runner, &j);
    }
    for(int i = 0; i < WORKERS_SIZE; ++i){
        pthread_join(workers[i], NULL);
    }

    printf("sum = %d\n", sum);

    return 0;
}

void* runner(void* param) {
    uint64_t tid;
    pthread_threadid_np(NULL, &tid);

    printf("thread self : %llu\n", tid);
    printf("param : %d\n", *(int*)param);

    int val = *(int*)param;

    sum += val;

    pthread_exit(0);
}