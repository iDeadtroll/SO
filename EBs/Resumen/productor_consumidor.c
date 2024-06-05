#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define QUEUESIZE 4 
#define LOOP 20

void *producer (void *args);  
void *consumer (void *args);

pthread_mutex_t mut =  PTHREAD_MUTEX_INITIALIZER;
sem_t notFull;
sem_t notEmpty;

typedef struct {
    int buf[QUEUESIZE];
    long head, tail;
    int full, empty;
} queue;

queue *queueInit (void);         
void queueDelete (queue *q);
void queueAdd (queue *q, int in);
void queueDel (queue *q, int *out);

int main ()
{
    sem_init(&notEmpty, 0, 0);
    sem_init(&notFull, 0 , QUEUESIZE);

    queue *fifo;
    pthread_t pro, con;

    fifo = queueInit ();
    if (fifo ==  NULL) {
        fprintf (stderr, "main: Queue Init failed.\n");
        exit (1);
    }

    pthread_create (&pro, NULL, producer, fifo);
    pthread_create (&con, NULL, consumer, fifo);

    pthread_join (pro, NULL);
    pthread_join (con, NULL);

    queueDelete (fifo);

    return 0;
}

void *producer (void *q)
{
    queue *fifo;
    int i;

    fifo = (queue *)q;

    for (i = 0; i < LOOP; i++) {
        pthread_mutex_lock (&mut);
        while (fifo->full) {
            printf ("producer: queue FULL.\n");
            pthread_mutex_unlock (&mut);
            sleep (1);
        }
        queueAdd (fifo, i);
        printf ("producer: added %d\n", i);
        pthread_mutex_unlock (&mut);
        sem_post (&notEmpty);
    }

    return (NULL);
}

void *consumer (void *q)
{
    queue *fifo;
    int i, d;

    fifo = (queue *)q;

    while(1) {
        sem_wait (&notEmpty);
        pthread_mutex_lock (&mut);
        while (fifo->empty) {
            printf ("consumer: queue EMPTY.\n");
            pthread_mutex_unlock (&mut);
            sleep (1);
        }
        queueDel (fifo, &d);
        printf ("consumer: deleted %d\n", d);
        pthread_mutex_unlock (&mut);
        sem_post (&notFull);
    }

    return (NULL);
}