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
        if (execl("/home/developer/proyectos/SO/EPD3/Problemas/AP1_source", "/home/developer/proyectos/SO/EPD3/Problemas/AP1_source", "3", "2", "1", NULL) == -1)
        {
            printf("Error al ejecutar execl");
            exit(1);
        }
    }
    else
    {
        wait(&status);
        exit(0);
    }
}