#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

void* customer(void*);
void* barber(void *);

sem_t customerIsWaiting;   
sem_t accessToWaitingRoom;   
sem_t doneHairCut;

int allDone = 0;
int numCustomerWaiting = 0;
int numCustomers = 10;
int numChairs = 5;

int main(void) {

	pthread_t btid;
	pthread_t tid[numCustomers];
	int i;

	sem_init(&customerIsWaiting, 0, 0);
	sem_init(&accessToWaitingRoom, 0, 1);
	sem_init(&doneHairCut, 0, 0);

	pthread_create(&btid, NULL, barber, NULL);

	for (i=0; i<numCustomers; i++)
		pthread_create(&tid[i], NULL, customer, &i);

	for (i=0; i<numCustomers; i++)
		pthread_join(tid[i],NULL);

	pthread_join(btid,NULL);	

	return 0;
}

void *customer(void* dummy) {

	char id = 'a' + *(int*)dummy;

	for(;;) {

		printf("Customer %c arrives barber shop.\n", id);
		sem_wait(&accessToWaitingRoom);

		if (numCustomerWaiting < numChairs) {

			printf("Customer %c enters waiting room.\n", id);
			numCustomerWaiting++;
			sem_post(&customerIsWaiting);
			sem_post(&accessToWaitingRoom);
			sem_wait(&doneHairCut);
			printf("Customer %c has been served and leaves the shop.\n", id);
			return;

		} else {

			sem_post(&accessToWaitingRoom);
			printf("Customer %c leaves barber shop because it's full.\n", id);
			sleep(5); //retry after 5 sec

		}

	}

}

void *barber(void *dummy) {

	for(;;) {

		printf("Barber falls sleep.\n");
		sem_wait(&customerIsWaiting);
		if (allDone)
			break;

		sem_wait(&accessToWaitingRoom);
		printf("Barber wakes up.\n");
		numCustomerWaiting--;

		sem_post(&accessToWaitingRoom);
		printf("Barber starts cutting hair.\n");

		sleep(1);
		sem_post(&doneHairCut);

		printf("Barber finishes cutting hair.\n");
	}

}




