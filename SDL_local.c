#include "SDL_local.h"

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

void Affichage_lights_resize(SDL_Rect** position_lights, SDL_Rect* position_buttons){
	for (int i = 0; i < LIGHTS_NUMBER; i++) {
		for (int j = 0; j < LIGHTS_NUMBER; j++) {
			position_lights[i][j].w = (my_window.size * 10) / (12 * LIGHTS_NUMBER);
			position_lights[i][j].h = (my_window.size * 10) / (12 * LIGHTS_NUMBER);
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

void Affichage_click_update(int** Tab_lights, SDL_Rect** position_lights, Sint32 x, Sint32 y){
	for (int i = 0; i < LIGHTS_NUMBER; i++) {
		for (int j = 0; j < LIGHTS_NUMBER; j++) {
			if(x >= position_lights[i][j].x && x <= position_lights[i][j].x + position_lights[i][j].w && y >= position_lights[i][j].y && y <= position_lights[i][j].y + position_lights[i][j].h){
				Tab_lights[i][j] = !Tab_lights[i][j];
				if(i != 0)
					Tab_lights[i-1][j] = !Tab_lights[i-1][j];
				if(j != 0)
					Tab_lights[i][j-1] = !Tab_lights[i][j-1];
				if(i != LIGHTS_NUMBER - 1)
					Tab_lights[i+1][j] = !Tab_lights[i+1][j];
				if(j != LIGHTS_NUMBER - 1)
					Tab_lights[i][j+1] = !Tab_lights[i][j+1];
			}
		}
	}
}

void Affichage_lights_update(SDL_Renderer* renderer, SDL_Texture*** lights, int** Tab_lights){
	SDL_Surface* image_light_on = IMG_Load("images/light_on.png");
	SDL_Surface* image_light_off = IMG_Load("images/light_off.png");

	for (int i = 0; i < LIGHTS_NUMBER; i++) {
		for (int j = 0; j < LIGHTS_NUMBER; j++) {
			if(Tab_lights[i][j] == 1)
				lights[i][j] = SDL_CreateTextureFromSurface(renderer, image_light_on);
			else
				lights[i][j] = SDL_CreateTextureFromSurface(renderer, image_light_off);
		}
	}

	SDL_FreeSurface(image_light_on);
	SDL_FreeSurface(image_light_off);
}

int Collision_button(SDL_Rect position_buttons[BUTTONS_NUMBER], Sint32 x, Sint32 y){
	for (int i = 0; i < BUTTONS_NUMBER; i++) {
		if(x >= position_buttons[i].x && x <= position_buttons[i].x + position_buttons[i].w && y >= position_buttons[i].y && y <= position_buttons[i].y + position_buttons[i].h){
			return i;
		}
	}
	return -1;
}

void Button_hoover(){
	SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(cursor);
}

void Button_unhoover(){
	SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	SDL_SetCursor(cursor);
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

	SDL_Surface* image_button = IMG_Load(name_images_buttons[index]);
	buttons[index] = SDL_CreateTextureFromSurface(renderer, image_button);

	SDL_FreeSurface(image_button);
}

void Affichage_jeu(){

	// Instanciation des pointeurs de la SDL
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Event e;

	// Initialisation des variables
    int quit = 0; // variable de test pour quitter le programme
	int** Tab_lights;
	int button_click; // variable to change between click and non click image for the buttons
	int button_hoover = -1; // variable pour le hoover des bouttons
	int old_button_hoover = -1; // variable pour le unhoover des bouttons

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
	lights = malloc(sizeof(SDL_Texture**) * LIGHTS_NUMBER);
	position_lights =  malloc(sizeof(SDL_Rect*) * LIGHTS_NUMBER);
	Tab_lights = malloc(sizeof(int*) * LIGHTS_NUMBER);

	for (int i = 0; i < LIGHTS_NUMBER; i++) {
		lights[i] = malloc(sizeof(SDL_Texture*) * LIGHTS_NUMBER);
		Tab_lights[i] = malloc(sizeof(int) * LIGHTS_NUMBER);
		position_lights[i] =  malloc(sizeof(SDL_Rect) * LIGHTS_NUMBER);
		for (int j = 0; j < LIGHTS_NUMBER; j++) {
			Tab_lights[i][j] = 0;
		}
	}

	

	for (int i = 0; i < BUTTONS_NUMBER; i++){
		image_buttons[i] = IMG_Load(name_images_buttons[i]);
		buttons[i] = SDL_CreateTextureFromSurface(renderer, image_buttons[i]);
	}

	Affichage_lights_update(renderer, lights, Tab_lights);

	// Initialisation des rectangles
	Affichage_lights_resize(position_lights, position_buttons);

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
						Affichage_click_update(Tab_lights, position_lights, e.button.x, e.button.y);
						Affichage_lights_update(renderer, lights, Tab_lights);
					}
					if(e.button.button == SDL_BUTTON_RIGHT) {
						printf("x: %d y: %d\n", e.button.x, e.button.y);
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					button_click = Collision_button(position_buttons, e.motion.x, e.motion.y);
					if(button_click != -1){
						Button_click(renderer, buttons, button_click);
					}
					break;
				case SDL_MOUSEMOTION:
					old_button_hoover = button_hoover;
					button_hoover = Collision_button(position_buttons, e.motion.x, e.motion.y);
					if(old_button_hoover == -1 && button_hoover != -1){
						Button_hoover();
					}
					if(old_button_hoover != -1 && button_hoover == -1){
						Button_unhoover();
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
						Affichage_lights_resize(position_lights, position_buttons);
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