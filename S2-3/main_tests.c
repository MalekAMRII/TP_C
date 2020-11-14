#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20


int main (void){
  /*Declaration des deux listes */
  Animal *proies = NULL;
  Animal *predateur= NULL; 

  /*Creation des proies*/
  Animal *a= creer_animal(1, 3, 5.0);
  proies= ajouter_en_tete_animal(proies, a);
  Animal *b= creer_animal(2, 2, 3.0);
  proies= ajouter_en_tete_animal(proies, b);
  Animal *c= creer_animal(6, 3, 1.0); 
  proies= ajouter_en_tete_animal(proies, c);
  

  /*Creation des predateurs*/
  Animal *d= creer_animal(2, 6, 5.0);
  predateur= ajouter_en_tete_animal(predateur, d);
  Animal *k= creer_animal(5, 4, 1.0);
  predateur= ajouter_en_tete_animal(predateur, k);

  printf("Le nombre de proies: %d",  compte_animal_rec(proies));
  printf("Le nombre de predateurs: %d",  compte_animal_rec(predateur));

  //Enlever quelques animaux 
  enlever_animal(&proies, b); 
  enlever_animal(&proies, c);
  enlever_animal(&predateur, k); 


  //liberation de la memoire 
  liberer_liste_animaux(proies);
  liberer_liste_animaux(predateur);

  /* A Completer. Exercice 5, question 3 */

  return 0;
}