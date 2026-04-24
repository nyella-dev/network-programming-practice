# `socket()`

------------------------------------------------------------------------

## 📌 What `socket()` Does

The `socket()` system calls creates file descriptor to a socket. A way to view a socket is a pipe between two interfaces to communicate that has not yet been connected. 
------------------------------------------------------------------------

## ⚙️ Function Signature

``` c
int socket(int domain, int type, int protocol);
```

### Parameters:

-   `<domain>`→ what protocol family to use such as PF_IFNET, PF_IFNET6, etc. 
-   `<type>`→ Type of communication such SOCK_STREAM, SOCK_DGRAM
-   `<protocol>` → usually 0 but refers to "TCP", "UDP", can also use `getprotobyname(). 

------------------------------------------------------------------------

## 🔁 Return Value

-   On success: Socket descriptor to use in later system calls.
-   On failure: -1 and global variable errno is set. 

------------------------------------------------------------------------

## 🧠 Key Concepts

### 1.

Socket is just a file descriptor. 

------------------------------------------------------------------------

### 2.

It does not connect anything, No IP, No port, No peer. Its just to setup the file descriptor for a socket. 

------------------------------------------------------------------------


------------------------------------------------------------------------

## 🚀 Example Usage

``` c
// Assuming addrResults is struct addrinfo and was filled out with getaddrinfo()

    socketDescriptor = socket(addrResults->ai_family, addrResults->ai_socktype, addrResults->ai_protocol);

    if (socketDescriptor == -1) {
        printf("Socket error");
    }

    printf("Socket descriptor is: %d \n", socketDescriptor);
```

------------------------------------------------------------------------

## 🧪 Example Output

``` text
"Socket descriptor is: 3"
```

------------------------------------------------------------------------

## ⚠️ Important Notes

-   Socket is created in kernel space not user space
-   Resources are limited and it should be closed once done.
-   Behavior depends on OS networking stack.

------------------------------------------------------------------------

## ❗ Common Pitfalls

-   Not checking return value
-   Not closing sockets -> file descriptor leaks
-   Assuming socket() creates a connection

------------------------------------------------------------------------

## 💡 Takeaways

-   Socket is just a pipe that is not connected to anything
-   Just a file descriptor backed by kernel.

------------------------------------------------------------------------

## 🔗 Related Concepts

-   connect()
-   bind()
-   listen()
-   accept()
-   send()
-   receive()
-   select()
-   poll()
-   epoll

------------------------------------------------------------------------

## 🧠 Mental Model

A telephone wire that CAN connects two phones however, this wire is not connected yet. 
------------------------------------------------------------------------

## 🧹 Cleanup / Resource Management

-   close(sockfd)
-   shutdown()
