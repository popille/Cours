#ifndef __SDL__H__
#define __SDL__H__

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include "monArbre.h"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080


void SDL_ExitWithError(const char *message);
void SDL_ExitWithErrorWindowAndRenderer(const char *message, SDL_Window *window, SDL_Renderer * renderer);
SDL_Texture *afficherFond(SDL_Renderer *renderer, SDL_Window *window,SDL_Texture *background );
SDL_Texture *afficherTexte(SDL_Renderer *renderer, SDL_Window *window, char * texte, 
                          TTF_Font * font,SDL_Texture * textureTexte,SDL_Color couleurMessage,
                          int positionX, int positionY);
void *ImageAffichee(SDL_Renderer *renderer, SDL_Window *window, char *lienImage, SDL_Rect rectangle2, SDL_Texture *background );

SDL_bool verifOptions(SDL_bool ChoixAnglais, SDL_bool ChoixFrnacais, SDL_bool ChoixEspagnol, SDL_bool ChoixAllemand);


#endif