#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"


/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  /*A Completer*/
  assert(x>=0 && x<SIZE_X && y>=0 && y<SIZE_Y);
  *liste_animal=ajouter_en_tete_animal(*liste_animal, creer_animal(x,y,energie));
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  /*A Completer*/
  Animal *l = *liste;
  if (l == animal) {
    (*liste) = (*liste)->suivant;
    free(l);
    return;
  }
  for (; l; l = l->suivant)
    if (l->suivant == animal) {
      Animal *temp = l->suivant;
      l->suivant = l->suivant->suivant;
      free(temp);
      return;
    }
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
   /*A Completer*/
   Animal *temp;
   while(liste){
     temp=liste;
     liste=liste->suivant;
     free(liste);
   }
   return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}

void afficher_liste(Animal *a){
  while(a){
    printf("( %d %d )-> ", a->x, a->y);
    a=a->suivant;
  }
  printf("\n");
}


/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  int nbpred=0,nbproie=0;
  Animal *pa=NULL;

  /* on initialise le tableau */
    /*A Completer*/
  for(i=0;i<SIZE_X;i++){
    for(j=0;j<SIZE_Y;j++){
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
    /*A Completer*/
  pa=liste_proie;
  while(pa){
    ecosys[pa->x][pa->y]='*';
    pa=pa->suivant;
    nbproie++;
  }
  /* on ajoute les predateurs */
  /*A Completer*/
  pa=liste_predateur;
  while(pa){
    if((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')){
      ecosys[pa->x][pa->y]='@';
    }
    else{
      ecosys[pa->x][pa->y]='O';
    }
    pa=pa->suivant;
    nbpred++;
  }

  /* on affiche le tableau */
  /*A Completer*/
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
  printf("+");
  for(int n=0;n<SIZE_Y;n++,printf("-"));
  printf("+\n");
  for(i=0;i<SIZE_X;i++){
    printf("|");
    for(j=0;j<SIZE_Y;j++){
      printf("%c",ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for(int n=0;n<SIZE_Y;n++,printf("-"));
  printf("+\n");

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/


/* Part 2. Exercice 5, question 1 */
void bouger_animaux(Animal *la) {
    /*A Completer*/
    while(la){
      if(rand()/(RAND_MAX+1.0)<p_ch_dir){
        int ix=0,iy=0;
        if(la->dir[0]==-1 && la->x==SIZE_X-1){
          la->x=0;
          ix++;
        }
        if(la->dir[0]==1 && la->x==0){
          la->x=SIZE_X-1;
          ix++;
        }
        if(la->dir[1]==1 && la->y==0){
          la->y=SIZE_Y-1;
          iy++;
        }
        if(la->dir[1]==-1 && la->y==SIZE_Y-1){
          la->y=0;
          iy++;
        }
        if(ix==0)la->x-=la->dir[0];
        if(iy==0)la->y-=la->dir[1];
      }
      la=la->suivant;
    }

}

/* Part 2. Exercice 5, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
   /*A Completer*/
   for(Animal *temp=*liste_animal; temp; temp=temp->suivant){
     if(rand()/(RAND_MAX+1.0)<p_reproduce){
       (temp->energie)/=2.0;
       ajouter_animal(temp->x, temp->y, temp->energie, liste_animal);
       assert((*liste_animal)->energie != 0.0);
       assert(temp->energie != 0.0);
     }
   }

}


/* Part 2. Exercice 7, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    /*A Completer*/
    bouger_animaux(*liste_proie);
    for(Animal *proie=*liste_proie; proie; proie=proie->suivant){
      proie->energie-=1.0;
      if(monde[proie->x][proie->y]>=0){
        proie->energie+=gain_energie_proie;
        monde[proie->x][proie->y]=temps_repousse_herbe;
      }
      if(proie->energie<=0.0){
        enlever_animal(liste_proie, proie);
      }
    }
    reproduce(liste_proie, p_reproduce_proie);

}

/* Part 2. Exercice 8, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    /*A Completer*/
    for(; l; l=l->suivant){
      if(l->x==x && l->y==y){
        return l;
      }
    }
    return NULL;
}

/* Part 2. Exercice 8, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
   /*A Completer*/
   bouger_animaux(*liste_predateur);
   for(Animal *pred=*liste_predateur; pred; pred=pred->suivant){
     pred->energie-=1.0;
     if(rand()/(RAND_MAX+1.0)<p_manger && animal_en_XY(*liste_proie, pred->x, pred->y)){
       pred->energie+=gain_energie_predateur;
       enlever_animal(liste_proie, pred);
     }
     if(pred->energie<=0.0){
       enlever_animal(liste_predateur, pred);
     }
   }
   reproduce(liste_predateur, p_reproduce_predateur);

}

/* Part 2. Exercice 6, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
   /*A Completer*/
   for(int i=0; i<SIZE_X; i++){
     for(int j=0; j<SIZE_Y; j++){
       monde[i][j]++;
     }
   }


}
