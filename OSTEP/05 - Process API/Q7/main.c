#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

/* 
    Q: Write a program that creates a child process, and then in the child
    closes standard output (STDOUT_FILENO). What happens if the child
    calls printf() to print some output after closing the descriptor?

    R: STDOUT_FILENO has no output for the child process, but the standard
    output is not closed and continues to function normally for the parent
    process.
*/

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
        printf("Forked child process with PID %d\n", getpid());
        printf("Closing STDOUT_FILENO in child process.\n");

        close(STDOUT_FILENO);

        printf("Printing in the child process.\n");
    }
    else 
    {
        pid_t wait_rc = wait(NULL);

        printf("Printing in the parent process.\n");
    }

    return 0;
}