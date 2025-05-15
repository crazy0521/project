// threads 
Example 1: Basic Thread Creation

#include<pthread.h> 
  void *thread(void *vargp); 
  int main() 
  { 
   pthread_t tid; 
   pthread_create(&tid,NULL,thread,NULL); 
        exit(0); 
     } 
 
  void *thread(void *vargp) 
  { 
   printf(“Hello World!\n”);  
   return NULL; 
  } 
 






 
Example 2: Thread Creation + Synchronization


 
void *thread(void *vargp); 
int main() 
{ 
 pthread_t tid; 
 pthread_create(&tid,NULL,thread,NULL); 
 pthread_join(tid,NULL); 
} 
 
/* Thread  Routine*/ 
 
 
void *thread(void *vargp) 
{ 
 printf(“Hello World!\n”); 
 return NULL; 
} 







Example 3: Passing Arguments to Threads & Returning Value  (sum of 2 numbers)
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int num1;
    int num2;
} NUM;

void* sum_function(void *argp);

int main() {
    pthread_t th1;
    NUM N1;
    int *ret_val;

    printf("Enter num1: ");
    scanf("%d", &N1.num1);
    printf("Enter num2: ");
    scanf("%d", &N1.num2);

    pthread_create(&th1, NULL, sum_function, (void*)&N1);
    pthread_join(th1, (void**)&ret_val);
    printf("Sum = %d\n", *ret_val);
    free(ret_val);

    return 0;
}

void* sum_function(void *argp) {
    NUM *N2 = (NUM*) argp;

    int *sum = (int*) malloc(sizeof(int));  // dynamically allocate memory
    *sum = N2->num1 + N2->num2;

    return (void*)sum;
}