#pragma once
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include <iostream>

struct GameSceneManager {
    int currentScene;
    Ogre::SceneManager *sceneManager = nullptr;
    OgreBites::ApplicationContext *ctx = nullptr;
    Ogre::Root *root = nullptr;
    Ogre::RenderWindow *window = nullptr;
    Ogre::Camera *cam = nullptr;
    Ogre::SceneNode *cam_node = nullptr;
    Ogre::Viewport *viewport = nullptr;

    void changeScene(int scene);
    int loadScene(std::string name);
    void UpdateAllEntities();
};
