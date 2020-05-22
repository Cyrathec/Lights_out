#include "SDL_local.h"

void Affichage_jeu(){

	// Instanciation des pointeurs de la SDL
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Event e;

	// Initialisation des variables
    int quit = 0; // variable de test pour quitter le programme
	int windowh; // hauteur de la fenêtre de la SDL
	int windoww; // largeur de la fenêtre de la SDL

	// Initialisation de la sdl
	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			printf("[-] ERROR - Failed to initialise SDL (%s)\n", SDL_GetError());
			return;
		}
	}

	// Initialisation des fonctionnalités liées aux images de la SDL
	if (!IMG_Init(IMG_INIT_PNG)) {
		printf("[-] ERROR -  Failed to initialise SDL_Image (%s)\n", SDL_GetError());
		return;
	}

	// Initialisation de la fenêtre
	window = SDL_CreateWindow("Light's out", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN + SDL_WINDOW_RESIZABLE);
	if (!window) {
		printf("[-] ERROR -  Failed to create SDL window (%s)\n", SDL_GetError());
		return;
	}

	// Récupération de la largeur et la hauteur de le fenêtre
	SDL_GetWindowSize(window, &windoww, &windowh);

	// Initilisation du rendeur
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	// Instanciation des textures, surfaces et rectangles
	SDL_Texture*** lights;
	SDL_Surface*** images_lights;
	SDL_Rect** position_lights;

	SDL_Texture* texture1;
	SDL_Surface* image;
	SDL_Rect positionRect1;

	SDL_Texture* texture2;
	SDL_Surface* rectangle;
	SDL_Rect positionRect2;

	// Initialisation des textures, surfaces
	image = IMG_Load("data/fond.jpg");
	texture1 = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	rectangle = SDL_CreateRGBSurface(0, windoww * 1480 / 1920, windowh * 220 / 1080, 32, 0, 0, 0, 0);
	SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 0, 0, 0));
	texture2 = SDL_CreateTextureFromSurface(renderer, rectangle);
	SDL_FreeSurface(rectangle);

	// Initialisation des rectangles
	positionRect1.x = 0;
	positionRect1.y = 0;

	while (!quit){

		while (SDL_PollEvent(&e)) {

			switch (e.type) {
				case SDL_QUIT:
					quit = 1;
					break;

				case SDL_KEYDOWN:
					switch (e.key.keysym.sym) {
						case SDLK_ESCAPE:
							quit = 1;
							break;
					}
					break;

				case SDL_MOUSEBUTTONUP:
					break;
				
				case SDL_WINDOWEVENT:
					if(e.window.event == SDL_WINDOWEVENT_RESIZED){
						// Change les valeurs de la largeur et la hauteur de le fenêtre
						windoww = e.window.data1;
						windowh = e.window.data2;
					}
					break;
			}

			// Mise à jour de l'affichage
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture1, NULL, &positionRect1);
			SDL_RenderPresent(renderer);
		}
	}

	// Destruction du rendeur, de la fenêtre et de la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}