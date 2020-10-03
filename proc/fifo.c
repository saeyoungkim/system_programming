#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <string.h>

#define MAXSIZE 256

int main(int args, char* argc[]) {
    if(args != 2) {
        perror("Must argumets 2");
        return -1;
    }

    if(mkfifo(argc[1], 0777) == -1) {
        perror("Cannot make fifo");
        return 1;
    } 

    int fd = open(argc[1], O_WRONLY | O_CREAT);

    if(fd == -1){
        perror("Cannot open fifo");
        return 2;
    }

    printf("hihi\n");

    const char buf[MAXSIZE] = "GREETINGS";
    int write_size = write(fd, buf, MAXSIZE);
    
    if(write_size != 9) return 3;

    close(fd);

    return 0;
}