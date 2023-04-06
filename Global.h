#pragma once
//do not include this file anywhere except main.cpp, and put all global variables in this file

#include "Defines.h"
#include <iostream>

#include "Game.h"

//SDL - temporary
#define SDL_MAIN_HANDLED //must be defined
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>

//SDL-specific objects
SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;
SDL_Event mainevent;
Mix_Music* music = nullptr;
SDL_Texture* debug_texture = nullptr;

Game game;//game object

//screen and mouse variables
int screenW;
int screenH;
int mouseX;
int mouseY;