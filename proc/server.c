#include <sys/socket.h> // socket
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h> // inet_aton
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // write

int main(int argc, const char* argv[]) {
    if(argc != 2){
        perror("enter port number");
        return -1;
    }

    // get port number from command
    unsigned short port = (unsigned short) atoi(argv[1]);

    if(port == 0){
        perror("unvalid port number");
        return 1;
    }

    // 1. create socket
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    // 2. bind information
    struct sockaddr_in addr_in;

    // initializing
    memset(&addr_in, 0, sizeof(addr_in));
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(port);
    addr_in.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(serv_sock, (struct sockaddr*) &addr_in, sizeof(addr_in)) == -1){
        perror("failure to bind address information");
        return 2;
    }

    // 3. listend and accept

    printf("listening... at port %d\n", port);

    if(listen(serv_sock, 0) == -1){
        perror("cannot listen from server socket");
        return 5;
    }

    struct sockaddr client_addr;
    unsigned int client_addr_length = sizeof(client_addr);
    int client_sock = accept(serv_sock, &client_addr, &client_addr_length);
    if(client_sock == -1){
        perror("cannot create link");
        return 3;
    }

    printf("accepted!!\n");

    char buf[256] = "Hello world! get it on";

    // 4. write
    int write_n = write(client_sock, buf, 256);
    if(write_n == -1){
        perror("cannot send text");
        return 4;
    }
    if(write_n == 0) fprintf(stdout, "No word\n");
    else fprintf(stdout, "text %s is sended\n", buf);
    
    // 5. close
    close(client_sock);
    close(serv_sock);
}