#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
/*
    bind.c - Program to test the bind system call functionality. 
    Ignore any obvious error checking for other system calls such as getaddrinfo() and sock() as 
    my main focus is just testing out bind.c.

*/

int main(int argc, int * argv[]){

    struct addrinfo hints;
    struct addrinfo* res; 
    int sockFileDesc; 

    memset(&hints, 0, sizeof(hints)); 
    hints.ai_flags = AI_PASSIVE; // FILL IP
    hints.ai_family = AF_UNSPEC; // USE IPV4 or IPV6
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(NULL, "3490", &hints, &res);

    sockFileDesc = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
    // Bind connects the FD to an ip address and a port

    // Mental model: Connecting a phone wire(Socket File Descriptor) to the phone(IP / PORT)
    int bindResult = bind(sockFileDesc, res->ai_addr, res->ai_addrlen);

    // On Error it returns -1 and outputs to errno
    if(bindResult == -1){
        perror("bind");
    }

    // On success it returns a 0
    printf("Bind result: %d\n", bindResult);

    // Freespace and close socket
    freeaddrinfo(res);
    close(sockFileDesc);

    return 1;

}