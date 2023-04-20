#include "Game.h"

#ifdef _WIN32
    #include <Windows.h>
#endif

#include <iostream>
#include <string>
#include <time.h>

#include "Player.h"

extern Game game;

class KeyHandler : public OgreBites::InputListener {
    bool keyPressed ( const OgreBites::KeyboardEvent &evt ) override
    {
        game.keybuffer[ ( unsigned char ) evt.keysym.sym ] |= 0b00000011;
        return true;
    }

    bool keyReleased ( const OgreBites::KeyboardEvent &evt ) override
    {
        game.keybuffer[ ( unsigned char ) evt.keysym.sym ] &= 0b11111101;
        game.keybuffer[ ( unsigned char ) evt.keysym.sym ] |= 0b00000100;
        return true;
    }

    bool mouseMoved ( const OgreBites::MouseMotionEvent &evt ) override
    {

        return true;
    }

    bool mouseWheelRolled ( const OgreBites::MouseWheelEvent &evt ) override
    {

        return true;
    }

    bool mousePressed ( const OgreBites::MouseButtonEvent &evt ) override
    {
        game.mousebuffer[ ( unsigned char ) evt.button ] |= 0b00000011;
        return true;
    }

    bool mouseReleased ( const OgreBites::MouseButtonEvent &evt ) override
    {
        game.mousebuffer[ ( unsigned char ) evt.button ] &= 0b11111101;
        game.mousebuffer[ ( unsigned char ) evt.button ] |= 0b00000100;
        return true;
    }
};

