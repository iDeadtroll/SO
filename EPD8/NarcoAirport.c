#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Constantes para el número de pistas, tiempos de despegue, aterrizaje, llegada a pista y tiempo entre aviones VIP
#define NUM_PISTAS 5
#define TIEMPO_DESPEGUE 15
#define TIEMPO_ATERRIZAJE 10
#define TIEMPO_LLEGADA_PISTA 5
#define TIEMPO_ENTRE_VIP 30

// Semaforos para las pistas, mutex, aviones normales y VIP
sem_t pistas[NUM_PISTAS];
sem_t mutex;
sem_t aviones_normales;
sem_t aviones_vip;

// Variables globales para los aviones en espera (normales y VIP) y el último avión (normal o VIP)
int aviones_en_espera[2] = {0, 0}; // 0: normal, 1: vip
char *ultimo_avion = NULL;
time_t ultimo_vip = 0; // Tiempo en el que el último avión VIP despegó o aterrizó


// Estructura para representar un avión con id, tipo, estado y operación
typedef struct
{
    int id;
    char *tipo;
    char *estado;
    char *operacion;
} Avion;


// Estructura para los nodos de la cola
typedef struct Node {
    Avion* avion;
    struct Node* next;
} Node;

// Estructura para la cola
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Función para crear una nueva cola
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// Función para añadir un avión al final de la cola
void enQueue(Queue* q, Avion* avion) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->avion = avion;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

// Función para eliminar un avión del frente de la cola
Avion* deQueue(Queue* q) {
    if (q->front == NULL)
        return NULL;
    Node* temp = q->front;
    Avion* avion = temp->avion;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return avion;
}

// Función para verificar si la cola está vacía
int isEmpty(Queue* q) {
    return (q->rear == NULL);
}

// Colas para la espera de los aviones
Queue* cola_aviones_normales;
Queue* cola_aviones_vip;

// Función para la ejecución de un avión
void *run(void *arg)
{
    Avion *avion = (Avion *)arg;
        if (strcmp(avion->tipo, "NORMAL") == 0) {
        avion = deQueue(cola_aviones_normales);
    } else {
        avion = deQueue(cola_aviones_vip);
    }
    printf("Avión [%d] %s está en %s, esperando para %s.\n", avion->id, avion->tipo, avion->estado, avion->operacion);
    sem_wait(&mutex);                                                               // Espera para acceder a la sección crítica
    aviones_en_espera[avion->tipo == "NORMAL" ? 0 : 1] += 1;                        // Incrementa el número de aviones en espera
    int pista_asignada = rand() % NUM_PISTAS;                                       // Asignación aleatoria de pista
    if (avion->tipo == "NORMAL" || (avion->tipo == "VIP" && ultimo_avion != "VIP")) // Si el avión es normal o es VIP y el último avión no fue VIP
    {
        printf("Pista %d preparada.\n", pista_asignada);
        sem_wait(&pistas[pista_asignada]); // Espera para acceder a la pista
        printf("Pista %d asignada a Avión [%d] %s.\n", pista_asignada, avion->id, avion->tipo);
        if (avion->tipo == "VIP") // Si el avión es VIP
        {
            time_t ahora = time(NULL);
            if (ultimo_avion == "VIP" && ahora - ultimo_vip < TIEMPO_ENTRE_VIP) // Si el último avión fue VIP y no ha pasado el tiempo mínimo entre aviones VIP
            {
                sleep(TIEMPO_ENTRE_VIP - (ahora - ultimo_vip)); // Espera el tiempo restante
            }
            ultimo_vip = time(NULL); // Actualiza el tiempo del último avión VIP
        }
    }
    sem_post(&mutex);                                                     // Libera la sección crítica
    sem_post(avion->tipo == "NORMAL" ? &aviones_normales : &aviones_vip); // Libera el semáforo correspondiente al tipo de avión
    printf("Avión [%d] %s dirigiéndose a pista de %s.\n", avion->id, avion->tipo, avion->operacion);
    sleep(TIEMPO_LLEGADA_PISTA); // Espera el tiempo de llegada a pista
    printf("Avión [%d] %s %s en Pista %d.\n", avion->id, avion->tipo, avion->operacion, pista_asignada);
    sleep(avion->operacion == "aterrizar" ? TIEMPO_ATERRIZAJE : TIEMPO_DESPEGUE); // Espera el tiempo de aterrizaje o despegue
    if (avion->operacion == "aterrizar")                                          // Si el avión está aterrizando
    {
        printf("Avión [%d] %s dirigiéndose a puerta de embarque.\n", avion->id, avion->tipo);
    }
    printf("Avión [%d] %s, hasta luego.\n", avion->id, avion->tipo); // Mensaje al terminar la operacion aterrizaje/despegue
    ultimo_avion = avion->tipo;        // Actualiza el último avión
    sem_post(&pistas[pista_asignada]); // Libera la pista
    free(avion);                       // Libera la memoria del avión
    return NULL;
}

int main()
{
    // Inicializa los semáforos de las pistas
    for (int i = 0; i < NUM_PISTAS; i++)
    {
        sem_init(&pistas[i], 0, 1);
    }
    sem_init(&mutex, 0, 1);            // Inicializa el semáforo mutex
    sem_init(&aviones_normales, 0, 0); // Inicializa el semáforo de aviones normales
    sem_init(&aviones_vip, 0, 0);      // Inicializa el semáforo de aviones VIP

    // Crea las colas para los aviones normales y VIP
    cola_aviones_normales = createQueue();
    cola_aviones_vip = createQueue();

    int id = 0;
    while (1)
    {
        char *tipo = rand() % 2 == 0 ? "NORMAL" : "VIP";               // Asigna el tipo de avión de forma aleatoria
        char *estado = rand() % 2 == 0 ? "aire" : "tierra";            // Asigna el estado de avión de forma aleatoria
        char *operacion = estado == "aire" ? "aterrizar" : "despegar"; // Asigna la operación de avión en base al estado
        Avion *avion = malloc(sizeof(Avion));                          // Crea un nuevo avión
        avion->id = id;
        avion->tipo = tipo;
        avion->estado = estado;
        avion->operacion = operacion;

        // Añade el avión a su cola correspondiente
        if (strcmp(tipo, "NORMAL") == 0) {
            enQueue(cola_aviones_normales, avion);
        } else {
            enQueue(cola_aviones_vip, avion);
        }

        pthread_t thread;
        pthread_create(&thread, NULL, run, avion); // Crea un nuevo hilo para el avión
        id += 1;
        sleep(6); // Tiempo entre la creación de cada avión
    }

    return 0;
}