#include "Game.h"

#include <iostream>

void Game::Load() {
	// I construct my object that will allow me to initialise Ogre easily.
	//OgreEasy::SimpleOgreInit lOgreInit;

	//if (!lOgreInit.initOgre())
	//{
	//	std::cout << "Impossible to init Ogre correctly." << std::endl;
	//	return;
	//}

	

	// STEP 1/ First, we will need to create the Ogre::Root object.
			// It is an object that must be created to use ogre correctly, and delete once we are finished using Ogre.

			// This is the name of an optionnal textual configuration file for the rendersystem.
			// I won't use it.
	Ogre::String lConfigFileName = "";
	// This is the name of an optionnal textual configuration file, which lists the available plugins.
	// I won't use it.
	Ogre::String lPluginsFileName = "";
	// This is the name of the log file. A log file is a file in which you can write things during the program execution.
	// Ogre use it to display general informations about the rendersystem.
	// You are not obliged to generate one, and ogre can even transmit the log data to you own class if you want.
	// Here we only ask the root to create the file.
	//Ogre::String lLogFileName = "ogre.log";
	Ogre::String lLogFileName = "";
	std::getline(std::cin, name);
	// I create the root and I wrap it in an auto_ptr so that it will be automatically released.
	// Now I can even do "throw std::bad_alloc("bad alloc");", the program will release the root smoothly.
	mRoot = new Ogre::Root(lConfigFileName, lPluginsFileName, lLogFileName);
	std::getline(std::cin, name);
	// STEP 2/ Then we need to load plugins. It means that there are functions that are stored inside dynamic libraries.
	// These libraries are .dll or .so files. Most projects Ogre Project do not need all functions to be usable.
	// That way, only a subset of all function can be loaded. It also means you can create your own plugins if you want.
	// If you want to know more on the subject, you 'll need to dig into a C++ tutorial.
	// Anyway, for our use, we will need to load at least a 'RenderSystem' plugin, which means something to drive opengl or directx.
	// The basic plugins you are the most likely to use are the RenderSystems, the particle FX and the Cgprogram.
	////{
	//	// Ogre uses Ogre::String (which is a typedef) to represent strings.
	//	// Here I use a typedef. If you don't know what it means, you should learn C++ basics first.
	//	// Same if you don't know what std::vector is.
	//	typedef std::vector<Ogre::String> Strings;
	//	// Here I list all the plugins I want to load.
	//	// I let those I don't want to use in comments.
	//	// Opengl rendersystem is supposed to work everywhere.
	//	// But in reality a rendersystem may fail on your computer. 
	//	// It is likely do to bad/old graphic card driver/installation,
	//	// or too old directx version on windows (try update).
	//	// Often, when one rendersystem fail, the other at least kind-a-work.
	//	// I put them in a std::vector, because then I can factorise operations and calls (do a 'for').
	//	Strings lPluginNames;
	//	//lPluginNames.push_back("RenderSystem_GL");//<-- was uncommented
	//	//lPluginNames.push_back("RenderSystem_Direct3D9");
	//	//lPluginNames.push_back("Plugin_ParticleFX");//<-- was uncommented
	//	//lPluginNames.push_back("Plugin_CgProgramManager");//<-- was uncommented
	//	//lPluginNames.push_back("Plugin_PCZSceneManager");
	//	//lPluginNames.push_back("Plugin_OctreeZone");
	//	lPluginNames.push_back("Plugin_OctreeSceneManager");
	//	//lPluginNames.push_back("Plugin_BSPSceneManager");

	//	{
	//		Strings::iterator lIter = lPluginNames.begin();
	//		Strings::iterator lIterEnd = lPluginNames.end();
	//		for (; lIter != lIterEnd; lIter++)
	//		{
	//			Ogre::String& lPluginName = (*lIter);
	//			bool lIsInDebugMode = OGRE_DEBUG_MODE;
	//			if (lIsInDebugMode)
	//			{
	//				lPluginName.append("_d");
	//			}
	//			mRoot->loadPlugin(lPluginName);
	//		}
	//	}
	////}
	//std::getline(std::cin, name);
	// STEP 3/ Then, we can select from the loaded plugins the unique RenderSystem we want to use.
	{
		// the root provide a method if you want to select 
		// the rendersystem and its options visually (lRoot->showConfigDialog()).
		// in that case, you don't need to set the render system manually

		const Ogre::RenderSystemList& lRenderSystemList = mRoot->getAvailableRenderers();
		if (lRenderSystemList.size() == 0)
		{
			std::cout << "Sorry, no rendersystem was found.\n";
			return;
		}

		Ogre::RenderSystem* lRenderSystem = lRenderSystemList.at(0);
		mRoot->setRenderSystem(lRenderSystem);
	}
	std::getline(std::cin, name);
	// STEP 4/ When the RenderSystem is selected, we can initialise the Root. The root can be initialised only when a rendersystem has been selected.
	{
		// I can create a window automatically, but I won't do it.
		bool lCreateAWindowAutomatically = false;
		// name of the automatically generated window. empty for me.
		Ogre::String lWindowTitle = "";
		// custom capabilities of the rendersystem. It's a feature for advanced use.
		Ogre::String lCustomCapacities = "";
		mRoot->initialise(lCreateAWindowAutomatically, lWindowTitle, lCustomCapacities);
	}
	std::getline(std::cin, name);
	// STEP 5/ Then we can ask to the RenderSystem to create a window.
	{
		Ogre::String lWindowTitle = "Hello Ogre World";
		unsigned int lSizeX = 800;
		unsigned int lSizeY = 600;
		//I don't want to use fullscreen during development.
		bool lFullscreen = false;
		// This is just an example of parameters that we can put. Check the API for more details.
		Ogre::NameValuePairList lParams;
		// fullscreen antialiasing. (check wikipedia if needed).
		lParams["FSAA"] = "0";
		// vertical synchronisation will prevent some image-tearing, but also
		// will provide smooth framerate in windowed mode.(check wikipedia if needed).
		lParams["vsync"] = "true";
		mWindow = mRoot->createRenderWindow(lWindowTitle, lSizeX, lSizeY, lFullscreen, &lParams);
	}
	std::getline(std::cin, name);
	//I prefer to be able to access my variables directly.
	lRoot = mRoot;
	lWindow = mWindow;

	// I create a scenemanager. This is like a 'Scene', in which I can put lights, 3d objects, etc...
	// The scenemanager contains an arborescent graph of 'SceneNodes'. To manage elements of the scene,
	// I will create SceneNodes in the SceneManager, and attach the elements to the scenenodes.
	// First parameter : I select a kind of SceneManager. This may have a huge impact on performance.
	// Depending on your scene, some are better than other. The default one does no optimization at all.
	// Second parameter : I give a name to the scenemanager.
	// Note : It is easy to have more than one scenemanager (If you got 2 different scenes for example).
	Ogre::SceneManager* lScene = lRoot->createSceneManager(1, "scenemanager");

	// The 'root SceneNode' is the only scenenode at the beginning in the SceneManager.
	// The SceneNodes can be seen as 'transformation' containers <=> it contains scale/position/rotation
	// of the objects. There is only 1 root scenenode, and all other scenenode are 
	// its direct or indirect children.
	Ogre::SceneNode* lRootSceneNode = lScene->getRootSceneNode();

	// I create a camera. It represent a 'point of view' in the scene.
	Ogre::Camera* lCamera = lScene->createCamera("MyFirstCamera");

	// I attach the camera to a new SceneNode. It will be easier then to move it in the scene.
	Ogre::SceneNode* lCameraNode = lRootSceneNode->createChildSceneNode("MyFirstCameraNode");
	lCameraNode->attachObject(lCamera);
	std::getline(std::cin, name);
	// We create a viewport on a part of the window.
	// A viewport is the link between 1 camera and 1 drawing surface (here the window).
	// I can then call 'update();' on it to make it draw the Scene from the camera.
	// You can have several viewports on 1 window.
	// Check API for details on parameters.
	float lViewportWidth = 0.88f;
	float lViewportHeight = 0.88f;
	float lViewportLeft = (1.0f - lViewportWidth) * 0.5f;
	float lViewportTop = (1.0f - lViewportHeight) * 0.5f;
	unsigned short lMainViewportZOrder = 100;
	Ogre::Viewport* vp = lWindow->addViewport(lCamera, lMainViewportZOrder, lViewportLeft, lViewportTop, lViewportWidth, lViewportHeight);

	// I want the viewport to draw the scene automatically
	// when I will call lWindow->update();
	vp->setAutoUpdated(true);

	// I choose a color for this viewport. 
	// I prefer to have a bright color, to detect holes in geometry etc...
	vp->setBackgroundColour(Ogre::ColourValue(1, 0, 1));

	// I choose the visual ratio of the camera. To make it looks real, I want it the same as the viewport.
	float ratio = float(vp->getActualWidth()) / float(vp->getActualHeight());
	lCamera->setAspectRatio(ratio);

	// I choose the clipping far& near planes. if far/near>2000, you can get z buffer problem.
	// eg : far/near = 10000/5 = 2000 . it's ok.
	// If (far/near)>2000 then you will likely get 'z fighting' issues.
	lCamera->setNearClipDistance(1.5f);
	lCamera->setFarClipDistance(3000.0f);

	// I want my window to be active
	lWindow->setActive(true);

	// I want to update myself the content of the window, not automatically.
	lWindow->setAutoUpdated(false);

	// cleaning of windows events managed by Ogre::WindowEventUtilities::...
	// I call it after a 'pause in window updating', in order to maintain smoothness.
	// Explanation : if you clicked 2000 times when the windows was being created, there are 
	// at least 2000 messages created by the OS to listen to. This is made to clean them.
	lRoot->clearEventTimes();

	return;
}

void Game::MainLoop() {
	// I wait until the window is closed.
	// The "message pump" thing is something you will see in most GUI application.
	// It allow the binding of messages between the application and the OS.
	// These messages are most of the time : keystroke, mouse moved, ... or window closed.
	// If I don't do this, the message are never caught, and the window won't close.
	while (!mWindow->isClosed())
	{
		// Drawings
		// the window update its content.
		// each viewport that is 'autoupdated' will be redrawn now,
		// in order given by its z-order.
		lWindow->update(false);

		// The drawn surface is then shown on the screen
		// (google "double buffering" if you want more details).
		// I always use vertical synchro.
		bool lVerticalSynchro = true;
		lWindow->swapBuffers(/*lVerticalSynchro*/);

		// This update some internal counters and listeners.
		// Each render surface (window/rtt/mrt) that is 'auto-updated' has got its 'update' function called.
		lRoot->renderOneFrame();

		Ogre::WindowEventUtilities::messagePump();
	}
}

void Game::Cleanup() {
	delete mRoot;
}