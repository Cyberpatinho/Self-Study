#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

/* 
    Q: Write a program that opens a file (with the open() system call)
    and then calls fork() to create a new process. Can both the child
    and parent access the file descriptor returned by open()? What
    happens when they are writing to the file concurrently, i.e., at the
    same time?

    R: Yes, there's no conflict between opening the same file descriptor 
    in different processes. Both can also write concurrently to it, as
    the O_APPEND is atomic, although the writing order is not deterministic.
*/

void write_to_file(int fd, char *process, int run)
{
    for (int i = 0; i < run; i++)
    {
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%s process %d\n", process, i);

        write(fd, buffer, strlen(buffer));
    }
}

int main()
{

    pid_t rc = fork();

    if (rc == -1)
    {
        printf("Failed to fork process.\n");
        exit(EXIT_FAILURE);
    }
    else if (rc == 0)
    {
        printf("Opening file test.txt on Child process.\n");
        int fd = open("test.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
        printf("Opened file descriptor %d on Child process\n", fd);

        write_to_file(fd, "Child", 100000);

        close(fd);
    }
    else 
    {
        printf("Opening file test.txt on Parent process.\n");
        int fd = open("test.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
        printf("Opened file descriptor %d on Parent process\n", fd);

        write_to_file(fd, "Parent", 100000);

        close(fd);
    }

    return 0;
}