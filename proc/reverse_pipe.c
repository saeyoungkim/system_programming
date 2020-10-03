#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define READ_ONLY 0
#define WRITE_ONLY 1
#define BUFFER_SIZE 128

int main(void) {
    // make filedscriptor
    int fd_p2c[2], fd_c2p[2];

    // make pipe for child
    if(pipe(fd_p2c) == -1) {
        perror("cannot make pipe for child.\n");
        return -1;
    }
    // make pipe for parent
    if(pipe(fd_c2p) == -1) {
        perror("cannot make pipe for parent.\n");
        return -1;
    }

    // message
    char write_message[256];
    char read_message[256];

    // fork pid
    pid_t pid;

    pid = fork();

    // error to fork
    if(pid == -1) {
        perror("cannot create child process.\n");
        return 1;
    }
    // child process
    else if(pid == 0) {
        close(fd_p2c[WRITE_ONLY]);
        close(fd_c2p[READ_ONLY]);

        read(fd_p2c[READ_ONLY], read_message, BUFFER_SIZE);
        for(int i = 0; i < strlen(read_message); ++i){
            int read_char = (int)read_message[i];
            if(65 <= read_char && read_char <= 90){
                read_message[i] = (char)(read_char + 32);
            }
            else if(97 <= read_char && read_char <= 122){
                read_message[i] = (char)(read_char - 32);
            }
        }
        write(fd_c2p[WRITE_ONLY], read_message, BUFFER_SIZE);

        close(fd_p2c[WRITE_ONLY]);
        close(fd_c2p[READ_ONLY]);

        return 0;
    }
    // parent process
    else {
        gets(write_message);

        close(fd_p2c[READ_ONLY]);
        close(fd_c2p[WRITE_ONLY]);

        printf("%s\n",write_message);

        write(fd_p2c[WRITE_ONLY], write_message, BUFFER_SIZE);
        read(fd_c2p[READ_ONLY], write_message, BUFFER_SIZE);

        printf("%s\n",write_message);

        close(fd_p2c[WRITE_ONLY]);
        close(fd_c2p[READ_ONLY]);

        return 0;
    }
}