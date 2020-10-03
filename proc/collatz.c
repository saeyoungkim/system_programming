#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

#define ui unsigned int
#define MAX 65536

ui collatz_number(ui number) {
    if(number & 1) return 3*number + 1;
    else return number >> 1;
}

ui* generate_sequence(ui number, ui* length) {
    ui ct = 1;
    ui number_for_count = number;
    while(number_for_count != 1){
        number_for_count = collatz_number(number_for_count);
        ++ct;
    }

    *length = ct;

    ui* arr = malloc(ct * sizeof(ui));
    ui idx = 0;
    while(ct > 0){
        arr[idx] = number;
        number = collatz_number(number);
        ++idx;
        --ct;
    }

    return arr;
}

int main(int argc, char* argv[]) {
    if(argc != 2){
        fprintf(stderr, "Illegal arguments\n");
        return -1;
    }

    // for write shm obj
    int shm_write = shm_open("Collatz", O_CREAT | O_WRONLY, 0666);
    // ftruncate
    ftruncate(shm_write, MAX);
    // mmap
    ui* access = (ui*)mmap(NULL, MAX, PROT_WRITE, MAP_SHARED, shm_write, 0);

    pid_t pid;
    pid = fork();

    if(pid < 0) // fork error
    {
        perror("cannot crate child process");
        return 1;
    }
    else if(pid == 0) // child process
    {
        while(!access) sleep(1);
        ui value = access[0];
        ui length = 1;
        ui* collatz_sequence = generate_sequence(value, &length);

        access[1] = length;

        for(ui idx = 0; idx < length; ++idx){
            access[idx+2] = collatz_sequence[idx];
        }

        printf("%d\n",access[0]);

        return 0;
    }
    else // parent process
    {
        ui value = (ui)atoi(argv[1]);
        access[0] = value;
        wait(NULL);
        ui length = access[1];
        for(ui idx = 0; idx < length; ++idx){
            printf("%d ", access[idx+2]);
        }
        printf("\n");
        return 0;
    }
}