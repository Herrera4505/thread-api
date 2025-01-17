#include <stdio.h>
#include <pthread.h>

#include "mythreads.h"

int balance = 0;

pthread_mutex_t lock;

void* worker(void* arg) {
    //Pthread_mutex_lock(&lock);
    printf("estoy en el lock del hijo\n");
    //balance++; // unprotected access
    //Pthread_mutex_unlock(&lock);
    printf("estoy fuera de lock del hijo\n");

    return NULL;
}

int main(int argc, char *argv[]) {
    Pthread_mutex_init(&lock, NULL);

    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);

    //Pthread_mutex_lock(&lock);
    balance++; // unprotected access
    printf("estoy en el lock\n");
    //Pthread_mutex_unlock(&lock);
    printf("sali del lock\n");
    Pthread_join(p, NULL);
    return 0;
}
