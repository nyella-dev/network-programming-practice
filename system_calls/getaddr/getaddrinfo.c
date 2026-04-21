#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>


/*
SYSTEM CALL getaddrinfo example

---------------------------------
int getaddrinfo(const char *node, // e.g. "www.example.com" or IP
const char *service, // e.g. "http" or port number
const struct addrinfo *hints,
struct addrinfo **res);
---------------------------------

*/
int main(int argc, char*argv[]){

    struct addrinfo hints, *res, *p; 
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    if(argc != 2) {
        fprintf(stderr, "usage: showip hostname\n");
        return 1;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;


    // getaddrinfo("www.example.com")
    status = getaddrinfo(argv[1], NULL, &hints, &res);

    if(status != 0) { 
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status)); 
        return 2;
    }

    printf("IP address forss %s:\n\n", argv[1]);

    // getaddrinfo returns a linked list of available address returned by DNS
    // Lets output each address
    for(p=res; p!=NULL; p = p->ai_next) {
        void * addr;
        void * ipver;
        struct sockaddr_in * ipv4;
        struct sockaddr_in6 * ipv6;

        // Check the Internet Address Family , AF_INET means IPV4
        if(p->ai_family == AF_INET) {

            ipv4 = (struct sockaddr_in*)p->ai_addr; 
            addr = &(ipv4->sin_addr);
            ipver = "IPv4"; 
        } else {
            ipv6 = (struct sockaddr_in6 *)p->ai_addr; 
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6"; 
        }

        // Internet Network to Presentation 
        // Convert Internet Address to Human Readable Text
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf(" %s: %s\n", ipver, ipstr);

    }


    freeaddrinfo(res);


    return 0; 


}