#include "UI.h"

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreFontManager.h"
#include <algorithm>


//Create a panel
Ogre::OverlayContainer* UI::createPanel(std::string panel_name, float position_x, float position_y, float height, float width, std::string material_name) { 
    Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
    //Create a panel
    Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", panel_name));
    panel->setMetricsMode(Ogre::GMM_PIXELS);
    panel->setPosition(position_x, position_y); 
    panel->setDimensions(height, width);
    //Optional background material
    panel->setMaterialName(material_name); 
    return panel;
}

//Create an overlay
Ogre::Overlay* UI::createOverlay(std::string overlay_name) {
    return overlayManager.create( overlay_name );
}

//Create a text
Ogre::TextAreaOverlayElement* UI::createText(std::string text_name, std::string text, std::string font_name, float size, float position_x, float position_y, float height, float width, std::string bottom_color, std::string top_color) {
    // Create a text area
    Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", text_name));
    textArea->setMetricsMode(Ogre::GMM_PIXELS);
    textArea->setPosition(position_x,position_y);
    textArea->setDimensions(height,widht);
    textArea->setCaption(text);
    textArea->setCharHeight(size); 
    textArea->setFontName(font_name);
    if(bottom_color.tolower() == "black"){
        textArea->setColourBottom(Ogre::ColorValue(0.0, 0.0, 0.0, 1.0));
    }
    else if(bottom_color.tolower() == "white"){
        textArea->setColourBottom(Ogre::ColorValue(1.0, 1.0, 1.0, 1.0));        
    }
    if(top_color.tolower() == "black"){
        textArea->setColourTop(Ogre::ColorValue(0.0, 0.0, 0.0, 1.0));
    }
    else if(top_color.tolower() == "white"){
        textArea->setColourTop(Ogre::ColorValue(1.0, 1.0, 1.0, 1.0));        
    }
    return textArea;
}

//Add the panel to the overlay
void UI::PanelToOverlay(Ogre::Overlay* overlay, Ogre::OverlayContainer* panel) {
    overlay->add2D( panel );
}
    
//Add text to panel
void UI::TextToPanel(Ogre::OverlayContainer* panel, Ogre::TextAreaOverlayElement text) {
    panel->addChild(text);
} 

//Show the overlay
void ShowOverlay(Ogre::Overlay* overlay){
    overlay->show();
}

//void UI::Load() {
//    // create material and texture
//    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MyImageMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//    Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().load("Skeleton.bmp", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//    material->getTechnique(0)->getPass(0)->createTextureUnitState()->setTextureName("Skeleton.bmp");
//
//    // create overlay container and element
//    //Ogre::Overlay* container = new Ogre::Overlay;
//    container = (Ogre::OverlayContainer*)(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "MyImageContainer"));//sus
//    element = Ogre::OverlayManager::getSingleton().createOverlayElement("Image", "MyImageElement");
//    element->setMaterialName("MyImageMaterial");
//    container->addChild(element);
//
//    // set position and size of overlay container and element
//    container->setPosition(100, 100);
//    container->setDimensions(200, 200);
//    element->setPosition(0, 0);
//    element->setDimensions(200, 200);
//
//    // show overlay container
//    Ogre::Overlay* overlay = Ogre::OverlayManager::getSingleton().create("MyOverlay");
//    overlay->add2D(container);
//    overlay->show();
//}
//
//void UI::Update() {
//    Ogre::Camera* camera = game.GetCamera();
//    Ogre::Viewport* viewport = camera->getViewport();
//    Ogre::Real screenX = viewport->getActualWidth() * 0.5f;
//    Ogre::Real screenY = viewport->getActualHeight() * 0.5f;
//    container->setPosition(screenX - 100, screenY - 100);
//}