#include <sys/socket.h> // socket
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h> // inet_aton
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // write

int main(int args, char* argc[]) {
    // 1. create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    // 2. set information
    struct sockaddr_in addr_in;
    memset(&addr_in, 0, sizeof(addr_in));
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons((unsigned short) atoi(argc[1]));
    addr_in.sin_addr.s_addr = INADDR_ANY;

    // 3. connect
    if(connect(sock, (const struct sockaddr*)&addr_in, sizeof(addr_in)) == -1){
        perror("cannnot connect to server");
        return 1;
    };

    // initializing
    char buf[256];
    memset(buf, 0, 256);

    // 4. read
    if(read(sock, buf, 256) == -1){
        perror("cannot read the data from socket\n");
        return 2;
    }

    fprintf(stdout, "read %s from socket", buf);

    // 5. close
    close(sock);
}