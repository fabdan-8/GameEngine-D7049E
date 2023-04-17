#include "Game.h"

#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>

void Game::Load() {
    std::string name;
	ctx = new OgreBites::ApplicationContext("OgreTutorialApp");
    ctx->initApp();
    
    //! [setup]
    // get a pointer to the already created root
    Ogre::Root* root = ctx->getRoot();
    //getline(std::cin, name);
    Ogre::SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen

    scnMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));// does not seem to work...

    Ogre::Light* light = scnMgr->createLight("MainLight");
    //light->setDiffuseColour(Ogre::ColourValue::White);
    //light->setSpecularColour(Ogre::ColourValue::White);
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(20, 40, -50);
    lightNode->attachObject(light);

    // also need to tell where we are
    camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 40, 140);

    // and tell it to render into the main window
    ctx->getRenderWindow()->addViewport(cam);

    // finally something to render
    //Ogre::Entity *ent = scnMgr->createEntity("Sinbad.mesh");
    //Ogre::Entity* ent = scnMgr->createEntity("skeleton.X");//"sibenik.mesh"
    Ogre::Entity* ent = scnMgr->createEntity("sibenik.mesh");
    //ent->setMaterial()
    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();

    node->setPosition(0, 0, -80);

    node->attachObject(ent);
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

    //Load music
    music = Mix_LoadMUS("Spinnin.mp3");
    if (!music) {
        return;
    }
    Mix_VolumeMusic(48);//set volume
    running = true;
	return;
}

void Game::MainLoop() {
    clock_t last_tick = clock();
    clock_t current_time;
    while (running) {
        current_time = clock();
        Render();//no fps cap.
        if (current_time >= last_tick + tick_speed) {//update once per tick_speed milliseconds
            last_tick += tick_speed;
            if (current_time > last_tick + tick_speed) {//running (more than) one whole tick behind
                //do something, you are lagging behind.
            }
            Update();
        }
        Input();//take inputs as often as possible
        //Connection(); //check internet communication, this should maybe be done on a separate thread
    }
}

void Game::Cleanup() {
    ctx->closeApp();
	delete ctx;

    SDLNet_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
}

bool Game::Clicked(unsigned char key) {
    if (keybuffer[key] & 0b00000001) {
        return true;
    }
    return false;
}

bool Game::Pressed(unsigned char key) {
    if (keybuffer[key] & 0b00000010) {
        return true;
    }
    return false;
}

bool Game::Released(unsigned char key) {
    if (keybuffer[key] & 0b00000100) {
        return true;
    }
    return false;
}

bool Game::MouseClicked(unsigned char button) {
    if (mousebuffer[button] & 0b00000001) {
        return true;
    }
    return false;
}

bool Game::MousePressed(unsigned char button) {
    if (mousebuffer[button] & 0b00000010) {
        return true;
    }
    return false;
}

bool Game::MouseReleased(unsigned char button) {
    if (mousebuffer[button] & 0b00000100) {
        return true;
    }
    return false;
}

void Game::Render() {
    ctx->getRoot()->renderOneFrame();
}

void Game::Input() {
    CheckEvents();
    if (Pressed(SDLK_TAB)) {
        running = false;
    }
    if (Clicked(SDLK_a)) {
        if (!music_playing) {
            Mix_PlayMusic(music, 0);
            music_playing = true;
            std::cout << "W";
        }
        else {
            Mix_HaltMusic();
            music_playing = false;
            std::cout << "\n\n";
        }
    }
}

void Game::Update() {
    if (music_playing) {
        rot += 0.01;
        if (rot >= M_PI * 2.0) {
            rot = rot - M_PI * 2.0;
        }
        std::cout << "e";
        //camNode->translate(Ogre::Vector3(0.0f, 1.0f, 0.0f));
        camNode->setPosition(0 + 220 * sin(rot), 40, -80 + 220 * cos(rot));
        camNode->lookAt(Ogre::Vector3(0, 0, -80), Ogre::Node::TS_PARENT);
    }
}

void Game::CheckEvents() {
    SDL_GetMouseState(&mouseX, &mouseY);//Get mouse positions
    for (int a = 0; a < 256; a++) {
        keybuffer[a] = (keybuffer[a] & 0b11111010);
    }
    while (SDL_PollEvent(&mainevent)) {//poll new event as long as we have a new event
        if (mainevent.type == SDL_QUIT) {//pressed red X
            running = false;
        }
        else if (mainevent.type == SDL_KEYDOWN) {
            keybuffer[(unsigned char)mainevent.key.keysym.sym] |= 0b00000011;
        }
        else if (mainevent.type == SDL_KEYUP) {
            keybuffer[(unsigned char)mainevent.key.keysym.sym] &= 0b11111101;
            keybuffer[(unsigned char)mainevent.key.keysym.sym] |= 0b00000100;
        }
        else if (mainevent.type == SDL_MOUSEBUTTONDOWN) {
            mousebuffer[(unsigned char)mainevent.button.button] |= 0b00000011;
        }
        else if (mainevent.type == SDL_MOUSEBUTTONUP) {
            mousebuffer[(unsigned char)mainevent.button.button] &= 0b11111101;
            mousebuffer[(unsigned char)mainevent.button.button] |= 0b00000100;
        }
    }
}
