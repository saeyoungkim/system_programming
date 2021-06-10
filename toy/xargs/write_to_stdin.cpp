#include <unistd.h>
#include <string.h>
#include <iostream>

#define SIZE 1024

int main(int args, char **argv) {
    // for(int i = 0; i < args; ++i) {
    //     char wbuf[strlen(argv[i])+1];
    //     strcpy(wbuf, argv[i]);
    //     wbuf[strlen(argv[i])] = '\n';
    //     write(0, wbuf, strlen(argv[i])+1);
    // }

    for(int i = 0; i < args; ++i) {
        write(0, argv[i], strlen(argv[i])+1);
    }
    write(0, "\n", 1);

    char buf[SIZE];
    while(read(0, buf, SIZE)){
        std::cout << "reading... \n";
        std::cout << buf << std::endl;
    }

    return 0;
}