#pragma once
#include "Defines.h"

#include "Ogre.h"
#include "OgreApplicationContext.h"

#ifdef _WIN32
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>
#endif
#ifdef __unix__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_pixels.h>
#endif

// probably change glm to ogre specific stuff later
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Scene.h"

/*
class Variable {
public:
    std::string name = "";
    std::string content = "";
    double value = 0;
    bool IsValue() {
        return content == "$value";
    }
    bool IsString() {
        return !IsValue();
    }
};

class Script {
public:
    std::vector<std::string> command;
    std::vector<std::vector<Variable>> argument;
    void Read();
};
*/

class Game {
  public:
    Game(){};
    ~Game(){};

    void Load();
    void MainLoop();
    void Cleanup();

  private:
    void Render();
    void Input();
    void Update();

    void CheckEvents();

    SDL_Event mainevent;
    SDL_Window *sdl_window = nullptr;
    Mix_Music *music;
    bool music_playing = false;

    int my;
    int mx;
    float camspeed = 0.5f;
    float rotspeed = 0.01f;

    OgreBites::ApplicationContext *ctx = nullptr;
    Ogre::Root *root = nullptr;
    Ogre::RenderWindow *window = nullptr;
    Ogre::Camera *cam = nullptr;
    Ogre::SceneNode *cam_node = nullptr;
    Ogre::Viewport *viewport = nullptr;

    // test
    double rot = 0.0;
};
