#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
    int pid;

    pid = fork();// Se crea el proceso hijo
    if (!pid) // Es lo mismo que poner: if( pid == 0)
    {
        // Cuando el proceso hijo muere pasa ha ser zombie
        printf("\nChild: pid: %d\n", getpid());
        exit(0);
    }
    sleep(1); // Aqui nos aseguramos que el proceso hijo muera antes que el padre
    printf("\nPlease, press enter after looking at the zombie process...");
    (void)getchar(); // Se detiene el proceso hasta que el usuario presione enter
}