#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>
//#include <Windows.h>//key presses
#include <iostream>

#include "Dataset.h"//Image.h included
#include "Server.h"
#include "Datapoint.h"

//#define VK_TAB		0x09
//#define VK_LEFT		0x25
//#define VK_UP		0x26
//#define VK_RIGHT	0x27
//#define VK_DOWN		0x28

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Event mainevent;
bool running = true;
Dataset data;
Image frame;
Server server;
Datapoint sensor;

int screenw = 1080;
int screenh = 640;

int my = 0;
int mx = 0;

unsigned short int window_width = 100;
unsigned short int window_height = 100;

unsigned char keypress[256] = { 0 };

bool Pressed(unsigned char key) {
	return keypress[key];
}

void InitSDL() {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	SDLNet_Init();
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenw, screenh, 0);
	if (window) {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
}

void MakeFrame(int ww, int hh) {
	SDL_Surface* frame_surf = SDL_CreateRGBSurfaceWithFormat(0, ww, hh, 32, SDL_PIXELFORMAT_RGBA32);
	if (frame_surf) {
		unsigned char* pixels = (unsigned char*)frame_surf->pixels;
		int channels = 4;
		unsigned char R = 32;
		unsigned char G = 180;
		unsigned char B = 32;
		for (int a = 0; a < hh; a++) {
			pixels[channels * ((a * ww) + 0) + 0] = R;
			pixels[channels * ((a * ww) + 0) + 1] = G;
			pixels[channels * ((a * ww) + 0) + 2] = B;
			pixels[channels * ((a * ww) + 0) + 3] = 255;

			pixels[channels * ((a * ww) + (ww - 1)) + 0] = R;
			pixels[channels * ((a * ww) + (ww - 1)) + 1] = G;
			pixels[channels * ((a * ww) + (ww - 1)) + 2] = B;
			pixels[channels * ((a * ww) + (ww - 1)) + 3] = 255;
		}
		for (int b = 0; b < ww; b++) {
			pixels[channels * ((0 * ww) + b) + 0] = R;
			pixels[channels * ((0 * ww) + b) + 1] = G;
			pixels[channels * ((0 * ww) + b) + 2] = B;
			pixels[channels * ((0 * ww) + b) + 3] = 255;

			pixels[channels * (((hh - 1) * ww) + b) + 0] = R;
			pixels[channels * (((hh - 1) * ww) + b) + 1] = G;
			pixels[channels * (((hh - 1) * ww) + b) + 2] = B;
			pixels[channels * (((hh - 1) * ww) + b) + 3] = 255;
		}
		frame.SetFromSurface(frame_surf, "frame");
	}
}

void MainLoop() {
	while (running) {
		SDL_RenderClear(renderer);

		SDL_PollEvent(&mainevent);
		SDL_GetMouseState(&mx, &my);

		if (mainevent.type == SDL_QUIT) {
			running = false;
		}
		else if (mainevent.type == SDL_KEYDOWN) {
			keypress[(unsigned char)mainevent.key.keysym.sym] = 1;
		}
		else if (mainevent.type == SDL_KEYUP) {
			keypress[(unsigned char)mainevent.key.keysym.sym] = 0;
		}
		else if (mainevent.type == SDL_MOUSEBUTTONDOWN) {
			keypress[(unsigned char)mainevent.button.button] = 1;
		}
		else if (mainevent.type == SDL_MOUSEBUTTONUP) {
			keypress[(unsigned char)mainevent.button.button] = 0;
		}

		if (Pressed(SDLK_TAB)) {
			running = false;
		}
		if (Pressed(SDLK_LEFT)) {
			data.movx--;
		}
		if (Pressed(SDLK_RIGHT)) {
			data.movx++;
		}
		if (Pressed(SDL_BUTTON_LEFT)) {//mouse button down
			SDL_Texture* textureL = data.GetL_edge().GetTexture();
			SDL_Texture* textureR = data.GetR_edge().GetTexture();
			if (textureL && textureR && mx >= 0 && mx < 192 * 4 && my >= 108 * 2 && my < screenh) {
				SDL_Rect disprect;
				disprect.x = 192 * 4;
				disprect.y = 0;
				disprect.w = screenw - 192 * 4;
				disprect.h = 108 * 6;
				int xpos = mx * 2;
				int ypos = (my - 108 * 2) * screenh / (108 * 6);
				SDL_Rect srcrect;
				srcrect.x = xpos;
				srcrect.y = ypos;
				srcrect.w = disprect.w;
				srcrect.h = disprect.h;
				SDL_RenderCopy(renderer, textureL, &srcrect, &disprect);
				xpos = mx * 2 - (float)data.movx * data.movfactor * (float)(1920) / (float)(192 * 4);
				srcrect.x = xpos;
				SDL_RenderCopy(renderer, textureR, &srcrect, &disprect);
			}
		}
		if (Pressed(SDL_BUTTON_RIGHT)) {
			unsigned short int max_search = 100;
			bool search_from_left = true;
			float y = (float)(my - 108 * 2) * (float)(1080) / (float)(108 * 4);
			float x = (float)mx * (float)(1920) / (float)(192 * 4);
			data.movx = -data.MatchSquare((unsigned char*)data.GetL_edge().GetSurface()->pixels, (unsigned char*)data.GetR_edge().GetSurface()->pixels, 4, x, y, window_width, window_height, data.GetL_edge().GetSurface()->w, data.GetL_edge().GetSurface()->h, max_search, search_from_left, 0);
			std::cout << data.movx << "\n";
		}

		data.Disp();
		frame.Disp(mx, my, (float)window_width * 0.4f, (float)window_height * 0.4f);

		SDL_RenderPresent(renderer);
		server.Receive();
	}
}

int main() {
	InitSDL();

	server.StartServer();

	data.Load("artroom1");
	MakeFrame((float)window_width * 0.4f, (float)window_height * 0.4f);

	MainLoop();

	server.StopServer();

	data.Cleanup();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDLNet_Quit();
	IMG_Quit();
	SDL_Quit();
}