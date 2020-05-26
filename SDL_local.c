#include "SDL_local.h"

void Affichage_lights_update(SDL_Rect** position_lights){
	for (int i = 0; i < LIGHTS_NUMBER; i++) {
		for (int j = 0; j < LIGHTS_NUMBER; j++) {
			position_lights[i][j].w = (my_window.size * 10) / (12 * LIGHTS_NUMBER);
			position_lights[i][j].h = (my_window.size * 10) / (12 * LIGHTS_NUMBER);
			if(my_window.w > my_window.size) {
				position_lights[i][j].x = (my_window.w - my_window.size) / 2 + (my_window.size / 12) + position_lights[i][j].w * i;
			}
			else {
				position_lights[i][j].x = (my_window.size / 12) + position_lights[i][j].h * i;
			}
			if(my_window.h > my_window.size) {
				position_lights[i][j].y = (my_window.h - my_window.size) / 2 + (my_window.size / 12) + position_lights[i][j].w * j;
			}
			else {
				position_lights[i][j].y = (my_window.size / 12) + position_lights[i][j].h * j;
			}
		}
	}
}

void Affichage_click_update(SDL_Rect** position_lights, Sint32 x, Sint32 y){
	for (int i = 0; i < LIGHTS_NUMBER; i++) {
		for (int j = 0; j < LIGHTS_NUMBER; j++) {
			if(x >= position_lights[i][j].x && x <= position_lights[i][j].x + position_lights[i][j].w && y >= position_lights[i][j].y && y <= position_lights[i][j].y + position_lights[i][j].h){
				printf("x: %d y: %d\n", x, y);
				printf("i: %d j: %d\n", i, j);
			}
		}
	}
}

void Affichage_jeu(){

	// Instanciation des pointeurs de la SDL
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Event e;

	// Initialisation des variables
    int quit = 0; // variable de test pour quitter le programme

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
	SDL_GetWindowSize(window, &my_window.w, &my_window.h);
	if(my_window.h > my_window.w) {
		my_window.size = my_window.w;
	}
	else {
		my_window.size = my_window.h;
	}

	// Initilisation du rendeur
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

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
	lights = malloc(sizeof(SDL_Texture**) * LIGHTS_NUMBER);
	position_lights =  malloc(sizeof(SDL_Rect*) * LIGHTS_NUMBER);

	for (int i = 0; i < LIGHTS_NUMBER; i++) {
		lights[i] = malloc(sizeof(SDL_Texture*) * LIGHTS_NUMBER);
		position_lights[i] =  malloc(sizeof(SDL_Rect) * LIGHTS_NUMBER);
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
	Affichage_lights_update(position_lights);

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
					if (e.button.button == SDL_BUTTON_LEFT) {
						Affichage_click_update(position_lights, e.button.x, e.button.y);
					}
					break;
				
				case SDL_WINDOWEVENT:
					if(e.window.event == SDL_WINDOWEVENT_RESIZED){
						// Change les valeurs de la largeur et la hauteur de le fenêtre
						my_window.w = e.window.data1;
						my_window.h = e.window.data2;
						if(my_window.h > my_window.w) {
							my_window.size =  my_window.w;
						}
						else {
							my_window.size = my_window.h;
						}
						Affichage_lights_update(position_lights);
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