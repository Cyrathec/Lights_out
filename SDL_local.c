#include "SDL_local.h"

#include <stdio.h>
#include <stdlib.h>

int num_light;

const char* name_images_buttons[BUTTONS_NUMBER] = {
    "images/button_restart_game.png",
    "images/button_new_game.png",
    "images/button_help.png",
    "images/button_resolve.png"
};

const char* name_images_buttons_c[BUTTONS_NUMBER] = {
    "images/button_restart_game_c.png",
    "images/button_new_game_c.png",
    "images/button_help_c.png",
    "images/button_resolve_c.png"
};

const char* name_images_lights[2] = {
    "images/light_off.png",
    "images/light_on.png"
};

const char* name_images_lights_c[2] = {
    "images/light_off_c.png",
    "images/light_on_c.png"
};

void Hoover(){
	SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(cursor);
}

void Unhoover(){
	SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	SDL_SetCursor(cursor);
}

void Window_resize(SDL_Rect** position_lights, SDL_Rect* position_buttons, int num_light){
	for (int i = 0; i < num_light; i++) {
		for (int j = 0; j < num_light; j++) {
			position_lights[i][j].w = (my_window.size * 10) / (12 * num_light);
			position_lights[i][j].h = (my_window.size * 10) / (12 * num_light);
			if(my_window.w > my_window.size) {
				position_lights[i][j].x = (my_window.w - my_window.size) / 2 + (my_window.size / 12) + position_lights[i][j].w * i;
			}
			else {
				position_lights[i][j].x = (my_window.size / 12) + position_lights[i][j].w * i;
			}
			if(my_window.h > my_window.size) {
				position_lights[i][j].y = (my_window.h - my_window.size) / 2 + (my_window.size / 12) + position_lights[i][j].h * j;
			}
			else {
				position_lights[i][j].y = (my_window.size / 12) + position_lights[i][j].h * j;
			}
		}
	}
	for (int i = 0; i < BUTTONS_NUMBER; i++){
		position_buttons[i].h = (my_window.size * 8) / (12 * 10);
		position_buttons[i].w = (my_window.size * 8) / (BUTTONS_NUMBER * 10);
		if(my_window.w > my_window.size) {
			position_buttons[i].x = (my_window.w - my_window.size) / 2 + (my_window.size * 2 * (i + 1)) / (10 * 5) + position_buttons[i].w * i;
		}
		else {
			position_buttons[i].x = (my_window.size * 2 * (i + 1)) / (10 * 5) + position_buttons[i].w * i;
		}
		if(my_window.h > my_window.size) {
			position_buttons[i].y = (my_window.h - my_window.size) / 2 + my_window.size / (12 * 10);
		}
		else {
			position_buttons[i].y = my_window.size / (12 * 10);
		}
	}
}

void Collision_Light(SDL_Rect** position_lights, Sint32 x, Sint32 y, int index[2], int num_light){
	for (int i = 0; i < num_light; i++) {
		for (int j = 0; j < num_light; j++) {
			if(x >= position_lights[i][j].x && x <= position_lights[i][j].x + position_lights[i][j].w && y >= position_lights[i][j].y && y <= position_lights[i][j].y + position_lights[i][j].h){
				index[0] = i;
				index[1] = j;
				return;
			}
		}
	}
	index[0] = -1;
	index[1] = -1;
	return;
}

void Light_click(SDL_Renderer* renderer, SDL_Texture*** lights, int** tab_lights, int index_i, int index_j, int num_light){
	if (index_i < 0 || index_i >= num_light){
		return;
	}
	if (index_j < 0 || index_j >= num_light){
		return;
	}

	SDL_Surface* image_light = IMG_Load(name_images_lights_c[tab_lights[index_i][index_j]]);
	lights[index_i][index_j] = SDL_CreateTextureFromSurface(renderer, image_light);

	SDL_FreeSurface(image_light);
}

