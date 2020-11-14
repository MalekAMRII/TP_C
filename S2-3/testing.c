#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>

#define SIZE_X 20
#define SIZE_Y 50

#define NB_PROIES 20
#define NB_PREDATEURS 20

float p_ch_dir=0.01;
int gain_energie_proie=6;
int gain_energie_predateur=20;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;
float p_manger=0.5;


typedef struct _animal {
  int x;
  int y;
  int dir[2]; /* direction courante sous la forme (dx, dy) */
  float energie;
  struct _animal *suivant;
} Animal;

Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  //na->dir[0] = 1; Verification du bon fonctionnement de la fonction bouger 
  //na->dir[1] = -1;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}

Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}

//Ajouter
void ajouter_animal(int x, int y, float energie, Animal **liste_animal) {
  assert(x >=0 && x<=SIZE_X); //Assert pour verification de la validite de x
  assert(y>= 0 && y<=SIZE_Y); //Assert pour verification de la validite de y 
  Animal *a = creer_animal(x, y, energie); //Appeler la fonction creer_animal pour creer un nouveau animal
  //En utilisant le pointeur sur pointeur sur Animal, modifier la liste directement et 
  //ajouter l'animal au debut de la liste. 
  *liste_animal = ajouter_en_tete_animal(*liste_animal, a); 
  /*A Completer*/
}

//librere 
Animal* liberer_liste_animaux(Animal *liste) {
  Animal *tmp = NULL;
  //Tant que liste n'est pas egale a NULL on rentre dans la boucle while 
  while(liste){
    tmp= liste->suivant; //Affecter l'element suivant de la liste a un pointeur temporaire. 
    free(liste); //Liberation de la memoire 
    liste=tmp; //Affecter la liste temporaire a la liste de depart
  }
   /*A Completer*/
  return NULL;
}

//Enlever
void enlever_animal(Animal **liste, Animal *animal) {
  //Verification si on veut supprimer le 1er element 
  if (animal==*liste){
    Animal *nl= animal->suivant; //On a affecte le reste de la liste chaine a nl
    free(animal);
    animal= NULL;
    *liste=nl; //La nouvelle liste apres suppression de l'element
  }
  else{
    Animal *tmp= *liste;//On fait une copie tmp de la liste chaine dans un pointeur tmp
    //Parcourir la liste jusqu'a trouver l'element 'animal' a supprimer. 
    while((tmp) && (tmp->suivant != animal)){
      tmp= tmp->suivant; 
    }
    if(tmp->suivant == animal){
      //On saute l'element a supprimer et on effecue a la liste tmp l'element suivant 'animal'
      tmp->suivant= animal->suivant;
      //on libere la memoire
      free(animal);
      animal=NULL;  
    }
    else{ printf("Attention animal n'est pas present dans la liste");
    }
  }
  /*A Completer*/
  return ;
}

//Bouger 
void bouger_animaux(Animal *la) {
  Animal *aa=la;
  while(aa){
    //Verification de la validite de x et y 
    assert(aa->x >= 0 && aa->x <=SIZE_X);
    assert(aa->y >=0 && aa->y <=SIZE_Y);

    // Conformement a l'enonce, la case d'origine est celle qui se trouve en haut a gauche donc 
    // le bord sur l'axe des x se trouve a droite et a comme valeur SIZE_X
    //et le bord sur l'axe des y se trouve en bas et a comme valeur SIZE_Y
    if ( (float)rand()/(float)(RAND_MAX/1.0) < p_ch_dir ){ 
    //Si l'animale souhaite bouger en haut alors qu'il est sur la premiere ligne (x, 0) il se retrouve sur
    //le bord en bas
        if (aa->y == 0 && aa->dir[0] == 1){ aa->y = SIZE_Y; }
    //S'il souhaite descendre alors qu'il est sur la derniere ligne, il se retrouve sur la premiere ligne 
        if (aa->y == SIZE_Y && aa->dir[0] == -1){ aa->y = 0; }

    //S'il souhaite bouger a droite alors qu'il se trouve a la limite droite, il se trouve sur le bord gauche 
        if(aa->x == SIZE_X && aa->dir[1] == -1){ aa->x = 0; }
    //S'il souhaite bouger a gauche alors qu'il se trouve a la limite gauche (0, y), il se trouve 
    //sur le bord droite.  
        if(aa->x == 0 && aa->dir[1] == 1){ aa->x = SIZE_X; }

        if (aa->dir[0] == 1 && aa->y != 0) { aa->y--; }
        if (aa->dir[0] == -1 && aa->y != SIZE_Y ) { aa->y++; }

        if (aa->dir[1] == 1 && aa->x != 0) { aa->x--; }
        if (aa->dir[1] == -1 && aa->x!= SIZE_X ) { aa->x++; }

    }
    aa=aa->suivant;
  }
}

