#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int max = 0, min = 0, avg = 0;

void* calculate_max(void* params);
void* calculate_min(void* params);
void* calculate_avg(void* params);

int main(int arg, char* argv[]) {
    if(arg < 2) {
        fprintf(stderr, "The number of arguments are illegal.\n");
        return 1;
    }

    pthread_t tid[3];
    pthread_attr_t attr;

    // init attribute of thread
    pthread_attr_init(&attr);
    // create 3 pthreads
    
    pthread_create(&tid[0], &attr, calculate_max, (void*) argv);
    pthread_create(&tid[1], &attr, calculate_min, (void*) argv);
    pthread_create(&tid[2], &attr, calculate_avg, (void*) argv);

    // join 3 pthreads
    for(int i = 0; i < 3; ++i){
        pthread_join(tid[i], NULL);
    }
    fprintf(stdout, "The maximum value is %d\n", max);
    fprintf(stdout, "The minimum value is %d\n", min);
    fprintf(stdout, "The average value is %d\n", avg);
}

void* calculate_max(void* params) {
    char** _params =  params;

    max = atoi(_params[1]);

    int idx = 1;
    int tmp;
    while(_params[idx] != '\0') {
        tmp = atoi(_params[idx]);
        if(max < tmp) max = tmp;
        ++idx;
    }
    pthread_exit(0);
}

void* calculate_min(void* params) {
    char** _params =  params;

    min = atoi(_params[1]);

    int idx = 1;
    int tmp;
    while(_params[idx] != '\0') {
        tmp = atoi(_params[idx]);
        if(min > tmp) min = tmp;
        ++idx;
    }
    pthread_exit(0);
}

void* calculate_avg(void* params) {
    char** _params = (char**) params;

    min = atoi(_params[1]);

    int idx = 1;
    int ct = 0;
    while(_params[idx] != '\0') {
        avg += atoi(_params[idx]);
        ++idx;
        ++ct;
    }

    avg /= ct;
    pthread_exit(0);
}