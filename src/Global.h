#pragma once

#include "Defines.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Ogre.h"
#include "OgreApplicationContext.h"

#ifdef _WIN32
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>
#endif
#ifdef __unix__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_pixels.h>
#endif

#include "Chunk.h"
#include "Entity.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Scene.h"
#include "UI.h"
#include "Server.h"

Game game;
Server server;

std::string meshfolder = "";
std::string scriptfolder = "";
std::map<std::string, Script*> scripthandler;