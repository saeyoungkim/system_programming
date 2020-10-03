#include <stdlib.h>

#define MIN_PID 300
#define MAX_PID 5000

#define uc unsigned char

struct (uc*) manager;

int allocate_map() {
    unsigned short size = MAX_PID - MIN_PID + 1; 

    manager = (unsigned char*)malloc(size * sizeof(uc));

    if(manager) {
        for(unsigned short i = 0; i < size; ++i){ manager[i] = 'f'; }
        return 1;
    }
    else -1;
}

int allocate_pid() {
    int 
}

int main(void) {
    allocate_map();
    free(manager);
}