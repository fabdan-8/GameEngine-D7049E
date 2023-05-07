#include "Game.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <map>
#include <vector>
#include <thread>

#include "Player.h"
#include "Script.h"

extern std::mutex ogre_resource_mut;
extern std::mutex clock_mut;

extern Game game;
extern Scene scene;
extern std::string meshfolder;
extern std::string scriptfolder;
extern std::map<std::string, Script*> scripthandler;
extern std::map<std::string, Mix_Music*> musichandler;

//class KeyHandler : public OgreBites::InputListener {
//    bool keyPressed(const OgreBites::KeyboardEvent &evt) override {
//        game.keybuffer[(unsigned char)evt.keysym.sym] |= 0b00000011;
//        return true;
//    }
//
//    bool keyReleased(const OgreBites::KeyboardEvent &evt) override {
//        game.keybuffer[(unsigned char)evt.keysym.sym] &= 0b11111101;
//        game.keybuffer[(unsigned char)evt.keysym.sym] |= 0b00000100;
//        return true;
//    }
//
//    // bool mouseMoved(const OgreBites::MouseMotionEvent& evt) override {
//
//    //    return true;
//    //}
//
//    // bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) override {
//
//    //    return true;
//    //}
//
//    bool mousePressed(const OgreBites::MouseButtonEvent &evt) override {
//        game.mousebuffer[(unsigned char)evt.button] |= 0b00000011;
//        return true;
//    }
//
//    bool mouseReleased(const OgreBites::MouseButtonEvent &evt) override {
//        game.mousebuffer[(unsigned char)evt.button] &= 0b11111101;
//        game.mousebuffer[(unsigned char)evt.button] |= 0b00000100;
//        return true;
//    }
//};

