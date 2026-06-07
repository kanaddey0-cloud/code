#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Global Thread IDs
pthread_t tid1, tid2;

struct Data {
    int x;
    int y;
    char msg[20];
};

// THREAD 1 FUNCTION ================================================================
void *thread1_func(void *arg)
{
    printf("\nThread 1 Started\n");
    printf("Thread 1 ID : %ld\n", pthread_self());

    struct Data *d = (struct Data *)arg;
    printf("%d\n", d->x);
    printf("%d\n", d->y);
    printf("%s\n", d->msg);

    sleep(2);
    printf("Thread 1 Completing...\n");
    pthread_exit("Thread 1 Exited Successfully");  // return massage
}

// THREAD 2 FUNCTION ================================================================
void *thread2_func(void *arg)
{
    while (1)
    {
        printf("Thread 2 Running...\n");
        sleep(1);
    }
    return NULL;
}


// ================================================================
// MAIN FUNCTION
// ================================================================
int main()
{
    void *msg;
    pthread_attr_t attr;

    pthread_attr_init(&attr);  // default configuration for thread
    printf("Thread Attributes Initialized\n");

    // pthread_create(thread_id, attr, function_name, argument);

    // --Thread 1 also defult attr because of pthread_attr_init(&attr), but this is the way being manual attr
    printf("\nCreating Thread 1...\n");
    struct Data d = {10, 20, "Hello"};
    pthread_create(&tid1, &attr, thread1_func, &d);

    printf("Creating Thread 2...\n");
    pthread_create(&tid2, NULL, thread2_func, NULL); // --Thread 2 with defult attr
    
    // --Main thread waits for Thread 1 to finish and collects its return value.
    pthread_join(tid1, &msg);
    printf("\nreturn message -> %s\n", (char *)msg);

    sleep(7);  // let Thread 2 run for some time
    pthread_cancel(tid2); printf("\nThread 2 Cancelled\n");
    pthread_join(tid2, NULL);  // Main thread waits for Thread 2 to terminate; NULL means no return value is collected.

    printf("\nAll Threads Finished Successfully\n");
    return 0;
}

// Main Thread
//    |
//    |-- init attributes
//    |
//    |-- create Thread 1
//    |-- create Thread 2
//    |
//    |---- Thread 1 runs → exits → returns message
//    |
//    |-- join Thread 1 (wait)
//    |
//    |-- sleep (let Thread 2 run)
//    |
//    |-- cancel Thread 2
//    |
//    |-- join Thread 2
//    |
//    ↓
// Program ends
