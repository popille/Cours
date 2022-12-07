#include "monArbre.h"

char minuscule(char *chaine){
    for( ; *chaine;chaine++){
        *chaine = tolower(*chaine);
    }
}

int nbMotCsv(){
    FILE *f = fopen("listeAnimaux.csv","r");

    char nomAnimal[150];
    int nbLigne = 0;
    while(fscanf(f,"%s",nomAnimal)!= EOF){                      
        char* s = strdup(nomAnimal);   
        char* val = strsep(&s,",");      
        int j = 1;
        
        while(val != NULL){ 
            if(j == 1){
                nbLigne += 1;
            }
            j += 1;
            val = strsep(&s,",");
        }
    }
    fseek(f,0,SEEK_SET);
    fclose(f);
    return nbLigne;
}

char *creationLienImage(char *lienImage,char * nomAnglais){

    DIR *dossier = NULL; 
    int cptValAlea =0;
    int valAlea= rand()% (60+1); 

    strcpy(lienImage,"");
    strcat(lienImage,"images/animals/");                // Création du chemin du dossier vers images 
    strcat(lienImage,nomAnglais);
        
    dossier = opendir(lienImage);                       // Ouverture du dossier
    if(dossier == NULL){
        printf("Erreur lors de l'ouverture du fichier animal\n");
        exit(EXIT_FAILURE);
    }

    struct dirent * ent = readdir(dossier);
    cptValAlea = 0;
    
    while(((ent != NULL) && cptValAlea < valAlea)|| ent->d_type == DT_DIR ){   //Parcours le dossier jusqu'a ce que le cpt atteigne le nombre aleatoire             
        ent = readdir(dossier);
        cptValAlea++;                        
    }
    strcat(lienImage,"/");
    strcat(lienImage,ent->d_name);
    closedir(dossier);
    
    return lienImage;
}

//recuperationTrad(char *nomAnimal, char * nomAnglais, char *nomFR, char * nomAll, char * nomEsp, char **tab){}


void chargementDesDonnees(Arbre *arbreDef, char **tab, int nbMot){
    
    srand(time(NULL));
    /*-----------------Variable FILE-----------------*/
    FILE *f = fopen("listeAnimaux.csv","r");
    if(f == NULL) printf("Errueur ouverture listeAnimaux.csv");
    int milieuList = 1; 
    /*--------Variable Arbre/Pile/Tableau------------*/
    char nomAnimal[500];
    char nomFR[50];
    char nomAnglais[50];
    char nomAll[50];
    char nomEsp[50];
    char lienImage[100]="";
    /*-----------Variable navigation dossier---------*/

    /*---------Recuperation premiere partie de la liste -----------*/
    while(fscanf(f,"%s",nomAnimal) != EOF){
        char* s = strdup(nomAnimal);   
        char* val = strsep(&s,",");
        
        int j = 1;
        while(val != NULL){ 
            switch(j)
            {
                case 1:
                    minuscule(val);
                    strcpy(nomAnglais, val);
                    break;
                case 2:
                    minuscule(val);
                    *tab = val;                    
                    strcpy(nomFR, val);
                    break;
                case 3:
                    minuscule(val);
                    strcpy(nomAll, val);
                    break;
                case 4:
                    minuscule(val);
                    strcpy(nomEsp, val);
                    break;
                default:
                    break;
            }
            val = strsep(&s,",");           
            j++;
           
        } 
        tab++;
        /*------------Creation du PATH de l'image-------------------*/
        strcpy(lienImage,creationLienImage(lienImage,nomAnglais));        
        /*---------------Ajout dans arbre------------------------------*/
        Arbre nouveauMot = CreerElement(nomAnglais, nomFR,nomAll,nomEsp,lienImage);    
        *arbreDef = ajoutAVL(nouveauMot,*arbreDef);
       
    }

}