void Light_unclick(SDL_Renderer* renderer, SDL_Texture*** lights, int** tab_lights, int index_i, int index_j, int num_light){
	if (index_i < 0 || index_i >= num_light){
		return;
	}
	if (index_j < 0 || index_j >= num_light){
		return;
	}

	tab_lights[index_i][index_j] = !tab_lights[index_i][index_j];
	SDL_Surface* image_light = IMG_Load(name_images_lights[tab_lights[index_i][index_j]]);
	lights[index_i][index_j] = SDL_CreateTextureFromSurface(renderer, image_light);

	if(index_i != 0){
		tab_lights[index_i-1][index_j] = !tab_lights[index_i-1][index_j];
		SDL_Surface* image_light = IMG_Load(name_images_lights[tab_lights[index_i-1][index_j]]);
		lights[index_i-1][index_j] = SDL_CreateTextureFromSurface(renderer, image_light);
	}
		
	if(index_j != 0){
		tab_lights[index_i][index_j-1] = !tab_lights[index_i][index_j-1];
		SDL_Surface* image_light = IMG_Load(name_images_lights[tab_lights[index_i][index_j-1]]);
		lights[index_i][index_j-1] = SDL_CreateTextureFromSurface(renderer, image_light);
	}

	if(index_i != num_light - 1){
		tab_lights[index_i+1][index_j] = !tab_lights[index_i+1][index_j];
		SDL_Surface* image_light = IMG_Load(name_images_lights[tab_lights[index_i+1][index_j]]);
		lights[index_i+1][index_j] = SDL_CreateTextureFromSurface(renderer, image_light);
	}

	if(index_j != num_light - 1){
		tab_lights[index_i][index_j+1] = !tab_lights[index_i][index_j+1];
		SDL_Surface* image_light = IMG_Load(name_images_lights[tab_lights[index_i][index_j+1]]);
		lights[index_i][index_j+1] = SDL_CreateTextureFromSurface(renderer, image_light);
	}

	SDL_FreeSurface(image_light);
}

int Collision_button(SDL_Rect position_buttons[BUTTONS_NUMBER], Sint32 x, Sint32 y){
	for (int i = 0; i < BUTTONS_NUMBER; i++) {
		if(x >= position_buttons[i].x && x <= position_buttons[i].x + position_buttons[i].w && y >= position_buttons[i].y && y <= position_buttons[i].y + position_buttons[i].h){
			return i;
		}
	}
	return -1;
}

void Button_click(SDL_Renderer* renderer, SDL_Texture* buttons[BUTTONS_NUMBER], int index){
	if (index < 0 || index >= BUTTONS_NUMBER){
		return;
	}

	SDL_Surface* image_button_hoover = IMG_Load(name_images_buttons_c[index]);
	buttons[index] = SDL_CreateTextureFromSurface(renderer, image_button_hoover);

	SDL_FreeSurface(image_button_hoover);
}

void Button_unclick(SDL_Renderer* renderer, SDL_Texture* buttons[BUTTONS_NUMBER], int index){
	if (index < 0 || index >= BUTTONS_NUMBER){
		return;
	}

	printf("%d\n", index);

	switch (index){
	case 0:
		/* code */
		break;
	case 1:
		/* code */
		break;
	case 2:
		/* code */
		break;
	case 3:
		/* code */
		break;
	default:
		break;
	}

	SDL_Surface* image_button = IMG_Load(name_images_buttons[index]);
	buttons[index] = SDL_CreateTextureFromSurface(renderer, image_button);

	SDL_FreeSurface(image_button);
}

