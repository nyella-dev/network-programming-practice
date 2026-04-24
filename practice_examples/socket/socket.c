#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>

/*
    Program to test out the socket() system call.
    Socket should return a socket descriptor when passed in the proper domain, type and protocol.

    Socket(int domain, int type, int protocol)

    DOMAIN: PF_INET, PF_INET6
    Type: SOCK_STREAM, SOCK_DGRAM
    Protocol: TCP or UDP, often retreived with getprotobyname()


*/



int main(int argc, char*argv[]) {


    if(argc != 2){
        fprintf(stderr, "usage: showip hostname\n");
        return 1;
    }


    struct addrinfo *addrResults;  
    struct addrinfo hints;
    struct addrinfo *p;

    int socketDescriptor; 
    int status;

    // (starting address of memory, value to fill with, number of bytes to fill)
    //
    // We need to make sure unitiliaized fields are zeroed out to prevent random behavior 
    memset(&hints, 0, sizeof(hints)); 

    hints.ai_family = AF_INET; 
    hints.ai_socktype = SOCK_STREAM; 
    
    status = getaddrinfo(argv[1], "http", &hints, &addrResults); 

    if(status != 0) { 
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status)); 
        return 2;
    }

    // We Will Assume the first value of addrResults in the linked list is valid and that we don't need to error check
    // Just for this example :) 
    socketDescriptor = socket(addrResults->ai_family, addrResults->ai_socktype, addrResults->ai_protocol);

    if (socketDescriptor == -1) {
        printf("Socket error");
    }

    printf("Socket descriptor is: %d \n", socketDescriptor);

    freeaddrinfo(addrResults);
    close(socketDescriptor);
    
    return 0;


}