void Game::Load() {
    std::string name;
    ctx = new OgreBites::ApplicationContext("GameEngine-D7049E");
    // getline(std::cin, name);

    ctx->initApp();
    window = ctx->getRenderWindow();

    // ctx->getRenderWindow()->destroy();
    // ctx->getRenderWindow()->create("GameEngine-D7049E", 1920, 1080, false,
    // NULL); ctx->destroyWindow("GameEngine-D7049E"); getline(std::cin, name);
    // ctx->createWindow("GameEngine-D7049E", 1920, 1080);

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

    // getline(std::cin, name);
    //// Create an Ogre3D window
    // window = root->createRenderWindow("MyWindow", 800, 600, false);
    // getline(std::cin, name);

    // Load Ogre configuration file
    // root->loadConfig("ogre.cfg");
    scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator *shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // attempt to resize the window
    // ctx->getRenderWindow()->destroy();

    // without light we would just get a black screen

    scnMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f)); // works on skeleton

    Ogre::Light *light = scnMgr->createLight("MainLight");
    // light->setDiffuseColour(Ogre::ColourValue::White);
    // light->setSpecularColour(Ogre::ColourValue::White);
    Ogre::SceneNode *lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(20, 40, -50);
    lightNode->attachObject(light);

    // also need to tell where we are
    cam_node = scnMgr->getRootSceneNode()->createChildSceneNode();
    cam_node->setPosition(0, 0, 15);
    cam_node->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
    cam_node->setFixedYawAxis(true, Ogre::Vector3(0, 1, 0)); // so that up is always up

    // create the camera
    cam = scnMgr->createCamera("camera");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    cam_node->attachObject(cam);
    cam_node->setPosition(0, 40, 140);

    //this is the node that we edit
    cam_node_alt = scnMgr->getRootSceneNode()->createChildSceneNode();
    cam_node_alt->setFixedYawAxis(true, Ogre::Vector3(0, 1, 0));
    cam_node_alt->setOrientation(cam_node->getOrientation());
    cam_node_alt->setPosition(cam_node->getPosition());
    //cam_node_alt = cam_node;

    // and tell it to render into the main window
    // ctx->getRenderWindow()->addViewport(cam);
    viewport = window->addViewport(cam);

    // Ogre::Root::getSingleton().getRenderSystem()->_setCullingMode(Ogre::CullingMode::CULL_CLOCKWISE);
    //Ogre::Root::getSingleton().getRenderSystem()->_setCullingMode(Ogre::CullingMode::CULL_CLOCKWISE);

    // if (ctx->getRenderWindow()->isActive()) {
    //     getline(std::cin, name);
    // }
    // ctx->getRenderWindow()->getCustomAttribute("SDL_Window", window);//does
    // not work

    // KeyHandler keyHandler;
    // ctx->addInputListener(&keyHandler);
    // getline(std::cin, name);

    scriptfolder = "ArgumentsGameFolder/data/scripts/";
    
    //ScriptReader("button1script.txt");
    //ScriptReader("button1script.txt");
    //getline(std::cin, name);

    meshfolder = "ArgumentsGameFolder/data/mesh/";
    Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();

    // Add the new resource location
    rgm.addResourceLocation(meshfolder, "FileSystem");

    //scene.AddEntity("skeleton");
    ////scene.AddEntity("sibenik.mesh");
    //// finally something to render
    //for (int a = 0; a < 10; a++) { // add 100 skeletons
    //    for (int b = 0; b < 10; b++) {
    //        if (rand() % 2 == 0) {
    //            std::string skeleton_name = scene.AddEntity("skeleton", 0.1f, -50.0f + a * 10 + ((float)(rand() % 10) - 4.5f) / 3, 0.0f, -80.0f - b * 10 + ((float)(rand() % 10) - 4.5f) / 3);
    //        }
    //        else {
    //            std::string orc_name = scene.AddEntity("Orc", 0.1f, -50.0f + a * 10 + ((float)(rand() % 10) - 4.5f) / 3, 0.0f, -80.0f - b * 10 + ((float)(rand() % 10) - 4.5f) / 3);
    //        }
    //    }
    //}
    scene.AddEntity("skeleton", 1, 0, 0, 0);
    scene.AddEntity("fern", 1, 50, 0, 0);
    scene.AddEntity("Desiccated Priest", 1, 0, 0, 200);
    scene.AddEntity("Goblin", 1, 50, 0, 50);
    scene.AddEntity("Orc", 1, 100, 0, 50);
    scene.AddEntity("crypt", 1, -400, 0, 100);
    scene.AddEntity("statuewall", 1, 0, 0, 300);
    scene.AddEntity("skeleton", 1, -50, 0, 0);
    scene.AddEntity("skeleton", 1, 0, 0, -100);
    scene.AddEntity("skeleton", 0.2, -50, 0, -50);

    //scene.AddImage("Skeleton.bmp", 50.0f, 10.0f, -100.0f, 40.0f, 40.0f);
    // std::cout << "---------------------\n";
    // std::cout << skeleton_name << "\n";
    // std::string town_name = scene.AddEntity("sibenik.mesh");
    // std::cout << "---------------------\n";
    // std::cout << town_name << "\n";

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
    // void* window_data = nullptr;

    // HWND wind;
    // ctx->getRenderWindow()->getCustomAttribute("WINDOW", wind);
    // getline(std::cin, name);
    // sdl_window = SDL_CreateWindowFrom(wind);

    // sdl_window = SDL_CreateWindow("SDL window", SDL_WINDOWPOS_CENTERED,
    // SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_OPENGL); if (!sdl_window)
    // {
    //     std::cout << "Couldn't make the SDL window\n";
    //     return;
    // }

    // Load music
    //Mix_Music* music = Mix_LoadMUS("Spinnin.mp3");
    ////if (!music) {
    ////    return;
    ////}
    //musichandler["Spinnin.mp3"] = music;

    Mix_VolumeMusic(48); // set volume
    running = true;//this is the only time it is OK to access game.running directly

    ScriptReader("startup.txt");//run the startup script

    return;
}

