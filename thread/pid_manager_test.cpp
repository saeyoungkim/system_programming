#include "pid_manager.h"
#include <time.h>

#define N 100

int main(void) {

  srand(time(0));

  int st;

  st = allocate_map();

  if(st != 1){
    exit(1);
  }

  for(int i = 0; i < 100; ++i){
    allocate_pid();
  }

  sleep(1);
  printMap();

  sleep(4);
  printMap();
}
