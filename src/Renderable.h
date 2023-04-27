#pragma once

#include "Ogre.h"
#include <iostream>

struct Renderable {
    const int entityId;
    // If you want the name use ent->getName()
    Ogre::Entity *ent;
    Ogre::SceneNode *node;

    void createLight(Ogre::Vector3 xyz);
    // void Load(...);
    void Update();

    Renderable(std::string filename, float scale, Ogre::Vector3 xyz);
    Renderable(Ogre::Vector3 xyz); // Constructor for light
};
