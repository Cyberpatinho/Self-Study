#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

/* 
    Q: Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be
    useful?

    R: waitpid() is useful in the case we want to waint for an specific process to finish among multiple ones.
    The wait() call just waits for any of the childrens to terminate.
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
    }
    else 
    {
        int status;
        pid_t wait_rc = waitpid(rc, &status, 0);

        printf("Return of wait() for parent process: %d\n", wait_rc);
    }

    return 0;
}