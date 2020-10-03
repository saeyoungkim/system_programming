#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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

int _kmsh_execute(struct _arguments* arg) {    
    pid_t pid;
    pid = fork();

    if(pid < 0){
        perror("Cannot fork.\n");
        exit(1);
    }
    else if(pid == 0){
        if(execvp(arg->args[0], arg->args) == -1){
            perror("execvp error");
            exit(2);
        }
    }
    else {
        int status;
        wait(&status);
    }
    return 0;
}

void _copy_to_hstr(struct _arguments* hstr_arg, struct _arguments* arg) {
        hstr_arg->argc = arg->argc;
        for(int i = 0; i < hstr_arg->argc-1; ++i){
            if(hstr_arg->args[i] == NULL) hstr_arg->args[i] = malloc(sizeof(char) * MAX_WORD_LENGTH);
            strcpy(hstr_arg->args[i], arg->args[i]);
        }
        hstr_arg->args[hstr_arg->argc-1] = NULL;
}

int main(void) {
    // history arguments
    struct _arguments hstr_arg;

    _init(&hstr_arg);

    int should_run = 1;

    // isFirst
    int isFirst = 1;

    while(should_run) {
        // arguments
        struct _arguments arg;

        _init(&arg);

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

        _split_arguments(&arg, str);

        _copy_to_hstr(&hstr_arg, &arg);

        _kmsh_execute(&arg);

        _delete(&arg);
        
    }
    _delete(&hstr_arg);
}