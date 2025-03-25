#define SDL_MAIN_USE_CALLBACKS 1

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "Sprite.h"
#include "Player.h"

static const double ASPECT_RATIO = 16.0/9.0;
static const int SCREEN_WIDTH = 800.0;
static const int SCREEN_HEIGHT = 800.0/ASPECT_RATIO;
static const int FPS = 144;

Uint64 current_tick = 0;
Uint64 last_tick = current_tick;
double delta_time;

static SDL_Window* window;
static SDL_Renderer* renderer;

SDL_FRect srcRect = { 0, 0, 32, 32 };

struct {
	int R=80, G=78, B=109;
	int A = 255;
} BUFFER_COLOR;

static Player* player;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	bool result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);
	if (!result) {
		SDL_Log("SDL_Init error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	window = SDL_CreateWindow("SDL3 Program :)", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
		SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == NULL) {
		SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	// Sprites
	player = new Player(renderer, "./Assets/Player/Player.png");

	player->SetPosition(300, 100);
	player->SetScale(.35);
	player->SetSourceRect(srcRect);
	player->SetMoveSpeed(300);

	setlocale(LC_ALL, "en");

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	player->Handle_Event(event);

	switch (event->type) {
	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;
		break;

	case SDL_EVENT_KEY_DOWN:
		switch (event->key.scancode) {
		case SDL_SCANCODE_ESCAPE:
			return SDL_APP_SUCCESS;
			break;
		default: break;
		}

	default: break;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {

	last_tick = current_tick;
	current_tick = SDL_GetTicks();
	delta_time = (current_tick - last_tick) / 1000.0;

	player->Update(delta_time);
	
	SDL_SetRenderDrawColor(renderer, BUFFER_COLOR.R, BUFFER_COLOR.G, BUFFER_COLOR.B, BUFFER_COLOR.A);
	SDL_RenderClear(renderer); // Fill the buffer with the draw collor

	player->Render();

	SDL_RenderPresent(renderer); // Display the buffer
	SDL_Delay(1000/FPS); // To prevent many FPS (max: 1000FPS)
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	delete player;
}