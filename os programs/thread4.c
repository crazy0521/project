// This code demonstrates how to pass an integer as an argument to a thread function in C using POSIX threads (pthreads).

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void * display_num(void * args);

int main() {
    pthread_t tid;
    int num = 5;

    pthread_create(&tid, NULL, display_num, (void*)&num);
    pthread_join(tid, NULL);
    return 0;
}

void * display_num(void* arg) {
    int *N = (int*) arg;
    printf("Number is Equal to %d\n", *N);  // ✅ Corrected format specifier
    return NULL;
}
