#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/* MESSAGE QUEUE */
#include <sys/ipc.h>
#include <sys/msg.h>

/* SEMAPHORE */
#include <sys/sem.h>

/* SHARED MEMORY */
#include <sys/shm.h>

/* MESSAGE STRUCTURE */
struct message
{
    long msg_type;
    char msg_text[100];
};

int main()
{
    /* ==========================================
       1. NAMED PIPE (FIFO)
       ========================================== */

    int fd;
    char fifo_write[] = "Hello from FIFO";
    char fifo_read[100];

    mkfifo("myfifo", 0666);

    fd = open("myfifo", O_RDWR);

    write(fd, fifo_write, strlen(fifo_write) + 1);
    read(fd, fifo_read, sizeof(fifo_read));

    printf("\n====== FIFO ======\n");
    printf("FIFO Write Message : %s\n", fifo_write);
    printf("FIFO Read Message  : %s\n", fifo_read);

    close(fd);

    /* ==========================================
       2. MESSAGE QUEUE
       ========================================== */

    int msgid;
    struct message msg;

    key_t key1 = ftok("progfile", 65);

    msgid = msgget(key1, 0666 | IPC_CREAT);

    msg.msg_type = 1;
    strcpy(msg.msg_text, "Hello from Message Queue");

    msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);

    msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);

    printf("\n====== MESSAGE QUEUE ======\n");
    printf("Message Queue Data : %s\n", msg.msg_text);

    msgctl(msgid, IPC_RMID, NULL);

    /* ==========================================
       3. SEMAPHORE
       ========================================== */

    int semid;

    key_t key2 = ftok("progfile", 75);

    semid = semget(key2, 1, 0666 | IPC_CREAT);

    semctl(semid, 0, SETVAL, 1);

    struct sembuf sb;

    sb.sem_num = 0;
    sb.sem_op = -1;
    sb.sem_flg = 0;

    semop(semid, &sb, 1);

    printf("\n====== SEMAPHORE ======\n");
    printf("Semaphore Locked\n");

    sleep(2);

    sb.sem_op = 1;

    semop(semid, &sb, 1);

    printf("Semaphore Unlocked\n");

    semctl(semid, 0, IPC_RMID);

    /* ==========================================
       4. SHARED MEMORY
       ========================================== */

    int shmid;
    char *shared_memory;

    key_t key3 = ftok("progfile", 85);

    shmid = shmget(key3, 1024, 0666 | IPC_CREAT);

    shared_memory = (char *)shmat(shmid, NULL, 0);

    strcpy(shared_memory, "Hello from Shared Memory");

    printf("\n====== SHARED MEMORY ======\n");
    printf("Shared Memory Data : %s\n", shared_memory);

    shmdt(shared_memory);

    shmctl(shmid, IPC_RMID, NULL);

    /* ========================================== */

    unlink("myfifo");

    return 0;
}
