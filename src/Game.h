#pragma once
#include "Defines.h"

#include "Ogre.h"
#include "OgreApplicationContext.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_net.h>

#include "Scene.h"

class Game {
public:
	Game() {};
	~Game() {};

	void Load();
	void MainLoop();
	void Cleanup();

	bool Clicked(unsigned char key);
	bool Pressed(unsigned char key);
	bool Released(unsigned char key);
	bool MouseClicked(unsigned char button);
	bool MousePressed(unsigned char button);
	bool MouseReleased(unsigned char button);

	Ogre::SceneManager* scnMgr = nullptr;

private:
	void Render();
	void Input();
	void Update();

	void CheckEvents();

	bool running = false;

	SDL_Event mainevent;
	Mix_Music* music;
	bool music_playing = false;
	Scene scene;//let's start with only one scene

	OgreBites::ApplicationContext* ctx = nullptr;
	Ogre::Camera* cam = nullptr;
	Ogre::SceneNode* camNode = nullptr;

	int mouseY;
	int mouseX;
	double rot = 0.0;

	unsigned char keybuffer[256] = { 0 };//0b00000000 is the binary representation. The last byte is "clicked", the second to last is "pressed", the third to last is "released"
	unsigned char mousebuffer[256] = { 0 };
};

