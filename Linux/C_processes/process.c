// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <unistd.h>

// int main()
// {
//     printf("I am %d before forking process\n", (int)getpid());
//     pid_t pid = fork();

//     printf("Fork returned: %d\n", (int)pid);
// }

//----------------------------------------------

// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <unistd.h>

// int main()
// {
//     printf("I am process %d before forking process\n\n", (int)getpid());
//     pid_t pid = fork();
//     printf("Fork returned inside process %d: %d\n", (int)getpid(), (int)pid);

//     if(pid < 0)
//         perror("Fork failed");
//     else if(pid == 0)
//         printf("I am the child process pid %d\n\n", (int)getpid());
//     else
//         printf("I am the parent process %d\n\n", (int)getpid());
    
//     return 0;
// }

//----------------------------------------------

// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>

// int main()
// {
//     pid_t pid, mypid, myppid;

//     pid = getpid();
//     printf("Before fork: Process id is %d\n", pid);
//     printf("Called fork() system call\n\n");
//     pid = fork();

//     if(pid < 0){
//         perror("fork() failure");
//         return 1;
//     }
//     if(pid == 0){
//         // Child
//         printf("This is child process with fork() = %d\n", pid);
//         mypid = getpid();
//         myppid = getppid();
//         printf("Process id is %d and PPID is %d\n\n", mypid, myppid);
//     }
//     else{
//         // Process
//         sleep(2);
//         printf("This is parent process with fork() = %d\n", pid);
//         mypid = getpid();
//         myppid = getppid();
//         printf("Process id is %d and PPID is %d\n", mypid, myppid);
//         printf("Newly created process id or child pid is %d\n\n", pid);
//     }

//     return 0;
// }

//----------------------------------------------
/*
Zombie Process

Technical Definition:
A zombie process is a child process that has terminated its execution, 
but its parent process has not yet retrieved its termination status using the wait() or waitpid() system call. 
As a result, the process remains as an entry in the process table.

Simple Meaning:
A zombie process is a dead child process whose parent is still alive and has not yet collected its exit information.
*/
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <unistd.h>
// // Zomie
// int main(){
//     pid_t pid;
//     pid = fork();

//     if(pid < 0){
//         printf("Fork Failed\n");
//         exit(1);
//     }
//     else if(pid == 0){
//         printf("Child Process\n");
//         printf("Child PID = %d\n", getpid());
//         printf("Child process terminated\n");
//         exit(0);
//     }
//     else{
//         printf("Parent Process\n");
//         printf("Parent PID = %d\n", getpid());
//         printf("Parent sleeping for 4 seconds\n");
//         sleep(7);
//         printf("\nParent process fork() after child dead : %d\n", (int)pid);
//         printf("Parent process completed\n");
//     }

//     return 0;
// }


/*
Orphan Process

Technical Definition:
An orphan process is a child process whose parent process has terminated before the child completes execution. 
The orphan process is subsequently adopted by the system's init process (PID 1) or an equivalent system process.

Simple Meaning:
An orphan process is a running child process whose parent has died, so the operating system assigns it a new parent.
*/
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <unistd.h>

// int main(){
//     pid_t pid;
//     pid = fork();

//     if (pid < 0){
//         printf("Fork Failed\n");
//         exit(1);
//     }
//     else if (pid == 0){  // Child process
//         sleep(7);  // Wait so parent can terminate first
//         printf("Child Process\n");
//         printf("Child PID = %d\n", getpid());
//         printf("New Parent PID = %d\n", getppid());
//     }
//     else{  // Parent process
//         printf("Parent Process\n");
//         printf("Parent PID = %d\n", getpid());
//         printf("Parent process terminated\n");
//         exit(0);
//     }

//     return 0;
// }

//----------------------------------------------

// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main(){
//     pid_t pid = fork();

//     if(pid < 0) exit(1);

//     if(pid == 0){
//         // Child process
//         printf("Child process running...\n");
//         sleep(4);
//         printf("Child process finished\n\n");
//     }
//     else{
//         // Parent process
//         printf("Parent waiting for child..!\n\n");
//         wait(NULL); // "Wait for child process to finished. I don't need extra information."
//         printf("Parent resumed after child finished\n");
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <stdlib.h>

// int main(){
//     pid_t pid = fork();

//     if(pid < 0) exit(1);

//     if(pid == 0){
//         printf("Child running...\n");
//         sleep(4);
//         printf("Child process finished\n\n");
//         exit(16);
//     }        // integer exit status (0–255)
//     else{
//         printf("Parent waiting for child..!\n\n");
//         int status;
//         wait(&status); // OS stores child result into `status`
//         if (WIFEXITED(status)) {
//             printf("Child exit status = %d\n", WEXITSTATUS(status));
//         }
//     }   // status stores full child termination information like exit code, signal, and process state.
//         // WEXITSTATUS(status) is a macro extracts the child process exit value Only
//     return 0;
// }

//----------------------------------------------

// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <stdlib.h>

// int main() {
//     pid_t pid = fork();

