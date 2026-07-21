// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>

// int main() {
//     int fd[2];
//     char write_msg[] = "Hello from pipe";
//     char read_msg[100];

//     pipe(fd);   // create pipe 
//     printf("Read  -> %d  \nWrite -> %d\n", fd[0], fd[1]); 

// // Process A             Kernel Pipe Buffer (Queue)                Process B
// // fd[1] ----write()-----> [ Hello MCA Students ] ----read()-----> fd[0]

// // write(fd[1], ...) → pushes bytes into the pipe buffer.
// // read(fd[0], ...) → removes (pops) bytes from the pipe buffer.

// // After fork(), both processes inherit both ends:

// // Parent: fd[0], fd[1]
// // Child : fd[0], fd[1]

// // So we use close() to keep only the required end open:

// // Parent (writer) -> close(fd[0])
// // Child  (reader) -> close(fd[1])

// // The pipe itself lives in the kernel, not in user memory.
// // Any process that have access that pipe descriptors can use them.
// //     If it has fd[1], it can write.
// //     If it has fd[0], it can read.
// // Usually a parent creates the pipe and then calls fork():

//     write(fd[1], write_msg, strlen(write_msg));

//     read(fd[0], read_msg, sizeof(read_msg));
//     printf("Received: %s\n", read_msg);

//     return 0;
// }


// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>

// int main() {
//     int fd[2];
//     pipe(fd);

//     pid_t pid = fork();

//     if (pid > 0) { // Parent → write
//         close(fd[0]); // Read off Only write
//         write(fd[1], "Hello Child, I am Your Parent.", 30);
//     }
//     else { // Child → read
//         char buffer[100];
//         close(fd[1]); // Write off Only Read
//         read(fd[0], buffer, 100);
//         printf("\nChild got: %s\n\n", buffer);
//     }

//     return 0;
// }




//Process Pipe --------------------------------------

// #include <stdio.h>

// int main() {
//     FILE *fp;
//     char buffer[100];

//     // Process Open (Uses a pipe internally)
//     fp = popen("ls", "r");   // Run command

//     if (fp == NULL) {
//         printf("Failed to execute command.\n");
//         return 1;
//     }

//     while (fgets(buffer, sizeof(buffer), fp) != NULL) {
//         printf("%s", buffer);
//     }

//     // Process Close
//     pclose(fp);

//     return 0;
// }

#include <stdio.h>

int main() {
    FILE *fp;
    char buffer[256];

    char *commands[] = {
        "date",
        "ls",
        "pwd",
        "whoami",
        "cat file.txt"
    };

    int n = sizeof(commands) / sizeof(commands[0]);

    for (int i = 0; i < n; i++) {

        printf("\n===== Command: %s =====\n", commands[i]);

        fp = popen(commands[i], "r");

        if (fp == NULL) {
            printf("Failed to execute command.\n");
            continue;
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }

        pclose(fp);
    }

    return 0;
}


/*-----------------------------------------------------------
Named Pipes (FIFOs, accessing FIFO)
//-----------------------------------------------------------
Why use Named Pipe (FIFO)?
Named pipes are used to communicate between unrelated processes, even if they are started separately or from different terminals.

Why not use a normal pipe()?
A normal pipe() is anonymous and typically works only between related processes (such as a parent and child created using fork()).

So, I use two files reader.c, writer.c 
*/

