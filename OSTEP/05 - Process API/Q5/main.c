#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

/* 
    Q: Now write a program that uses wait() to wait for the child process
    to finish in the parent. What does wait() return? What happens if
    you use wait() in the child?

    R: The return of the wait() call is the PID of the child process.
    Calling wait() in the child process leads a -1 return, as it has 
    no further child processes to wait for.

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

        pid_t wait_child_rc = wait(NULL);
        printf("Return of wait() for child process: %d\n", wait_child_rc);

        exit(EXIT_SUCCESS);
    }
    else 
    {
        pid_t wait_rc = wait(NULL);

        printf("Return of wait() for parent process: %d\n", wait_rc);
    }

    return 0;
}