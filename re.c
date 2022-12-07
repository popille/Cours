#include "monArbre.h"
#include "SDL.h"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080



 int main(int argc, char const *argv[])
 {
    srand(time(NULL));
     /*--------Variable pour menu-----------------*/
    int nombreDeJoueurs = 0;
    LangueJeu langue;
    int langue_tmp;
    /*----------------Initialisation affichage SDL--------------------*/
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_bool program_launched = SDL_TRUE;
    
    if(SDL_Init(SDL_INIT_VIDEO)!= 0)
       SDL_ExitWithError("initialisation SDL");

    if(TTF_Init() != 0)
        SDL_ExitWithError("Initialisation Texte");

    if(SDL_CreateWindowAndRenderer(1920,1080,SDL_WINDOW_RESIZABLE,&window,&renderer))
        SDL_ExitWithError("Impossible de creer la fenetre et le rendu");

     
    SDL_Texture * background = NULL;
    background = afficherFond(renderer,window,background);
    /*-------------------Affichage menu-------------------------*/  
    menu(renderer,window,background,&nombreDeJoueurs,&langue);
    
    /*-----------------------Variable recuperation des données----------------*/
    int nombreLigne = 0;
    nombreLigne = nbMotCsv();

   

    /*---------------Variable en cours de partie-----*/
    Bool verifImage = false; 
    Bool jeu = true;
    int scoreJ1 = 0;
    int scoreJ2 = 0;
    int nbMauvaiseReponse = 0;
    int nbVies = 3;
    int vieRestante = nbVies -nbMauvaiseReponse;
    char affNbVie[2];
    SDL_itoa(vieRestante,affNbVie,10);
    char messageVies[] = "Vies : ";
    strcat(messageVies,affNbVie);
    // /*----------Texte affichage ---------------------------*/
    // char choixLangue[] = "Dans quelle langue voulez jouer ?";

    /*---------Declaration Arbre/Tableau-------------------*/
    Arbre arbreRef = CreationArbre();   
    char **tab = NULL;
    tab = (char**)malloc(nombreLigne*sizeof(char*));
    for(int i = 0; i < nombreLigne; i++){
        tab[i] = malloc(50*sizeof(char));       
    }  

    /*--------------------Recuperation des donnés----------*/
    chargementDesDonnees(&arbreRef, tab, nombreLigne);
    //parcours(arbreRef);

     /*-----------------------------------------------------*/
    SDL_Rect rectangle2;
    if(nombreDeJoueurs == 1){
        TTF_Font * textePartie = TTF_OpenFont("fonts/font1.ttf",40);
        SDL_Color couleurBoutonDeValidation = {0,255,0};
        SDL_Color couleurBoutonSuivant = {255,0,0};
        SDL_Texture * boutonDeValidation = NULL;
        SDL_Texture * boutonSuivant = NULL;
        SDL_Texture * AffichageNbVies = NULL;
        boutonDeValidation = afficherTexte(renderer,window,"Valider",textePartie,boutonDeValidation,couleurBoutonDeValidation,-200, -700);
        boutonSuivant = afficherTexte(renderer,window, "Suivant", textePartie,boutonSuivant,couleurBoutonSuivant,200,-700);
        AffichageNbVies = afficherTexte(renderer,window,messageVies,textePartie,AffichageNbVies,couleurBoutonSuivant,-1400,1000);
        SDL_RenderPresent(renderer);
        while(jeu){
            int motAlea = rand() % nombreLigne +1;                  
            //verifImage = rechercheCorrespondance(tab[motAlea], arbreRef, langue, renderer,window,"",rectangle2,background); 
            if(verifImage == 1) scoreJ1++;
            else nbMauvaiseReponse++;
           
        }
        SDL_DestroyTexture(AffichageNbVies);
        SDL_DestroyTexture(boutonSuivant);
        SDL_DestroyTexture(boutonDeValidation);
    } else 
    if(nombreDeJoueurs == 2){
        printf("\nMode 2 joueurs a venir\n");
    }
    SDL_RenderClear(renderer);
    if(SDL_RenderCopy(renderer,background,NULL,NULL) != 0)
            SDL_ExitWithErrorWindowAndRenderer("Impossible d'afficher le fond",window,renderer);
    SDL_RenderPresent(renderer);
    //affTableau(tab,nombreLigne);*/
    
    while(program_launched)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                default:
                    break;
            
            }
        }
    }
    //nettoyerArbre(arbreRef);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    
//     /*for(int i = 0; i < nombreLigne;i++){
//             free(tab[i]);      
//     }*/
//     free(tab);
   

     return 0;
 }