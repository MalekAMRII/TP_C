/* PARTIE 2*/

/* Part 2. Exercice 5, question 1 */
void bouger_animaux(Animal *la) {
  Animal *aa=la;
  while(aa){
    if (aa->y == SIZE_Y && aa->dir[0] == 1){
      aa->y = 0;    }
    if(aa->x == SIZE_X && aa->dir[1] == -1){ aa->x = 0; }
    else {
      assert(0>= aa->x && aa->x <=SIZE_X);
      assert(0>= aa->y && aa->y <=SIZE_Y); 
      aa->y = aa->y + aa->dir[0];
      if (aa->dir[1] == -1) {aa->x = aa->x + 1;} 
      else if (aa->dir[1] == 1) {aa->x = la->x -1; }
    }
    aa=aa->suivant;
  }
    /*A Completer*/

}

/* Part 2. Exercice 5, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  Animal *ani= *liste_animal; 
  while(ani){
    ajouter_animal(ani->x, ani->y, (ani->energie)/2, &liste_animal);
    ani->energie= (ani->energie)/2; 
    ani=ani->suivant; 
  }
   /*A Completer*/

}


/* Part 2. Exercice 7, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  bouger_animaux(liste_proie); 
  Animal *a= *liste_proie; 
  while(a) {
    a->energie-=1; 
    if(monde[a->x][a->y] >= 0){
      a->energie+=gain_energie_proie;
      monde[a->x][a->y]=temps_repousse_herbe; 
    }
    if(a->energie < 0){
      Animal *tmp= a;
      a=a->suivant; 
      enlever_animal(&liste_proie, tmp);
    }
    else{a=a->suivant;}
  }
  reproduce(&liste_proie, p_reproduce_proie); 
    /*A Completer*/

}

/* Part 2. Exercice 8, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    /*A Completer*/

  return NULL;
} 

/* Part 2. Exercice 8, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
   /*A Completer*/

}

/* Part 2. Exercice 6, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
    for(int i=0; i<SIZE_X; i++){
      for(int j=0; j<SIZE_Y; j++){
        monde[i][j]+=1;
    }
  }

   /*A Completer*/


}