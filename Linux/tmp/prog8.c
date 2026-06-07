#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int sig)
{
    printf("\nSignal %d received\n", sig);

    if (sig == SIGINT)
    {
        printf("SIGINT handled\n");
    }

    if (sig == SIGALRM)
    {
        printf("SIGALRM handled\n");
    }
}

int main()
{
    sigset_t set;

    // Register signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGALRM, signal_handler);

    printf("Process ID = %d\n", getpid());

    // BLOCKING SIGNAL
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, NULL);

    printf("\nSIGINT blocked for 5 seconds\n");
    sleep(5);

    // UNBLOCK SIGNAL
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    printf("SIGINT unblocked\n");

    // ALARM SIGNAL
    alarm(5);
    printf("\nAlarm set for 5 seconds\n");

    // SELF SIGNAL USING raise()
    printf("\nSending signal to itself using raise()\n");
    raise(SIGINT);

    // DELIVER SIGNAL USING kill()
    printf("\nSending signal using kill()\n");
    kill(getpid(), SIGINT);

    // SUSPEND PROCESS
    printf("\nProcess suspended using pause()\n");
    printf("Press Ctrl+C to continue...\n");
    pause();

    printf("\nProcess resumed\n");

    return 0;
}
