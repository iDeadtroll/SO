#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
    int pid = 0, status = 0, n = 0;
    printf("Introduzca un numero: ");
    scanf("%d", &n);
    if ((pid = fork()) == -1)
    {
        printf("Error al crear proceso hijo\n");
        exit(1);
    }
    if (pid == 0)
    { /* Proceso Hijo */
        n = n * 2;
        printf("Hijo: El PID de mi proceso padre es %d mi PID es %d\n", getppid(), getpid());
        printf("Hijo: La variable n vale %d \n", n);
        printf("Hijo: voy a dormir 2 segundos\n");
        sleep(6);
        printf("Hijo: mi estado actual %d\n", status);
        exit(1);
    }
    else
    { /* Proceso Padre */
        printf("Padre: Mi PID es el %d y he creado un proceso hijo cuyo pid es %d\n", getpid(), pid);
        printf("Padre: La variable n vale %d \n", n);
        printf("Padre: Espero a mi hijo\n");
        wait(&status);
        printf("\nPadre: El proceso hijo finalizo con el estado %d\n", status);
        exit(0);
    }
}