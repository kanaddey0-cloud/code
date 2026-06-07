#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char write_msg[] = "Hello from pipe";
    char read_msg[100];

    pipe(fd);   // create pipe

// Process A             Kernel Pipe Buffer (Queue)                Process B
// fd[1] ----write()-----> [ Hello MCA Students ] ----read()-----> fd[0]

// write(fd[1], ...) → pushes bytes into the pipe buffer.
// read(fd[0], ...) → removes (pops) bytes from the pipe buffer.

// After fork(), both processes inherit both ends:

// Parent: fd[0], fd[1]
// Child : fd[0], fd[1]

// So we use close() to keep only the required end open:

// Parent (writer) -> close(fd[0])
// Child  (reader) -> close(fd[1])

// The pipe itself lives in the kernel, not in user memory.
// Any process that possesses the pipe descriptors can use them.
//     If it has fd[1], it can write.
//     If it has fd[0], it can read.
// Usually a parent creates the pipe and then calls fork():

    write(fd[1], write_msg, strlen(write_msg));

    read(fd[0], read_msg, sizeof(read_msg));
    printf("Received: %s\n", read_msg);

    return 0;
}


#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid > 0) { // Parent → write
        close(fd[0]); // Read off Only write
        write(fd[1], "Hello Child", 12);
    }
    else { // Child → read
        char buffer[100];
        close(fd[1]); // Write off Only Read
        read(fd[0], buffer, 100);
        printf("Child got: %s\n", buffer);
    }

    return 0;
}

/*
Inter-process communication 
Pipes (use functions pipe(), popen(), pclose()),  
Named Pipes (FIFOs, accessing FIFO),  
Message Queues (use functions msgget(), msgsnd(), msgrcv(), msgctl()),  
Semaphores (use functions semctl(), semget(), semop()) 
Shared Memory (use functions shmget(), shmat(), shmdt(), shmctl()) 
*/

// /* File Descriptor Duplication */
// int dup2(int oldfd, int newfd);

// /* Signals */
// void (*signal(int signum, void (*handler)(int)))(int);

/*
pid_t fork(void);
int pipe(int fd[2]);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);
pid_t wait(int *status);
int dup2(int oldfd, int newfd);
int execvp(const char *file, char *const argv[]);
*/



