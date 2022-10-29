#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nb_c(FILE *f){
    int cpt = 0;
    char c;
    while((c = fgetc(f)) != EOF)     
            cpt = cpt+1;  
    cpt -=1;
    return cpt;
}

int nb_w(FILE *f){

    int cpt = 0;
    int cpt_w = 0;
    char c;
    
    while((c =fgetc(f)) != EOF){           
            if(c!= ' ' && c != '\n') cpt += 1;
            
            if((c == '\n' || c == ' ') && cpt >= 1){
                cpt_w += 1;
                cpt = 0;
            }
        }
        if(cpt > 0) cpt_w += 1;

    return cpt_w;
}

int nb_l(FILE *f){
    char ligne[255];
    int cpt = 0;
    while(fgets(ligne,254,f) != NULL)
        cpt += 1;

    return cpt;
}

void EX1_EX2(){
/*if(strcmp(argc[2], "comp") == 0){
        int i,j;
        j = 0;
        int val,val2;
        int croissance = 1;
        for(int i = 2; i <4; i++){
            sscanf(argc[i], "%d", &val);
            sscanf(argc[i+1], "%d", &val2);

            if(val > val2)
            	croissance = 0;
        }
        if(croissance == 1) printf("Croissant\n");
        else printf("Non croissant\n");
    }
    else{

    int cpt_c = 0;
    int cpt_w = 0;
    int cpt_l = 0;
    FILE *f = fopen(argc[2],"r");

    if(strcmp(argc[1], "-c") == 0){
        cpt_c = nb_c(f);
        printf("Nombre de caractere = %d\n",cpt_c);
    }


    if(strcmp(argc[1], "-w") == 0){
        cpt_w = nb_w(f);
        printf("Nombre de mot : %d\n", cpt_w);
    }


    if(strcmp(argc[1], "-l") == 0){
        cpt_l = nb_l(f);
        printf("nombre de ligne %d\n", cpt_l);
    }
    

    fclose(f);
    }*/
}

void ajout_moyennes_ecTypes(FILE *f){
    FILE *f2 = fopen("newfile.csv","a"); /////////////// A verifier
    char ligne[1024];

    if(f != NULL){

        int nb_ligne = 0;                                               // certainement possibilite de reduire les variables mais flm      
       
        float moyenne,moyenne1,moyenne2,moyenne3,Smoyen,moyenneM;
        float somme,somme_col1, somme_col2, somme_col3;
        float tabCol1[8], tabCol2[8],tabCol3[8],tabCol4[8];
        float Var1,Var2, Var3, Var4;  
        float ecType1, ecType2, ecType3, ecType4;
        
        moyenne1 = 0,moyenne2 = 0,moyenne3 = 0, moyenneM = 0,Smoyen = 0;
        somme_col1 = 0, somme_col2 = 0, somme_col3 = 0;
        Var1 = 0, Var2 = 0, Var3 = 0,Var4= 0;
        ecType1 = 0, ecType2 = 0, ecType3 = 0, ecType4 = 0;

        while(fgets(ligne,1023,f) != NULL){        //Pendant le while, actions affectuée sur chaque ligne
            moyenne = 0;
            somme = 0;
                
            if(nb_ligne >= 0) {                    //je comprend pas pourquoi je print pas ma ligne 0. Du coup le if sert surtout d'indicateur                
                fscanf(f,"%s", ligne);             //affectation de la ligne du fichier dans ma chaine de caractère

                char* s = strdup(ligne);              
                char* val = strsep(&s,";"); 
                int j = 1;
                while(val != NULL){                   
                    if(j==3){
                        somme += atoi(val);                 // Calcul moyenne élève
                        somme_col1 += atof(val);            // Calcul somme pour la moyenne du groupe sur la matière (addition colonne 1)
                        tabCol1[nb_ligne] = atof(val);
                    }                            
                    else if(j==4){
                        somme += atoi(val);
                        somme_col2 += atof(val);
                        tabCol2[nb_ligne] = atof(val);     
                    }    
                    else if(j==5){
                        somme += atoi(val);
                        somme_col3 += atof(val);
                        tabCol3[nb_ligne] = atof(val);
                    }

                    val = strsep(&s,";"); 
                    j += 1;                   
                }

                fprintf(f2,"%s",ligne);             //Ajout de la ligne du fichier f1 dans f2
                moyenne = somme/3;
                Smoyen += moyenne;
                tabCol4[nb_ligne] = moyenne;
                printf("tabCol4 : %f\n", tabCol4[nb_ligne]);

                fprintf(f2,";%f\n",moyenne);        //Ajout de la moyenne sur cette même ligne dans f2
                

            }
            nb_ligne += 1;

        }
        moyenne1 = somme_col1/nb_ligne;                    //Calcul moyenne sur la matière 1
        moyenne2 = somme_col2/nb_ligne;
        moyenne3 = somme_col3/nb_ligne;
        moyenneM = Smoyen/nb_ligne;                        //Calcul moyenne génerale
        printf("moyenneM : %f\n", moyenneM);      

        //                                                   Calcul variance
        for(int i = 0; i <= nb_ligne-1; i++){
            Var1 += pow((abs(tabCol1[i] - moyenneM)),2);
            Var2 += pow((abs(tabCol2[i] - moyenneM)),2);
            Var3 += pow((abs(tabCol3[i] - moyenneM)),2);
            Var4 += pow((abs(tabCol4[i] - moyenneM)),2);
        } 
        printf("somme pour Var4 : %f\n", Var4);      
        Var1 /= nb_ligne, Var2 /= nb_ligne;
        Var3 /= nb_ligne, Var4 /= nb_ligne;
        printf("Var4 : %f\n", Var4);      

        //                                                    Fin calcul variance 
        
        ecType1 = sqrt(Var1), ecType2 = sqrt(Var2);           //Calcul ecart-typ
        ecType3 = sqrt(Var3), ecType4 = sqrt(Var4);
        printf("ecType4 : %f\n", ecType4);      

        fprintf(f2,"moyenne;groupe;%f;%f;%f;%f\n", moyenne1,moyenne2,moyenne3,moyenneM);             //Ajout de la ligne des moyennes dans f2
        fprintf(f2,"ecart-type; ;%f;%f;%f;%f\n",ecType1,ecType2,ecType3,ecType4);                    //Ajout ecart-type dans f2
    }
    fclose(f2);
}

int main(int argv, char *argc[])
{
	
    FILE *f = fopen("notes.csv","r");
    ajout_moyennes_ecTypes(f);
    fclose(f);
		

	
	return 0;
}
