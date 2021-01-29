#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 40
#define NB_PREDATEURS 40
#define T_WAIT 80000


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.1;
int gain_energie_proie=15;
int gain_energie_predateur=20;
float p_reproduce_proie=0.8;
float p_reproduce_predateur=0.6;
int temps_repousse_herbe=-15;
float p_manger=0.2;


int main(void) {
  FILE *f=NULL;
  f=fopen("Evol_Pop.txt", "w");
  if(!f){
    printf("Erreur a l'ouverture du fichier\n");
    return 1;
  }

   // A completer. Part 2:
   srand(time(NULL));
   // exercice 6, question 1
   int monde[SIZE_X][SIZE_Y]={0};
   // exercice 7, question 2
   Animal *liste_proie=NULL;
   for(int i=0; i<NB_PROIES; i++){
     ajouter_animal(rand()%SIZE_X, rand()%SIZE_Y, gain_energie_proie, &liste_proie);
   }
   // exercice 8, question 3
   Animal *liste_pred=NULL;
   for(int i=0; i<NB_PREDATEURS; i++){
     ajouter_animal(rand()%SIZE_X, rand()%SIZE_Y, gain_energie_predateur, &liste_pred);
   }

   printf("Notre ecosysteme initiale : \n");
   afficher_ecosys(liste_proie, liste_pred);

   for(int i=1; i<500 && liste_proie; i++){
     printf("\nIteration %d\n", i);
     rafraichir_proies(&liste_proie, monde);
     rafraichir_predateurs(&liste_pred, &liste_proie);
     printf("Proies : ");
     afficher_liste(liste_proie);

     printf("Predateurs : ");
     afficher_liste(liste_pred);

     afficher_ecosys(liste_proie, liste_pred);

     fprintf(f, "%d %d %d\n", i, compte_animal_it(liste_proie), compte_animal_it(liste_pred));

     usleep(T_WAIT);
   }
   // exercice 9, question 1
   fclose(f);

   return 0;
}
