#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd, fd2;
    char write_buffer[] = "Hello MCA Students";
    char read_buffer[100];
    char ch;

/*
0777 → rwx rwx rwx
0644 → rw- r-- r--
0755 → rwx r-x r-x
    Owner  : Read, Write, Execute
    Group  : Read, Write, Execute
    Others : Read, Write, Execute

Read = 4  Write = 2  Execute = 1
7 = 4 + 2 + 1 = rwx
*/
    // STEP 1: Create File
    fd = creat("mca.txt", 0777);
    if (fd < 0) {
        perror("File creation fatled\n");
        exit(1);
    }
    printf("File created successfully\n");
    close(fd);


/*
| Flag       | Meaning                 |
| ---------- | ----------------------- |
| `O_RDONLY` | Open for Read Only      |
| `O_WRONLY` | Open for Write Only     |
| `O_RDWR`   | Open for Read and Write |
| ---------- | ------------------------------------------------ |
| `O_CREAT`  | Create file if it doesn't exist                  |
| `O_TRUNC`  | Erase existing contents                          |
| `O_APPEND` | Always write at the end                          |
| `O_EXCL`   | Used with `O_CREAT`, fail if file already exists |

fd = open("data.txt", O_CREAT | O_EXCL, 0777);
  1. O_CREAT → Create data.txt if it does not exist.
  2. O_EXCL → If data.txt already exists, do not open it; return an error instead.

fd = open("data.txt", O_CREAT | O_RDWR, 0777);
  ✔ File is created if not exists
  ✔ File opened for read + write
*/
    // STEP 2: open File
    fd = open("mca.txt", O_RDWR);
    if(fd < 0) {
        perror("File open failed\n");
        exit(1);
    }
    printf("File opened successfully\n");

    // STEP 3: Write Into File
    write(fd, write_buffer, sizeof(write_buffer));
    printf("Data written into file\n");

    // STEP 4: Read from File
    read(fd, read_buffer, sizeof(read_buffer));
    printf("File Content: %s\n", read_buffer);


/*
off_t lseek(int fd, off_t offset, int whence);
    offset = how many bytes to move
    whence = where to start counting from

lseek(fd, 5, SEEK_SET);  → Go to byte 5 from the beginning.
lseek(fd, -5, SEEK_SET); ❌ Invalid

lseek(fd, 5, SEEK_CUR);  → Go 5 bytes forward from the current position.
lseek(fd, -5, SEEK_CUR); → Go 5 bytes backward from the current position.

lseek(fd, -5, SEEK_END); → Go 5 bytes before the end of the file.
lseek(fd, 5, SEEK_END);  → Move 5 bytes after end of file 0................17  0................17.....23
This is usually valid on Unix/Linux.   
                                   ^                           ^
*/
    // STEP 5: Hove File Pointer using Iseek()
    lseek(fd, 0, SEEK_SET); // Go to beginning of the file.

    // STEP 6: Move Pointer to 6th Posttton
    lseek(fd, 6, SEEK_SET); // Go to byte 6 from the beginning of the file.
    read(fd, &ch, 1);
    printf("Character at position 6  = %c\n", ch);

    // STEP 7: Duplicate File Descriptor
    fd2 = dup(fd);
    printf("Original File Descriptor= %d\n", fd);
    printf("Duplicated File Descriptor = %d\n", fd2);

    // STEP 8: file information (metadata)
    struct stat st;
    stat("file.txt", &st);
    printf("Size: %ld bytes\n", st.st_size);
// struct stat {
//     dev_t     st_dev;     // device ID
//     ino_t     st_ino;     // inode number
//     mode_t    st_mode;    // file type + permissions
//     nlink_t   st_nlink;   // hard links count
//     uid_t     st_uid;     // user ID of owner
//     gid_t     st_gid;     // group ID of owner
//     off_t     st_size;    // file size in bytes
//     time_t    st_atime;   // last access time
//     time_t    st_mtime;   // last modify time
//     time_t    st_ctime;   // last status change time
// };

    // STEP 9: Close Files
    close(fd);
    close(fd2);
    printf("Files closed successfully\n");
    return 0;
}
