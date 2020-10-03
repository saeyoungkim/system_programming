#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_ONLY 0
#define WRITE_ONLY 1

#define SIZE 1024

int main(int argc, char** args) {
    const char* copy_from_path = args[1];
    const char* copy_to_path = args[2];

    // make pipe
    int fd[2];
    if(pipe(fd) == -1){
        perror("Cannot create pipe.");
        return -1;
    }

    pid_t pid;
    pid = fork();

    // if cannot fork => error
    if(pid == -1){
        perror("Cannot fork.");
        return 1;
    }
    // if child process
    else if(pid == 0){
        close(fd[WRITE_ONLY]);
        // char array
        char* read_buf = malloc(sizeof(char) * SIZE);
        
        // read line from pipe
        read(fd[READ_ONLY], read_buf, sizeof(char) * SIZE);
        
        printf("read array size : %lu\n", strlen(read_buf));

        // write to to_path file
        FILE* fwr;
        // read file error
        if((fwr = fopen(copy_to_path, "w")) == NULL){
            perror("Cannot open file.");
            return 2;
        }

        size_t idx = 0;
        while(read_buf[idx] != '\0'){
            fputc((int)read_buf[idx++], fwr);
        }

        free(read_buf);
        close(fd[READ_ONLY]);
        return 0;
    }
    // if parent process
    else {
        close(fd[READ_ONLY]);

        // read from_path file
        FILE* frd;
        // read file error
        if((frd = fopen(copy_from_path, "r")) == NULL){
            perror("Cannot open file.");
            return 2;
        }
        // char array
        char* write_buf = malloc(sizeof(char) * SIZE);
        size_t idx = 0;

        // read file
        int ch;
        while((ch = fgetc(frd)) != EOF){
            printf("%c", (char)ch);
            write_buf[idx++] = (char)ch;
        }

        printf("\n");

        write_buf[idx] = '\0';

        // write from_path to pipe
        write(fd[WRITE_ONLY], write_buf, strlen(write_buf));

        free(write_buf);
        close(fd[WRITE_ONLY]);
        return 0;
    }
}