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
    Ogre::Camera *camera = nullptr;
    Ogre::SceneNode *cameraNode = nullptr;
    Ogre::Viewport *viewport = nullptr;
    std::string meshfolder;

    Ogre::Entity *TEMPORARY_ENTITY = nullptr;
    Ogre::SceneNode *TEMPORARY_SCENE_NODE = nullptr;

    void InitWindowContext();
    void ChangeScene(int scene);
    int LoadScene(std::string name);
    void UpdateAllEntities();
    void Resize();
    void Render();
};
