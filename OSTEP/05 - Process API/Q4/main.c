#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

/* 
    Q: Write a program that calls fork() and then calls some form of
    exec() to run the program /bin/ls. See if you can try all of the
    variants of exec(), including (on Linux) execl(), execle(),
    execlp(), execv(), execvp(), and execvpe(). Why do
    you think there are so many variants of the same basic call?

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
        printf("Calling ls from Child process %d\n", getpid());

        char *myargs[2];
        myargs[0] = strdup("/bin/ls");
        myargs[1] = NULL;

        execv(myargs[0], myargs);
    }

    return 0;
}