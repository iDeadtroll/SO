#include <semaphore.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h>
#include <fcntl.h>

#define NOTEMPTY "/notempty"
#define NOTFULL "/notfull"
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
sem_t* init_semaphore(char *, int);
void destroy_semaphore(sem_t *, char *);
void unlink_previous_semaphores(void); 

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; 
sem_t* notFull; 
sem_t* notEmpty; 

int main (void){

	unlink_previous_semaphores();	
  	queue *fifo; 
  	pthread_t pro, con; 

	fifo = queueInit (); 
	if (fifo ==  NULL) { 
		fprintf (stderr, "main: Queue Init failed.\n"); 
	    exit (1); 
	} 
  
  notEmpty = init_semaphore(NOTEMPTY, 0);
  notFull = init_semaphore(NOTFULL, QUEUESIZE);

  pthread_create (&pro, NULL, producer, fifo); 
  pthread_create (&con, NULL, consumer, fifo); 
 
  pthread_join (pro, NULL); 
  pthread_join (con, NULL); 
  
  queueDelete (fifo); 

  pthread_mutex_destroy(&mut);
  destroy_semaphore(notEmpty,NOTEMPTY);
  destroy_semaphore(notFull,NOTFULL);

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
    
    sem_wait(notFull); 
    pthread_mutex_lock(&mut); 
     
    queueAdd (fifo, i); 

    pthread_mutex_unlock(&mut); 
    sem_post(notEmpty); 
    
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
    sem_wait(notEmpty); 
    pthread_mutex_lock(&mut); 

    queueDel (fifo, &d); 
     
    pthread_mutex_unlock(&mut); 
    sem_post(notFull); 
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

sem_t * init_semaphore(char * sem_name, int value){
    sem_t * s;
    if((s = sem_open(sem_name, O_CREAT, 0644, value)) == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }
    return s;      
}

void destroy_semaphore(sem_t * sem, char * name){
  if (sem_close(sem) == -1) {
    perror("sem_close");
    exit(EXIT_FAILURE);
  }
  if (sem_unlink(name) == -1) {
    perror("sem_unlink");
    exit(EXIT_FAILURE);
  }
}

void unlink_previous_semaphores(){
  int r1 = sem_unlink(NOTEMPTY);
  int r2 = sem_unlink(NOTFULL);
  if (r1==-1||r2==-1)
  	printf("INFO: ningún semapforo que des-enlazar\n");
  else
  	printf("INFO: semáforos des-enlazados\n");
}