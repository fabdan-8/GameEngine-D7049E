#include "Input.h"

#include "GameEngine.h"
#include "GameSceneManager.h"
#include "Global.h"
#include "SDL.h"

bool Input::Clicked(unsigned char key) {
    if (keybuffer[key] & 0b00000001) {
        return true;
    }
    return false;
}

bool Input::Pressed(unsigned char key) {
    if (keybuffer[key] & 0b00000010) {
        return true;
    }
    return false;
}

bool Input::Released(unsigned char key) {
    if (keybuffer[key] & 0b00000100) {
        return true;
    }
    return false;
}

bool Input::MouseClicked(unsigned char button) {
    if (mousebuffer[button] & 0b00000001) {
        return true;
    }
    return false;
}

bool Input::MousePressed(unsigned char button) {
    if (mousebuffer[button] & 0b00000010) {
        return true;
    }
    return false;
}

bool Input::MouseReleased(unsigned char button) {
    if (mousebuffer[button] & 0b00000100) {
        return true;
    }
    return false;
}
void Input::GetInput() {
    CheckEvents();
    if (Pressed(SDLK_TAB) || Pressed(SDLK_ESCAPE)) {
        GAME_ENGINE->running = false;
    }
    if (Clicked(SDLK_RETURN)) {
        /*
        if (!music_playing) {
            Mix_PlayMusic(music, 0);
            music_playing = true;
            std::cout << "W";
        } else {
            Mix_HaltMusic();
            music_playing = false;
            std::cout << "\n\n";
        }
        */
        // ctx->getRenderWindow()->setHidden(false);
    }
    if (MouseClicked(SDL_BUTTON_MIDDLE)) {

        // ctx->getRenderWindow()->resize(screenW, screenH);
        // cam->setAspectRatio(Ogre::Real((float)ctx->getRenderWindow()->getWidth()
        // / (float)ctx->getRenderWindow()->getHeight()));

        // ctx->getRenderWindow()->set

        // sdl_window = (SDL_Window*)(void*)ctx->getRenderWindow();
        // SDL_WarpMouseInWindow(sdl_window, 800 / 2, 800 / 2);

        // SDL_WarpMouseInWindow(window, 800 / 2, 800 / 2);
        // SDL_GetMouseState(&mX, &mY);
        ////mX = screenw / 2;
        ////mY = screenh / 2;
        // SDL_ShowCursor(false);
        /*
        my = mouseY;
        mx = mouseX;
        */
    }
    if (MousePressed(SDL_BUTTON_MIDDLE)) {

        // screenW = 1920;
        // screenH = 1080;
        ////ctx->getRenderWindow()->resize(screenW, screenH);
        ////ctx->getRenderWindow()->setHidden(true);
        // std::cout << ctx->getRenderWindow()->getWidth();

        // camera_orientation = glm::vec4((float)camNode->getOrientation().x,
        // (float)camNode->getOrientation().y,
        // (float)camNode->getOrientation().z,
        // (float)camNode->getOrientation().w);

        SDL_GetMouseState(&mouseX,
                          &mouseY); //"bug" in SDL (?) means that I have to call it again
                                    // to get
                                    // the correct value after setting it the loop before
        // std::cout << mX << " " << mY << "\n";
        /*
        float rotX = -2.0 * (float)(mouseX - mx) / 500; // / window->getWidth();
        float rotY = -2.0 * (float)(mouseY - my) / 500; // / window->getHeight();
        mx = mouseX;
        my = mouseY;

        cam_node->rotate(Ogre::Quaternion(Ogre::Radian(rotX), Ogre::Vector3::UNIT_Y), Ogre::Node::TS_PARENT);
        cam_node->rotate(Ogre::Quaternion(Ogre::Radian(rotY), Ogre::Vector3::UNIT_X), Ogre::Node::TS_LOCAL);
        */

        // glm::vec3 new_orientation = glm::rotate(camera.orientation,
        // glm::radians(-rotX), glm::normalize(glm::cross(camera.orientation,
        // camera.up)));

        // if (!((glm::angle(new_orientation, camera.up) <= glm::radians(5.0f)
        // || (glm::angle(new_orientation, -camera.up) <= glm::radians(5.0f)))))
        // {
        //     camera.orientation = new_orientation;
        // }

        // camera.orientation = glm::rotate(camera.orientation,
        // glm::radians(-rotY), camera.up); SDL_WarpMouseInWindow(window,
        // screenw / 2, screenh / 2); SDL_GetMouseState(&mX, &mY);

        // camNode->yaw(Ogre::Radian(rotX));
        // camNode->pitch(Ogre::Radian(rotY));
    }
    /*
    if (Pressed(SDLK_UP) || Pressed(SDLK_w)) {
        cam_node->translate(Ogre::Vector3(0.0f, 0.0f, -camspeed), Ogre::Node::TS_LOCAL);
    }
    if (Pressed(SDLK_DOWN) || Pressed(SDLK_s)) {
        cam_node->translate(Ogre::Vector3(0.0f, 0.0f, camspeed), Ogre::Node::TS_LOCAL);
    }
    if (Pressed(SDLK_LEFT) || Pressed(SDLK_a)) {
        cam_node->translate(Ogre::Vector3(-camspeed, 0.0f, 0.0f), Ogre::Node::TS_LOCAL);
    }
    if (Pressed(SDLK_RIGHT) || Pressed(SDLK_d)) {
        cam_node->translate(Ogre::Vector3(camspeed, 0.0f, 0.0f), Ogre::Node::TS_LOCAL);
    }
    if (Pressed(SDLK_SPACE)) {
        cam_node->translate(Ogre::Vector3(0.0f, camspeed, 0.0f), Ogre::Node::TS_PARENT);
    }
    if (Pressed(SDLK_LSHIFT)) {
        cam_node->translate(Ogre::Vector3(0.0f, -camspeed, 0.0f), Ogre::Node::TS_PARENT);
    }
    if (Pressed(SDLK_q)) {
        cam_node->rotate(Ogre::Quaternion(Ogre::Radian(rotspeed), Ogre::Vector3::UNIT_Y), Ogre::Node::TS_PARENT);
    }
    if (Pressed(SDLK_e)) {
        cam_node->rotate(Ogre::Quaternion(Ogre::Radian(-rotspeed), Ogre::Vector3::UNIT_Y), Ogre::Node::TS_PARENT);
    }
    */
}

