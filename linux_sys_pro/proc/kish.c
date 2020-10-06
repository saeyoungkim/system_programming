#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){

 int should_run = 1;

 while(should_run) {
  printf("kish> ");
  fflush(stdout);
 
  char* command;

  scanf("%s", command);
  printf("\n"); 
  
  if(strcmp(command, "exit")){
   should_run = 0;
  }
 
  pid_t pid;

  pid = fork();

  // if fork failed
  if(pid < 0) {
   perror("Fork failed");
   return 1;
  }
  // if child process
  else if(pid > 0) {
   
   if(execv(command,args) == -1){
    perror("cannot exec command");
    return 2; 
   }
  }
 }
}