void Game::MainLoop() {
    clock_t last_tick = clock();
    clock_t last_input = clock();
    clock_t current_time;

    //launch the separate thread(s)
    //std::thread input_thread(&Game::InputThread, this);//needs many mutexes to work
    //input_thread.detach();

    //std::thread render_thread(&Game::RenderThread, this);//needs many mutexes to work
    //render_thread.detach();

    while (IsRunning()) {
        clock_mut.lock();
        current_time = clock();
        clock_mut.unlock();
        Render();                                     // no fps cap.
        if (current_time >= last_tick + tick_speed) { // update once per tick_speed milliseconds
            last_tick += tick_speed;
            if (current_time > last_tick + tick_speed) { // running (more than) one whole tick behind
                // do something, you are lagging behind.
            }
            Update();
        }
        //the following does not really work, you need fast inputs
        //CheckEvents();
        //if (current_time >= last_input + input_speed) { // update once per tick_speed milliseconds
        //    last_input += input_speed;
        //    if (current_time > last_input + input_speed) { // running (more than) one whole tick behind
        //        // do something, you are lagging behind.
        //        //for (int a = 0; a < (current_time - last_input - input_speed) / input_speed; a++) {
        //        //    Input();
        //        //}
        //    }
        //    CheckEvents();
        //    Input();
        //    ApplyChangesFromInput();
        //}
        CheckEvents();
        Input();
        ApplyChangesFromInput();
        // Connection(); //check internet communication, this should maybe be
        // done on a separate thread
    }

    //join the threads again
    //input_thread.join();
}

void Game::Cleanup() {
    // ctx->closeApp();
    // delete ctx;
    scene.Cleanup();

    delete root;

    for (auto const& script : scripthandler) {
        delete script.second;
    }

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

void Game::ScriptReader(std::string filename) {
    Script* script = nullptr;
    if (scripthandler.find(filename) != scripthandler.end()) {//script already exists, just read it
        script = scripthandler[filename];
        //std::cout << "script already exists\n";
    }
    else {//script does not exist, first make it
        std::ifstream file;
        file.open(scriptfolder + filename);
        if (!file.is_open()) {
            //could not run script
            //std::cout << "could not find script '" << scriptfolder + filename << "'\n";
            return;
        }

        script = new Script;//deleted in game.Cleanup()
        scripthandler[filename] = script;//add script to scripthandler map
        //std::cout << "making script\n";
        //parse file, make script
        std::string buf;
        int iter = 0;
        while (file.good()) {//loop over all lines in the script file
            //std::cout << "command\n";
            getline(file, buf);
            buf += ";";//add ';' to be able to find end easier
            size_t div = buf.find_first_of(" ");//find first space
            if (div > 0 && div != std::string::npos && buf[0] != '#') {//also check if it is a comment
                script->command.push_back(buf.substr(0, div));//command name
                std::vector<Variable> var_vector;
                script->argument.push_back(var_vector);//argument vector
                bool find_args = true;
                while (find_args) {//loop over all arguments
                    //std::cout << "argument:\n";
                    if (buf.size() > div + 1) {
                        buf = buf.substr(div + 1);//remove previous part of string
                        div = buf.find_first_of(",;");//find next argument
                    }
                    else {
                        div = 0;//will result in find_args = false;
                    }
                    if (div > 0 && div != std::string::npos) {
                        std::string arg = buf.substr(0, div);//arg is the whole argument, including the equals

                        size_t equals = buf.find_first_of("=");//find the equals sign

                        if (equals > 0 && equals != std::string::npos && buf.size() > equals + 1) {
                            Variable var;
                            var.name = buf.substr(0, equals);//name before the equals
                            var.content = buf.substr(equals + 1, div - var.name.size() - 1);//content after the equals
                            //std::cout << "name: '" << var.name << "'\n";
                            //std::cout << "content: '" << var.content << "'\n";
                            if (var.content.size() > 1 && var.content[0] == '\"' && var.content[var.content.size() - 1] == '\"') {//is string
                                var.content = var.content.substr(1, var.content.size() - 2);//remove " "-signs
                                //std::cout << "content changed to: '" << var.content << "'\n";
                            }
                            else {//is value
                                var.value = atof(var.content.c_str());//convert the value from string to numerical value
                                //std::cout << "value changed to: '" << var.value << "'\n";
                                var.content = "$value";
                            }
                            script->argument.back().push_back(var);//add to argument vector
                        }
                        else {//no equals sign, this is a single line argument

                            Variable var;
                            var.name = "oneline";
                            var.content = buf.substr(0, buf.size() - 1);//remove ';' that was added previously
                            //std::cout << "name: '" << var.name << "'\n";
                            //std::cout << "content: '" << var.content << "'\n";
                            script->argument.back().push_back(var);//add to argument vector

                            find_args = false;//also break since there is only one argument
                        }
                    }
                    else {//can't find next argument
                        find_args = false;
                    }
                }
            }
            iter++;
        }

        file.close();
    }
    if (script) {
        //std::cout << "running script\n";
        script->Read();
    }
    //std::cout << "all done\n";
}

bool Game::IsRunning() {
    bool ret;
    running_mut.lock();
    ret = running;
    running_mut.unlock();
    return ret;
}

void Game::Shutdown() {
    running_mut.lock();
    running = false;
    running_mut.unlock();
}

void Game::Render() {
    // ctx->getRoot()->renderOneFrame();
    //std::cout << "n";
    ogre_resource_mut.lock();
    root->renderOneFrame();
    ogre_resource_mut.unlock();
    //SDL_Delay(1);
    // SDL_GL_SwapWindow(sdl_window);
}

void Game::CheckEvents() {
    SDL_GetMouseState(&mouseX, &mouseY); // Get mouse positions
    for (int a = 0; a < 256; a++) {
        if (keybuffer[a] & 0b00000100) {//fail safe
            keybuffer[a] & 0b11111101;
        }
        if (mousebuffer[a] & 0b00000100) {//fail safe;
            mousebuffer[a] & 0b11111101;
        }
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
            Shutdown();
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
                //viewport->setDimensions(0, 0, 1, 1);
                //viewport->setActualDimensions(window->getWidth(), window->getHeight());//does not exist
                window->resize(window->getWidth(), window->getHeight());
                // Update the aspect ratio of the camera associated with the viewport
                //if (cam) {
                //    cam->setAspectRatio(Ogre::Real(window->getWidth()) / Ogre::Real(window->getHeight()));
                //}
                // std::cout << "Resized window\n";
                // cam->setAspectRatio(Ogre::Real((float)ctx->getRenderWindow()->getWidth()
                // / (float)ctx->getRenderWindow()->getHeight()));
            }
        }
    }
}

