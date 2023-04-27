#include "GameEngine.h"
#include "EntityManager.h"
#include "GameSceneManager.h"
#include "Global.h"

int main(int argv, char **argc) {
    GAME_ENGINE = new GameEngine();
    ENTITY_M = new EntityManager();
    GAME_SCENE_M = new GameSceneManager();
    GAME_ENGINE->Startup();
}

void GameEngine::Startup() {
    // Start creating stuff for the game
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
