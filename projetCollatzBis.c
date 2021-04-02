// pour compiler : gcc -D_REENTRANT ...  -lpthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NB_THREAD 500    // n-1 threads
#define TAILLE 300000     // taille du tableau des résultats

long tab[TAILLE][2];
pthread_mutex_t	mutex_stdout = PTHREAD_MUTEX_INITIALIZER;

// cette fonction arete la recursivite sur 1 et renvoie le nbr d'iterations-1
int collatz(long val){
  long val_loc;
  int static niveau=1;
  int static profondeur=0;
  if(val == 1) return 1;
  
  //descente de récursivité
  if(niveau>1) niveau=1; // garde niveau à 1 en descendant
  profondeur++;  // croit en descendant
  if(val%2 == 0)  val_loc=val/2;
  else val_loc=3*val+1;
  tab[val][0]=val_loc;
  collatz(val_loc);
  
  // remontée de récursivité
  tab[val][1]=niveau;
  niveau++;  // en sortie de fonction (remontée de récursivité) on incrémente le niveau
  profondeur--;  // décroit en remontant
  //printf("profondeur=%d, niveau=%d; val_loc=%ld\n",profondeur, niveau,val_loc);
  return niveau;
}

void * fonction_thread(void * arg){
	long val = (long) arg;
        long retour;
        
        pthread_mutex_lock(& mutex_stdout);
	printf("\n%ld:valeur a calculer = %ld\n",pthread_self(),val);
	retour = collatz(val);
        printf("%ld: fin du calcul recursif\n",pthread_self());
        pthread_mutex_unlock(& mutex_stdout);
        
	pthread_exit((void*)retour);
}


int main(int argc, char ** argv){
	
	pthread_t thread[NB_THREAD];
	long i,val_suite;
        long valeur=1;
	void* pt;
	for(i=1; i<NB_THREAD; i++){  // creation des NB_THREAD-1 threads
	  pthread_create(&thread[i], NULL, fonction_thread, (void *) i);
	}
	
	for(i=1; i<NB_THREAD; i++){  // synchro du main sur la fin des threads secondaires
	  pthread_join(thread[i],(void*)&pt);
          pthread_mutex_lock(& mutex_stdout);
	  printf("\n%ld:fin de la thread=%ld, profondeur retournee : %ld\n",pthread_self(),thread[i],(long)pt);
          pthread_mutex_unlock(& mutex_stdout);
	}
	printf("\n");
	for(i=1; i<TAILLE; i++){  // on affiche les valeurs calculees
	  if(tab[i][0]>1) printf("%ld[%ld,%ld]\n",i,tab[i][0],tab[i][1]);
	}
	
	while(1) {
            printf("entrez la valeur souhaitee, -1 pour sortir\n");
            scanf("%ld",&valeur);
            val_suite=tab[valeur][0];
            if ((valeur>1)&&(val_suite>1)) {
                printf("%ld:",valeur);
                //val_suite=tab[valeur][0];
                while(val_suite>1){
                    printf("%ld ",val_suite);
                    val_suite=tab[val_suite][0];
                }
                printf("1 \n");
            }
            else break;
            
        }
   //for (i=0; i<TAILLE_TAB; i++) printf("%d[%d][%d]\n",i+1,tab[i][0],tab[i][1]);
   printf("fin du programme !\n");
	return 0;
	
}
