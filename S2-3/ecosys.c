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
  assert(0>=x && x<=SIZE_X);
  assert(0>=y && y<=SIZE_Y);
  Animal *a = creer_animal(x, y, energie);
  *liste_animal = ajouter_en_tete_animal(*liste_animal, a); 
  /*A Completer*/
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  //Verification si on veut supprimer le 1er element 
  if (animal==*liste){
    Animal *nl= animal->suivant; //On a affecte le reste de la liste chaine a nl
    free(animal);
    animal= NULL;
    *liste=nl; //La nouvelle liste apres suppression de l'element
  }
  else{
    Animal *tmp= *liste;//On fait une copie tmp de la liste 
    //Parcourir la liste jusqu'a trouver l'element 'animal' a supprimer. 
    while((tmp) && (tmp->suivant != animal)){
      tmp= tmp->suivant; 
    }
    if(tmp->suivant == animal){
      //On saute l'element a supprimer et on effecue a la liste tmp l'element apres 'animal'
      tmp->suivant= animal->suivant;
      //on libere la memoire
      free(animal);
      animal=NULL;  
      //Modifier la liste apres supression de l'element; 
      *liste= tmp;
    }
    else{ printf("Attention animal n'est pas present dans la liste");
    }
  }
  /*A Completer*/
  return ;
}

/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
  Animal *a = liste;
  Animal *tmp;
  while(a){
    tmp =a;
    a = a->suivant;
    free(tmp);
  }
   /*A Completer*/
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



/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  int nbpred=0,nbproie=0;
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }
    /*A Completer*/


  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ++nbproie;
    assert (pa->x >= 0 && pa->x < SIZE_X && pa->y >= 0 && pa->y < SIZE_Y);
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }
    /*A Completer*/

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
  ++nbpred;
  assert (pa->x >= 0 && pa->x < SIZE_X && pa->y >= 0 && pa->y <SIZE_Y);
  if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /*proies aussi present */
    ecosys[pa->x][pa->y] = '@';
  } else {
    ecosys[pa->x][pa->y] = 'O';
  }
  pa = pa->suivant;
  }
  /*A Completer*/

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
  printf("-");
  }
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
  }


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}



