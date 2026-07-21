/*
EXAMPLE : while (1);

When You press: Ctrl+C ( It's stop execution, Then the default action for SIGINT is: )
    ↓
Terminal driver detects it
    ↓
Kernel sends SIGINT
    ↓
Foreground process receives SIGINT
Infinite loop itself does not generate a signal.
Ctrl+C generates SIGINT, which tells the process to stop.


>> A signal is a software notification sent by the kernel (or another process) to a process to inform it that an important event has occurred and that some action may be required.
>> A signal is an asynchronous software interrupt delivered to a process by the operating system or another process to notify it of an event and trigger a predefined or user-defined response.

Why? Processes run independently and cannot continuously check for every event happening in the system. Signals provide a way for the kernel to asynchronously notify a process about events such as:
Signal = Kernel's message to a process about an important event.

SIGINT   (2)   - User interruption (Ctrl + C)
SIGSEGV  (11)  - Invalid memory access (Segmentation Fault)
SIGCHLD  (17)  - Child process terminated or stopped
SIGALRM  (14)  - Timer expiration (Alarm signal)
SIGTERM  (15)  - Termination request
SIGSTOP  (19)  - Stop process (cannot be caught or ignored)
SIGCONT  (18)  - Continue a stopped process

Event occurs
      ↓
Kernel detects event
      ↓
Kernel sends signal
      ↓
Process receives signal
      ↓
Default action OR user-defined handler runs
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("\nReceived SIGINT (%d)\n", sig);
}   // Fixed Function_name and Funtion_perameter

int main() {
    signal(SIGINT, handler);  // void (*signal(int signum, void (*handler)(int)))(int);
    while (1) {
        printf("Running...\n");  sleep(1);
    }
    return 0;
} // cd Linux/C_Processes
