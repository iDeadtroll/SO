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
        printf("Error al crear el proceso");
        exit(1);
    }

    if (pid == 0)
    {
        printf("Hijo: ejutando proceso...\n");
        if (execl("/bin/ls", "/bin/ls", "-ll", "./", NULL) == -1)
        {
            printf("Error al ejecutar execl\n");
            exit(1);
        }
    }
    else
    {
        printf("Padre: Esperando a hijo...\n");
        wait(&status);
        printf("Padre: hijo ha terminado\n");
        exit(0);
    }
}