#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

/* 
    Q: Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the
    pipe() system call.
*/

int main()
{

    int pipefd[2];
    int pipe_result = pipe(pipefd);
    if (pipe_result == -1)
    {
        perror("Unable to create pipe.");
        exit(EXIT_FAILURE);
    }

    pid_t child1 = fork();

    if (child1 == -1)
    {
        perror("Failed to fork process.\n");
        exit(EXIT_FAILURE);
    }
    else if (child1 == 0)
    {
        
        close(pipefd[0]);
        
        int dup_result = dup2(pipefd[1], STDOUT_FILENO);
        if (dup_result == -1)
        {
            perror("Failed to redirect pipe write to STDOUT\n");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]);
        
        char *myargs[3] = { strdup("ls"), strdup("-l"), NULL };

        execv("/bin/ls", myargs);
    }
    
    pid_t child2 = fork();
    if (child2 == -1)
    {
        perror("Failed to fork process.\n");
        exit(EXIT_FAILURE);
    }
    else if (child2 == 0)
    {
        close(pipefd[1]);

        int dup_result = dup2(pipefd[0], STDIN_FILENO);
        if (dup_result == -1)
        {
            perror("Failed to redirect pipe read to STDIN\n");
            exit(EXIT_FAILURE);
        }

        char *myargs[3] = { strdup("grep"), strdup("test"), NULL };

        execv("/bin/grep", myargs);
    
        close(pipefd[0]);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    return 0;
}