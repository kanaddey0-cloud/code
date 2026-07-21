/*
>> Message Queue is a kernel-managed queue that stores complete messages.
>> It preserves message boundaries (unlike pipes).
>> Processes communicate by sending and receiving messages.

    MESSAGE QUEUE
(Kernel Message Queue)
        Message 1
        Message 2
        Message 3
            ▲
            │
+-------------------------+
|   Kernel Message Queue  |
+-------------------------+
      ▲             ▼
    msgsnd()      msgrcv()
      │             │
    Process A     Process B

Key Points
    Kernel-managed queue for Inter-Process Communication (IPC).
    Stores complete messages (not just bytes).
    Preserves message boundaries.
    Supports message types/priorities.
    Communication is asynchronous (sender and receiver don't need to run at the same time).
    Data is stored in kernel space.
    Slower than Shared Memory, but easier and safer for exchanging messages.

Definition
A Message Queue is a kernel-managed IPC mechanism that stores and transfers complete messages between processes while preserving message boundaries.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// The first field must be long (message type), used to identify/filter messages during receiving.
struct message {
    long type;
    char text[100];
};
// The kernel maintains a queue of complete messages. (void *msgp)
// Each message can have any structure (variables, arrays, strings, etc.).
// But its first field must be a long (message type) used to identify/filter messages.
// Messages are stored in a normal queue by default (not a priority queue).

struct student {
    long type;
    int id; char name[50]; float marks;
};
        // OR

struct employee {
    long type;
    int emp_id; double salary; char dept[20];
};


int main() {

// int msgget(key_t key, int msgflg);
// >> Creates a new message queue or gets an existing one.
//     key → Unique key used to identify the message queue.
//     msgflg → Flags and permissions (e.g., IPC_CREAT | 0666).
//         IPC_CREAT = Create if not exists, otherwise use the existing queue.
//         with (0666) file permission.
// Returns: Message Queue ID (msgid) on success, -1 on failure.
    int msgid = msgget(1234, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        return 1;
    }


// struct message
// +-----------------------+
// | long type             |
// +-----------------------+
// | char text[100]        |
// +-----------------------+

    struct message msg;
    msg.type = 1;

    // strcpy(dest, src);
    strcpy(msg.text, "Hello Message Queue!");


// int msgsnd(int msgid, const void *msgp, size_t msgsz, int msgflg);
// >> Sends a message to the message queue.
//     msgid → Message Queue ID.
//     msgp → Pointer to the message structure.
//     msgsz → Size of the message (excluding long type).
//     msgflg → Flags.
//         0 → Default (wait if the queue is full).
//         IPC_NOWAIT → Don't wait; return -1 immediately if the queue is full.
// Returns: 0 on success, -1 on failure.
    msgsnd(msgid, &msg, sizeof(msg.text), 0);


// ssize_t msgrcv(int msgid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
// >> Receives a message from the message queue.
//     msgid → Message Queue ID.
//     msgp → Pointer to store the received message.
//     msgsz → Size of the message (excluding long type).
//     msgtyp → Message type to receive (0 = first message).
//     msgflg → Flags 
//         0 → Default (wait until a matching message arrives).
//         IPC_NOWAIT → Don't wait; return -1 immediately if no matching message exists.
//         MSG_NOERROR → If the message is larger than your buffer, truncate it instead of failing.
//         MSG_EXCEPT → Receive any message except the specified msgtyp (Linux/System V extension).
// Returns: Number of bytes received, -1 on failure.
    msgrcv(msgid, &msg, sizeof(msg.text), 0, 0);

    printf("\nReceived : %s\n\n", msg.text);


// int msgctl(int msgid, int cmd, struct msqid_ds *buf);
// >> Controls the message queue.
//     msgid → Message Queue ID.
//     cmd → Operation to perform.
//         IPC_RMID = Delete queue.
//         IPC_STAT = Get queue information.
//         IPC_SET  = Modify queue information.
//     buf → Used with IPC_STAT / IPC_SET, NULL when deleting.
// Returns: 0 on success, -1 on failure.
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}


// msgget() → Message Get
//     │
//     ▼
// Create/Get Message Queue
//     │
//     ▼
// msgsnd() → Message Send
//     │
//     ▼
// Send Message
//     │
//     ▼
// msgrcv() → Message Receive
//     │
//     ▼
// Receive Message
//     │
//     ▼
// msgctl() → Message Control
//     │
//     ▼
// Delete / Get Info / Modify Queue