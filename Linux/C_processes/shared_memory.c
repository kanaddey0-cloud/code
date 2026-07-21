/*
>> Shared Memory is simply a common memory block that multiple processes can read and write directly; it is not a FIFO or queue.
>> Is just a shared block of RAM—processes can read or write any location in any order.

+------------------------+
|   Shared Memory Block  |
+------------------------+
    ▲                 ▲
    │                 │
Process A         Process B
Read/Write       Read/Write

It is the fastest IPC because data is not copied between processes.
Both processes directly access the same memory from their user-space.
Pipe/FIFO: Data is copied through kernel space.

Shared Memory  → Stores Data
Semaphore      → Controls Access
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {

// int shmget(key_t key, size_t size, int shmflg);
// >> Creates a new shared memory segment or gets an existing one.
//     key → Unique key used to identify the shared memory segment.
//     size → Size of the shared memory (in bytes).
//     shmflg → Flags and permissions (e.g., IPC_CREAT | 0666).
//         IPC_CREAT = Create if not exists, otherwise use the existing shared memory. 
//         with (0666) file permission.
// Returns: Shared Memory ID (shmid) on success, -1 on failure.
    int shmid = shmget(1234, 1024, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    } // Any process using the same key (and having permission) can access the same shared memory by calling shmget() and then shmat().


// void *shmat(int shmid, const void *shmaddr, int shmflg);
// >> Attaches the shared memory segment to the process's address space.
//     shmid → Shared Memory ID returned by shmget().
//     shmaddr → Memory address where to attach (NULL lets the kernel choose).
//     shmflg → Attach mode (0 = read/write, SHM_RDONLY = read-only).
// Returns: Pointer to the attached shared memory on success, (void *)-1 on failure.
    char *data = (char *)shmat(shmid, NULL, 0);
    if (data == (char *)-1) {
        perror("shmat");
        return 1;
    }
//             Shared Memory (1024 bytes)
//         +-----------------------------+
//         |                             |
//         +-----------------------------+
// Process Virtual Memory
// 0x1000
// 0x2000
// 0x3000   ◄── Kernel may choose or any where in this share buffer if shmaddr = NULL
// 0x4000
// 0x5000
//             Shared Memory (1024 bytes)
//         +-----------------------------+
//         |                             |
//         +-----------------------------+
// Process Virtual Memory
// 0x1000
// 0x2000
// 0x3000   ◄── Requested by: shmat(shmid, (void *)0x3000, 0);
// 0x4000
// 0x5000

// After shmat(), the shared memory can be used like a normal byte array or pointer 
// (read/write with strcpy(), memcpy(), data[i], etc.).


    // strcpy(dest, src);
    strcpy(data, "Hello Shared Memory!");
    printf("\nWritten : %s\n\n", data);


// int shmdt(const void *shmaddr);
// >> Detaches the shared memory from the process (does not delete it).
//     shmaddr → Pointer returned by shmat().
// Returns: 0 on success, -1 on failure.
    if (shmdt(data) == -1) {
        perror("shmdt");
    }


// int shmctl(int shmid, int cmd, struct shmid_ds *buf);
// >> Controls the shared memory. Commonly used to delete the shared memory using IPC_RMID.
//     shmid → Shared Memory ID.
//     cmd → Operation to perform
//         IPC_RMID = Delete shared memory.
//         IPC_STAT = Get shared memory information.
//         IPC_SET  = Modify shared memory information.
//     buf → Pointer to struct shmid_ds (used with IPC_STAT/IPC_SET; NULL when deleting with IPC_RMID).
// Returns: 0 on success, -1 on failure.
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
    }
    // shmctl(shmid, IPC_RMID, NULL);      // Delete memory
    // struct shmid_ds info;
    // shmctl(shmid, IPC_STAT, &info);     // Get information
    // shmctl(shmid, IPC_SET, &info);      // Set information

    return 0;
}

// shmget()   → Shared Memory Get
//     │
//     ▼
// Create/Get Shared Memory
//     │
//     ▼
// shmat()    → Shared Memory Attach
//     │
//     ▼
// Attach to Process
//     │
//     ▼
// Read / Write Data
//     │
//     ▼
// shmdt()    → Shared Memory Detach
//     │
//     ▼
// Detach Memory
//     │
//     ▼
// shmctl()   → Shared Memory Control
//     │
//     ▼
// Delete / Get Info / Modify Memory

// shmget() → Get (Create/Get shared memory)
// shmat() → Attach (Connect shared memory to the process)
// shmdt() → Detach (Disconnect shared memory from the process)
// shmctl() → Control (Delete or manage shared memory)




//----------------------------- SEMAPHORE(to synchornized shared memomry) 

// semid
//   │
//   ▼
// +--------------------------------+
// |  Sem[0]  |  Sem[1]  |  Sem[2]  |
// +--------------------------------+
//      ▲          ▲          ▲
//  sem_num=0  sem_num=1  sem_num=2

// Suppose you have three shared resources:
//     Shared Memory A  ← Sem[0]
//     Shared Memory B  ← Sem[1]
//     Printer          ← Sem[2]
// Each resource has its own lock.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

// Required for semctl()
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {

    // Shared Memory 
    int shmid = shmget(1234, 1024, IPC_CREAT | 0666);  // Create shared memory
    char *data = (char *)shmat(shmid, NULL, 0);        // Attach shared memory


// int semget(key_t key, int nsems, int semflg);
// >> Creates a new semaphore set or gets an existing one.
//     key → Unique key used to identify the semaphore set.
//     nsems → Numbers of semaphores to create (1 = one semaphore).
//     semflg → Flags and permissions (e.g., IPC_CREAT | 0666).
// Returns: Semaphore ID (semid) on success, -1 on failure.
    int semid = semget(5678, 1, IPC_CREAT | 0666);
    // semid is not a semaphore. It is the ID of a semaphore set.
    //   ▼
    // +---------------------------+
    // | Sem[0] | Sem[1] | Sem[2] |
    // +---------------------------+


// union semun
// >> Used with semctl() to initialize or modify semaphore values.
//     val → Initial value of the semaphore.
    union semun arg;
    arg.val = 1;          // 1 = Unlocked


// int semctl(int semid, int semnum, int cmd, ...);
// >> Controls the semaphore (initialize, delete, get/set values).
//     semid → Semaphore ID.
//     semnum → Semaphore number in the set (0 = first semaphore).
//     cmd → Operation to perform.
//         SETVAL   = Initialize semaphore value.
//         GETVAL   = Get semaphore value.
//         IPC_STAT = Get semaphore information.
//         IPC_SET  = Modify semaphore information.
//         SETALL   = Set all semaphore values.
//         GETALL   = Get all semaphore values.
//         IPC_RMID = Delete semaphore set.
//
//     ... → Remaining parameter (depends on cmd)
//         SETVAL   → union semun (arg.val)
//         IPC_STAT → union semun (arg.buf)
//         IPC_SET  → union semun (arg.buf)
//         SETALL   → union semun (arg.array)
//         GETALL   → union semun (arg.array)
//         GETVAL   → No remaining parameter
//         IPC_RMID → No remaining parameter
//
// Returns: Depends on cmd, -1 on failure.
    semctl(semid, 0, SETVAL, arg);
    


// struct sembuf
// >> Describes a semaphore operation.
//     sem_num → Semaphore number (0 = first semaphore).
//     sem_op → Semaphore operation
//         Negative = Decrease semaphore by that amount (wait if not possible)
//         Positive = Increase semaphore by that amount
//         Zero     = Wait until semaphore value becomes 0
//     sem_flg → Additional options for semaphore operation.
//         0          = Default (wait/block) Process waits until another process unlocks the semaphore.
//         IPC_NOWAIT = Don't wait; return -1 immediately. Don't enter the critical section.
//         SEM_UNDO   = If a process crashes after locking the semaphore, the kernel automatically restores the semaphore value.
    struct sembuf lock = {0, -1, 0};


// int semop(int semid, struct sembuf *sops, size_t nsops);
// >> Performs semaphore operations (Lock / Unlock).
//     semid → Semaphore ID.
//     sops → Pointer to semaphore operation(s).
//     nsops → Number of operations.
// Returns: 0 on success, -1 on failure.
    semop(semid, &lock, 1);


    // ===== Critical Section =====
    strcpy(data, "Hello Shared Memory!");
    printf("Written: %s\n", data);
    // ============================


    struct sembuf unlock = {0, +1, 0};
    semop(semid, &unlock, 1);


    shmdt(data);                   // Detach shared memory (Cleanup)
    shmctl(shmid, IPC_RMID, NULL); // Delete shared memory

    if (semctl(semid, 0, IPC_RMID) == -1) {  // Delete Semaphore set
        perror("semctl");
    }

    return 0;
}

    //                 START
    //                   │
    //                   ▼
    //     Create/Get Shared Memory
    //     shmget() + shmat()
    //                   │
    //                   ▼
    //     Create/Get Semaphore Set
    //         semget(key, 1, ...)
    //                   │
    //                   ▼
    //   Initialize Semaphore = 1
    //  semctl(SETVAL, arg.val = 1)
    //                   │
    //                   ▼
    //           Lock Semaphore
    //      semop(lock : sem_op = -1)
    //                   │
    //                   ▼
    //     ===== Critical Section =====
    //     Write to Shared Memory
    //     strcpy(data, "Hello...")
    //                   │
    //                   ▼
    //          Unlock Semaphore
    //     semop(unlock : sem_op = +1)
    //                   │
    //                   ▼
    //    Detach & Delete Shared Memory
    //   shmdt() + shmctl(IPC_RMID)
    //                   │
    //                   ▼
    //        Delete Semaphore
    //   semctl(IPC_RMID)
    //                   │
    //                   ▼
    //                 END
    