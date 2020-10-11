#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <regex.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define SIZE 256

int main(int argc, char* argv[]){
    // check arguments
    if(argc != 2){
        fprintf(stderr, "Illegal Arguments : Two arguments needed\n");
        return 1;
    }

    const char* url = argv[1];
    printf("url : %s\n", url);

    // get ip address
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    struct addrinfo* result = NULL;
    int dns_result = getaddrinfo(url, "ftp", &hints, &result);
    if (dns_result != 0) {
        perror("DNS서버에서 값을 받아 올 수 없습니다.");
        return 1;
    }

    // create socket
    int sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(sock == -1) {
        perror("소켓을 생성할 수 없습니다.");
        return 2;
    }

    // connect 
    printf("연결을 시작합니다\n");

    int conn = connect(sock, result->ai_addr, result->ai_addrlen);
    if(conn == -1) {
        perror("소켓을 연결할 수 없습니다.");
        return 3;
    }

    // for read and write

    char buf[SIZE];
    int write_num, read_num;

    // print
    while(1){
        memset(buf, 0, SIZE);
        read_num = recv(sock, buf, SIZE, 0);
        printf("%d\n", read_num);

        printf("%s", buf);

        printf("lftp :~> \n");
        fgets(buf, SIZE, stdin);

        char* command = strchr( buf, '\n' );
        write_num = send(sock, command, SIZE, 0);
        printf("%d\n", write_num);
    }

    close(sock); 
    return 0;
}