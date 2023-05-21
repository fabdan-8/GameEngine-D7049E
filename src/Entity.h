#pragma once

#include "Defines.h"
#include "Ogre.h"
#include "OgreApplicationContext.h"

#include <string>

#include "Script.h"

struct QueuedMove {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    Ogre::Vector3 dir = { 0.0f, 0.0f, 0.0f };
    int counter = 0;
    int maxcounter = 1;
    Script* finished_script = nullptr;
};

class Entity {
public:
    std::string Load(std::string name, float scale = 1.0f, float start_x = 0.0f, float start_y = 0.0f, float start_z = 0.0f);
    std::string LoadAsImage(std::string filename, float x, float y, float z, float w, float h, float rot);
    void Update();
    void Interact();
    void QueueMove(float x, float y, float z, float speed, Script* script);

    Ogre::Vector3 getSize() {
        return size;
    }
    Ogre::Real getMass() {
        return mass;
    }
    Ogre::Entity* getEntity() {
        return ent;
    }
    Ogre::SceneNode* getNode() {
        return node;
    }

    Script* update_script = nullptr;
    Script* interaction_script = nullptr;
private:
    void SetMaterial(std::string name);

    std::vector<QueuedMove> moves;

    Ogre::Entity *ent = nullptr;
    Ogre::SceneNode *node = nullptr;
    //double speed = 0;//??
    Ogre::Vector3 size = { 1.0f, 1.0f, 1.0f };
    Ogre::Real mass = 1.0f;
    //float speed = 0.0f;
    //Ogre::Vector3 target = { 0.0f, 0.0f, 0.0f };
};
