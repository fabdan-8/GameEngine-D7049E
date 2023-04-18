#pragma once

#include "Defines.h"
#include "Ogre.h"

class Entity {
public:
    void Update();

    Ogre::Entity* ent = nullptr;
    Ogre::SceneNode* node = nullptr;
    double speed;
};

