#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <string.h>

#define MAXSIZE 256

int main(void) {
    const char* path_name = "named_pipe";

    int fd;

    if((fd = open(path_name, O_RDONLY)) == -1){
        perror("Cannot open fifo");
    }

    const char buf[MAXSIZE];
    
    memset((char*)buf, 0, MAXSIZE);

    int read_size = read(fd, (char*) buf, MAXSIZE);
    
    if(read_size <= 0){
        perror("Cannot read fifo");
    }

    printf("%s", buf);

    close(fd);

    return 0;
}