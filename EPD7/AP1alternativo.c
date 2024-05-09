#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

#define CUSTOMER "/customer"
#define WAITINGROOM "/waitingroom"
#define HAIRCUT "/haircut"

void* customer(void*);
void* barber(void *);
sem_t* init_semaphore(char *, int);
void destroy_semaphore(sem_t *, char *);
void unlink_previous_semaphores(void); 

sem_t* customerIsWaiting;   
sem_t* accessToWaitingRoom;   
sem_t* doneHairCut;

int allDone = 0;
int numCustomerWaiting = 0;
int numCustomers = 10;
int numChairs = 5;

int main(void) {
	
	unlink_previous_semaphores();	
	
	pthread_t btid;
	pthread_t tid[numCustomers];
	int i;

	customerIsWaiting = init_semaphore(CUSTOMER, 0);
  	accessToWaitingRoom = init_semaphore(WAITINGROOM, 1);
  	doneHairCut = init_semaphore(HAIRCUT, 0);

	pthread_create(&btid, NULL, barber, NULL);

	for (i=0; i<numCustomers; i++)
		pthread_create(&tid[i], NULL, customer, &i);

	for (i=0; i<numCustomers; i++)
		pthread_join(tid[i],NULL);

	pthread_join(btid,NULL);	

	destroy_semaphore(customerIsWaiting,CUSTOMER);
 	destroy_semaphore(accessToWaitingRoom,WAITINGROOM);
 	destroy_semaphore(doneHairCut,HAIRCUT);

	return 0;
}

void *customer(void* dummy) {

	char id = 'a' + *(int*)dummy;

	for(;;) {

		printf("Customer %c arrives barber shop.\n", id);
		sem_wait(accessToWaitingRoom);

		if (numCustomerWaiting < numChairs) {

			printf("Customer %c enters waiting room.\n", id);
			numCustomerWaiting++;
			sem_post(customerIsWaiting);
			sem_post(accessToWaitingRoom);
			sem_wait(doneHairCut);
			printf("Customer %c has been served and leaves the shop.\n", id);
			

		} else {

			sem_post(accessToWaitingRoom);
			printf("Customer %c leaves barber shop because it's full.\n", id);
			sleep(5); //retry after 5 sec

		}

	}

}

void *barber(void *dummy) {

	for(;;) {

		printf("Barber falls sleep.\n");
		sem_wait(customerIsWaiting);
		if (allDone)
			break;

		sem_wait(accessToWaitingRoom);
		printf("Barber wakes up.\n");
		numCustomerWaiting--;

		sem_post(accessToWaitingRoom);
		printf("Barber starts cutting hair.\n");

		sleep(1);
		sem_post(doneHairCut);

		printf("Barber finishes cutting hair.\n");
	}

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
  int r1 = sem_unlink(CUSTOMER);
  int r2 = sem_unlink(WAITINGROOM);
  int r3 = sem_unlink(HAIRCUT);
  if (r1==-1||r2==-1||r3==-1)
  	printf("INFO: ningún semapforo que des-enlazar\n");
  else
  	printf("INFO: semáforos des-enlazados\n");
}



