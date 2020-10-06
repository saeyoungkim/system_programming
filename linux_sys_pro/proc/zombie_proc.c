#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
 pid_t pid;
 
 pid = fork();

 if(pid < 0)
 {
  perror("fork() does not work");
  return 1;
 }
 else if(pid == 0) // child process
 {
  printf("Im child\n");
  return 0;
 }
 else 
 {
  printf("Im parent\n");
  return 0;
 }

 return 0;
}