void Affichage_jeu(int** tab_lights_init, int weight){

	// Instanciation des pointeurs de la SDL
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Event e;

	// Initialisation des variables
    int quit = 0; // variable de test pour quitter le programme
	int** tab_lights;
	int light_click[2]; // variable to change between click and non click image for lights
	int button_click; // variable to change between click and non click image for the buttons
	int hoover = 0; // variable for the hoover
	int old_hoover = 0; // variable for the unhoover

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

	if (TTF_Init() != 0) {
		printf("[-] ERROR -  Failed to initialise SDL_TTF (%s)\n", SDL_GetError());
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

	// Instanciation des variables SDL
	TTF_Font* agencyFB = TTF_OpenFont("./AGENCYR.TTF", 24);
	SDL_Color white = { 255, 255, 255 };

	// Instanciation des textures, surfaces et rectangles
	SDL_Texture*** lights;
	SDL_Surface* image_light_on;
	SDL_Surface* image_light_off;
	SDL_Rect** position_lights;

	SDL_Texture* buttons[BUTTONS_NUMBER];
	SDL_Surface* image_buttons[BUTTONS_NUMBER];
	SDL_Rect position_buttons[BUTTONS_NUMBER];

	// Initialisation des textures, surfaces
	num_light = weight;
	lights = malloc(sizeof(SDL_Texture**) * num_light);
	position_lights =  malloc(sizeof(SDL_Rect*) * num_light);
	tab_lights = malloc(sizeof(int*) * num_light);

	for (int i = 0; i < num_light; i++) {
		lights[i] = malloc(sizeof(SDL_Texture*) * num_light);
		tab_lights[i] = malloc(sizeof(int) * num_light);
		position_lights[i] =  malloc(sizeof(SDL_Rect) * num_light);
		for (int j = 0; j < num_light; j++) {
			printf("i: %d j: %d\n", i, j);
			printf("%d\n", tab_lights_init[i][j]);
			tab_lights[i][j] = tab_lights_init[i][j];
			SDL_Surface* image_light = IMG_Load(name_images_lights[tab_lights[i][j]]);
			lights[i][j] = SDL_CreateTextureFromSurface(renderer, image_light);
		}
	}

	// Initialisation des rectangles
	Window_resize(position_lights, position_buttons, num_light);

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
						if(button_click != -1){
							Button_unclick(renderer, buttons, button_click);
							button_click = -1;
						}
						if(light_click[0] != -1 && light_click[1] != -1){
							Light_unclick(renderer, lights, tab_lights, light_click[0], light_click[1], num_light);
							light_click[0] = -1;
							light_click[1] = -1;
						}
					}
					if(e.button.button == SDL_BUTTON_RIGHT) {
						printf("x: %d y: %d\n", e.button.x, e.button.y);
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					button_click = Collision_button(position_buttons, e.motion.x, e.motion.y);
					Collision_Light(position_lights, e.button.x, e.button.y, light_click, num_light);
					if(button_click != -1){
						Button_click(renderer, buttons, button_click);
					}
					if(light_click[0] != -1 && light_click[1] != -1){
						Light_click(renderer, lights, tab_lights, light_click[0], light_click[1], num_light);
					}
					break;
				case SDL_MOUSEMOTION:
					old_hoover = hoover;
					int col_but = Collision_button(position_buttons, e.motion.x, e.motion.y);
					int col_ligth[2];
					Collision_Light(position_lights, e.motion.x, e.motion.y, col_ligth, num_light);
					if(col_but != -1 || (col_ligth[0] != -1 && col_ligth[1] != -1))
						hoover = 1;
					else
						hoover = 0;
					if(!old_hoover && hoover){
						Hoover();
					}
					if(old_hoover && !hoover){
						Unhoover();
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
						Window_resize(position_lights, position_buttons, num_light);
					}
					break;
			}

			// Mise à jour de l'affichage
			SDL_RenderClear(renderer);

			for (int i = 0; i < num_light; i++) {
				for (int j = 0; j < num_light; j++) {
					SDL_RenderCopy(renderer, lights[i][j], NULL, &position_lights[i][j]);
				}
			}
			for (int i = 0; i < BUTTONS_NUMBER; i++){
				SDL_RenderCopy(renderer, buttons[i], NULL, &position_buttons[i]);
			}
			
			SDL_RenderPresent(renderer);
		}
	}

	// Destruction du rendeur, de la fenêtre et de la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(agencyFB);
	SDL_Quit();
}