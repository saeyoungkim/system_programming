#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void error(char* msg, int code) {
    printf("%s\n", msg);
    exit(code);
}

int isInteger(char* msg, int len) {
    if(!len) return 0;

    for(int i = 0; i < len; ++i) {
        if('0' > msg[i] || msg[i] > '9') return 0;
    }

    return 1;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        error("please pass only one parameter ...",1);
    }

    if(!isInteger(argv[1], strlen(argv[1]))){
        error("please pass right string which can be converted to integer ...",1);
    }

    int s_t = atoi(argv[1]);

    if(s_t < 0){
        error("please pass positive value for time...",1);
    }

    sleep((unsigned int)(s_t));
    return 0;
}