#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, int * argv[]){

    struct addrinfo hints;
    struct addrinfo* res; 
    int sockfd; 

    memset(&hints, 0, sizeof(hints)); 
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    getaddrinfo("127.0.0.1", "3490", &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol); 
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }
    
    if(connect(sockfd, res->ai_addr, res->ai_addrlen) == -1){
        perror("connect");
    };

    char *msg = "Llyn was here";
    int len, bytes_sent; 

    bytes_sent = send(sockfd, msg, 14, 0);

    printf("Bytes sent %d\n", bytes_sent);

    // Freespace and close socket
    freeaddrinfo(res);
    close(sockfd);

    return 1;

}