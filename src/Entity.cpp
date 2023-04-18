#include "Entity.h"

#include <iostream>

#include "Game.h"

extern Game game;

void Entity::Update() {

}

std::string Entity::Load(std::string name, float scale, float start_x, float start_y, float start_z) {
    Ogre::Entity* ent;
    try {
        ent = game.scnMgr->createEntity(name);
    }
    catch (...) {
        ent = nullptr;
    }
    if (ent) {
        Ogre::SceneNode* node = game.scnMgr->getRootSceneNode()->createChildSceneNode();
        
        node->setScale(Ogre::Vector3(scale, scale, scale));
        node->setPosition(start_x, start_y, start_z);

        node->attachObject(ent);
        return ent->getName();
    }
    else {
        std::cout << "Can't find mesh '" << name << "'\n";
        return "";
    }
}