#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int pid, status = 0;
    int fd[2];
    pipe(fd);

    if ((pid = fork()) == -1)
    {
        printf("Error al crear hijo\n");
        exit(1);
    }

    if (pid == 0)
    {
        close(fd[0]);               // Cerramos el extremo de lectura del tubo en el hijo
        dup2(fd[1], STDOUT_FILENO); // Redirigimos la salida estándar al tubo
        printf("Hijo: ejecutando ...\n");
        if (execl("/bin/grep", "/bin/grep", "-n", "printf", "P2.c", NULL) == 0)
        {
            printf("Hijo: fin de ejecucion\n");
            exit(0);
        }
        else
        {
            printf("Error al ejecutar execl\n");
            exit(1);
        }
    }
    else
    {
        char buffer[1024];
        close(fd[1]); // Cerramos el extremo de escritura del tubo en el padre
        printf("Padre: esperando a que hijo termine...\n");
        wait(&status);
        read(fd[0], buffer, sizeof(buffer)); // Leemos la salida del comando grep del tubo
        printf("Padre: La salida del comando grep es: \n%s", buffer);
        printf("Padre: fin de ejecucion\n");
        exit(0);
    }
}