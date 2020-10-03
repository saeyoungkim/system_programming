#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h> /* mode 定数用 */
#include <fcntl.h> /* O_定数 */

#define SIZE 512

char *concat(const char *a, const char *b){
    int lena = strlen(a);
    int lenb = strlen(b);
    char *con = malloc(lena+lenb+1);
    memcpy(con,a,lena);
    memcpy(con+lena,b,lenb+1);        
    return con;
}

int main(int argc, char** argv) {
    if(argc != 2){
        fprintf(stderr, "Illegal arguments : need two arguments");
        return -1;
    }

    pid_t pid;

    struct timeval start, end;
    
    int fd[2];

#define READ_ONLY 0
#define WRITE_ONLY 1

    if(pipe(fd) == -1){
        perror("cannot create pipe");
        return -1;
    }

    pid = fork();

    if(pid < 0) // cannot create process
    {
        perror("fork() not work");
        return 1;
    }
    else if(pid == 0) // child process
    {
        const char* baseUri = "/bin/";
        struct timeval start;
        gettimeofday(&start, NULL);
        write(fd[WRITE_ONLY], &start, sizeof(start));
        execlp(concat(baseUri, argv[1]), argv[1], NULL);
        return 0;
    }
    else // parent process
    {
        wait(NULL);
        gettimeofday(&end, NULL);

        read(fd[READ_ONLY], &start, sizeof(end));

        float diff_time = end.tv_sec - start.tv_sec +  (float)(end.tv_usec - start.tv_usec) / 1000000;

        printf("\nElasped time : %f s\n", diff_time);
        return 0;
    }

    return 0;
}