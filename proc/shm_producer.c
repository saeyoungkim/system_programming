#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h> // shm_open

#include <unistd.h> // ftruncate
#include <sys/types.h>

int main(void) {
    // the size
#define SIZE 4096
    // name of shared memory object
    const char* name = "OS";
    // file descriptor
    int fd;
    // messages
    const char* message1 = "Hello";
    const char* message2 = "Brother!";

    // 1 create the shared memory object
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    // 2 configure the size
    ftruncate(fd, SIZE);
    // 3 memory map to shared memory object
    char* ptr = (char *)
        mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sprintf(ptr, "%s", message1);
    ptr += strlen(message1);
    sprintf(ptr, "%s", message2);
    ptr += strlen(message2);

    printf("%s, %s is in shared memory segments\n", message1, message2);
    while(1){}
    return 0;
}