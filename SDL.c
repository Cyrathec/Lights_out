#include "./librairies/SDL2-2.0.6/include/SDL.h"
#include "./librairies/SDL2-2.0.6/include/SDL_image.h"
#include "./librairies/SDL2-2.0.6/include/SDL_ttf.h"

#include <stdio.h>
/*
void Affichage_jeu(){
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Event e;

    int quit = 0;

	if (!SDL_WasInit(SDL_INIT_VIDEO))
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			printf("[-] ERROR - Failed to initialise SDL (%s)\n", SDL_GetError());
			return;
		}
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		printf("[-] ERROR -  Failed to initialise SDL_Image (%s)\n", SDL_GetError());
		return;
	}

	window = SDL_CreateWindow("Light's out", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN + SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		printf("[-] ERROR -  Failed to create SDL window (%s)\n", SDL_GetError());
		return;
	}

	int windowh;
	int windoww;
	SDL_GetWindowSize(window, &windoww, &windowh);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
}
*/