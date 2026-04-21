# Network Programming Practice

This repository documents my hands-on learning of low-level networking using *Beej's Guide to Network Programming*.
The focus is on understanding sockets, system calls, and how networked programs actually communicate at the OS level.

---

## 📌 Goals

* Build intuition for **socket programming**
* Understand core **network-related system calls**
* Practice writing small, focused programs
* Bridge the gap between theory and real systems

---

## 📂 Repository Structure

```
.
system_calls/
└── getaddrinfo/
    ├── getaddrinfo.c
    └── README.md
```

---

## 🧠 Approach

For each system call:

* Implement a minimal working example
* Write a short explanation of:

  * what it does
  * when it’s used
  * key arguments
* Experiment with variations to understand behavior

For exercises:

* Solve problems from the guide
* Focus on correctness and clarity over complexity

---

## ⚙️ Key Concepts Covered

* Sockets (`socket`)
* Address structures (`sockaddr`, `sockaddr_in`, `sockaddr_storage`)
* Binding and listening (`bind`, `listen`)
* Connections (`accept`, `connect`)
* Data transfer (`send`, `recv`)
* IPv4 vs IPv6
* Blocking vs non-blocking behavior

---

## 🚀 How to Run

Compile using `gcc`:

```bash
gcc file.c -o program
./program
```

Some programs may require running multiple terminals (e.g., server/client).

---

## 📝 Notes

This is a learning repository:

* Code is intentionally simple and experimental
* Focus is on understanding, not production readiness

---

## 📚 Reference

* Beej’s Guide to Network Programming
