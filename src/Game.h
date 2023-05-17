#pragma once
#include "Defines.h"

#include <mutex>

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

//// probably change glm to ogre specific stuff later
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/rotate_vector.hpp>
//#include <glm/gtx/vector_angle.hpp>

#include "Scene.h"

class Game {
  public:
    Game(){};
    ~Game(){};

    void Load();
    void MainLoop();
    void Cleanup();

    bool Clicked(unsigned char key);
    bool Pressed(unsigned char key);
    bool Released(unsigned char key);
    bool MouseClicked(unsigned char button);
    bool MousePressed(unsigned char button);
    bool MouseReleased(unsigned char button);

    Script* ScriptLoader(std::string filename);
    void ScriptReader(std::string filename);
    bool IsRunning();
    void Shutdown();

    Ogre::Camera* GetCamera() {
        return cam;
    }
    Ogre::RenderWindow* GetWindow() {
        return window;
    }

    Ogre::SceneManager *scnMgr = nullptr;
    
    unsigned char keybuffer[256] = {0}; // 0b00000000 is the binary representation. The last byte
                                        // is "clicked", the second to last is "pressed", the third
                                        // to last is "released"
    unsigned char mousebuffer[256] = {0};
    int mouseX;
    int mouseY;
    int screenW;
    int screenH;

  private:
    void Render();
    void CheckEvents();
    void Input();
    void ApplyChangesFromInput();
    void Update();

    void InputThread();
    void RenderThread();
    bool ThreadIsRunning();

    SDL_Event mainevent;
    //SDL_Window *sdl_window = nullptr;
    //bool music_playing = false;

    bool running = false;//don't access this directly, use IsRunning() and Shutdown() instead
    bool fixed_y = true;
    std::mutex running_mut;

    int my;
    int mx;
    float camspeed = 2.5f;
    float rotspeed = 0.01f;

    OgreBites::ApplicationContext* ctx = nullptr;
    Ogre::Root* root = nullptr;
    Ogre::RenderWindow* window = nullptr;
    Ogre::Camera* cam = nullptr;
    Ogre::SceneNode* cam_node = nullptr;
    Ogre::SceneNode* cam_node_alt = nullptr;
    Ogre::Viewport* viewport = nullptr;

    // test
    double rot = 0.0;
};
