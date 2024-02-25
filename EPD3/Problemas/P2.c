#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int n = 1, pid, status = 0;

    if ((pid = fork()) == -1)
    {
        printf("Error al crear el proceso\n");
        exit(1);
    }
    if (pid == 0)
    {
        int m;
        printf("Hijo: valor inicial %d\n", n);
        printf("Ingrese un numero: ");
        scanf("%d", &m);
        n = m;
        printf("\nHijo: valor modificado por %d", m);
        int varPrueba = 10;
        printf("\nHijo: valor nueva variable %d", varPrueba);
        exit(0);
    }
    else
    {
        wait(&status);
        printf("\nPadre: valor inicial %d", n);
        n += 35;
        printf("\nPadre: valor modificado por %d", n);
        int varPrueba = 10;
        printf("\nPadre: valor nueva variable %d\n", varPrueba);
        exit(0);
    }
}
