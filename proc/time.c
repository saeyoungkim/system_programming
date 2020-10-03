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
    
    // name of shared memory object
    const char* name = "time_shared";
    // open shm object for write
    int shmo_wr_fd = shm_open(name, O_CREAT | O_WRONLY, 0666);
    // open shm object for read
    int shmo_rd_fd = shm_open(name, O_CREAT | O_RDONLY, 0666);
    // ftruncat
    ftruncate(shmo_wr_fd, SIZE);
    // ftruncat
    ftruncate(shmo_rd_fd, SIZE);
    // memorymapping
    struct timeval* start_wr = (struct timeval*) mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED, shmo_wr_fd, 0);
    // memorymapping
    struct timeval* start_rd = (struct timeval*) mmap(NULL, SIZE, PROT_READ, MAP_SHARED, shmo_rd_fd, 0);

    pid = fork();

    if(pid < 0) // cannot create process
    {
        perror("fork() not work");
        return 1;
    }
    else if(pid == 0) // child process
    {
        const char* baseUri = "/bin/";
        gettimeofday(start_wr, NULL);
        execlp(concat(baseUri, argv[1]), argv[1], NULL);
        return 0;
    }
    else // parent process
    {
        wait(NULL);
        gettimeofday(&end, NULL);

        float diff_time = end.tv_sec - start_rd->tv_sec +  (float)(end.tv_usec - start_rd->tv_usec) / 1000000;

        printf("\nElasped time : %f s\n", diff_time);
        return 0;
    }

    return 0;
}