void Game::Load ( )
{
    std::string name;
    ctx = new OgreBites::ApplicationContext ( "GameEngine-D7049E" );
    // getline(std::cin, name);

    ctx->initApp ( );
    window = ctx->getRenderWindow ( );

    // ctx->getRenderWindow()->destroy();
    // ctx->getRenderWindow()->create("GameEngine-D7049E", 1920, 1080, false,
    // NULL); ctx->destroyWindow("GameEngine-D7049E"); getline(std::cin, name);
    // ctx->createWindow("GameEngine-D7049E", 1920, 1080);

    //! [setup]
    // get a pointer to the already created root
    root = ctx->getRoot ( );
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
    scnMgr = root->createSceneManager ( );

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator *shadergen
            = Ogre::RTShader::ShaderGenerator::getSingletonPtr ( );
    shadergen->addSceneManager ( scnMgr );

    // attempt to resize the window
    // ctx->getRenderWindow()->destroy();

    // without light we would just get a black screen

    scnMgr->setAmbientLight ( Ogre::ColourValue ( 0.5f, 0.5f, 0.5f )
    ); // works on skeleton

    Ogre::Light *light = scnMgr->createLight ( "MainLight" );
    // light->setDiffuseColour(Ogre::ColourValue::White);
    // light->setSpecularColour(Ogre::ColourValue::White);
    Ogre::SceneNode *lightNode
            = scnMgr->getRootSceneNode ( )->createChildSceneNode ( );
    lightNode->setPosition ( 20, 40, -50 );
    lightNode->attachObject ( light );

    // also need to tell where we are
    camNode = scnMgr->getRootSceneNode ( )->createChildSceneNode ( );
    camNode->setPosition ( 0, 0, 15 );
    camNode->lookAt ( Ogre::Vector3 ( 0, 0, -1 ), Ogre::Node::TS_PARENT );
    camNode->setFixedYawAxis (
            true,
            Ogre::Vector3 ( 0, 1, 0 )
    ); // so that up is always up

    // create the camera
    cam = scnMgr->createCamera ( "camera" );
    cam->setNearClipDistance ( 5 ); // specific to this sample
    cam->setAutoAspectRatio ( true );
    camNode->attachObject ( cam );
    camNode->setPosition ( 0, 40, 140 );

    // and tell it to render into the main window
    // ctx->getRenderWindow()->addViewport(cam);
    window->addViewport ( cam );

    // if (ctx->getRenderWindow()->isActive()) {
    //     getline(std::cin, name);
    // }
    // ctx->getRenderWindow()->getCustomAttribute("SDL_Window", window);//does
    // not work

    // KeyHandler keyHandler;
    // ctx->addInputListener(&keyHandler);
    scene.AddEntity ( "skeleton.X" );
    // finally something to render
    // for (int a = 0; a < 10; a++) {//add 100 skeletons
    //    for (int b = 0; b < 10; b++) {
    //        std::string skeleton_name = scene.AddEntity("skeleton.X", 0.1f,
    //        -50.0f + a * 10 + ((float)(rand() % 10) - 4.5f) / 3, 0.0f, -80.0f
    //        -b
    //        * 10 + ((float)(rand() % 10) - 4.5f) / 3);
    //    }
    //}
    // std::cout << "---------------------\n";
    // std::cout << skeleton_name << "\n";
    // std::string town_name = scene.AddEntity("sibenik.mesh");
    // std::cout << "---------------------\n";
    // std::cout << town_name << "\n";

    //! [setup]

    if ( SDL_Init ( SDL_INIT_EVERYTHING ) != 0 )
    {
        std::cout << "SDL failed\n";
        return;
    }
    if ( SDLNet_Init ( ) != 0 )
    {
        std::cout << "SDL Net failed\n";
        return;
    }
    if ( Mix_OpenAudio ( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0 )
    {
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
    music = Mix_LoadMUS ( "Spinnin.mp3" );
    if ( !music )
    {
        return;
    }
    Mix_VolumeMusic ( 48 ); // set volume
    running = true;

    return;
}

void Game::MainLoop ( )
{
    clock_t last_tick = clock ( );
    clock_t current_time;
    while ( running )
    {
        current_time = clock ( );
        Render ( ); // no fps cap.
        if ( current_time >= last_tick + tick_speed )
        { // update once per tick_speed milliseconds
            last_tick += tick_speed;
            if ( current_time > last_tick + tick_speed )
            { // running (more than) one whole tick behind
              // do something, you are lagging behind.
            }
            Update ( );
        }
        Input ( ); // take inputs as often as possible
        // Connection(); //check internet communication, this should maybe be
        // done on a separate thread
    }
}

void Game::Cleanup ( )
{
    // ctx->closeApp();
    // delete ctx;
    delete root;

    SDLNet_Quit ( );
    Mix_CloseAudio ( );
    IMG_Quit ( );
    SDL_Quit ( );
}

bool Game::Clicked ( unsigned char key )
{
    if ( keybuffer[ key ] & 0b00000001 )
    {
        return true;
    }
    return false;
}

bool Game::Pressed ( unsigned char key )
{
    if ( keybuffer[ key ] & 0b00000010 )
    {
        return true;
    }
    return false;
}

bool Game::Released ( unsigned char key )
{
    if ( keybuffer[ key ] & 0b00000100 )
    {
        return true;
    }
    return false;
}

bool Game::MouseClicked ( unsigned char button )
{
    if ( mousebuffer[ button ] & 0b00000001 )
    {
        return true;
    }
    return false;
}

bool Game::MousePressed ( unsigned char button )
{
    if ( mousebuffer[ button ] & 0b00000010 )
    {
        return true;
    }
    return false;
}

bool Game::MouseReleased ( unsigned char button )
{
    if ( mousebuffer[ button ] & 0b00000100 )
    {
        return true;
    }
    return false;
}

void Game::Render ( )
{
    // ctx->getRoot()->renderOneFrame();
    root->renderOneFrame ( );
    // SDL_GL_SwapWindow(sdl_window);
}

void Game::Input ( )
{
    CheckEvents ( );
    if ( Pressed ( SDLK_TAB ) )
    {
        running = false;
    }
    if ( Clicked ( SDLK_RETURN ) )
    {
        if ( !music_playing )
        {
            Mix_PlayMusic ( music, 0 );
            music_playing = true;
            std::cout << "W";
        }
        else
        {
            Mix_HaltMusic ( );
            music_playing = false;
            std::cout << "\n\n";
        }
        // ctx->getRenderWindow()->setHidden(false);
    }
    if ( MouseClicked ( SDL_BUTTON_MIDDLE ) )
    {

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
    if ( MousePressed ( SDL_BUTTON_MIDDLE ) )
    {

        // screenW = 1920;
        // screenH = 1080;
        ////ctx->getRenderWindow()->resize(screenW, screenH);
        ////ctx->getRenderWindow()->setHidden(true);
        // std::cout << ctx->getRenderWindow()->getWidth();

        // camera_orientation = glm::vec4((float)camNode->getOrientation().x,
        // (float)camNode->getOrientation().y,
        // (float)camNode->getOrientation().z,
        // (float)camNode->getOrientation().w);

        SDL_GetMouseState (
                &mouseX,
                &mouseY
        ); //"bug" in SDL (?) means that I have to call it again
           // to get
           // the correct value after setting it the loop before
        // std::cout << mX << " " << mY << "\n";
        float rotX = -2.0 * ( float ) ( mouseX - mx ) / window->getWidth ( );
        float rotY = -2.0 * ( float ) ( mouseY - my ) / window->getHeight ( );
        mx         = mouseX;
        my         = mouseY;

        camNode->rotate (
                Ogre::Quaternion (
                        Ogre::Radian ( rotX ),
                        Ogre::Vector3::UNIT_Y
                ),
                Ogre::Node::TS_PARENT
        );
        camNode->rotate (
                Ogre::Quaternion (
                        Ogre::Radian ( rotY ),
                        Ogre::Vector3::UNIT_X
                ),
                Ogre::Node::TS_LOCAL
        );

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
    if ( Pressed ( SDLK_UP ) || Pressed ( SDLK_w ) )
    {
        camNode->translate (
                Ogre::Vector3 ( 0.0f, 0.0f, -camspeed ),
                Ogre::Node::TS_LOCAL
        );
    }
    if ( Pressed ( SDLK_DOWN ) || Pressed ( SDLK_s ) )
    {
        camNode->translate (
                Ogre::Vector3 ( 0.0f, 0.0f, camspeed ),
                Ogre::Node::TS_LOCAL
        );
    }
    if ( Pressed ( SDLK_LEFT ) || Pressed ( SDLK_a ) )
    {
        camNode->translate (
                Ogre::Vector3 ( -camspeed, 0.0f, 0.0f ),
                Ogre::Node::TS_LOCAL
        );
    }
    if ( Pressed ( SDLK_RIGHT ) || Pressed ( SDLK_d ) )
    {
        camNode->translate (
                Ogre::Vector3 ( camspeed, 0.0f, 0.0f ),
                Ogre::Node::TS_LOCAL
        );
    }
    if ( Pressed ( SDLK_SPACE ) )
    {
        camNode->translate (
                Ogre::Vector3 ( 0.0f, camspeed, 0.0f ),
                Ogre::Node::TS_PARENT
        );
    }
    if ( Pressed ( SDLK_LSHIFT ) )
    {
        camNode->translate (
                Ogre::Vector3 ( 0.0f, -camspeed, 0.0f ),
                Ogre::Node::TS_PARENT
        );
    }
    if ( Pressed ( SDLK_q ) )
    {
        camNode->rotate (
                Ogre::Quaternion (
                        Ogre::Radian ( rotspeed ),
                        Ogre::Vector3::UNIT_Y
                ),
                Ogre::Node::TS_PARENT
        );
    }
    if ( Pressed ( SDLK_e ) )
    {
        camNode->rotate (
                Ogre::Quaternion (
                        Ogre::Radian ( -rotspeed ),
                        Ogre::Vector3::UNIT_Y
                ),
                Ogre::Node::TS_PARENT
        );
    }
}

void Game::Update ( )
{
    if ( music_playing )
    {
        rot += 0.05;
        if ( rot >= M_PI * 2.0 )
        {
            rot = rot - M_PI * 2.0;
        }
        std::cout << "e";
        // camNode->translate(Ogre::Vector3(0.0f, 1.0f, 0.0f));
        camNode->setPosition (
                0.0 + 200.0 * sin ( rot ),
                40.0,
                0.0 + 200.0 * cos ( rot )
        );
        camNode->lookAt ( Ogre::Vector3 ( 0, 0, 0 ), Ogre::Node::TS_PARENT );
        // camNode->roll(Ogre::Radian(0), Ogre::Node::TS_PARENT);
    }
}

void Game::CheckEvents ( )
{
    SDL_GetMouseState ( &mouseX, &mouseY ); // Get mouse positions
    for ( int a = 0; a < 256; a++ )
    {
        keybuffer[ a ]   = ( keybuffer[ a ] & 0b11111010 );
        mousebuffer[ a ] = ( mousebuffer[ a ] & 0b11111010 );
        // if (*SDL_GetKeyboardState(&a)) {
        //     //held down
        // }
        // else {
        //     keybuffer[a] = (keybuffer[a] & 0b11111101);
        //     keybuffer[(unsigned char)mainevent.key.keysym.sym] |= 0b00000100;
        // }
    }
    while ( SDL_PollEvent ( &mainevent ) )
    { // poll new event as long as we have a new event
        if ( mainevent.type == SDL_QUIT )
        { // pressed red X
            running = false;
        }
        else if ( mainevent.type == SDL_KEYDOWN )
        {
            keybuffer[ ( unsigned char ) mainevent.key.keysym.sym ]
                    |= 0b00000011;
        }
        else if ( mainevent.type == SDL_KEYUP )
        {
            keybuffer[ ( unsigned char ) mainevent.key.keysym.sym ]
                    &= 0b11111101;
            keybuffer[ ( unsigned char ) mainevent.key.keysym.sym ]
                    |= 0b00000100;
        }
        else if ( mainevent.type == SDL_MOUSEBUTTONDOWN )
        {
            mousebuffer[ ( unsigned char ) mainevent.button.button ]
                    |= 0b00000011;
        }
        else if ( mainevent.type == SDL_MOUSEBUTTONUP )
        {
            mousebuffer[ ( unsigned char ) mainevent.button.button ]
                    &= 0b11111101;
            mousebuffer[ ( unsigned char ) mainevent.button.button ]
                    |= 0b00000100;
        }
    }
}
