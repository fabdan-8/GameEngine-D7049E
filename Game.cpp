#include "Game.h"
#include <time.h>
#include <iostream>

#include <Windows.h>//DEBUG - use something different for input

//SDL - temporary
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>

//ogre
#include <OGRE/Ogre.h>

//access global variables by using extern
extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern SDL_Event mainevent;
extern Mix_Music* music;
extern SDL_Texture* debug_texture;
extern int screenW;
extern int screenH;
extern int mouseX;
extern int mouseY;

void Game::Load() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {//initialize SDL
		return;
	}
	if (SDLNet_Init() != 0) {//initialize sdl_net
		return;
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {//initialize audio channels
		return;
	}
	//we're ok so far
	screenW = 1080;
	screenH = 720;
	window = SDL_CreateWindow("Spinning proboscis monkey", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenW, screenH, 0);
	if (!window) {
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");//default to pixel art. "0" is for pixel art, "1" is for text
	if (!renderer) {
		return;
	}

	//Load debug texture
	debug_texture = IMG_LoadTexture(renderer, "proboscismonkey.png");
	if (!debug_texture) {
		return;
	}

	std::cout << "W";//print W

	//Load music
	music = Mix_LoadMUS("spinnin.mp3");
	if (!music) {
		return;
	}
	Mix_VolumeMusic(48);//set volume
	Mix_PlayMusic(music, 0);

	//everything is ok, set running to true
	running = true;
}

void Game::MainLoop() {//single threaded solution
	clock_t last_tick = clock();
	clock_t current_time;
	while (running) {
		current_time = clock();
		Render();//no fps cap.
		if (current_time >= last_tick + tick_speed) {//update once per tick_speed milliseconds
			last_tick += tick_speed;
			if (current_time > last_tick + tick_speed) {//running (more than) one whole tick behind
				//do something, you are lagging behind.
			}
			Update();
		}
		Input();//take inputs as often as possible
		//Connection(); //check internet communication, this should be done on a separate thread, but can also be done on the same thread (not optimal)
	}
}

void Game::Render() {
	//do this as fast as possible (or cap FPS similar to how Update() is capped)

	//SDL-specific code below
	SDL_RenderClear(renderer);//clear old stuff

	//View on screen
	SDL_Rect rect = { screenW / 2, screenH / 2, 400, 400 };
	rect.x = screenW / 2 - 200;
	rect.y = screenH / 2 - 200;
	rect.w = 400;
	rect.h = 400;
	SDL_RenderCopyEx(renderer, debug_texture, NULL, &rect, rot, NULL, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);//show new stuff on screen
}

void Game::Input() {
	SDL_PollEvent(&mainevent);
	SDL_GetMouseState(&mouseX, &mouseY);
	if (GetAsyncKeyState(VK_TAB)) {//press tab to stop application - using Windows.h
		running = false;
	}
}

void Game::Update() {
	rot += 2;//update rot once every tick_speed milliseconds
	if (rot >= 360) {
		rot -= 360;
	}
	std::cout << "e";
}

void Game::Cleanup() {
	running = false;
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (music) {
		Mix_FreeMusic(music);
		music = nullptr;
	}
	Mix_CloseAudio();
	SDLNet_Quit();
	IMG_Quit();
	SDL_Quit();
}