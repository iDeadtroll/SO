/*
 threads.c
 Ejemplo de cómo se crea un thread.
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* Datos compartidos */
int contador = 0;
void *hilo_ejecucion(void *ignorado)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        contador++;
        printf("(%d) %d elefante%s se columpiaba%s sobre...\n", getpid(),
               contador,
               contador > 1 ? "s" : "",
               contador > 1 ? "n" : "");
        sleep(2);
    }
    pthread_exit(NULL);
}
main()
{
    int i;
    pthread_t thread; /* thread */
    printf("(%d) Creando thread\n", getpid());
    if (pthread_create(&thread, NULL, hilo_ejecucion, NULL) != 0)
        perror("pthread_create");
    if (pthread_join(thread, NULL) != 0)
        perror("pthread_join");
    printf("(%d) El valor del contador es %d\n", getpid(), contador);
}