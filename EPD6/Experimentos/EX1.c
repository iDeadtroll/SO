#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void *MyThread(void *);
pthread_mutex_t mutex; /* mutex id */
main()
{
    pthread_t idA, idB;                       /* ids of threads */
    if (pthread_mutex_init(&mutex, NULL) < 0) // Primero se inicializan los semaforos
    {
        perror("pthread_mutex_init");
        exit(1);
    }
    if (pthread_create(&idA, NULL, MyThread, (void *)"A") != 0)
    {
        perror("pthread_create"); // Inicializacion de hilo A
        exit(1);
    }
    if (pthread_create(&idB, NULL, MyThread, (void *)"B") != 0)
    {
        perror("pthread_create");
        exit(1);
    }
    (void)pthread_join(idA, NULL);
    (void)pthread_join(idB, NULL);
    (void)pthread_mutex_destroy(&mutex); // Hay que destruir los semaforos
}
int x = 0; /* global shared variable */
void *MyThread(void *arg)
{
    char *sbName;
    sbName = (char *)arg;
    IncrementX();
    printf("X = %d in Thread %s\n", x, sbName);
}
IncrementX()
{
    int Temp; /* local variable */
    Temp = x;
    Temp = Temp + 1;

    BeginRegion(); /* enter critical region */
    x = Temp;
    EndRegion(); /* exit critical region */
}
BeginRegion()
{
    pthread_mutex_lock(&mutex);
}
EndRegion()
{
    pthread_mutex_unlock(&mutex);
}

// • ¿Qué pasa si en IncrementX() comentamos la linea EndRegion();?
// • ¿Qué podría pasar si en IncrementX() comentamos la linea BeginRegion();?