void Game::Input() {
    //CheckEvents();//done separately as well
    if (Pressed(SDLK_TAB)) {
        Shutdown();
    }
    if (Clicked(SDLK_RETURN)) {
        //if (!music_playing) {
        //    Mix_PlayMusic(music, 0);
        //    music_playing = true;
        //    //std::cout << "W";
        //} else {
        //    Mix_HaltMusic();
        //    music_playing = false;
        //    //std::cout << "\n\n";
        //}
        //// ctx->getRenderWindow()->setHidden(false);
    }
    if (MouseClicked(SDL_BUTTON_LEFT)) {
        scene.Update();
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
        my = mouseY;
        mx = mouseX;
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

        //SDL_GetMouseState(&mouseX, &mouseY);
        // std::cout << mX << " " << mY << "\n";
        float rotX = -3.0 * (float)(mouseX - mx) / window->getHeight();//500 (-3.0, getHeight/-5.0, getWidth)
        float rotY = -3.0 * (float)(mouseY - my) / window->getHeight();//500
        mx = mouseX;
        my = mouseY;
        cam_node_alt->rotate(Ogre::Quaternion(Ogre::Radian(rotX), Ogre::Vector3::UNIT_Y), Ogre::Node::TS_PARENT);
        cam_node_alt->rotate(Ogre::Quaternion(Ogre::Radian(rotY), Ogre::Vector3::UNIT_X), Ogre::Node::TS_LOCAL);

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
    if (Pressed(SDLK_UP) || Pressed(SDLK_w)) {
        cam_node_alt->translate(Ogre::Vector3(0.0f, 0.0f, -camspeed), Ogre::Node::TS_LOCAL);
    }
    if (Pressed(SDLK_DOWN) || Pressed(SDLK_s)) {
        cam_node_alt->translate(Ogre::Vector3(0.0f, 0.0f, camspeed), Ogre::Node::TS_LOCAL);
    }
    if (Pressed(SDLK_LEFT) || Pressed(SDLK_a)) {
        cam_node_alt->translate(Ogre::Vector3(-camspeed, 0.0f, 0.0f), Ogre::Node::TS_LOCAL);
    }
    if (Pressed(SDLK_RIGHT) || Pressed(SDLK_d)) {
        cam_node_alt->translate(Ogre::Vector3(camspeed, 0.0f, 0.0f), Ogre::Node::TS_LOCAL);
    }
    if (Pressed(SDLK_SPACE)) {
        cam_node_alt->translate(Ogre::Vector3(0.0f, camspeed, 0.0f), Ogre::Node::TS_PARENT);
    }
    if (Pressed(SDLK_LSHIFT)) {
        cam_node_alt->translate(Ogre::Vector3(0.0f, -camspeed, 0.0f), Ogre::Node::TS_PARENT);
    }
    if (Pressed(SDLK_q)) {
        cam_node_alt->rotate(Ogre::Quaternion(Ogre::Radian(rotspeed), Ogre::Vector3::UNIT_Y), Ogre::Node::TS_PARENT);
    }
    if (Pressed(SDLK_e)) {
        cam_node_alt->rotate(Ogre::Quaternion(Ogre::Radian(-rotspeed), Ogre::Vector3::UNIT_Y), Ogre::Node::TS_PARENT);
    }
}

void Game::ApplyChangesFromInput() {
    //std::cout << "a";
    ogre_resource_mut.lock();
    //std::cout << "b";
    cam_node->setOrientation(cam_node_alt->getOrientation());
    cam_node->setPosition(cam_node_alt->getPosition());
    //std::cout << "c";
    ogre_resource_mut.unlock();
    //std::cout << "d";
}

void Game::Update() {
    scene.Update();
    //if (music_playing) {
    //    rot += 0.05;
    //    if (rot >= M_PI * 2.0) {
    //        rot = rot - M_PI * 2.0;
    //    }
    //    std::cout << "e";
    //    // camNode->translate(Ogre::Vector3(0.0f, 1.0f, 0.0f));
    //    cam_node->setPosition(0.0 + 200.0 * sin(rot), 40.0, 0.0 + 200.0 * cos(rot));
    //    cam_node->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);
    //    // camNode->roll(Ogre::Radian(0), Ogre::Node::TS_PARENT);
    //}
}

void Game::InputThread() {
    clock_mut.lock();
    clock_t last_input = clock();
    clock_mut.unlock();
    clock_t current_time;
    while (ThreadIsRunning()) {
        //CheckEvents();
        //Input();
        //ApplyChangesFromInput();
        std::cout << "g";
        clock_mut.lock();
        current_time = clock();
        clock_mut.unlock();
        //CheckEvents();
        if (current_time >= last_input + input_speed) { // update once per tick_speed milliseconds
            last_input += input_speed;
            if (current_time > last_input + input_speed) { // running (more than) one whole tick behind
                // do something, you are lagging behind.
                //for (int a = 0; a < (current_time - last_input - input_speed) / input_speed; a++) {
                //    CheckEvents();
                //    Input();
                //}
            }
            CheckEvents();
            Input();
            ApplyChangesFromInput();
        }
    }
}

void Game::RenderThread() {
    while (ThreadIsRunning()) {
        //std::cout << "a";
        Render();
    }
}

bool Game::ThreadIsRunning() {
    bool ret;
    running_mut.lock();
    ret = running;
    running_mut.unlock();
    return ret;
}