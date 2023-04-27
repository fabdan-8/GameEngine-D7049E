#pragma once

#include "Entity.h"

struct EntityManager {
    int entityId = 0;
    // This gets incremented after each object added
    // that does not share id

    void deleteEntity(); // This also deletes associated components

    Entity *createEntity();
};
