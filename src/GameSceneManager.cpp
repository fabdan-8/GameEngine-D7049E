#include "GameSceneManager.h"
#include "Camera.h"
#include "GameEngine.h"
#include "Global.h"
#include "Physics.h"
#include "Renderable.h"
#include "SDL.h"
#include "ScriptData.h"

void GameSceneManager::UpdateAllEntities() {
    for (const auto &i : GAME_ENGINE->renderableMap) {
        i.second->Update();
    }
    for (const auto &i : GAME_ENGINE->physicsMap) {
        i.second->Update();
    }
    for (const auto &i : GAME_ENGINE->scriptDataMap) {
        i.second->Update();
    }
    // TODO: Is this needed?
    for (const auto &i : GAME_ENGINE->cameraMap) {
        i.second->Update();
    }
}

void GameSceneManager::InitWindowContext() {
    std::string name;
    ctx = new OgreBites::ApplicationContext("GameEngine-D7049E");

    ctx->initApp();
    window = ctx->getRenderWindow();

    //! [setup]
    // get a pointer to the already created root
    root = ctx->getRoot();
    // root = new Ogre::Root();

    //// Load plugins and configure Ogre3D
    // root->loadPlugin("RenderSystem_GL");
    //
    // Ogre::RenderSystem* rs = root->getRenderSystemByName("OpenGL Rendering
    // Subsystem"); root->setRenderSystem(rs); rs->setConfigOption("Full
    // Screen", "No"); rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit
    // colour");

    // Load Ogre configuration file
    // root->loadConfig("ogre.cfg");
    sceneManager = root->createSceneManager();

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator *shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(sceneManager);

    sceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

    Ogre::Light *light = sceneManager->createLight("MainLight");
    // light->setDiffuseColour(Ogre::ColourValue::White);
    // light->setSpecularColour(Ogre::ColourValue::White);
    Ogre::SceneNode *lightNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(20, 40, -50);
    lightNode->attachObject(light);

    // also need to tell where we are
    cameraNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    cameraNode->setPosition(0, 0, 15);
    cameraNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
    cameraNode->setFixedYawAxis(true, Ogre::Vector3(0, 1, 0)); // so that up is always up

    // create the camera
    camera = sceneManager->createCamera("camera");
    camera->setNearClipDistance(5); // specific to this sample
    camera->setAutoAspectRatio(true);
    cameraNode->attachObject(camera);
    cameraNode->setPosition(0, 40, 140);

    viewport = window->addViewport(camera);

    // Ogre::Root::getSingleton().getRenderSystem()->_setCullingMode(Ogre::CullingMode::CULL_CLOCKWISE);

    // KeyHandler keyHandler;
    // ctx->addInputListener(&keyHandler);

    TEMPORARY_ENTITY = GAME_SCENE_M->sceneManager->createEntity("sibenik.mesh");
    TEMPORARY_SCENE_NODE = GAME_SCENE_M->sceneManager->getRootSceneNode()->createChildSceneNode();
    TEMPORARY_SCENE_NODE->attachObject(TEMPORARY_ENTITY);

    //add a mesh folder
    meshfolder = "ArgumentsGameFolder/data/mesh/";
    Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
    rgm.addResourceLocation(meshfolder, "FileSystem");

    //create an entity
    Renderable entities[10];
    entities[0].Load("skeleton.X", 1, 0, 0, 0);
    entities[1].Load("fern", 1, 50, 0, 0);
    entities[2].Load("Desiccated Priest", 1, 0, 0, 200);
    entities[3].Load("Goblin", 1, 50, 0, 50);
    entities[4].Load("Orc", 1, 100, 0, 50);
    entities[5].Load("crypt", 1, -400, 0, 100);
    entities[6].Load("statuewall", 1, 0, 0, 300);
    entities[7].Load("skeleton", 1, -50, 0, 0);
    entities[8].Load("skeleton", 1, 0, 0, -100);
    entities[9].Load("skeleton", 0.2, -50, 0, -50);


    //! [setup]

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL failed\n";
        return;
    }
    if (SDLNet_Init() != 0) {
        std::cout << "SDL Net failed\n";
        return;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        std::cout << "SDL Mixer failed\n";
        return;
    }

    /*
    // Load music
    music = Mix_LoadMUS("Spinnin.mp3");
    if (!music) {
        return;
    }
    Mix_VolumeMusic(48); // set volume
    running = true;
    */

    return;
}

void GameSceneManager::Resize() {
    window->resize(window->getWidth(), window->getHeight());
}

void GameSceneManager::Render() {
    // ctx->getRoot()->renderOneFrame();
    root->renderOneFrame();
    // SDL_GL_SwapWindow(sdl_window);
}
