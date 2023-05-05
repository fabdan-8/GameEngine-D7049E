
#include "EntityManager.h"
#include "Entity.h"
#include "GameEngine.h"
#include "Global.h"

Entity* EntityManager::createEntity() {
    entityId++;
    auto e = new Entity(entityId);
    GAME_ENGINE->entityMap[entityId] = e;
    return e;
}

void EntityManager::deleteEntity(unsigned int ID) {
    Entity* e = nullptr;
    if (GAME_ENGINE->entityMap.find(ID) != GAME_ENGINE->entityMap.end()) {
        e = GAME_ENGINE->entityMap[ID];
        GAME_ENGINE->entityMap.erase(ID);
    }
    if (GAME_ENGINE->renderableMap.find(ID) != GAME_ENGINE->renderableMap.end()) {
        GAME_ENGINE->renderableMap.erase(ID);
    }
    //and repeat for all other maps
    
    //I'm still not sold on the current idea for the entity system...
}