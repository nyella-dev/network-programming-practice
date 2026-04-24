# getaddrinfo()

This example demonstrates how to use `getaddrinfo()` to resolve a hostname into one or more IP addresses (IPv4 and IPv6).

---

## 📌 What `getaddrinfo()` Does

`getaddrinfo()` is used to:

* Convert a **hostname** (e.g., `www.google.com`) into IP addresses
* Support both **IPv4 and IPv6**
* Return results in a **linked list of address structures**

It replaces older functions like `gethostbyname()` and is the modern, flexible API for DNS resolution.

---

## ⚙️ Function Signature

```c
int getaddrinfo(const char *node,
                const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);
```

### Parameters:

* `node` → hostname or IP (e.g., `"www.example.com"`)
* `service` → port or service name (can be `NULL`)
* `hints` → filters results (IPv4/IPv6, TCP/UDP, etc.)
* `res` → output linked list of results

---

## 🧠 Key Concepts

### 1. Hints Structure

```c
memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;
```

* `AF_UNSPEC` → allow both IPv4 and IPv6
* `SOCK_STREAM` → TCP addresses only

---

### 2. Linked List of Results

`getaddrinfo()` returns a linked list:

```c
for (p = res; p != NULL; p = p->ai_next)
```

Each node contains:

* address family (`AF_INET`, `AF_INET6`)
* socket type
* actual address (`sockaddr`)

---

### 3. Extracting IP Addresses

Depending on the type:

```c
if (p->ai_family == AF_INET) {
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
    addr = &(ipv4->sin_addr);
} else {
    struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
    addr = &(ipv6->sin6_addr);
}
```

---

### 4. Converting to Human-Readable Form

```c
inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
```

* Converts binary IP → readable string

---

## 🚀 How to Compile & Run

```bash
gcc getaddrinfo.c -o getaddrinfo
./getaddrinfo example.com
```

---

## 🧪 Example Output

```text
IP addresses for example.com:

 IPv4: 93.184.216.34
 IPv6: 2606:2800:220:1:248:1893:25c8:1946
```

---

## ⚠️ Important Notes

* Always call `freeaddrinfo(res)` to avoid memory leaks
* `getaddrinfo()` may return multiple addresses (DNS can map to many IPs)
* Not all systems will return IPv6 results

---

## 💡 Takeaways

* `getaddrinfo()` is the **entry point for networking**
* It abstracts away IPv4 vs IPv6 differences
* It returns **all possible connection options**, not just one

---

## 🔗 Related Concepts

* `sockaddr`, `sockaddr_in`, `sockaddr_in6`
* Address families (`AF_INET`, `AF_INET6`)
* DNS resolution
* `inet_ntop()`

---

## 🧠 Mental Model

> `getaddrinfo()` = “Give me all the ways I can reach this host”

You then choose one of those options to:

* create a socket
* connect or bind

---
