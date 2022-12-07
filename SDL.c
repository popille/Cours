#include "monArbre.h"
#include "SDL.h"

void SDL_ExitWithError(const char *message){
    SDL_Log("Erreur : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void SDL_ExitWithErrorWindowAndRenderer(const char *message, SDL_Window *window, SDL_Renderer * renderer){
    SDL_Log("Erreur : %s > %s\n", message, SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void *ImageAffichee(SDL_Renderer *renderer, SDL_Window *window, char *lienImage, SDL_Rect rectangle2, SDL_Texture *background ){
    
    rectangle2.w = 500;
    rectangle2.h = 300;
    SDL_Texture *imageDeJeu = NULL;
    imageDeJeu = IMG_LoadTexture(renderer, lienImage);
    if(imageDeJeu == NULL)
        SDL_ExitWithErrorWindowAndRenderer("Impossible de creer l'image de jeu",window,renderer);
                        
    if(SDL_QueryTexture(imageDeJeu,NULL,NULL,&rectangle2.w,&rectangle2.h))
        SDL_ExitWithErrorWindowAndRenderer("Impossible de charger l'image",window,renderer);

        rectangle2.x = (WINDOW_WIDTH - rectangle2.w)/2;
        rectangle2.y = (WINDOW_HEIGHT - rectangle2.h)/2;

    if(SDL_RenderCopy(renderer,background,NULL,NULL) != 0)
            SDL_ExitWithErrorWindowAndRenderer("Impossible d'afficher le fond",window,renderer);

    if(SDL_RenderCopy(renderer,imageDeJeu,NULL,&rectangle2)!=0)
        SDL_ExitWithErrorWindowAndRenderer("Impossible d'afficher l'image de jeu",window,renderer);

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(imageDeJeu);
 }

SDL_Texture *afficherFond(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *background ){
    SDL_Surface * image = NULL;
    image = SDL_LoadBMP("images/fond/FondNoir2.bmp");
    if(image == NULL)
        SDL_ExitWithErrorWindowAndRenderer("Impossible de charger le l'image de fond",window,renderer);

    background = SDL_CreateTextureFromSurface(renderer,image);
    SDL_FreeSurface(image);
    
    if(background == NULL)
        SDL_ExitWithErrorWindowAndRenderer("Impossible de creer le fond d'ecran",window,renderer);

    SDL_Rect rectangle;
    rectangle.w = WINDOW_WIDTH;
    rectangle.h = WINDOW_HEIGHT;

    if(SDL_QueryTexture(background,NULL,NULL,&rectangle.w,&rectangle.h))
        SDL_ExitWithErrorWindowAndRenderer("Impossible de charger le fond d'ecran ",window,renderer);
    rectangle.x = (WINDOW_WIDTH -rectangle.w)/2;
    rectangle.y = (WINDOW_HEIGHT - rectangle.h)/2;

    if(SDL_RenderCopy(renderer,background,NULL,NULL)!=0)    //Affichade l'image de fond sur la totalité de la fenêtre
        SDL_ExitWithErrorWindowAndRenderer("Impossible d'afficher le fond d'ecran",window,renderer);    

    //SDL_RenderPresent(renderer);
    return background;
}

SDL_Texture *afficherTexte(SDL_Renderer *renderer, SDL_Window *window, char * texte, 
                          TTF_Font * font,SDL_Texture * textureTexte,SDL_Color couleurMessage,
                          int positionX, int positionY){

    SDL_Surface * surfaceTexte = TTF_RenderText_Solid(font,texte, couleurMessage);
    textureTexte = SDL_CreateTextureFromSurface(renderer,surfaceTexte);
    SDL_FreeSurface(surfaceTexte);
    int textW = 0;
    int textH = 0;
      if(SDL_QueryTexture(textureTexte,NULL,NULL,&textW,&textH) != 0)
        SDL_ExitWithErrorWindowAndRenderer("Impossible de charger du texte",window,renderer);
   
    SDL_Rect rectangleTexte = { (WINDOW_WIDTH - textW- positionX)/2, (WINDOW_HEIGHT - textH - positionY)/2, textW, textH};
    if(SDL_RenderCopy(renderer,textureTexte,NULL,&rectangleTexte) != 0)
        SDL_ExitWithErrorWindowAndRenderer("Impossible de creer du texte",window,renderer);
    

   return textureTexte;
}

SDL_bool verifOptions(SDL_bool ChoixAnglais, SDL_bool ChoixFrnacais, SDL_bool ChoixEspagnol, SDL_bool ChoixAllemand){
    
    int cpt = 0;
    if(ChoixAnglais) cpt ++;
    if(ChoixFrnacais) cpt++;
    if(ChoixEspagnol) cpt++;
    if(ChoixAllemand) cpt++;
    if(cpt >= 1) return SDL_FALSE;
    else return SDL_TRUE;
    
}

void menu(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *background, int *nombreDeJoueurs, LangueJeu *langue){
    SDL_bool menu_launched = SDL_TRUE;

    SDL_Color couleurMessageMenu = {255,0,0};
    SDL_Color couleurTexteMenu = {255,255,255};
    SDL_Color optionSelectionnee = {0,255,0};
    TTF_Font * TexteNom = TTF_OpenFont("fonts/font1.ttf",100);
    TTF_Font * TexteMenu= TTF_OpenFont("fonts/font1.ttf",40);
    TTF_Font * ChoixMenu= TTF_OpenFont("fonts/font1.ttf",35);
    TTF_Font * TTF_BoutonValider = TTF_OpenFont("fonts/font1.ttf",80);

    SDL_Texture * nomJeu = NULL;
    SDL_Texture * QuestionNbJoueur = NULL;
    SDL_Texture * QuestionLangueDeJeu = NULL;
    SDL_Texture * Choix1Joueur = NULL;
    SDL_Texture * Choix2Joueurs = NULL;
    SDL_Texture * ChoixLangue1 = NULL;
    SDL_Texture * ChoixLangue2 = NULL;
    SDL_Texture * ChoixLangue3 = NULL;
    SDL_Texture * ChoixLangue4 = NULL;

    SDL_Texture * BoutonValider = NULL;

    nomJeu = afficherTexte(renderer,window,"Trouves l'image",TexteNom,nomJeu,couleurMessageMenu,0,600);
    QuestionNbJoueur = afficherTexte(renderer,window,"Combien de joueurs ?", TexteMenu,QuestionNbJoueur,couleurTexteMenu,700,200);
    QuestionLangueDeJeu = afficherTexte(renderer,window,"Langue cible de la partie ?",TexteMenu,QuestionLangueDeJeu,couleurTexteMenu,-700,200);
    Choix1Joueur = afficherTexte(renderer,window, "1 Joueur",ChoixMenu,Choix1Joueur,couleurTexteMenu,700,100);
    Choix2Joueurs = afficherTexte(renderer,window, "2 Joueurs",ChoixMenu,Choix2Joueurs,couleurTexteMenu,700,0);
    ChoixLangue1 = afficherTexte(renderer,window,"Anglais",ChoixMenu,ChoixLangue1,couleurTexteMenu,-700, 100);
    ChoixLangue2 = afficherTexte(renderer,window,"Francais",ChoixMenu,ChoixLangue2,couleurTexteMenu,-700, 0);
    ChoixLangue3 = afficherTexte(renderer,window,"Espagnol",ChoixMenu,ChoixLangue3,couleurTexteMenu,-700, -100);
    ChoixLangue4 = afficherTexte(renderer,window,"Allemand",ChoixMenu,ChoixLangue4,couleurTexteMenu,-700, -200);

    BoutonValider = afficherTexte(renderer,window,"Commencer", TTF_BoutonValider,BoutonValider,couleurTexteMenu,0,-500);
    SDL_RenderPresent(renderer);
    SDL_bool Choix1Selectionne = SDL_FALSE;
    SDL_bool Choix2Selectionne = SDL_FALSE;
    SDL_bool ChoixAnglais = SDL_FALSE;
    SDL_bool ChoixFrancais = SDL_FALSE;
    SDL_bool ChoixEspagnol = SDL_FALSE;
    SDL_bool ChoixAllemand = SDL_FALSE;
    SDL_bool autreOption = SDL_FALSE;
    SDL_bool optionJoueur = SDL_FALSE;
    SDL_bool optionLangue = SDL_FALSE;
    while(menu_launched)
    {
        SDL_Event event;
        
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    /*-----------------Actions aux cliques sur les choix pour nombre de joueurs-------------------*/
                                        /*------------------Parite 1 joueur------------------*/
                    if(event.button.button == SDL_BUTTON_LEFT &&
                      event.button.x >= 530 && event.button.x <= 670 && 
                      event.button.y >=410 && event.button.y <450
                    ){
                        switch (Choix1Selectionne)
                        {
                        case SDL_FALSE:
                            if(Choix2Selectionne == SDL_FALSE){
                                Choix1Joueur = afficherTexte(renderer,window, "1 Joueur",ChoixMenu,Choix1Joueur,optionSelectionnee,700,228);                          
                                *nombreDeJoueurs = 1;    
                                optionJoueur = SDL_TRUE;                      
                                Choix1Selectionne = SDL_TRUE;
                            }
                            break;
                        case SDL_TRUE:
                            Choix1Joueur = afficherTexte(renderer,window, "1 Joueur",ChoixMenu,Choix1Joueur,couleurTexteMenu,700,228);
                            *nombreDeJoueurs = 0; 
                            optionJoueur = SDL_FALSE;                         
                            Choix1Selectionne = SDL_FALSE;
                            break;
                        default:
                            break;
                        }
                        SDL_RenderPresent(renderer);
                    }               
                                        /*------------------Partie 2 Joueurs-----------------*/ 
                    if(event.button.button == SDL_BUTTON_LEFT &&
                      event.button.x >= 530 && event.button.x <= 670 && 
                      event.button.y >=450 && event.button.y <490
                    ){
                        switch (Choix2Selectionne)
                        {
                        case SDL_FALSE:
                            if(Choix1Selectionne == SDL_FALSE){
                                Choix2Joueurs = afficherTexte(renderer,window, "2 Joueurs",ChoixMenu,Choix2Joueurs,optionSelectionnee,700,128);                          
                                *nombreDeJoueurs = 2;
                                optionJoueur = SDL_TRUE;                      
                                Choix2Selectionne = SDL_TRUE;
                            }
                            break;
                        case SDL_TRUE:
                            Choix2Joueurs = afficherTexte(renderer,window, "2 Joueurs",ChoixMenu,Choix2Joueurs,couleurTexteMenu,700,128);
                            *nombreDeJoueurs = 0;                          
                            optionJoueur = SDL_FALSE;
                            Choix2Selectionne = SDL_FALSE;
                            break;
                        default:
                            break;
                        }
                        SDL_RenderPresent(renderer);
                    }                       
                    /*----------------------------------Choix *langue--------------------------------------------------*/   
                                        /*----------------Anglais----------------*/   
                    if(event.button.button == SDL_BUTTON_LEFT &&
                      event.button.x >= 1220 && event.button.x <= 1390 && 
                      event.button.y >=410 && event.button.y <470
                    ){
                        switch (ChoixAnglais)
                        {
                        case SDL_FALSE:
                            autreOption = verifOptions(ChoixAnglais,ChoixFrancais,ChoixEspagnol,ChoixAllemand);
                            if(autreOption == SDL_TRUE){
                                ChoixLangue1 = afficherTexte(renderer,window,"Anglais",ChoixMenu,ChoixLangue1,optionSelectionnee,-700, 228);                               
                                *langue = anglais;
                                optionLangue = SDL_TRUE;
                                ChoixAnglais = SDL_TRUE;
                                break; 
                            }
                        case SDL_TRUE:
                            ChoixLangue1 = afficherTexte(renderer,window,"Anglais",ChoixMenu,ChoixLangue1,couleurTexteMenu,-700, 228);
                            optionLangue = SDL_FALSE;
                            ChoixAnglais = SDL_FALSE;
                            break; 
                        
                        default:
                            break;
                        }
                        SDL_RenderPresent(renderer);

                    }
                                        /*----------------Francais----------------*/                      
                    if(event.button.button == SDL_BUTTON_LEFT &&
                      event.button.x >= 1220 && event.button.x <= 1390 && 
                      event.button.y >=470 && event.button.y <500
                    ){
                        switch (ChoixFrancais)
                        {
                        case SDL_FALSE:
                            autreOption = verifOptions(ChoixAnglais,ChoixFrancais,ChoixEspagnol,ChoixAllemand);
                            if(autreOption == SDL_TRUE){
                                ChoixLangue2 = afficherTexte(renderer,window,"Francais",ChoixMenu,ChoixLangue2,optionSelectionnee,-700, 128);
                                *langue = francais;
                                optionLangue = SDL_TRUE;
                                ChoixFrancais = SDL_TRUE;
                                break; 
                            }
                        case SDL_TRUE:
                            ChoixLangue2 = afficherTexte(renderer,window,"Francais",ChoixMenu,ChoixLangue2,couleurTexteMenu,-700, 128);
                            optionLangue = SDL_FALSE;
                            ChoixFrancais = SDL_FALSE;
                            break; 
                        
                        default:
                            break;
                        }
                        SDL_RenderPresent(renderer);
                    }
                                        /*----------------Espagnol----------------*/   

                    if(event.button.button == SDL_BUTTON_LEFT &&
                      event.button.x >= 1220 && event.button.x <= 1390 && 
                      event.button.y >=500 && event.button.y <560
                    ){
                        switch (ChoixEspagnol)
                        {
                        case SDL_FALSE:
                            autreOption = verifOptions(ChoixAnglais,ChoixFrancais,ChoixEspagnol,ChoixAllemand);
                            if(autreOption == SDL_TRUE){
                                ChoixLangue3 = afficherTexte(renderer,window,"Espagnol",ChoixMenu,ChoixLangue3,optionSelectionnee,-700, 28);
                                *langue = espagnol;
                                optionLangue = SDL_TRUE;
                                ChoixEspagnol = SDL_TRUE;
                                break; 
                            }
                        case SDL_TRUE:
                            ChoixLangue3 = afficherTexte(renderer,window,"Espagnol",ChoixMenu,ChoixLangue3,couleurTexteMenu,-700, 28);
                            optionLangue = SDL_FALSE;
                            ChoixEspagnol = SDL_FALSE;
                            break; 
                        
                        default:
                            break;
                        }
                        SDL_RenderPresent(renderer);
                    }
                                        /*----------------Allemand----------------*/   
                    if(event.button.button == SDL_BUTTON_LEFT &&
                      event.button.x >= 1220 && event.button.x <= 1390 && 
                      event.button.y >=560 && event.button.y <610
                    ){
                        switch (ChoixAllemand)
                        {
                        case SDL_FALSE:
                            autreOption = verifOptions(ChoixAnglais,ChoixFrancais,ChoixEspagnol,ChoixAllemand);
                            if(autreOption == SDL_TRUE){
                                ChoixLangue4 = afficherTexte(renderer,window,"Allemand",ChoixMenu,ChoixLangue4,optionSelectionnee,-700, -72);
                                optionLangue = SDL_TRUE;
                                ChoixAllemand = SDL_TRUE;
                                break; 
                            }
                        case SDL_TRUE:
                            ChoixLangue4 = afficherTexte(renderer,window,"Allemand",ChoixMenu,ChoixLangue4,couleurTexteMenu,-700, -72);
                            optionLangue = SDL_FALSE;
                            ChoixAllemand = SDL_FALSE;
                            break; 
                        
                        default:
                            break;
                        }
                        SDL_RenderPresent(renderer);
                    }
                                        /*----------------Bouton valider----------------*/   

                    if(event.button.button == SDL_BUTTON_LEFT &&
                      event.button.x >= 830 && event.button.x <= 1070 && 
                      event.button.y >=695 && event.button.y <775
                    ){
                        if(optionJoueur && optionLangue) menu_launched = SDL_FALSE;
                    }
                    
                    if(event.button.button == SDL_BUTTON_LEFT){
                        printf("\nx : %d, y : %d", event.button.x, event.button.y);
                    }
                    break;
                case SDL_QUIT:
                    menu_launched = SDL_FALSE;
                    break;
                default:
                    break;
            
            }
        }
    }
    
    TTF_CloseFont(TTF_BoutonValider);
    TTF_CloseFont(ChoixMenu);    
    TTF_CloseFont(TexteMenu);
    TTF_CloseFont(TexteNom);
    SDL_DestroyTexture(BoutonValider);
    SDL_DestroyTexture(ChoixLangue4);
    SDL_DestroyTexture(ChoixLangue3);
    SDL_DestroyTexture(ChoixLangue2);
    SDL_DestroyTexture(ChoixLangue1);
    SDL_DestroyTexture(Choix2Joueurs);
    SDL_DestroyTexture(Choix1Joueur);
    SDL_DestroyTexture(QuestionLangueDeJeu);
    SDL_DestroyTexture(QuestionNbJoueur);
    SDL_DestroyTexture(nomJeu);
}