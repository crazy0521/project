// It demonstrates how to pass arguments to a thread function using pthread_create().

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *display_msg(void *args);

int main()
{

    pthread_t tid;
    char *msg = "Hello";

    pthread_create(&tid, NULL, display_msg, (void *)msg);
    pthread_join(tid, NULL);
    return 0;
}

void *display_msg(void *arg)
{

    char *N = (char *)arg;
    printf("Message is Equal to %s\n", N);
    return NULL;
}
