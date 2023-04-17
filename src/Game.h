#pragma once

#include "Ogre.h"
#include "OgreRoot.h"
#include "OgreRenderWindow.h"
#include "OgreWindowEventUtilities.h"

class Game {
public:
	std::string name;
	void Load();
	void MainLoop();
	void Cleanup();
	// I put the member in public because there is no need to put them private in these tutorials.
		// It will allow very simple access to these useful members.
		///\brief the root of ogre will be contained in this member.
		/// it will be initialised in initOgre().
	Ogre::Root* mRoot;
	///\brief the window created in the initOgre(). NULL otherwise.
	/// This is just a handle, not a real aggregation. 
	/// The destruction of the Root will imply its destruction.
	Ogre::RenderWindow* mWindow;

	//I prefer to be able to access my variables directly.
	Ogre::Root* lRoot;
	Ogre::RenderWindow* lWindow;
};

