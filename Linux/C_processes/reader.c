// Named Pipes (FIFOs, accessing FIFO)

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

    char buffer[100];

    int fd = open("mypipe", O_RDONLY);
    if (fd == -1) {
        perror("open"); return 1;
    }

    int n = read(fd, buffer, sizeof(buffer));
    if (n > 0) {
        buffer[n] = '\0';
        printf("Received: %s\n", buffer);
    }

    close(fd);

    return 0;
}

/*
Named Pipe (FIFO) — Short Summary
             Named Pipe (FIFO)
         (Special File: mypipe)
                 │
                 ▼
      +---------------------+
      | Kernel FIFO Buffer  |
      +---------------------+
         ▲             ▼
     write()        read()
         │             │
     Process A     Process B

Key Points
    FIFO (First-In, First-Out) is a named pipe for IPC.
    Appears as a special file (p in ls -l).
    Data is stored in the kernel buffer, not on disk.
    Supports communication between unrelated processes.
    Works on the same machine only.
    A single FIFO is half-duplex (one-way).
    read() blocks if no data; write() blocks if no reader/buffer full.
    Exists until deleted (unlink() or rm).

System Calls
    mkfifo() → open() → write()/read() → close() → unlink()

Definition
A Named Pipe (FIFO) is a special file that enables unrelated processes on the same machine to communicate through a kernel-managed First-In, First-Out byte stream.
*/