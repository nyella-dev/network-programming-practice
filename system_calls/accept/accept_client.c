#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int main(int argc, int * argv[]){

    struct addrinfo hints;
    struct addrinfo* res; 
    int sockfd; 

    memset(&hints, 0, sizeof(hints)); 
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, "3490", &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); 

    connect(sockfd, res->ai_addr, res->ai_addrlen);

    char *msg = "Llyn was here";
    int len, bytes_sent; 

    bytes_sent = send(sockfd, msg, 14, 0);

    printf("Bytes sent %d\n", bytes_sent);
    return 1;

}