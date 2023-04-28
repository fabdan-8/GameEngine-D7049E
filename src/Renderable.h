#pragma once

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include <iostream>

struct Renderable {
    const int entityId;
    Ogre::Entity *ent;
    Ogre::SceneNode *node;

    void createLight(Ogre::Vector3 xyz);
    void Load(std::string filename, float scale, Ogre::Vector3 xyz);
    // void Load(...);
    // void SetMaterial(std::string name);
    void Update();

    Renderable(int entityId, std::string filename, float scale, Ogre::Vector3 xyz);
    Renderable(Ogre::Vector3 xyz); // Constructor for light
};
