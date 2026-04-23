# `bind()`

------------------------------------------------------------------------

## 📌 What `bind()` Does

The `bind()` system call takes a socket descriptor, a sockaddr and length and binds it to the ip address and port. 
------------------------------------------------------------------------

## ⚙️ Function Signature

``` c
#include <sys/types.h>
#include <sys/socket.h>
int bind(int sockfd, struct sockaddr *my_addr, int addrlen);
```

### Parameters:

-   `<sockfd>` → the socket file descriptor generated from socket ()
-   `<sockaddr>` → the address within addrinfo->ai_addr , contains ip address and port 
-   `<addrlen>` → the length in bytes the address

------------------------------------------------------------------------

## 🔁 Return Value

-   On success: It returns a 0
-   On failure: It returns a -1 and also sets errno to the error's value.

------------------------------------------------------------------------

## 🧠 Key Concepts

### 1.

``` c
You can manually fill out `sockaddr` 
```

------------------------------------------------------------------------

### 2.

``` c
bind() does NOT start listening for connections
```
This is a common misunderstanding:

bind() → assigns local address (IP + port)
listen() → starts accepting incoming connections

Typical server flow is 
``` c
socket() → bind() → listen() → accept()
```
------------------------------------------------------------------------

### 3.

``` c
Port numbers must be in network byte order
```
If you manually set the port:
```c
addr.sin_port = htons(8080);
```
htons() = host-to-network short
Without this, your port may be wrong (endianness issue)
------------------------------------------------------------------------

## 🚀 Example Usage

``` c
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
```

------------------------------------------------------------------------

## 🧪 Example Output

``` text
Bind result: 0
```

------------------------------------------------------------------------

## ⚠️ Important Notes

-   If you manually fill out port number and don't use getaddrinfo() , ports below 1024 are RESERVED unless you are SUPER user.
-   If a bind() fails you can wait for it to clear or use setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
-   There are times when you don't need bind() where you only care about remote port and call connect ()
- Binding to "0.0.0.0" (INADDR_ANY) means: Accept connections on all local interfaces
- Binding to "127.0.0.1": Only local connections (localhost)
- Binding to a specific IP: Only that interface is used

------------------------------------------------------------------------

## ❗ Common Pitfalls

-   
-   Using wrong struct size
```
sizeof(struct sockaddr)   // ❌ often wrong
sizeof(struct sockaddr_in) // ✅ correct (if manual)
```
-   Address already in use fix:
```
setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
```
- Binding to same port twice: Only one process can own a port (without special flags)


------------------------------------------------------------------------

## 💡 Takeaways

-   bind() assigns a local identity (IP + port) to a socket
-   It’s required for servers, optional for clients
-   It does not establish connections
-   It’s tightly coupled with listen() and accept()
------------------------------------------------------------------------

## 🔗 Related Concepts

-   socket() → creates the file descriptor
-   listen() → marks socket as passive (server mode)
-   accept() → receives incoming connections
-   connect() → used by clients (auto-binds if needed)
-   getsockname() → see what address was actually bound

------------------------------------------------------------------------

## 🧠 Mental Model

Bind takes the telephone wire (socket file descriptor) and connects it to a phone (ip address and port).

------------------------------------------------------------------------

## 🧹 Cleanup / Resource Management

-   close(sockfd);
-   If your program crashes without closing:
    - The port may stay in TIME_WAIT
    - That’s why SO_REUSEADDR is commonly used
