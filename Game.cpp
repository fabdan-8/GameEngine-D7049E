#include "Game.h"
#include <time.h>
#include <iostream>

#include <Windows.h>//DEBUG

void Game::Load() {

}

void Game::MainLoop() {//single threaded solution
	running = true;
	clock_t last_tick = clock();
	clock_t current_time;
	while (running) {
		current_time = clock();
		Render();//no fps cap.
		if (current_time >= last_tick + tick_speed) {//update once per tick_speed milliseconds
			last_tick += tick_speed;
			if (current_time > last_tick + tick_speed) {//running (more than) one whole tick behind
				//do something, you are lagging behind.
			}
			Update();
		}
		Input();//take inputs as often as possible
		//Connection(); //check internet communication, this should be done on a separate thread, but can also be done on the same thread (not optimal)
	}
}

void Game::Render() {
	//do this as fast as possible (or cap FPS similar to how Update() is capped)
}

void Game::Input() {
	if (GetAsyncKeyState(VK_TAB)) {//press tab to stop application
		running = false;
	}
}

void Game::Update() {
	std::cout << "a";//print 'a' once every tick_speed milliseconds
}

void Game::Cleanup() {
	running = false;
}