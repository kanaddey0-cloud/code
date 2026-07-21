Inter-Process Communication (IPC)
│
├── 1. Pipes
│   │
│   ├── Anonymous Pipe
│   │   ├── pipe()
│   │   ├── read()
│   │   ├── write()
│   │   └── close()
│   │
│   └── Process Pipe
│       ├── popen()
│       └── pclose()
│
├── 2. Named Pipes (FIFO)
│   ├── mkfifo()
│   ├── open()
│   ├── read()
│   ├── write()
│   ├── close()
│   └── unlink()
│
├── 3. Shared Memory 
│   ├── shmget()
│   ├── shmat()
│   ├── shmdt()
│   └── shmctl()
│
├── 4. Message Queues
│   ├── msgget()
│   ├── msgsnd()
│   ├── msgrcv()
│   └── msgctl()
│
└── 5. Semaphores
    ├── semget()
    ├── semop()
    └── semctl()


// /* File Descriptor Duplication */
// int dup2(int oldfd, int newfd);


Shared Memory (use functions shmget(), shmat(), shmdt(), shmctl()) 
👉 **Shared memory is a kernel-controlled memory segment that is not accessed via file descriptors fd[2]; like pipes, and any process can use it only after attaching to it with `shmat()`, provided it has permission set during `shmget()`.**

shmget → creates shared memory segment (with permissions)
int shmget(key_t key, size_t size, int shmflg);
     (key, size, IPC_CREAT | permissions); 👉 Kernel creates shared segment

shmat  → attaches shared memory to process address space (request entry)
void *shmat(int shmid, const void *shmaddr, int shmflg);
    (shmid, NULL, 0); 👉 Kernel checks: 
                        permission bits  --user access  --validity of shmid  --If OK → gives pointer

shmdt  → detaches shared memory (leave the room)
int shmdt(const void *shmaddr);

shmctl → controls shared memory (delete, status, permissions control)
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
      (shmid, IPC_RMID, NULL); 👉 Deletes the shared memory segment
      (shmid, IPC_STAT, &buf); 👉 Gets status (size, permissions, owner, etc.)
      (shmid, IPC_SET, &buf);  👉 Changes permissions/metadata