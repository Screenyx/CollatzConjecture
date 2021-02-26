#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NB_THREADS 5

void * fonction_thread(void * arg);

int main(void){
    pthread_t thr[NB_THREADS];
    int i;
    for (int i = 0; i < NB_THREADS; i++)
    {
        if(pthread_create(&thr[i], NULL, fonction_thread, (void *)i)!=0){
            fprintf(stderr, "Erreur dans pthread_create\n");
            exit(EXIT_FAILURE);
        }
    }
    while (1)
    {
        fprintf(stderr,"Thread Main\n");
        sleep(1);
    }
}

void * fonction_thread(void * arg) {
    int num = (int) arg;
    while (1) {
        fprintf(stderr, "Thread numero %d, id %d\n", num+1,pthread_self());
        sleep(1);
    }
}