#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define QUEUESIZE 4
#define LOOP 20
void *producer(void *args);
void *consumer(void *args);
// SEMAFORO BINARIO INICIALIZADO
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
// SEMAFOROS GENERICOS, TIENEN QUE SE INICIALIZADOS EN EL MAIN
sem_t notFull;
sem_t notEmpty;
typedef struct
{
    int buf[QUEUESIZE];
    long head, tail;
    int full, empty;
} queue;
queue *queueInit(void);
void queueDelete(queue *q);
void queueAdd(queue *q, int in);
void queueDel(queue *q, int *out);
int main()
{
    queue *fifo;
    pthread_t pro, con;
    fifo = queueInit();
    if (fifo == NULL)
    {
        fprintf(stderr, "main: Queue Init failed.\n");
        exit(1);
    }
    /***************************************/
    // completar
    // inicia aqui
    // fin
    /**************************************/
    // delete the queue
    queueDelete(fifo);
    return 0;
}
void *producer(void *q)
{
    queue *fifo;
    int i;
    fifo = (queue *)q;
}
void *consumer(void *q)
{
    queue *fifo;
    int i, d;

    fifo = (queue *)q;
}
queue *queueInit(void)
{
    queue *q;
    q = (queue *)malloc(sizeof(queue));
    if (q == NULL)
        return (NULL);
    q->empty = 1;
    q->full = 0;
    q->head = 0;
    q->tail = 0;
    return (q);
}
void queueDelete(queue *q)
{
    free(q);
}
void queueAdd(queue *q, int in)
{
    q->buf[q->tail] = in;
    q->tail++;
    if (q->tail == QUEUESIZE)
        q->tail = 0;
    if (q->tail == q->head)
        q->full = 1;
    q->empty = 0;
    return;
}
void queueDel(queue *q, int *out)
{
    *out = q->buf[q->head];
    q->head++;
    if (q->head == QUEUESIZE)
        q->head = 0;
    if (q->head == q->tail)
        q->empty = 1;
    q->full = 0;
    return;
}
