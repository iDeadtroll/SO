#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>    /* POSIX threads */
void *mythread(void *); /* prototype of thread routine */
int sharedVar = 1234;   /* global variable */
int main()
{
    pthread_t tid;
    int pid;
    printf("\n Main: sharedVar= %d.\n", sharedVar);
    pid = fork(); /* create a child process */
    if (pid == 0) /* child code begins */
    {
        pthread_create(&tid, NULL, mythread, NULL);
        printf("\n CHILD: created thread %lu. sharedVar=%d \n",
               (unsigned long)tid, sharedVar);
        pthread_yield(); /* yield to another thread */
        printf("\n CHILD: sharedVar= %d.\n", sharedVar);
        pthread_yield(); /* yield to another thread */
        printf("\n CHILD: sharedVar= %d.\n", sharedVar);
        pthread_join(tid, NULL);
        printf("CHILD: DONE\n");
    }
    if (pid > 0) /* PARENT CODE */
    {
        printf("\n PARENT: sharedVar= %d.\n", sharedVar);
        sharedVar = 44444444;
        printf("\n PARENT: sharedVar= %d.\n", sharedVar);
        pthread_yield(); /* yield to another thread */
        printf("\n PARENT: sharedVar= %d.\n", sharedVar);
        pthread_yield(); /* yield to another thread */
        printf("\n PARENT: sharedVar= %d.\n", sharedVar);
    }
    exit(0);
}
/******************/
/* thread routine */
/******************/
void *mythread(void *arg)
{
    /* display the value of the global variable */
    printf("\n thread %lu: sharedVar now is %d.\n",
           pthread_self() % 1000, sharedVar);
    sharedVar = 111;
    printf("\n thread %lu: sharedVar now is %d.\n",
           pthread_self() % 1000, sharedVar);
    pthread_yield(); /* yield to another thread or main */
    printf("\n thread %lu: sharedVar now is %d.\n",
           pthread_self() % 1000, sharedVar);
    sharedVar = 222;
    printf("\n thread %lu: sharedVar now is %d.\n",
           pthread_self() % 1000, sharedVar);
    pthread_yield(); /* yield to another thread or main */
    pthread_exit(NULL);
}