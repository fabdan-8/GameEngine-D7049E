#pragma once

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include <iostream>

struct Renderable {
    const int entityId;
    Ogre::Entity *ent;
    Ogre::SceneNode *node;

    void createLight(Ogre::Vector3 xyz);
    std::string Load(std::string name, float scale, float start_x, float start_y, float start_z);
    void SetMaterial(std::string name);
    void Update();

    //Renderable(int entityId, std::string filename, float scale, Ogre::Vector3 xyz);
    //Renderable(Ogre::Vector3 xyz); // Constructor for light
};
