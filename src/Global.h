#pragma once

#include "Defines.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

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

#include "Entity.h"
#include "Game.h"
#include "Scene.h"
//#include "UI.h"
//#include "Server.h"
#include "Script.h"
//#include "Physics.h"

Game game;
Scene scene; //let's start with only one scene
//Server server;

std::string meshfolder = "";
std::string scriptfolder = "";
std::string soundsfolder = "";
std::map<std::string, Script*> scripthandler;
std::map<std::string, Mix_Music*> musichandler;
std::map<std::string, Mix_Chunk*> soundhandler;
std::map<std::string, Variable*> variablehandler;

std::mutex ogre_resource_mut;
std::mutex clock_mut;