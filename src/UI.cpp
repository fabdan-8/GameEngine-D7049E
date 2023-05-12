#include "UI.h"

#include "Game.h"

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreOverlay.h"
#include "OgreOverlayManager.h"

extern Game game;

void UI::Load() {
    // create material and texture
    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MyImageMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().load("Skeleton.bmp", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    material->getTechnique(0)->getPass(0)->createTextureUnitState()->setTextureName("Skeleton.bmp");

    // create overlay container and element
    //Ogre::Overlay* container = new Ogre::Overlay;
    container = (Ogre::OverlayContainer*)(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "MyImageContainer"));//sus
    element = Ogre::OverlayManager::getSingleton().createOverlayElement("Image", "MyImageElement");
    element->setMaterialName("MyImageMaterial");
    container->addChild(element);

    // set position and size of overlay container and element
    container->setPosition(100, 100);
    container->setDimensions(200, 200);
    element->setPosition(0, 0);
    element->setDimensions(200, 200);

    // show overlay container
    Ogre::Overlay* overlay = Ogre::OverlayManager::getSingleton().create("MyOverlay");
    overlay->add2D(container);
    overlay->show();
}

void UI::Update() {
    Ogre::Camera* camera = game.GetCamera();
    Ogre::Viewport* viewport = camera->getViewport();
    Ogre::Real screenX = viewport->getActualWidth() * 0.5f;
    Ogre::Real screenY = viewport->getActualHeight() * 0.5f;
    container->setPosition(screenX - 100, screenY - 100);
}