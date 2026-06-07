#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    printf("PID of prog1.c = %d\n", getpid());

    pid_t p;
    p = fork();

    if(p == -1)
        printf("There is an error while calling fork()\n");
    
    if(p == 0){
        printf("Child process is running\n");
        printf("Now we will call prog2.c as child\n\n");
        char *args[] = {"prog2", "C", "Programming", "10", "2.4", NULL};
                        // Pass any number of arguments or Pass no arguments
        execv("./prog2", args);
    }
// int execl(const char *path, const char *arg, ...);
// execl() → Run a program using its full path, passing arguments one by one.
// execl("/bin/ls", "ls", "-l", NULL);

// int execlp(const char *file, const char *arg, ...);
// execlp() → Same as execl(), but searches the program in the PATH environment variable, so you can write "ls" instead of "/bin/ls".
// execlp("ls", "ls", "-l", NULL);

// int execv(const char *path, char *const argv[]);
// execv() → Run a program using its full path, passing arguments as an array (argv[]).
// execv("./prog1", argv);

// int execvp(const char *file, char *const argv[]);
// execvp() → Same as execv(), but searches the program in the PATH environment variable, so you can write "ls" instead of "/bin/ls".
// execvp("ls", argv);

    else
        printf("Now parent process is running\n");
    
    return 0;
}