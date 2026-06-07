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

    // STEP 1 : Create File
    fd = creat("mca.txt", 0777);
    if (fd < 0)
    {
        printf("File creation failed\n");
        exit(1);
    }

    printf("File created successfully\n");
    close(fd);

    // STEP 2 : Open File
    fd = open("mca.txt", O_RDWR);
    if (fd < 0)
    {
        printf("File open failed\n");
        exit(1);
    }

    printf("File opened successfully\n");

    // STEP 3 : Write into File
    write(fd, write_buffer, sizeof(write_buffer));
    printf("Data written into file\n");

    // STEP 4 : Move File Pointer using lseek()
    lseek(fd, 0, SEEK_SET);

    // STEP 5 : Read from File
    read(fd, read_buffer, sizeof(read_buffer));
    printf("File Content: %s\n", read_buffer);

    // STEP 6 : Move Pointer to 6th Position
    lseek(fd, 6, SEEK_SET);
    read(fd, &ch, 1);
    printf("Character at position 6 = %c\n", ch);

    // STEP 7 : Duplicate File Descriptor
    fd2 = dup(fd);
    printf("Original File Descriptor = %d\n", fd);
    printf("Duplicated File Descriptor = %d\n", fd2);

    // STEP 8 : Close Files
    close(fd);
    close(fd2);

    printf("Files closed successfully\n");

    return 0;
}
