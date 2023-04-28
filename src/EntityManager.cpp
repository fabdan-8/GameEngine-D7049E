
#include "EntityManager.h"
#include "Entity.h"
#include "GameEngine.h"
#include "Global.h"

Entity *EntityManager::createEntity() {
    entityId++;
    auto e = new Entity(entityId);
    GAME_ENGINE->entityMap[entityId] = e;
    return e;
}
