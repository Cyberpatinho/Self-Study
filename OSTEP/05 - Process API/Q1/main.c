#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

/*  
    Q: Write a program that calls fork(). Before calling fork(), have the
    main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process?
    What happens to the variable when both the child and parent change
    the value of x?

    R: The functions change_on_child() and change_on_parent() demonstrate that the variables in the child process are 
    just a copy of what is in the parent at the moment of the fork. Changing the variables in either the child or parent 
    process won't affect the other.
*/

/* Change the variable on Child and check the value on Parent after */
void change_on_child()
{
    int test_var = 100;
    printf("Parent process original value of test_var: %d\n", test_var);

    pid_t rc = fork();

    if (rc == -1)
    {
        printf("Failed to fork child process.\n");
        exit(EXIT_FAILURE);
    }
    else if (rc == 0)
    {
        printf("Running child process with PID %d\n", getpid());

        printf("Child process original value of test_var: %d\n", test_var);

        test_var = 200;

        printf("Child process final value of test_var: %d\n", test_var);
    }
    else 
    {
        printf("Process with PID %d forked a child with PID %d\n", getpid(), rc);
        
        int rc_wait = wait(NULL);
        if (rc_wait == -1) 
        {
            printf("Failed to wait for child process to finish.\n");
            exit(EXIT_FAILURE);
        }
        
        printf("Parent process final value of test_var: %d\n", test_var);
    }
}

/* Change the variable on Parent and check the value on Child */
void change_on_parent()
{
    int test_var = 100;
    printf("Parent process original value of test_var: %d\n", test_var);

    pid_t rc = fork();

    if (rc == -1)
    {
        printf("Failed to fork child process.\n");
        exit(EXIT_FAILURE);
    }
    else if (rc == 0)
    {
        printf("Running child process with PID %d\n", getpid());

        printf("Child process original value of test_var: %d\n", test_var);

        sleep(2);

        printf("Child process final value of test_var: %d\n", test_var);
    }
    else 
    {
        printf("Process with PID %d forked a child with PID %d\n", getpid(), rc);
        
        test_var = 200;
        
        printf("Parent process final value of test_var: %d\n", test_var);
    }
}

int main() 
{
    printf("Running change variable on Child:\n");
    change_on_child();

    sleep(2);
    
    printf("\n\nRunning change variable on Parent:\n");
    change_on_parent();
    
    return 0;
}