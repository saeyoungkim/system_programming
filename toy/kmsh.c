#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define EXIT_COMMAND "exit"

#define MAX_SIZE 40
#define MAX_WORD_LENGTH 15

#define READ_ONLY 0
#define WRITE_ONLY 1

const char* history_command = "!!";

struct _arguments {
    // arguments number
    int argc;
    // arguments
    char** args;
};

void _copy_argument(struct _arguments* hstr_arg, struct _arguments* arg, int from, int size) {
    hstr_arg->argc = arg->argc;
    for(int i = from; i < size-1; ++i){
        if(hstr_arg->args[i] == NULL) hstr_arg->args[i] = malloc(sizeof(char) * MAX_WORD_LENGTH);
        strcpy(hstr_arg->args[i], arg->args[i]);
    }
    hstr_arg->args[size-1] = NULL;
}

void _init(struct _arguments* arg) {
    arg->args = malloc(sizeof(char*) * MAX_SIZE);

    for(size_t i = 0; i < MAX_SIZE; ++i){
        arg->args[i] = malloc(sizeof(char) * MAX_WORD_LENGTH);
    }

    arg->argc = 0;
}

void _delete(struct _arguments* arg) {
    for(size_t i = 0; i < MAX_SIZE; ++i){
        free(arg->args[i]);
    }

    free(arg->args);
}

void _split_arguments(struct _arguments* arg, const char* str) {
    size_t start = 0, ct = 0, idx = 0, end = strlen(str);
    while(idx < end){
        if(str[idx] == ' '){
            if(str[start] != ' ') {
                strncpy(arg->args[ct], str + start, idx - start);
                arg->args[ct++][idx-start] = '\0';
            }
            start = idx;
        }
        else {
            if(str[start] == ' ') start = idx;
        }
        ++idx;
    }

    if(str[start] != ' ') {
        strncpy(arg->args[ct], str + start, idx - start);
        arg->args[ct++][idx-start] = '\0';
    }

    arg->args[ct++] = NULL;
    arg->argc = ct;
}

void _kmsh_single_launch(char** args) {
    pid_t pid;
    pid = fork();

    if(pid < 0){
        perror("Cannot fork.\n");
        exit(1);
    }
    else if(pid == 0){
        execvp(args[0], args);
    }
    else {
        wait(NULL);
    }
    return ;
}

void _kmsh_launch(struct _arguments* arg) {
    char* output;
    int has_output = 0;
    int has_pipe = 0;

    // split command and output file
    // the last element is NULL
    for(int i = 0; i < arg->argc-1; ++i){
        if(strcmp(arg->args[i], ">") == 0){
            has_pipe = i;
            arg->args[i] = NULL;
            output = arg->args[i+1];
            break;
        }
        if(strcmp(arg->args[i], "|") == 0){
            has_pipe = i;
            arg->args[i] = NULL;
            break;
        }
    }

    if(has_pipe) {
        int fd[2];

        if(pipe(fd) == -1) {
            perror("Cannot create pipe.");
            exit(5);
        }

        pid_t pid;
        pid = fork();

        if(pid < 0){
            perror("Cannot fork.\n");
            exit(1);
        }
        else if(pid == 0){
            close(fd[READ_ONLY]);

            if(dup2(fd[WRITE_ONLY], STDOUT_FILENO) == -1){
                perror("Cannot duplicate file descriptor to stdout table number.\n");
                exit(4);
            }

            execvp(arg->args[0], arg->args);
            close(fd[WRITE_ONLY]);
        }
        else {
            close(fd[WRITE_ONLY]);

            if(dup2(fd[READ_ONLY], STDIN_FILENO) == -1){
                perror("Cannot duplicate file descriptor to stdout table number.\n");
                exit(4);
            }
            
            execvp(arg->args[has_pipe + 1], arg->args + has_pipe + 1);
            wait(NULL);
            close(fd[READ_ONLY]);
        }

        return ;
    }

    else if(has_output) {
        int fd;
        if((fd = open(output, O_WRONLY | O_CREAT, S_IRWXU)) == -1){
            perror("Cannot create or write to file.\n");
            exit(3);
        }

        if(dup2(fd, STDOUT_FILENO) == -1){
            perror("Cannot duplicate file descriptor to stdout table number.\n");
            exit(4);
        }
    }

    if(execvp(arg->args[0], arg->args) == -1){
        perror("execvp error");
        exit(2);
    }
    return ;
}

int _kmsh_execute(struct _arguments* arg) {    
    pid_t pid;
    pid = fork();

    if(pid < 0){
        perror("Cannot fork.\n");
        exit(1);
    }
    else if(pid == 0) _kmsh_launch(arg);
    else wait(NULL);
    
    return 0;
}

int main(void) {
    // history arguments
    struct _arguments hstr_arg;

    _init(&hstr_arg);

    int should_run = 1;

    // isFirst
    int isFirst = 1;

    while(should_run) {
        printf("kmsh > ");
        fflush(stdout);

        // read string
        char str[MAX_SIZE * MAX_WORD_LENGTH + MAX_SIZE - 1];

        fgets(&str[0], MAX_SIZE * MAX_WORD_LENGTH + MAX_SIZE - 1, stdin);
        str[strlen(&str[0])-1] = '\0';

        if(&str[0] == NULL) return 1;
        if(strcmp(&str[0],"quit") == 0) {
            printf("Quit.\n");
            should_run = 0;
            return 0;
        }
        if(strcmp(&str[0], history_command) == 0) {
            if(isFirst == 1) printf("No commands in history.\n");
            else  _kmsh_execute(&hstr_arg);
            
            continue;
        }

        isFirst = 0;

        // arguments
        struct _arguments arg;

        _init(&arg);

        _split_arguments(&arg, str);

        _copy_argument(&hstr_arg, &arg, 0, arg.argc);

        _kmsh_execute(&arg);

        _delete(&arg);
    }
    _delete(&hstr_arg);
}