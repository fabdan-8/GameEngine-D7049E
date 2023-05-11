#pragma once

#include "OgreApplicationContext.h"

struct Entity {
    const int entityId;
    Entity(int entityId);

    Ogre::Vector3 getSize();
    Ogre::Real getMass();
};
