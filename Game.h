#pragma once
#include "Defines.h"

class Game {
public:
	Game() {//constructor

	};
	void Load();
	void MainLoop();
	void Cleanup();
	~Game() {//destructor - calls cleanup
		Cleanup();
	}
private:
	bool running = false;
	void Render();
	void Input();
	void Update();
};

