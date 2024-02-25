#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
    int pid;
    /* let's create a child process */
    pid = fork();
    if (pid)
    {
        /* this is the parent: dies immediately it leaves one child
        behind */
        // sleep(1);
        printf("\nParent: pid: %d\n", getpid());
        exit(0);
    }
    /* child process: becomes orphane soon */
    printf("Child: my original parent id is: %d\n", getppid());
    sleep(1);
    printf("Child: my new parent id is: %d ... I am an orphane...\n", getppid());
}