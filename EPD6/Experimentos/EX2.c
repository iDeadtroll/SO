#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>

#define TAMBUF 8     // Tamaño del búfer circular
#define NUMDATOS 100 // Número de datos a enviar
//
// El buffer circular y los correspondientes punteros
int buffer[TAMBUF];
int bufin = 0;
int bufout = 0;
//
// Semaforo binario
pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;
//
// Variable suma
unsigned int sum = 0;
//
// Semaforos generales
sem_t hay_datos;
sem_t hay_sitio;
//
// Funciones de escritura y lectura del buffer circular
void obten_dato(int *itemp)
{
    *itemp = buffer[bufout];
    printf("Consumidor lee %d desde posición %d \n", *itemp, bufout);
    bufout = (bufout + 1) % TAMBUF;
    return;
}
void pon_dato(int item)
{
    printf("Productor pone %d en posición %d \n", item, bufin);
    buffer[bufin] = item;
    bufin = (bufin + 1) % TAMBUF;
    return;
}
//
// Funciones productor-consumidor
void *productor(void *arg1)
{
    int i;
    for (i = 1; i <= NUMDATOS; i++)
    {
        sem_wait(&hay_sitio);
        pthread_mutex_lock(&buffer_lock);
        pon_dato(i * i);
        pthread_mutex_unlock(&buffer_lock);
        sem_post(&hay_datos);
    }
    pthread_exit(NULL);
}
void *consumidor(void *arg2)
{
    int i, midato;
    for (i = 1; i <= NUMDATOS; i++)
    {
        sem_wait(&hay_datos); // Resta 1 al semaforo
        pthread_mutex_lock(&buffer_lock);
        obten_dato(&midato);
        pthread_mutex_unlock(&buffer_lock);
        sem_post(&hay_sitio); // Suma 1 al semaforo
        sum += midato;
    }
    pthread_exit(NULL);
}
//
// Funcion principal
main()
{
    pthread_t tidprod, tidcons;
    unsigned int i, total;
    total = 0;
    for (i = 1; i <= NUMDATOS; i++)
        total += i * i;
    //
    // Inicializacion de semaforos
    sem_init(&hay_datos, 0, 0);
    sem_init(&hay_sitio, 0, TAMBUF);
    //
    // Se crean los threads
    pthread_create(&tidcons, NULL, consumidor, NULL); // Hilo de tipo consumidor
    pthread_create(&tidprod, NULL, productor, NULL);  // Hilo del tipo productor

    //
    // Se espera a que los threads terminen
    pthread_join(tidprod, NULL);
    pthread_join(tidcons, NULL);
    printf("\nEl resultado deberia ser %d\n", total);
    printf("Los threads produjeron el valor %d\n", sum);
}
// 1. ¿Qué pasa si en la función consumidor comentamos la instrucción sem_wait(&hay_datos);? ¿Y si borramos la instrucción
// sem_post(&hay_sitio);?
// 2. ¿Qué pasa si el la función productor borramos la instrucción pthread_mutex_unlock(&buffer_lock);?
// 3. ¿Qué pasa si inicializamos el semáforo hay_sitio a 0?
// 4. ¿En este caso, cuando hay context switch? ¿Por qué?
// 5. ¿Por qué los hilos siempre se ejecutan hasta que se bloquean? ¿Como se podía cambiar ese comportamiento? Intente
// insertar la instrucción pthread_yield() para ver su efecto