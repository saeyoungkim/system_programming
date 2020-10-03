#include <sys/socket.h> // socket
#include <netinet/in.h> // sockaddr_in
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // write
#define PORTS_SIZE 65536

void scan_port() {
    // initialization
    struct sockaddr_in addr_in;
    memset(&addr_in, 0, sizeof(addr_in));

    // set sock address
    addr_in.sin_family = AF_INET;
    addr_in.sin_addr.s_addr = INADDR_ANY;
    
    // bind and find
    for(int port = 1; port < PORTS_SIZE; ++port){
        // get socket fd
        int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

        addr_in.sin_port = port;
        if(bind(sock_fd, (struct sockaddr*)&addr_in, sizeof(addr_in)) == -1){
            fprintf(stdout, "Available port : %d\n", port);
        }
        close(sock_fd);
    }
    return ;
}

int main(void) {
    scan_port();
    return 0;
}