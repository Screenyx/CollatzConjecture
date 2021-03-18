//Mathias Romero
//Cette version permet de créer un enfant qui va réaliser tout les calculs, et le tuer si l'on veut arrêter le programme


#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#define TAILLE_MAX 3000

int tab[2][TAILLE_MAX]= {-1};
int compteur = 0;


void fr(long val){

  if(val == 1)return;

  if(val%2== 0) val = val/2;
  else val = 3*val+1;

  if(tab[0][compteur] == -1){
    tab[0][compteur] = 0;
    tab[1][compteur] = val;
  }
  tab[0][compteur]++;
  fr(val);
}


int main(void) {


    long val = 0;

    int fils = fork();
    clock_t tic = clock(); //Démmarage de l'horloge
    while(compteur < 3000){
    val = rand()% 10000 +1;

    if(fils == 0){ // Code du fils


    //printf("enfant : Mon PID est %d, mon père est %d \n",getpid(),getppid);


    fr(val);

  //  printf("Résultat : %d\n",tab[0][compteur]);
    compteur++;
    }else{

    wait();
   // printf("Je termine l'enfant \n");
    kill(fils, SIGTERM);


    return 0;
    }
    }
    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
  return 0;
}