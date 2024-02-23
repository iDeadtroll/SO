#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    int estadoHijo;
    int pid;
    int pid_son;
    pid = fork();
    if (pid == -1)
    {
        printf("Error al crear el proceso hijo\n");
        exit(-1);
    }
    if (pid == 0)
    {
        printf("Proceso hijo, pid %d\n", getpid());
        exit(0);
    }
    else
    {
        pid_son = wait(&estadoHijo);
        printf("Padre, el hijo con id %d %d ha terminado con código %d \n", pid_son, pid, estadoHijo);
    }
}