//Reproduire
void reproduce(Animal **liste_animal, float p_reproduce) {
  Animal *ani= *liste_animal; 
  while(ani){
    //probability 
    if ( (float)rand()/(float)(RAND_MAX/1.0) < p_reproduce){
    ajouter_animal(ani->x, ani->y, (ani->energie)/2, &(*liste_animal));
    ani->energie= (ani->energie)/2; 
    }
    ani=ani->suivant; 
  }
   /*A Completer*/

}

//Rafraichir monde
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
    for(int i=0; i<SIZE_X; i++){
      for(int j=0; j<SIZE_Y; j++){
        monde[i][j]+=1;
    }
  }
   /*A Completer*/
}

//Rafraichir proie
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  bouger_animaux(*liste_proie); 
  Animal *a= *liste_proie; 
  while(a) {
    a->energie--; 
    if(monde[a->x][a->y] >= 0){
      a->energie+=gain_energie_proie;
      monde[a->x][a->y]=temps_repousse_herbe; 
    }
    if(a->energie < 0){
      Animal *tmp= a;
      a=a->suivant; 
      enlever_animal(&(*liste_proie), tmp);
    }
    else{a=a->suivant;}
  }
  reproduce(&(*liste_proie), p_reproduce_proie); 
    /*A Completer*/
}

//Affichage 
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
    assert (pa->x >= 0 && pa->x <= SIZE_X && pa->y >= 0 && pa->y <= SIZE_Y);
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }
    /*A Completer*/

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
  ++nbpred;
  assert (pa->x >= 0 && pa->x <= SIZE_X && pa->y >= 0 && pa->y <= SIZE_Y);
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


Animal *animal_en_XY(Animal *l, int x, int y) {
  Animal *a= l; 
  while(a){
    if( a->x == x && a->y == y){
      return a; 
    }
    a=a->suivant; 
  }
    /*A Completer*/

  return NULL;
} 


void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  bouger_animaux(*liste_predateur); 
  Animal *a= *liste_predateur; 
  while(a) {
    a->energie--; 
    Animal *b= animal_en_XY(*liste_proie, a->x , a->y);
    if(b){
      if ( (float)rand()/(float)(RAND_MAX/1.0) < p_manger){
        a->energie+=b->energie; 
        b->energie= -1; 
      }
    }
    if(a->energie < 0){
      Animal *tmp= a;
      a=a->suivant; 
      enlever_animal(&(*liste_predateur), tmp);
    }
    else{a=a->suivant;}
  }
  reproduce(&(*liste_predateur), p_reproduce_predateur); 
   /*A Completer*/

}


int main(void){

  int eco[SIZE_X][SIZE_Y];

  //initialisation des cases a 0 
  for(int i=0; i<SIZE_X; i++){
      for(int j=0; j<SIZE_Y; j++){
          eco[i][j]=0; 
      }
  }

    Animal *proie= NULL;
    Animal *predateur= NULL;
    //Dans main-ecosys
    //Creation de 20 proies 
    for(int i=0; i<NB_PROIES; i++){
        ajouter_animal(rand()%(SIZE_X), rand()%(SIZE_Y), ((float)rand()/(float)(RAND_MAX/1.0))*10, &proie);  
    }

    //Creation des predateurs 
    for(int i=0; i<NB_PREDATEURS; i++){
      ajouter_animal(rand()%(SIZE_X), rand()%(SIZE_Y),((float)rand()/(float)(RAND_MAX/1.0))*10, &predateur);  
    }


    //Boucle pour rafraichir les prois 
    while(compte_animal_it(proie) !=  0 && compte_animal_it(predateur) !=  0 ){
      rafraichir_proies(&proie, eco);
      printf("%d\n", compte_animal_it(proie));
      printf("%d\n", compte_animal_it(predateur));
      rafraichir_predateurs(&predateur, &proie); 
      printf("%d\n", compte_animal_it(proie));
      printf("%d\n", compte_animal_it(predateur));
      afficher_ecosys(proie, predateur); 
      //usleep(3.00); 
    }
    
    for(int i=0; i<20; i++){
      printf("%f\n", ((float)rand()/(float)(RAND_MAX/1.0))*10); 
      i++ ;
    }



    //ajouter_animal(8, 6, 2.0, &proie);
    //bouger_animaux(proie);
    //printf("x= %d, y= %d", proie->x, proie->y); 

    //Animal *k= creer_animal(2, 4, 7); 
    //Animal *b= creer_animal(5, 0, 8);

    //proie= ajouter_en_tete_animal(proie, k);
    //proie= ajouter_en_tete_animal(proie, b);

    //ajouter_animal(8, 6, 2.0, &proie);

    //printf("%d\n", compte_animal_it(proie)); 

    //reproduce(&proie, 1.0); 

    //printf("%d\n", compte_animal_it(proie)); 

    //enlever_animal(&proie, k); 

    //printf("%d\n", compte_animal_it(proie));

    //liberer_liste_animaux(proie); 

    return 0; 
}
