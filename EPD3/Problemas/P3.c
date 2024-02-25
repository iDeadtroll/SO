#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int pid, status = 0;
    if ((pid = fork()) == -1)
    {
        printf("Error la crear hijo\n");
        exit(1);
    }

    if (pid == 0)
    {
        printf("Hijo: ejecutando ...\n");
        if (execl("/bin/grep", "/bin/grep", "-n", "printf", "P2.c", NULL) == -1)
        {
            printf("Error al ejecutar execl\n");
            exit(1);
        }
    }
    else
    {
        printf("Padre: esperando a que hijo termine...\n");
        wait(&status);
        printf("Padre: fin de ejecucion\n");
        exit(0);
    }
}