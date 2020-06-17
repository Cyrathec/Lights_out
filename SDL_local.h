#include "./librairies/SDL2-2.0.12/include/SDL2/SDL.h"
#include "./librairies/SDL2-2.0.12/include/SDL2/SDL_image.h"
#include "./librairies/SDL2-2.0.12/include/SDL2/SDL_ttf.h"

#include <stdio.h>
#include <stdlib.h>

#define LIGHTS_NUMBER 5
#define BUTTONS_NUMBER 4

struct {
    int h;
    int w;
    int size;
} my_window;

void Affichage_jeu(int weigth, int **tab_lights);