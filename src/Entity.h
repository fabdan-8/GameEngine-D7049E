#pragma once

/*
#include "Defines.h"
#include "Ogre.h"
#include "OgreApplicationContext.h"

#include <string>

class Entity {
  public:
    void Update();
    void SetMaterial(std::string name);
    std::string Load(std::string name, float scale = 1.0f, float start_x = 0.0f, float start_y = 0.0f, float start_z = 0.0f);

    Ogre::Entity *ent = nullptr;
    Ogre::SceneNode *node = nullptr;
    double speed;
};
*/
struct Entity {
    const int entityId;
    Entity(int entityId);
};
