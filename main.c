#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define TAILLE_MAX 3000

int tab[2][TAILLE_MAX]= {-1};
int compteur = 0;

void * fonction_thread(void * arg);
void fr(long val);

#ifndef NB_THREADS
  #define NB_THREADS 5
#endif

int main (void)
{
    printf("Entrez une valeur");
    scanf("%ld",&val);
    clock_t tic = clock(); //Démmarage de l'horloge

    fr(val);
    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    printf("%d\n",tab[0][compteur]);

    compteur++;
}

void fr(long val){
    pthread_t thr[NB_THREADS];
	long i;
	for (i = 0; i < NB_THREADS; i ++) {
		if (pthread_create(& thr[i], NULL, fonction_thread, (void *) i) != 0) {
			fprintf(stderr, "Erreur dans pthread_create\n");
			exit(EXIT_FAILURE);
		}
	}
	while (1) {
		fprintf(stderr, "Thread Main\n");
		sleep(1);
	}
}


void * fonction_thread(void * arg)
{
	long num = (long) arg;
	while (1) {
		fprintf(stderr, "Thread numero %ld, id %lu\n", num+1,pthread_self());
		sleep(1);
	}
}
