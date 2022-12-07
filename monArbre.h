#ifndef __MONARBRE__H__
#define __MONARBRE__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <time.h>
#include "SDL.h"

typedef enum{
    anglais= 1,
    francais,
    espagnol,
    allemand
}LangueJeu;

typedef enum{
    false,
    true
}Bool;

typedef struct noeud{
    char motFr[50];
    char motAn[50];
    char motEsp[50];
    char motAl[50];
    char lienImage[100];
    //Bool apparition;
    struct noeud *g;
    struct noeud *d;
}noeud, *Arbre;



/*---------------Arbre-----------------------*/
Arbre CreationArbre();
Arbre CreerElement(char *tradAn, char *tradFr, char *tradAl, char *tradEsp, char *lienImage);
void nettoyerArbre(Arbre A);
int rechercheCorrespondance(char *motFr, Arbre ArbreDeTrad, LangueJeu langue, 
                            SDL_Renderer *renderer, SDL_Window *window, char *lienImage, 
                            SDL_Rect rectangle2, SDL_Texture *background);
int hauteur(Arbre monArbre);
int desequilibre(Arbre monArbre);
Arbre rotationDG(Arbre monArbre);
Arbre rotationGD(Arbre monArbre);
Arbre rotationD(Arbre monArbre);
Arbre rotationG(Arbre monArbre);
Arbre ajoutAVL(Arbre nouveauMot, Arbre monArbre);
void parcours(Arbre A);
/*------------Tableau------------------------*/
void affTableau(char **tab, int nombreLigne);
char *motAleatoire(char **tab, Arbre ArbreDeTrad, int nombreLigne);
/*-------------------------------------------*/
int nbMotCsv();
void chargementDesDonnees(Arbre *arbreDef, char **tab, int nbMot);


void menu(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *background, int *nombreDeJoueurs, LangueJeu *langue);
#endif