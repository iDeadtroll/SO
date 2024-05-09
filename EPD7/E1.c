#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <semaphore.h> 

#define QUEUESIZE 4 
#define LOOP 20 

typedef struct { 
  int buf[QUEUESIZE]; 
  long head, tail; 
  int full, empty; 
} queue;

void* producer (void *args); 
void* consumer (void *args); 
queue *queueInit (void); 
void queueDelete (queue *q); 
void queueAdd (queue *q, int in); 
void queueDel (queue *q, int *out);

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; 
sem_t notFull; 
sem_t notEmpty; 

int main (void){

	
  	queue *fifo; 
  	pthread_t pro, con; 

	fifo = queueInit (); 
	if (fifo ==  NULL) { 
		fprintf (stderr, "main: Queue Init failed.\n"); 
	    exit (1); 
	} 
  
  sem_init(&notEmpty, 0, 0);
  sem_init(&notFull, 0, QUEUESIZE);

  pthread_create (&pro, NULL, producer, fifo); 
  pthread_create (&con, NULL, consumer, fifo); 
 
  pthread_join (pro, NULL); 
  pthread_join (con, NULL); 
  
  queueDelete (fifo); 

  pthread_mutex_destroy(&mut);

  return 0; 
} 

void *producer (void *q) { 
  queue *fifo; 
  int i; 

  fifo = (queue *)q; 

  for (i = 0; i < LOOP; i++) { 
           
    if (fifo->full) { 
      printf ("producer: queue FULL.\n");      

    } 
    
    sem_wait(&notFull); 
    pthread_mutex_lock(&mut); 
     
    queueAdd (fifo, i); 

    pthread_mutex_unlock(&mut); 
    sem_post(&notEmpty); 
    
    printf("producer: inserted %d\n",i); 
    usleep (100000); 
  } 
   
  pthread_exit(NULL);
} 

void *consumer (void *q) { 
  queue *fifo; 
  int i, d; 

  fifo = (queue *)q; 

  for (i = 0; i < LOOP; i++) {     
    if (fifo->empty) { 
      printf ("consumer: queue EMPTY.\n");       
    } 
    sem_wait(&notEmpty); 
    pthread_mutex_lock(&mut); 

    queueDel (fifo, &d); 
     
    pthread_mutex_unlock(&mut); 
    sem_post(&notFull); 
    printf ("consumer: recieved %d.\n", d); 
    usleep(200000); 
  } 
   pthread_exit(NULL);
} 

queue *queueInit (void) { 
  queue *q; 
  q = (queue *)malloc (sizeof (queue)); 
  if (q == NULL) return (NULL); 
  q->empty = 1; 
  q->full = 0; 
  q->head = 0; 
  q->tail = 0; 
  return (q); 
} 

void queueDelete (queue *q) { 
  free (q); 
} 

void queueAdd (queue *q, int in) { 
  q->buf[q->tail] = in; 
  q->tail++; 
  if (q->tail == QUEUESIZE) 
  q->tail = 0; 
  if (q->tail == q->head) 
  q->full = 1; 
  q->empty = 0; 
  return; 
} 

void queueDel (queue *q, int *out) { 
  *out = q->buf[q->head]; 
  q->head++; 
  if (q->head == QUEUESIZE) 
  q->head = 0; 
  if (q->head == q->tail) 
  q->empty = 1; 
  q->full = 0; 
  return; 
} 