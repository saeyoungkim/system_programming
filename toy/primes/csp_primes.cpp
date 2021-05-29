#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void enterInput(int& a) {
    std::cout << "Please enter the number: ";
    std::cin >> a;

    assert(a > 0);
}

unsigned char* intToBytes(const int& param) {
    unsigned int v = param;
    unsigned int mask = 0xF;
    unsigned char* ret = new unsigned char[4];
    for(int i = 0; i < 4; ++i){
        ret[3-i] = v & mask;
        v >>= 4;
    }

    return ret;
}

int bytesToInt(unsigned char a[4]) {
    int ret = 0;
    for(int i = 0; i < 4; ++i){
        ret += (int)(a[3-i]) << (i*4);
    } 

    return ret;   
}

void writeInt(int fd, int v) {
    write(fd, intToBytes(v), 4);
}

int readInt(int fd) {
    unsigned char a[4];
    return read(fd, a, 4) < 4 ? 0 : bytesToInt(a);
}

void do_primes(int old_p[2]) {
    int new_p[2];
    pipe(new_p);

    // close wrtie on old pipe
    close(old_p[1]);
    int p = readInt(old_p[0]);

    if(p == 0) return ;
    
    std::cout << getpid() << ": " << p << std::endl;

    int pid = fork();
    assert(pid != -1);

    if(pid > 0) {
        close(new_p[0]);
        while(true) {
            int n = readInt(old_p[0]);
            if(n == 0) {
                close(new_p[1]);
                break;
            }
            if(n % p != 0) {
                writeInt(new_p[1], n);
            }
        }
        wait(0);
    } else {
        do_primes(new_p);
    }
    close(old_p[0]);
}

int main() {
    int start, end;
    enterInput(start);
    enterInput(end);

    assert(start <= end);

    int p[2];
    pipe(p);

    int pid = fork();
    assert(pid != -1);
    
    if(pid > 0) {
        // close read pipe
        close(p[0]);
        std::cout << getpid() << ": " << start << std::endl;
        for(int cand = start+1; cand <= end; ++cand) {
            if(cand % start != 0) {
                writeInt(p[1], cand);
            }
        }
        // close write pipe
        close(p[1]);
        wait(0);
    } else {
        do_primes(p);
    }
}