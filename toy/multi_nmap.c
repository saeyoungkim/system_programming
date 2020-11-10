#include <pthread.h>
#include <sys/socket.h> // socket
#include <netinet/in.h> // sockaddr_in
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // write

struct Range {
    int start;
    int end;
};

#define THREAD_MAX 8
#define PORT_MAX 65536

void* scan(void*);

int isUsed[PORT_MAX];

int main(void) {

    const int INTERVAL = PORT_MAX / THREAD_MAX;

    pthread_t threads[THREAD_MAX];
    struct Range ranges[THREAD_MAX];

    int start = 0;
    int end = INTERVAL;

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for(int i = 0; i < THREAD_MAX; ++i){
        ranges[i].start = start;
        ranges[i].end = end;
        pthread_create(&threads[i], &attr, scan, &ranges[i]);
        start += INTERVAL;
        end += INTERVAL;
    }

    for(int i = 0; i < THREAD_MAX; ++i){
        pthread_join(threads[i], NULL);
    }

    for(int i = 0; i < PORT_MAX; ++i){
        if(i && isUsed[i]){
            fprintf(stdout, "The port %d is used.\n", i);
        }
        else if(i && !isUsed[i]){
            fprintf(stdout, "The port %d is available.\n", i);
        }
    }

    return 0;
}

void* scan(void* param) {
    struct Range* range = (struct Range*) param;

    // initialization
    struct sockaddr_in addr_in;
    memset(&addr_in, 0, sizeof(addr_in));

    // set sock address
    addr_in.sin_family = AF_INET;
    addr_in.sin_addr.s_addr = INADDR_ANY;
    
    // bind and find
    for(int port = range->start; port < range->end; ++port){
        // get socket fd
        int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

        addr_in.sin_port = port;
        if(bind(sock_fd, (struct sockaddr*)&addr_in, sizeof(addr_in)) == -1){
            isUsed[port] = 1;
        }
        close(sock_fd);
    }

    pthread_exit(NULL);
}