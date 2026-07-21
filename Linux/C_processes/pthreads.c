// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>

// void *thread1(void *arg) {
//     int i = 1;
//     while (i <= 16) {
//         printf("Thread 1 : %d\n", i);
//         // sleep(1);
//         i++;
//     }
//     return NULL;
// }

// void *thread2(void *arg) {
//     int i = 1;
//     while (i <= 16) {
//         printf("Thread 2 : %d\n", i);
//         // sleep(1);
//         i++;
//     }
//     return NULL;
// }

// int main() {  printf("\n");

//     pthread_t t1, t2;

//     // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
//     pthread_create(&t1, NULL, thread1, NULL);
//     pthread_create(&t2, NULL, thread2, NULL);
//     // thread → Pointer to a pthread_t variable that will store the thread ID.
//     // attr → Thread attributes (NULL for default).
//     // start_routine → Function the thread will execute.
//     // arg → Argument passed to the thread function (NULL if no argument).

//     // int pthread_join(pthread_t thread, void **retval); -> Wait for both threads to finish
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);
//     // thread → The thread ID to wait for.
//     // retval → Address where the thread's return value will be stored.
//     //     Use NULL if you don't need the return value.

//     printf("\nt1 = %d   t2 = %d \nBoth threads are finished.\n", (int)t1, (int)t2);

//     return 0;
// }

//-----------------------------------------------------------


// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>

// void *worker(void *arg)
// {
//     printf("\nThread is running...\n");
//     sleep(2);
//     printf("Thread finished.\n\n");
//     return NULL;
// }

// int main()
// {
//     pthread_t thread;
//     pthread_attr_t attr;

//     // 1. Initialize attributes with default values
//     pthread_attr_init(&attr);

//     // 2. Set thread as JOINABLE (default)
//     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

//     // 3. Set stack size (1 MB)
//     pthread_attr_setstacksize(&attr, 1024 * 1024);

//     // 4. Create thread using custom attributes
//     pthread_create(&thread, &attr, worker, NULL);

//     // 5. Destroy attribute object (no longer needed)
//     pthread_attr_destroy(&attr);

//     // 6. Wait for thread to finish
//     pthread_join(thread, NULL);

//     printf("Main thread finished.\n");

//     return 0;
// }

/*
pthread_attr_t is an opaque data type. That means its internal structure is intentionally hidden by the POSIX threads library.
typedef struct
{
    int detachstate;      // Joinable or Detached
    size_t stacksize;     // Thread stack size
    void *stackaddr;      // Stack address
    size_t guardsize;     // Guard page size
    int schedpolicy;      // Scheduling policy
    struct sched_param priority; // Thread priority
    int inheritsched;     // Inherit scheduling?
    int scope;            // Scheduling scope
} 
pthread_attr_t;

Instead, you must use the provided API functions:
| Function                                                      | Purpose                                          |
| ------------------------------------------------------------- | ------------------------------------------------ |
| `pthread_attr_init(&attr)`                                    | Initialize attribute object with default values. |
| `pthread_attr_destroy(&attr)`                                 | Destroy/free the attribute object.               |
| `pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE)` | Create a joinable thread.                        |
| `pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)` | Create a detached thread.                        |
| `pthread_attr_setstacksize(&attr, size)`                      | Set thread stack size.                           |
| `pthread_attr_getstacksize(&attr, &size)`                     | Get thread stack size.                           |
| `pthread_attr_setschedpolicy()`                               | Set scheduling policy (advanced).                |
| `pthread_attr_setinheritsched()`                              | Set scheduling inheritance (advanced).           |
*/

//-----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t tid1, tid2; // Global Thread IDs

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
    printf("%s\n\n", d->msg);

    sleep(2);
    printf("\nThread 1 Completing...\n\n");
    pthread_exit("Thread 1 Exited Successfully");  // return massage
}

// THREAD 2 FUNCTION ================================================================
void *thread2_func(void *arg)
{
    while (1) {
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


    // --Thread 1 also defult attr because of pthread_attr_init(&attr), but this is the way being manual attr
    printf("\nCreating Thread 1...\n");
    struct Data d = {10, 20, "Hello"};
    pthread_create(&tid1, &attr, thread1_func, &d);

    printf("Creating Thread 2...\n");
    pthread_create(&tid2, NULL, thread2_func, NULL); // --Thread 2 with defult attr
    
    // --Main thread waits for Thread 1 to finish and collects its return value.
    pthread_join(tid1, &msg);
    printf("\nreturn message -> %s\n\n", (char *)msg);

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
