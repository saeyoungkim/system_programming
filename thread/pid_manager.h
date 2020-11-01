#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <unordered_map>
#include <sys/types.h>

#define MIN_PID 300
#define MAX_PID 5000

void* run(void*);

struct PidManager {
  std::unordered_map<int, pthread_t*> mappingThreads;
};

PidManager* pm = nullptr;

PidManager* create_pid_manager(void) {
  PidManager* ret = new PidManager();
  ret->mappingThreads = std::unordered_map<int, pthread_t*>();
  return ret;
}

int allocate_map(void) {
  if(pm == nullptr){
    pm = create_pid_manager();
    for(int i = 0; i < MAX_PID - MIN_PID + 1; ++i) {
      pm->mappingThreads[i] = NULL;
    }
    fprintf(stdout, "Success to allocate Pid Manager.\n");
    return 1;
  }
  else{
    fprintf(stdout, "Error to allocate Pid Manager.\n");
    return -1;
  }
}

int allocate_pid(void) {
  for(int i = 0; i < MAX_PID - MIN_PID + 1; ++i) {
    if(!pm->mappingThreads[i]){
      pthread_t tid;
      pthread_create(&tid, NULL, run, NULL);
      fprintf(stdout, "Sucess to allocate pid %d to pid manager.\n", i + MIN_PID);
      pm->mappingThreads[i] = &tid;
      return 1;
    }
  }
  fprintf(stdout, "Full pids.\n");
  return -1;
}

void release_pid(int pid) {
  fprintf(stdout, "pid %d is released.\n", pid);
  pm->mappingThreads[pid] = NULL;
}

void printMap(void) {
  if(pm == nullptr) std::exit(1);
  for(auto it = pm->mappingThreads.begin(); it != pm->mappingThreads.end(); ++it){
    if(it->second) fprintf(stdout, "pid %d is used : %p\n", it->first, it->second);
  }
}

void* run(void* params) {
  sleep(((double)rand() / RAND_MAX) * 10);
  fprintf(stdout, "%s is running\n", __func__);
  pthread_exit(0);
}
