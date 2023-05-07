#pragma once

#include "Defines.h"
#include "Ogre.h"
#include "OgreApplicationContext.h"

#include <string>

class Entity {
public:
    std::string Load(std::string name, float scale = 1.0f, float start_x = 0.0f, float start_y = 0.0f, float start_z = 0.0f);
    void Update();
    Ogre::Vector3 getSize() {
        return size;
    }
    Ogre::Real getMass() {
        return mass;
    }
private:
    void SetMaterial(std::string name);

    Ogre::Entity *ent = nullptr;
    Ogre::SceneNode *node = nullptr;
    //double speed = 0;//??
    Ogre::Vector3 size = { 1.0f, 1.0f, 1.0f };
    Ogre::Real mass = 1.0f;
};
