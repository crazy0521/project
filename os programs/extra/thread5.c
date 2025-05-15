// This code demonstrates how to pass multiple values (in this case, two integers) to a thread using a struct in C with POSIX threads (pthreads).

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct
{
    int m;
    int n;
} NUM;

void *add(void *arg);

int main()
{

    pthread_t tid;
    int a = 5, b = 6;
    NUM N;
    N.m = a;
    N.n = b;

    pthread_create(&tid, NULL, add, (void *)&N);
    pthread_join(tid, NULL);

    return 0;
}
