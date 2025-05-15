#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *display(void *arg); // Thread function

int main()
{
    pthread_t tid;

    // Create a thread
    pthread_create(&tid, NULL, display, NULL);

    // Wait for the thread to complete
    pthread_join(tid, NULL);

    return 0;
}

void *display(void *arg)
{
    printf("Hello from Thread\n");
    return NULL;
}
