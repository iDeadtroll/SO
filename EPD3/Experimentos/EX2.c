#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int pid = 0, status = 0;
    if ((pid = fork()) == -1)
    {
        printf("Error al crear proceso hijo\n");
        exit(1);
    }
    if (pid == 0)
    { // proceso hijo
        if (execl("/bin/ls", "/bin/ls", "-al", NULL) == -1)
            printf("Error al ejecutar execl\n");
            exit(1);
    }
    else
    { // Proceso Padre
        wait(&status);
        printf("El proceso hijo finalizo con el estado %d\n", status);
    }
}