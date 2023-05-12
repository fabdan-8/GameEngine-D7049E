#pragma once

#include <OgreOverlayManager.h>

class UI { 

    ////Create a panel
    //Ogre::OverlayContainer* UI::createPanel(std::string panel_name, float position_x, float position_y, float height, float width, std::string material_name) { 
    //    Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
    //    Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", panel_name ) );
    //    panel->setPosition( position_x, position_y);
    //    panel->setDimensions( height, width );
    //    panel->setMaterialName( material_name );
    //    return panel;
    //}

    ////Create an overlay
    //Ogre::Overlay* UI::createOverlay(std::string overlay_name) {
    //    return overlayManager.create( overlay_name );
    //}

    ////Create a text
    //Ogre::TextAreaOverlayElement* UI::createText() {
    //    return static_cast<Ogre::TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", "TextView"));
    //}

    ////Add the panel to the overlay
    //void UI::PanelToOverlay(Ogre::Overlay* overlay, Ogre::OverlayContainer* panel) {
    //    overlay->add2D( panel );
    //}
    //

    ////Add text to panel
    //void UI::TextToPanel(Ogre::OverlayContainer* panel, Ogre::TextAreaOverlayElement text) {
    //    panel->addChild(text);
    //}    

    //// Show the overlay
    ////overlay->show();

};
