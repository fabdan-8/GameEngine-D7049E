// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level
// directory of this distribution and at https://www.ogre3d.org/licensing.
// SPDX-License-Identifier: MIT

#include "Global.h"
#include "Ogre.h"
#include "OgreApplicationContext.h"

//! [key_handler]
// class KeyHandler : public OgreBites::InputListener {
//   bool keyPressed(const OgreBites::KeyboardEvent &evt) override {
//     if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) {
//       Ogre::Root::getSingleton().queueEndRendering();
//     }
//     //else if (evt.keysym.sym == OgreBites::SDLK_UP) {
//     //    camNode->translate(Ogre::Vector3(0.0f, 1.0f, 0.0f));
//     //}
//     //else if (evt.keysym.sym == OgreBites::SDLK_DOWN) {
//     //    camNode->translate(Ogre::Vector3(0.0f, -1.0f, 0.0f));
//     //}
//     //else if (evt.keysym.sym == OgreBites::SDLK_LEFT) {
//     //    camNode->translate(Ogre::Vector3(-1.0f, 0.0f, 0.0f));
//     //}
//     //else if (evt.keysym.sym == OgreBites::SDLK_RIGHT) {
//     //    camNode->translate(Ogre::Vector3(1.0f, 0.0f, 0.0f));
//     //}
//     return true;
//   }
// };
//! [key_handler]

int main(int argc, char *argv[]) {

    // Ogre::String version =
    // Ogre::StringConverter::toString(OGRE_VERSION_MAJOR) + "." +
    //     Ogre::StringConverter::toString(OGRE_VERSION_MINOR) + "." +
    //     Ogre::StringConverter::toString(OGRE_VERSION_PATCH);

    //// Print the version number to the console
    // std::cout << "Ogre version: " << version << std::endl;
    // Ogre version is 13.6.4

    game.Load();
    game.MainLoop();
    game.Cleanup();
    return 0;

    //! [constructor]
    OgreBites::ApplicationContext ctx("OgreTutorialApp");
    ctx.initApp();
    //! [constructor]

    //! [setup]
    // get a pointer to the already created root
    Ogre::Root *root = ctx.getRoot();
    Ogre::SceneManager *scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator *shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen

    scnMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f,
                                              0.5f)); // does not seem to work...

    Ogre::Light *light = scnMgr->createLight("MainLight");
    // light->setDiffuseColour(Ogre::ColourValue::White);
    // light->setSpecularColour(Ogre::ColourValue::White);
    Ogre::SceneNode *lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(20, 40, -50);
    lightNode->attachObject(light);

    // also need to tell where we are

    Ogre::Camera *cam;
    Ogre::SceneNode *camNode;

    camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
    // camNode->setFixedYawAxis(true, Ogre::Vector3(0, 1, 0));

    // create the camera
    cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 40, 140);

    // and tell it to render into the main window
    ctx.getRenderWindow()->addViewport(cam);

    // finally something to render
    // Ogre::Entity *ent = scnMgr->createEntity("Sinbad.mesh");
    Ogre::Entity *ent = scnMgr->createEntity("skeleton.X"); //"sibenik.mesh"
    // ent->setMaterial()
    Ogre::SceneNode *node = scnMgr->getRootSceneNode()->createChildSceneNode();

    node->setPosition(0, 0, -80);

    node->attachObject(ent);
    //! [setup]

    //! [main]
    // register for input events
    // KeyHandler keyHandler;
    // ctx.addInputListener(&keyHandler);
    //
    // while (true) {
    //    ctx.getRoot()->renderOneFrame();
    //}
    ctx.getRoot()->startRendering();
    ctx.closeApp();
    //! [main]
    return 0;
}
