#pragma once

#include "Entity.h"

struct EntityManager {
    unsigned int entityId = 0;
    // This gets incremented after each object added
    // that does not share id

    void deleteEntity(unsigned int ID); // This also deletes associated components

    Entity *createEntity();
};
