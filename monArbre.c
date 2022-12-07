#include "monArbre.h"
 #include "SDL.h"

Arbre CreationArbre(){
    return NULL;
} 

Arbre CreerElement(char *tradAn, char *tradFr, char *tradAl, char *tradEsp, char *lienImage){

    noeud * element = malloc(sizeof(*element));
        if(element == NULL){
            fprintf(stderr,"Erreur : probleme allocation dynamique.\n");
            exit(EXIT_FAILURE);
         }
    strcpy((element)->motAn, tradAn);
    strcpy((element)->motFr, tradFr);
    strcpy((element)->motAl, tradAl);
    strcpy((element)->motEsp, tradEsp);
    strcpy((element)->lienImage, lienImage);
    (element)->g = NULL;
    (element)->d = NULL;

    return element;
}

void parcours(Arbre A)
{
	if(A == NULL) return;
		printf("%s : Premier passage\n", A->motFr);
		parcours(A->g);  
        		printf("%s : second passage\n", A->motFr);

		parcours(A->d);

}

int rechercheCorrespondance(char *motFr, Arbre ArbreDeTrad, LangueJeu langue, 
                            SDL_Renderer *renderer, SDL_Window *window, char *lienImage, 
                            SDL_Rect rectangle2, SDL_Texture *background){

    if(ArbreDeTrad == NULL) return 0;
    else if (strcmp(ArbreDeTrad->motFr,motFr) == 0){
      
            ImageAffichee(renderer,window,ArbreDeTrad->lienImage,rectangle2,background);
            char reponseJoueur[50];
            printf("mot en francais : %s\n Reponse du joueur : ", ArbreDeTrad->motFr);
            scanf("%s", reponseJoueur);
            switch (langue)
            {
                case anglais:
                    if(strcmp(reponseJoueur,ArbreDeTrad->motAn)== 0) printf("\nBonne réponse !\n");
                    else {
                        printf("\nMauvaise reponse !\n ");
                        return 0;
                    }
                    break;
                case francais:
                    if(strcmp(reponseJoueur,ArbreDeTrad->motFr)== 0) printf("Bonne réponse !\n");
                    else {
                        printf("\nMauvaise reponse !\n ");
                        return 0;
                    }
                    break;
                case allemand:
                    if(strcmp(reponseJoueur,ArbreDeTrad->motAl)== 0) printf("Bonne réponse !\n");
                    else {
                        printf("\nMauvaise reponse !\n ");
                        return 0;
                    }
                    break;
                case espagnol: 
                    if(strcmp(reponseJoueur,ArbreDeTrad->motEsp)== 0) printf("Bonne réponse !\n");
                    else {
                        printf("\nMauvaise reponse !\n ");
                        return 0;
                    }
                    break;

                default:
                    break;
            }
            return 1;
        }        
    else if (strcmp(motFr, ArbreDeTrad->motFr) < 0)rechercheCorrespondance(motFr, ArbreDeTrad->g, langue,renderer,window,"",rectangle2,background); 
    else rechercheCorrespondance(motFr, ArbreDeTrad->d,langue, renderer,window,"",rectangle2,background);   
} 

Arbre rotationD(Arbre monArbre){
    Arbre B = NULL;
    if(monArbre == NULL) return monArbre;
    else{
        B = monArbre->g;
        monArbre->g = B->d;
        B->d = monArbre;
    }
    return B;
}

Arbre rotationG(Arbre monArbre){
    Arbre B = NULL;
    if(monArbre == NULL) return monArbre;
    else{
        B = monArbre->d;
        monArbre->d = B->g;
        B->g = monArbre;
    }
    return B;
}

Arbre rotationGD(Arbre monArbre){
    monArbre->g = rotationG(monArbre->g);
    monArbre = rotationD(monArbre);
    return monArbre;
}

Arbre rotationDG(Arbre monArbre){
    monArbre->d = rotationD(monArbre->d);
    monArbre = rotationG(monArbre);
    return monArbre;
}

int max(int valeur, int valeur2){
    if(valeur>= valeur2) return valeur;
    return valeur2;
}
int hauteur(Arbre monArbre){
    if(monArbre == NULL) return -1;
    else{
        return  1+ max(hauteur(monArbre->g), hauteur(monArbre->d)); //fonctionne pas avec +1
    } 
}

int desequilibre(Arbre monArbre){
    if(monArbre == NULL) return 0;
    else return (hauteur(monArbre->g) - hauteur(monArbre->d));
}
Arbre reequilibrer(Arbre monArbre){
    //printf("\n%d %d %d",desequilibre(monArbre), desequilibre(monArbre->g), desequilibre(monArbre->d));

    if(desequilibre(monArbre) >= 2 && desequilibre(monArbre->g) == 1 ){
        //printf(" -> rotationD");
        return rotationD(monArbre);
    }
        
    if(desequilibre(monArbre) <= -2 && desequilibre(monArbre->d) == -1){
        //printf(" -> rotationG");
        return rotationG(monArbre);
    }
        
    if(desequilibre(monArbre) >= 2 && desequilibre(monArbre->g) == -1){
        //printf(" -> rotationGD");
        return rotationGD(monArbre);
    }

    if(desequilibre(monArbre) <= -2 && desequilibre(monArbre->d) == 1){
       //printf(" -> rotationDG");
        return rotationDG(monArbre);

    }
    
    if(desequilibre(monArbre) >= -1 && desequilibre(monArbre) <= 1){  
            return monArbre; 
    }
    
}
Arbre ajoutAVL(Arbre nouveauMot, Arbre monArbre ){
    if(monArbre == NULL) return nouveauMot;
    if(strcmp(nouveauMot->motFr,monArbre->motFr)<0) monArbre->g = reequilibrer(ajoutAVL(nouveauMot,monArbre->g));
    else monArbre->d =  reequilibrer(ajoutAVL(nouveauMot,monArbre->d));

    return reequilibrer(monArbre);
}
void nettoyerArbre(Arbre A){
    if(A == NULL) return;
    nettoyerArbre(A->g);
    nettoyerArbre(A->d);

    free(A);
}


/*---------------Fonctions pour tableau-----------------------*/
void affTableau(char **tab, int nombreLigne){
    for(int i = 0; i < nombreLigne;i++)
        printf("%s\n", tab[i]);      
}

//Faire une seule fonction pour la recherche, l'affichage et la verificatiton
// recuperer nombrealeatoire pour trouver un mot, retrouver celui-ci dans l'arbre, l'afficher. verifier la correspondance
char *motAleatoire(char **tab, Arbre ArbreDeTrad, int nombreLigne){
    int imgAlea = 0;
    int cpt = 1;
    //while(cpt < nombreLigne || (!mot->apparition))
        imgAlea = rand() %nombreLigne +1;
        return tab[imgAlea];
    
}


