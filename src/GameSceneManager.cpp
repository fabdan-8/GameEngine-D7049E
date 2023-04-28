#include "GameSceneManager.h"
#include "Camera.h"
#include "GameEngine.h"
#include "Global.h"
#include "Physics.h"
#include "Renderable.h"
#include "ScriptData.h"

void GameSceneManager::UpdateAllEntities() {
    for (const auto &i : GAME_ENGINE->renderableMap) {
        i.second->Update();
    }
    for (const auto &i : GAME_ENGINE->physicsMap) {
        i.second->Update();
    }
    for (const auto &i : GAME_ENGINE->scriptDataMap) {
        i.second->Update();
    }
    // TODO: Is this needed?
    for (const auto &i : GAME_ENGINE->cameraMap) {
        i.second->Update();
    }
}
