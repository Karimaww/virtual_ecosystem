#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


float p_ch_dir=0.01;
int gain_energie_proie=6;
int gain_energie_predateur=20;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;
float p_manger=1.0;

int main(void) {
  srand(time(0));
  /* A Completer. Exercice 5, question 3 */
  Animal *liste_predateur=NULL, *liste_proie=NULL;
  for(int i=0;i<4;i++){
    liste_predateur=ajouter_en_tete_animal(liste_predateur, creer_animal( rand()%SIZE_X, rand()%SIZE_Y, 5. ));
    liste_proie=ajouter_en_tete_animal(liste_proie, creer_animal( rand()%SIZE_X, rand()%SIZE_Y, 5. ));
  }

  afficher_ecosys(liste_proie,liste_predateur);

  printf("Proies : ");
  afficher_liste(liste_proie);

  printf("Predateurs : ");
  afficher_liste(liste_predateur);

  /*
  printf("L'animal qu'on veut enlever : liste_proie->suivant = ( %d, %d, %f )\n", liste_proie->suivant->x,liste_proie->suivant->y,liste_proie->suivant->energie);
  enlever_animal(&liste_proie, liste_proie->suivant);

  afficher_ecosys(liste_proie,liste_predateur);

  Animal *ani=creer_animal(5, 2, 6.);
  printf("ani->dir[0] : %d\nani->dir[1] : %d\n", ani->dir[0], ani->dir[1]);
  bouger_animaux(ani);
  printf("ani->x : %d\nani->y : %d\n", ani->x, ani->y);
  liste_proie = ajouter_en_tete_animal(liste_proie, ani);
  afficher_ecosys(liste_proie,liste_predateur);
  */


  reproduce(&liste_predateur, 1.0);
  afficher_ecosys(liste_proie, liste_predateur);

  printf("Proies : ");
  afficher_liste(liste_proie);
  printf("Predateurs : ");
  afficher_liste(liste_predateur);

  liberer_liste_animaux(liste_proie);
  liberer_liste_animaux(liste_predateur);
  if(!liste_proie || !liste_predateur)
  printf("Les listes sont vides!\n");
  return 0;
}
