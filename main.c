#include <stdbool.h>
#include <stdio.h>
#include <time.h>
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

  while(val != -1){

    scanf("%ld",&val);

    printf("Valeur récupér& : %ld\n",val);
    clock_t tic = clock(); //Démmarage de l'horloge

    fr(val);

    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    printf("%d\n",tab[0][compteur]);

    compteur++;
  }
}
