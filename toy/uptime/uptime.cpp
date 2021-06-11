#include <time.h>
#include <errno.h>
#include <sys/sysctl.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <unistd.h>

int main(void) {
    const long tick = 1;

    time_t start = time(0);
    time_t now;
    while(1) {
        now = time(0);
        if(now - start == tick){
            int pid = fork();
            if(pid > 0) {
                wait(0);
                start = now;
            } else if (pid == 0) {
                execl("/usr/bin/uptime", "uptime", NULL);
            }
        }
    }
}