void Input::CheckEvents() {
    SDL_GetMouseState(&mouseX, &mouseY); // Get mouse positions
    SDL_Event mainevent;
    for (int a = 0; a < 256; a++) {
        keybuffer[a] = (keybuffer[a] & 0b11111010);
        mousebuffer[a] = (mousebuffer[a] & 0b11111010);
        // if (*SDL_GetKeyboardState(&a)) {
        //     //held down
        // }
        // else {
        //     keybuffer[a] = (keybuffer[a] & 0b11111101);
        //     keybuffer[(unsigned char)mainevent.key.keysym.sym] |= 0b00000100;
        // }
    }
    while (SDL_PollEvent(&mainevent)) {   // poll new event as long as we have a new event
        if (mainevent.type == SDL_QUIT) { // pressed red X
            GAME_ENGINE->running = false;
        }
        if (mainevent.type == SDL_KEYDOWN) {
            keybuffer[(unsigned char)mainevent.key.keysym.sym] |= 0b00000011;
        }
        if (mainevent.type == SDL_KEYUP) {
            keybuffer[(unsigned char)mainevent.key.keysym.sym] &= 0b11111101;
            keybuffer[(unsigned char)mainevent.key.keysym.sym] |= 0b00000100;
        }
        if (mainevent.type == SDL_MOUSEBUTTONDOWN) {
            mousebuffer[(unsigned char)mainevent.button.button] |= 0b00000011;
        }
        if (mainevent.type == SDL_MOUSEBUTTONUP) {
            mousebuffer[(unsigned char)mainevent.button.button] &= 0b11111101;
            mousebuffer[(unsigned char)mainevent.button.button] |= 0b00000100;
        }
        if (mainevent.type == SDL_WINDOWEVENT) {
            if (mainevent.window.event == SDL_WINDOWEVENT_RESIZED) {
                // viewport->setDimensions(0, 0, 1, 1);
                // viewport->setActualDimensions(window->getWidth(), window->getHeight());//does not exist
                GAME_SCENE_M->Resize();
                // Update the aspect ratio of the camera associated with the viewport
                // if (cam) {
                //    cam->setAspectRatio(Ogre::Real(window->getWidth()) / Ogre::Real(window->getHeight()));
                //}
                // std::cout << "Resized window\n";
                // cam->setAspectRatio(Ogre::Real((float)ctx->getRenderWindow()->getWidth()
                // / (float)ctx->getRenderWindow()->getHeight()));
            }
        }
    }
}
