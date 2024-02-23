// Programa ejemplo.c
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int i = 0;
    printf("Hola, soy un programa de ejemplo\n");
    for (i = 0; i <= 10; i++)
    {
        printf("Ejecutando el for iteracion %d\n", i);
    }
    // salgo normalmente
    return (0);
}