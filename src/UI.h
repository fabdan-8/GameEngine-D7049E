#pragma once

#include "OgreOverlayManager.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreColourValue.h"
#include <string>

class UI { 

    //Create a panel
    Ogre::OverlayContainer* createPanel(std::string panel_name, float position_x, float position_y, float height, float width, std::string material_name);

    //Create a text
    Ogre::TextAreaOverlayElement* createText(std::string text_name, std::string text, std::string font_name, float size, float position_x, float position_y, float height, float width, std::string bottom_color, std::string top_color);

    //Create an overlay
    Ogre::Overlay* createOverlay(std::string overlay_name);

    //Add the panel to the overlay
    void PanelToOverlay(Ogre::Overlay* overlay, Ogre::OverlayContainer* panel);

    //Add text to panel
    void TextToPanel(Ogre::OverlayContainer* panel, Ogre::TextAreaOverlayElement text);

    // Show the overlay
    void ShowOverlay(Ogre::Overlay* overlay);

};
