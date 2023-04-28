#include "Ogre.h"
#include "OgreApplicationContext.h"
#include <iostream>
#include <map>

/*
#include "Camera.h"
#include "Entity.h"
#include "Physics.h"
#include "Renderable.h"
#include "Script.h"
#include "ScriptData.h"
#include "Sound.h"
*/
struct Script;
struct Entity;
struct Renderable;
struct Physics;
struct ScriptData;
struct Sound;
struct Camera;

struct GameEngine {
    std::map<int, Ogre::SceneManager *> sceneMap;
    std::map<int, Script *> scriptMap;

    std::map<int, Entity *> entityMap;
    std::map<int, Renderable *> renderableMap;
    std::map<int, Physics *> physicsMap;
    std::map<int, ScriptData *> scriptDataMap;
    std::map<int, Sound *> soundMap;
    std::map<int, Camera *> cameraMap;

    Script *getScriptFromName(std::string name);
    Renderable *getRenderableFromName(std::string name);
    Sound *getSoundFromName(std::string name);

    void Load();
    void MainLoop();
    void Cleanup();
};

#include "Camera.h"
#include "Entity.h"
#include "EntityManager.h"
#include "GameSceneManager.h"
#include "Physics.h"
#include "Renderable.h"
#include "Script.h"
#include "ScriptData.h"
#include "Sound.h"
