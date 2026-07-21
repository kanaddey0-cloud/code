// Named Pipes (FIFOs, accessing FIFO)

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {

    if (mkfifo("mypipe", 0666) == -1) {
        perror("mkfifo");
    }
    
    int fd = open("mypipe", O_WRONLY);
    if (fd == -1) {
        perror("open"); return 1;
    }

    char msg[] = "Hello MCA Students";
    write(fd, msg, strlen(msg) + 1);

    close(fd);
    unlink("mypipe");    // Delete the FIFO

    return 0;
}

// Writer
//    │
// mkfifo()
//    │
// open()
//    │
// Reader
//    │
// open()
//    │
// read/write
