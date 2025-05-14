#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void* display(void* arg);
int main(){

pthread_t tid;

pthread_create(&tid,NULL,display,NULL);
pthread_join(tid,NULL);

return 0;
}

void * display(void * arg){
printf("Hello from Thread\n");
return NULL;
}


