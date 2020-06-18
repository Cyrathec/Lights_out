#ifndef _SDLLOCAL_H_
#define _SDLLOCAL_H_

#include "./librairies/SDL2-2.0.12/include/SDL2/SDL.h"
#include "./librairies/SDL2-2.0.12/include/SDL2/SDL_image.h"
#include "./librairies/SDL2-2.0.12/include/SDL2/SDL_ttf.h"

#define BUTTONS_NUMBER 4

struct {
    int h;
    int w;
    int size;
} my_window;

void Affichage_jeu(int **tab_lights, int weigth);

#endif