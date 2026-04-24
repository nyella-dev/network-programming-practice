#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>



int main(int argc, int * argv[]){

    struct addrinfo hints;
    struct addrinfo* res; 

    // We don't know if a client will be IPV4 or IPV6 so the sockaddr_storage is big enough to hold either one
    // We can cast it to (struct sockaddr*) to make compiler happy
    struct sockaddr_storage their_add; 

    // Accept will write back how big the struct actually was 
    socklen_t addr_size;


    int sockFileDesc; 
    int newFileDesc;

    memset(&hints, 0, sizeof(hints)); 
    hints.ai_flags = AI_PASSIVE; // FILL IP
    hints.ai_family = AF_UNSPEC; // USE IPV4 or IPV6
    hints.ai_socktype = SOCK_STREAM;

    addr_size = sizeof their_add;
    getaddrinfo(NULL, "3490", &hints, &res);

    sockFileDesc = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    int yes=1;
    int forceBind = setsockopt(sockFileDesc, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
    printf("Force bind result: %d\n", forceBind);

    int bindResult = bind(sockFileDesc, res->ai_addr, res->ai_addrlen);
    printf("Bind result: %d\n", bindResult);


    

    int listenResult = listen(sockFileDesc, 10);
    printf("Listen result: %d\n", listenResult);
    
    newFileDesc = accept(sockFileDesc, (struct sockaddr*)&their_add, &addr_size);
    // IF QUE EMPTY - PROCESS GOES TO SLEEPING/WAITING
    //
    printf("\n\n");

    char buffer[1024];

    int len;

    int bytes_received = recv(newFileDesc, &buffer, 14, 0);


    buffer[bytes_received] = '\0';

    close(newFileDesc);
    close(sockFileDesc);
    printf("Bytes received %d\n", bytes_received);
    printf("Result %s\n", buffer);

    return 1;

}