//     if(pid < 0) exit(1);

//     if (pid == 0) {
//         printf("Child running... PID = %d\n", getpid());
//         sleep(2);
//         printf("Child exiting\n");

//     } else {
//         int status;
//         printf("Parent waiting for child PID = %d\n", pid);

//         // waitpid(pid, &status, 0);   // wait for specific child
//         waitpid(pid, &status, WNOHANG);  // (like server checking multiple children) — there it usefull & powerful.

//         printf("Child finished : %d\n", WEXITSTATUS(status));
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <stdlib.h>

// int main() {
//     pid_t pid = fork();

//     if(pid < 0) exit(1);

//     if (pid == 0) {
//         printf("Child running... PID = %d\n", getpid());
//         sleep(2);
//         printf("Child exiting\n");
//         exit(5);   // giving exit status
//     } 
//     else {
//         int status;
//         printf("Parent waiting for child PID = %d\n", pid);

//         pid_t ret = waitpid(pid, &status, WNOHANG);

//         printf("waitpid return = %d\n", ret);

//         if (ret == 0) {
//             printf("Child still running (no status yet)\n");
//         }
//         else if (ret == pid) {
//             if (WIFEXITED(status)) {
//                 printf("Child exit status = %d\n", WEXITSTATUS(status));
//             }
//         }
//         else {
//             printf("Error in waitpid\n");
//         }
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <stdlib.h>

// int main() {
//     pid_t pid = fork();

//     if(pid < 0) exit(1);

//     if (pid == 0) {
//         // child
//         printf("Child working...\n");
//         sleep(5);
//         printf("Child done\n");
//     } else {
//         int status;

//         while (1) {
//             pid_t result = waitpid(pid, &status, WNOHANG);

//             if (result == 0) {
//                 // child still running
//                 printf("Parent: child still running...\n");
//             }
//             else if (result == pid) {
//                 // child finished
//                 printf("Parent: child finished\n");
//                 break;
//             }
//             else {
//                 // error
//                 printf("Error\n");
//                 break;
//             }

//             sleep(1); // avoid busy loop
//         }
//     }

//     return 0;
// }

//----------------------------------------------

// int kill(pid_t pid, int sig);

// 🔥 Termination signals
//     SIGKILL   (9) → force kill process (cannot be ignored)
//     SIGTERM  (15) → polite request to terminate (default kill)
//     SIGINT    (2) → interrupt from keyboard (Ctrl + C)
//     SIGQUIT   (3) → quit + core dump (Ctrl + \)

// ⏸️ Stop / Resume signals
//     SIGSTOP   (19) → forcefully pause process (cannot be ignored)
//     SIGTSTP   (20) → pause from terminal (Ctrl + Z)
//     SIGCONT   (18) → continue a stopped process

// ⚠️ Important system signals
//     SIGHUP     (1) → terminal closed / reload config
//     SIGALRM   (14) → timer alarm expired
//     SIGCHLD   (17) → child process stopped/terminated

// 💥 Crash / error signals
//     SIGSEGV   (11) → segmentation fault (invalid memory access)
//     SIGFPE     (8) → floating point error (divide by zero)
//     SIGABRT    (6) → abort() called
//     SIGILL     (4) → illegal instruction

                                // Commonly Use
// SIGKILL → force kill process
// SIGTERM → politely terminate
// SIGSTOP → pause process
// SIGCONT → continue paused process
// SIGINT  → Ctrl+C interrupt

// #include <stdio.h>
// #include <unistd.h>
// #include <signal.h>

// int main() {
//     pid_t pid = getpid();   // current process ID

//     printf("My PID = %d\n", pid);

//     sleep(2);

//     printf("Stopping myself (SIGSTOP)\n");
//     kill(pid, SIGSTOP);   // process will PAUSE here

//     printf("This will not print immediately\n");

//     sleep(2);

//     printf("Continuing myself (SIGCONT)\n");
//     kill(pid, SIGCONT);   // resume process

//     sleep(2);

//     printf("Now terminating using SIGTERM\n");
//     kill(pid, SIGTERM);   // polite termination

//     return 0;
// }

// // ✔ The OS (kernel) is the one that actually stops the process.
// // parent → optional sender, not controller
// #include <stdio.h>
// #include <unistd.h>
// #include <signal.h>
// #include <stdlib.h>

// int main() {
//     pid_t pid = fork();

//     if(pid < 0) exit(1);

//     if (pid == 0) 
//         while (1) {
//             printf("Child running...\n");
//             sleep(1);
//         }
//     else {  sleep(4);

//         printf("Parent sending SIGSTOP\n");
//         kill(pid, SIGSTOP);  // Child process PAUSE 

//         printf("\nParent sleepping!\n\n"); sleep(7);

//         printf("Parent sending SIGCONT\n");
//         kill(pid, SIGCONT);  // Child process RESUME 

//         sleep(4);

//         printf("Parent sending SIGKILL\n");
//         kill(pid, SIGKILL);  // Child process polite termination 
//     }

//     return 0;
// }

//----------------------------------------------

