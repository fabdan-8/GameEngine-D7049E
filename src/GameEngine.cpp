#include "GameEngine.h"

//#include "OgreMeshSerializer.h"

#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "Entity.h"
#include "EntityManager.h"
#include "GameSceneManager.h"
#include "Global.h"
#include "Input.h"
#include "Renderable.h"
#include "Script.h"
#include "Sound.h"

GameEngine *GAME_ENGINE;
EntityManager *ENTITY_M;
GameSceneManager *GAME_SCENE_M;
Input *INPUT;

int main(int argv, char **argc) {
    GAME_ENGINE = new GameEngine();
    ENTITY_M = new EntityManager();
    GAME_SCENE_M = new GameSceneManager();
    INPUT = new Input();
    GAME_ENGINE->Load();
    GAME_ENGINE->MainLoop();
    GAME_ENGINE->Cleanup();
    return 0;
}

void GameEngine::Load() {
    // Start creating stuff for the game
    GAME_SCENE_M->InitWindowContext();
}

void GameEngine::MainLoop() {
    clock_t last_tick = clock();
    clock_t current_time;
    while (running) {
        current_time = clock();
        GAME_SCENE_M->Render();                       // no fps cap.
        if (current_time >= last_tick + TICK_SPEED) { // update once per tick_speed milliseconds
            last_tick += TICK_SPEED;
            if (current_time > last_tick + TICK_SPEED) { // running (more than) one whole tick behind
                                                         // do something, you are lagging behind.
            }
            Update();
        }
        INPUT->GetInput(); // take inputs as often as possible
    }
}

void GameEngine::Cleanup() {
    // ctx->closeApp();
    // delete ctx;
    delete GAME_SCENE_M->root;
    delete ENTITY_M;
    delete GAME_SCENE_M;
    delete INPUT;

    SDLNet_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
}

void GameEngine::Update() {
    return;
}

Script *getScriptFromName(std::string name) {
    for (const auto &i : GAME_ENGINE->scriptMap) {
        if (name.compare(i.second->name) == 0) {
            return GAME_ENGINE->scriptMap[i.first];
        }
    }
    // TODO: Throw error?
    return NULL;
}

Renderable *getRenderableFromName(std::string name) {
    for (const auto &i : GAME_ENGINE->renderableMap) {
        if (name.compare(i.second->ent->getName()) == 0) {
            return GAME_ENGINE->renderableMap[i.first];
        }
    }
    // TODO: Throw error?
    return NULL;
}

Sound *getSoundFromName(std::string name) {
    for (const auto &i : GAME_ENGINE->soundMap) {
        if (name.compare(i.second->name) == 0) {
            return GAME_ENGINE->soundMap[i.first];
        }
    }
    // TODO: Throw error?
    return NULL;
}
