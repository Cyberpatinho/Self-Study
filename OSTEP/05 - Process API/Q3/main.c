#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

/* 
    Q: Write another program using fork(). The child process should
    print “hello”; the parent process should print “goodbye”. You should
    try to ensure that the child process always prints first; can you do
    this without calling wait() in the parent?

*/

void handler(int signum) {
}

int main()
{

    signal(SIGUSR1, handler);
    
    pid_t rc = fork();

    if (rc == -1)
    {
        printf("Failed to fork process.\n");
        exit(EXIT_FAILURE);
    }
    else if (rc == 0)
    {
        printf("hello\n");
        
        kill(getppid(), SIGUSR1);
    }
    else 
    {
        pause();

        printf("goodbye\n");
    }

    return 0;
}