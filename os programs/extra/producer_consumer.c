#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    int item;
    while (1)
    {
        item = rand() % 100;        // Produce item
        sem_wait(&empty);           // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Enter critical section

        buffer[in] = item; // Add item to buffer
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full);              // Signal that there's a full slot

        printf("Produced: %d\n", item);
    }
}

void *consumer(void *arg)
{
    int item;
    while (1)
    {
        sem_wait(&full);            // Wait for a full slot
        pthread_mutex_lock(&mutex); // Enter critical section

        item = buffer[out]; // Remove item from buffer
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty);             // Signal that there's an empty slot

        printf("Consumed: %d\n", item);
    }
}

int main()
{
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE); // Initialize empty semaphore
    sem_init(&full, 0, 0);            // Initialize full semaphore
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

Example 1 :

#include <pthread.h>

    void *
    thread(void *vargp);

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread, NULL);
    exit(0);
}

void *thread(void *vargp)
{
    printf(“Hello World !\n”);
    return NULL;
}

Example 2 :

    void *
    thread(void *vargp);
int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread, NULL);
    pthread_join(tid, NULL);
}

/* Thread  Routine*/

void *thread(void *vargp)
{
    printf(“Hello World !\n”);
    return NULL;
}

Example 3 : typedef struct
{
    int num1;
    int num2;
} NUM;
void *sum_function(void *argp);
8. Mutual Exclusion and Synchronization of threads int main()
{
    pthread_t th1;
    NUM N1;
    int n1, n2;
    int ret_val;
    printf("Enter num1\n");
    scanf("%d", &n1);
    printf("Enter num2\n");
    scanf("%d", &n2);
    N1.num1 = n1;
    N1.num2 = n2;
    pthread_create(&th1, NULL, sum_function, (void *)&N1);
    pthread_join(th1, (void *)&ret_val);
    printf("sum = %d\n", ret_val);
    return 0;
}
void *sum_function(void *argp)
{
    NUM *N2 = (NUM *)argp;
    int a = N2 > num1;
    int b = N2 > num2;
    int sum = a + b;
    return (void *)sum;
}