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
	SDL_Surface* image_light;
	SDL_Rect** position_lights;

	/* Exemples : 
	SDL_Texture* texture1;
	SDL_Surface* image;
	SDL_Rect positionRect1;

	SDL_Texture* texture2;
	SDL_Surface* rectangle;
	SDL_Rect positionRect2;
	*/

	// Initialisation des textures, surfaces
	lights = malloc(sizeof(int) * LIGHTS_NUMBER);
	position_lights =  malloc(sizeof(int) * LIGHTS_NUMBER);

	for (int i = 0; i < LIGHTS_NUMBER; i++) {
		lights[i] = malloc(sizeof(int) * LIGHTS_NUMBER);
		position_lights[i] =  malloc(sizeof(int) * LIGHTS_NUMBER);
		for (int j = 0; j < LIGHTS_NUMBER; j++) {
			image_light = IMG_Load("images/light_off.png");
			lights[i][j] = SDL_CreateTextureFromSurface(renderer, image_light);
			SDL_FreeSurface(image_light);
		}
	}
	
	/* Exemples : 
	image = IMG_Load("data/fond.jpg");
	texture1 = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	rectangle = SDL_CreateRGBSurface(0, windoww * 1480 / 1920, windowh * 220 / 1080, 32, 0, 0, 0, 0);
	SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 0, 0, 0));
	texture2 = SDL_CreateTextureFromSurface(renderer, rectangle);
	SDL_FreeSurface(rectangle);
	*/

	// Initialisation des rectangles
	for (int i = 0; i < LIGHTS_NUMBER; i++) {
		for (int j = 0; j < LIGHTS_NUMBER; j++) {
			position_lights[i][j].x = 0 + 80 * i;
			position_lights[i][j].y = 0 + 80 * j;
			position_lights[i][j].w = 80;
			position_lights[i][j].h = 80;
		}
	}

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

			for (int i = 0; i < LIGHTS_NUMBER; i++) {
				for (int j = 0; j < LIGHTS_NUMBER; j++) {
					SDL_RenderCopy(renderer, lights[i][j], NULL, &position_lights[i][j]);
				}
			}
			
			SDL_RenderPresent(renderer);
		}
	}

	// Destruction du rendeur, de la fenêtre et de la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}