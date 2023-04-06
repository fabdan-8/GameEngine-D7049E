#include "Global.h"
//put all includes in Global.h instead of here, all global variables are available without doing extern.

int main() {
	game.Load();
	game.MainLoop();//single threaded solution
	game.Cleanup();
}