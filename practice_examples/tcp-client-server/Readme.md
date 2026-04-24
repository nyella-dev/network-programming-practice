# TCP Client–Server Example (C)

------------------------------------------------------------------------

## 📌 Overview

This project demonstrates a minimal TCP client and server using POSIX sockets in C.

- The **server** listens for incoming connections and receives data
- The **client** connects to the server and sends a message

This example focuses on understanding the **full connection lifecycle**, not individual system calls in isolation.

------------------------------------------------------------------------

## 🔄 Connection Flow

### Server:
socket() → bind() → listen() → accept() → recv() → close()

### Client:
socket() → connect() → send() → close()

------------------------------------------------------------------------

## 🧠 Key Concepts Learned

### 1. Client vs Server Roles
- Server waits for connections using `listen()` and `accept()`
- Client initiates connection using `connect()`

### 2. TCP Connection Lifecycle
- `connect()` starts the TCP 3-way handshake
- `accept()` completes the connection on the server side
- A new socket is created for each client connection

### 3. Address Resolution (`getaddrinfo`)
- Server uses: `NULL` + `AI_PASSIVE`
- Client uses: `"127.0.0.1"` or hostname

### 4. Blocking Behavior
- `accept()`, `connect()`, and `recv()` block by default

### 5. Data Transmission
- `send()` transmits bytes
- `recv()` reads incoming data

### 6. Loopback Interface
- `"127.0.0.1"` allows local testing

### 7. File Descriptors
- Sockets behave like file descriptors

------------------------------------------------------------------------

## ⚙️ System Calls Used

- `socket()`
- `getaddrinfo()`
- `bind()` (server)
- `listen()` (server)
- `accept()` (server)
- `connect()` (client)
- `send()` (client)
- `recv()` (server)
- `close()`
- `setsockopt()` (server)

------------------------------------------------------------------------

## ⚠️ Important Notes

- `AI_PASSIVE` is only for servers
- Always check return values
- `recv()` may return 0 (connection closed)
- Buffers must be null-terminated manually

------------------------------------------------------------------------

## ❗ Common Pitfalls

- Using `AI_PASSIVE` on client
- Not initializing `socklen_t`
- Ignoring return values
- Assuming `send()` sends all bytes
- Printing uninitialized memory

------------------------------------------------------------------------

## 🧪 How to Run

Compile:
gcc server.c -o server
gcc client.c -o client

Run server:
./server

Run client:
./client

------------------------------------------------------------------------

## 💡 Takeaways

- Focus on flows, not isolated syscalls
- Understand client vs server roles
- Error handling is critical

------------------------------------------------------------------------

## 🔗 Next Steps

- Echo server
- Multiple clients
- Non-blocking sockets
