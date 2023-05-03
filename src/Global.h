#pragma once

#define TICK_SPEED 10

struct GameEngine;
struct EntityManager;
struct GameSceneManager;
struct Input;

extern GameEngine *GAME_ENGINE;
extern EntityManager *ENTITY_M;
extern GameSceneManager *GAME_SCENE_M;
extern Input *INPUT;

/*
std::string meshfolder = "";
std::string scriptfolder = "";
std::map<std::string, Script*> scripthandler;
*/
