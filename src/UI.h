#pragma once

#include "OgreOverlayContainer.h"
#include "OgreOverlayElement.h"

class UI {
public:
	void Load();
	void Update();
private:
	Ogre::OverlayContainer* container = nullptr;
	Ogre::OverlayElement* element = nullptr;
};
