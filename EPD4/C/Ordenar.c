#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int pid1, pid2, status;

    pid1 = fork();
    if (pid1 == -1)
    {
        printf("Error al crear el primer proceso");
        exit(1);
    }

    if (pid1 == 0)
    {
        printf("Sin ordenar\n");
        if (execl("/bin/cat", "/bin/cat", "nombres.txt", NULL) == -1)
        {
            printf("Error al ejecutar execl");
            exit(1);
        }
    }
    else
    {
        printf("\nPadre: esperando hijo1\n");
        wait(&status);
        printf("\nPadre: fin de ejecucion hijo1\n");
    }

    pid2 = fork();
    if (pid2 == -1)
    {
        printf("Error al crear el segundo proceso");
        exit(1);
    }

    if (pid2 == 0)
    {
        printf("Ordenado\n");
        if (execl("/bin/sort", "/bin/sort", "nombres.txt", NULL) == -1)
        {
            printf("Error al ejecutar execl");
            exit(1);
        }
    }
    else
    {
        printf("\nPadre: esperando hijo2\n");
        wait(&status);
        printf("\nPadre: fin de ejecucion hijo2\n");
        exit(0);
    }

    return 0;
}